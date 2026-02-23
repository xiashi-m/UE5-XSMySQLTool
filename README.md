# UE5-XSMySQLTool

# XSMySQLTool（UE 插件)


> **项目定位**：为 Unreal Engine 提供一个可在 **蓝图/CPP** 中直接使用的 **MySQL C API** 封装插件。
**核心目标**：把 MySQL 连接、SQL 执行、结果集解析、常用 SQL 生成（SELECT/INSERT/UPDATE/DDL/事务/函数/存储过程等）抽象成 UE 风格的对象与数据结构，降低业务侧写 SQL/处理结果的成本。

---

## 1. 项目结构总览（文件与职责）

项目主要由 3 层组成：

### A. Blueprint 层（对外 API 入口）

- **`XSMySQLLibrary.h / .cpp`**

  - `UXSMySQLLibrary : UBlueprintFunctionLibrary`

  - 提供大量 `UFUNCTION(BlueprintCallable)` 静态接口，用于蓝图直接调用。

  - 典型接口：

    - 创建连接对象：`CreateMysqlObject(...)`

    - 执行查询与取结果：`QueryLinkResult(...)`

    - 参数化拼 SELECT：`GetSelectTableData(...)` / `GetSelectTableDataSQL(...)`

    - DDL/CRUD/事务/元数据/常用函数/日期函数等

- **`XSMySQLObject.h / .cpp`**

  - `UXSMySQLObject : UObject`

  - 持有 `TSharedPtr<FXSMysqlLink>`，把 “连接生命周期” 从蓝图侧抽离出来。

  - `InitMysql(...)` 内部 `MakeShared<FXSMysqlLink>(...)` 创建真实连接对象。

---

### B. Core 层（真正的 MySQL 连接与执行）

- **`XSMySQLLink.h / .cpp`**

  - `struct FXSMysqlLink : TSharedFromThis<FXSMysqlLink>`

  - **核心类**：负责 MySQL 初始化/重连/执行 SQL/获取结果/构建常用 SQL。

  - 关键能力：

    - 自动检测连接状态：`mysql_ping(Mysql)`

    - 断线后重新 `mysql_real_connect(...)` 并 `mysql_set_character_set(Mysql, "utf8")`

    - 两种结果获取模式：

      - `STORE_RESULT`（一次性读完）：`GetStoreResult(...)`

      - `USE_RESULT`（流式读取）：`GetUseResult(...)`（适合大数据，不能随机访问”）

    - 结果集转换：`GetResult(MYSQL_RES*, TArray<FMysqlResult>&)`

---

### C. 类型/参数/工具层（SQL 生成与数据结构）

- **`XSMySQLLinkType.h / .cpp`**

  - 定义大量 `UENUM / USTRUCT`，把 SQL 参数化为 UE 可编辑结构：

    - `EMysqlVariableType`（字段类型枚举）

    - `EMysqlCharset`（字符集）

    - `EMysqlSaveEngine`（存储引擎）

    - `EClientFlags`（客户端连接 flags）

    - `EMysqlQuerySaveType`（Store/Use）

    - `EMysqlComparisonOperator`、`EMysqlLogicalOperators`（WHERE 条件表达）

    - `FMysqlQueryParameters`（SELECT 拼装参数）

    - `FMysqlFieldType`（建表字段定义，`ToString()` 输出字段 SQL）

    - `FMysqlResult`（结果：`TMap<FString, FString> Rows`）

    - `FMysqlDebugResult`（是否打印到屏幕/日志）

    - `FMysqlAssignment / FMysqlWhereCondition`（WHERE 子句）

    - `FMysqlJoinParameters / FMysqlQueryOrderBy` 等

- **`XSMySQLPF.h / .cpp`**（PracticalFunction）

  - 一组 SQL 拼装工具函数：

    - `ComparisonOperatorToString(...)`

    - `ConditionToString(...)`

    - `FieldTypeArrayToString(...)`

    - `SpawnValue(...)`、`SpawnKeyAndValue(...)`

    - `IsMysqlFunction(...)`：插入时判断值是不是 MySQL 函数/表达式，从而决定要不要自动加引号
（例如 `NOW()`、`UUID()`、`COUNT(...)`、`@var`、包含 `+ - * /` 的表达式会被识别为“函数/表达式”直接拼入 SQL）

- **`XSMySQLMacro.h`**

  - `MysqlFuntionParam`：统一大量函数接口的参数列表，减少重复（Results/ErrMesg/SaveType/Debug）

---

## 2. 编译与依赖（Build.cs 完全基于项目）

**`XSMySQLTool.Build.cs`** 明确了第三方库与 DLL：

- 静态链接库：

  - `libmysql.lib`

- 延迟加载 DLL：

  - `libmysql.dll`

  - `libcrypto-3-x64.dll`

  - `libssl-3-x64.dll`

- 运行时依赖：

  - 同上 3 个 DLL 都通过 `RuntimeDependencies.Add(...)` 带入

包含路径：

- `ThirdParty/XSMySQLToolLibrary/.../include`

模块依赖：

- `Core`, `Projects`, `CoreUObject`, `Engine`, `XSMySQLToolLibrary`

> 说明：从 Build.cs 可以看出这是一个 **Windows x64 Release** 目录结构的三方库接入方式，并且显式带上 OpenSSL 相关 DLL（crypto/ssl）。

---

## 3. 核心设计

### 3.1 连接对象为何做成 `UXSMySQLObject + FXSMysqlLink` 两层

- 蓝图侧不能直接管理 `MYSQL*` 这种 C 结构指针生命周期；

- 因此用 `UXSMySQLObject` 承载一个 `TSharedPtr<FXSMysqlLink>`：

  - UE 对象系统管理 `UXSMySQLObject` 生命周期；

  - C++ SharedPtr 管理 `FXSMysqlLink` 生命周期；

- 业务侧只需要持有 `UXSMySQLObject*`，避免蓝图误用导致崩溃。

### 3.2 自动重连机制（项目代码里真实存在）

在 `FXSMysqlLink::QueryLink(...)` 中：

- 先 `mysql_ping(Mysql)` 检测连接；

- 若失败：

  - `mysql_close(Mysql)`

  - `Mysql = mysql_init(nullptr)`

  - `mysql_real_connect(...)` 重新连接

  - `mysql_set_character_set(Mysql, "utf8")`

- 最后执行 SQL：先 `mysql_query(...)`，失败再试 `mysql_real_query(...)`

这套逻辑解决了常见的：

- 游戏运行中 DB 连接被服务器踢掉/网络瞬断

- 业务层不想在每次 Query 前手动检测连接

### 3.3 两种结果集读取模式（大数据场景）

- `EMysqlQuerySaveType::STORE_RESULT`：一次性 `store`（便于随机访问/数据量不大）

- `EMysqlQuerySaveType::USE_RESULT`：流式 `use`（代码注释明确“适合大数据，不能随机访问”）

业务侧可以通过同一套 API 切换读取策略。

---

## 4. 数据模型与结果结构（对业务方“足够 UE 化”）

### 4.1 查询结果：`FMysqlResult`

```C++
USTRUCT(BlueprintType)
struct FMysqlResult
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, FString> Rows;
};
```


- 每一行是一个 `FMysqlResult`

- 行内用 `TMap<列名, 值字符串>` 表示
优点：蓝图里访问简单；缺点：所有值都字符串化（类型转换需业务侧处理/或扩展）

### 4.2 SELECT 参数化：`FMysqlQueryParameters`

包含：

- 表名/别名：`TableName`, `TableNameAsName`

- 字段列表：`TArray<FMysqlVariableSettings> InFields`

- 去重：`bDistinct`

- JOIN：`FMysqlJoinParameters`

- WHERE：`TArray<FMysqlWhereCondition>`

- GROUP BY / HAVING / ORDER BY

- LIMIT：`FVector2D Limit`（x=第几个,y=偏移；按注释语义）

- `ToString(FString& SQL)`：负责输出完整 SELECT SQL

### 4.3 WHERE 条件结构

- `FMysqlAssignment`：A op B

- `FMysqlWhereCondition`：Assignment + LogicalOperators（AND/OR/NOT 等）

- `XSMySQLPF::ConditionToString(...)` 负责拼接为 WHERE 子句

---

## 5. 功能清单（从代码接口汇总）

下面这些都在 `FXSMysqlLink` 与 `UXSMySQLLibrary` 中有对应函数（非口嗨，都是项目真实接口）：

### 5.1 基础查询

- `QueryLink(SQL, ErrMsg)`

- `QueryLinkResult(SQL, Results, ErrMsg, SaveType, Debug)`

- 参数化 SELECT：

  - `GetSelectTableData(QueryParam, Results, ErrMsg, SaveType, Debug, PrintSQL)`

  - `GetSelectTableDataSQL(SQL, QueryParam, PrintSQL)`

### 5.2 数据库操作

- `CreateDatabase(DatabaseName, Charset, ErrorMsg)`

- `DropDataBase(DatabaseName, ErrorMsg)`

- `SelectNewDB(NewDB, ErrMsg)`

- `CreateAndSelectDatabase(DataBaseName, Charset, ErrorMsg)`

### 5.3 表操作 / DDL

- `CreateTable(TableName, Fields, PrimaryKeys, Param, ErrorMsg)`

- 临时表：

  - `CreateTemporaryTable(TableName, Fields, QueryParam, ErrorMsg)`

  - `CreateTemporaryTableALikeB(A, B, ErrorMsg)`

- 表复制：

  - `CopyTableAToB(A, B, Fields, ErrorMsg)`

  - `CopyTableAToBFast(...)`（内部还有 `CopyTableAToBFastInternal(...)`）

- 清理与维护：

  - `DropTable(...)`

  - `TruncateTable(...)`

  - `DeleteFromTable(...)` / `DeleteFromTableWhereData(...)`

  - `OptimiseTable(...)`

### 5.4 更新 / 插入

- Update：

  - `UpdateTableData(TableName, Assignments, Condition, ErrorMsg)`

  - `ReplaceTableData(...)`

- Insert：

  - `InsertTableData(TableName, KeyValueMap, QueryParam, ErrorMsg, bIgnore)`

  - `SimpleInsertTableData(TableName, Values, QueryParam, ErrorMsg, bIgnore)`

  - `ReplaceIfExistence(...)`

- 插入辅助：`XSMySQLPF::SpawnValue / SpawnKeyAndValue`（支持识别 `NOW()` 等函数值不加引号）

### 5.5 事务

- `StartTransaction(ErrorMsg)`

- `SetAutoCommit(bAuto, ErrorMsg)`（SQL: `SET AUTOCOMMIT = 0/1;`）

- `Commit(ErrorMsg)`（SQL: `COMMIT;`）

- `SetSavePointName(SaveName, ErrorMsg)`（SQL: `SAVEPOINT xxx;`）

- `Rollback(SaveName, ErrorMsg)`（可 `ROLLBACK TO xxx;` 或 `ROLLBACK;`）

- `ReleaseSavePoint(SaveName, ErrorMsg)`

### 5.6 元数据与诊断

- `GetSelectVersion(...)`（内部 `SELECT VERSION()`）

- `GetSelectDatabaseName(...)`（`SELECT DATABASE()`）

- `GetSelectUser(...)`（`SELECT USER()`）

- `GetShowStatus(...)`（`SHOW STATUS;`）

- `GetShowVariables(...)`（`SHOW VARIABLES;`）

- Debug 输出控制：`FMysqlDebugResult` + `PrintResult(...)`

### 5.7 常用 MySQL 函数封装

例如：

- `Bin / Binary / Cast / Conv / Convert / IsNULL / NULLIf / Charset`

- `GetConnection_ID / GetCurrent_user / GetLast_Insert_ID / GetSession_user / GetSystem_user`
并且在 `UXSMySQLLibrary` 里还有统一入口：

- `MySQLCommonFunctions(...)`（通过 `EMySQLCommonFunctions` 分发）

### 5.8 日期时间函数封装（非常丰富）

`YearWeek / WeekOfYear / WeekDay / Year / Week / ToDays / TimeStamp / TimeDiff / TimeToSec / TimeFormat / SysDate / SubTime / SubDate / StringToDate / SecToTime / Quarter / PeriodDiff / PeriodAdd / ...`
（这些在 `FXSMysqlLink` 里是独立函数，在 `UXSMySQLLibrary` 里也暴露为蓝图接口）

### 5.9 自定义函数 / 存储过程（封装成可执行接口）

- 自定义函数：

  - `CreateFunction(...)`

  - `ExecuteFunction(...)`

  - `DropFunction(...)`

  - `ShowCreateFunction(...)`

  - `ShowFunctionsStatus(...)`

- 存储过程：

  - `DefiningVariables(...)`

  - `CreateProcedure(...)`

  - `ExecuteProcedure(...)`

  - `DropProcedure(...)`

  - `ShowCreateProcedure(...)`

  - `ShowProceduresStatus(...)`

### 5.10 ALTER（表结构变更）

- `ChangeEngine(...)`

- `DropTableField(...)`

- `AddTableField(...)`

- `ModifyTableFieldType(...)`

- `ChangeTableField(...)`

- `RenameTable(...)`

---

## 6. 快速使用示例（基于项目 API）

### 6.1 蓝图使用流程（逻辑步骤）

1. `CreateMysqlObject(WorldContext, Host, User, Password, DB, Port, ClientFlags, UnixSocket)`

2. 调用任意查询：

  - 无结果：`QueryLink(MySQLObject, SQL, ErrMsg)`

  - 有结果：`QueryLinkResult(MySQLObject, SQL, Results, ErrMsg, SaveType, Debug)`

3. 从 `Results` 遍历每行 `FMysqlResult.Rows`（列名->值）

### 6.2 参数化 SELECT（推荐面试重点：可视化拼 SQL）

- 组装 `FMysqlQueryParameters`：

  - TableName

  - InFields（可加 `*` 或指定列）

  - Condition（由 `FMysqlWhereCondition` 组成）

  - OrderBy / Limit / GroupBy / Having 等

- 调用：

  - `GetSelectTableData(MySQLObject, QueryParam, Results, ErrMsg, SaveType, Debug, PrintSQL)`

- 若只想查看 SQL：

  - `GetSelectTableDataSQL(MySQLObject, SQL, QueryParam, PrintSQL)`

---


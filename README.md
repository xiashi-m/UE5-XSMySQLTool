# UE5-XSMySQLTool

# XSMySQLTool

A plugin specifically designed to encapsulate MySQL functionality for UE5. It provides blueprint availability and UE5 C++ MySQL access capabilities, allowing for database-related operations without the need for developers to write complex SQL code manually.

专门为UE5封装 MySQL 功能的插件。它提供了蓝图可用和UE5C++的 MySQL 访问能力，无需开发者手写复杂的 SQL 代码即可实现数据库相关操作。

## Framwork 框架

--------

蓝图接口层（Library）  
→ 连接对象（Object）  
→ MySQL 执行核心（Link）  
→ SQL 辅助构建（Tool）  
→ 结构/枚举定义（Type）    
→ 底层平台依赖（Build.cs）

### 连接对象层：UXSMySQLObject

主要职责：

* 保存一个 `TSharedPtr<FXSMysqlLink>`

* 初始化连接参数

* 提供 `GetLink()` 访问 MySQL 逻辑核心

> **蓝图只持有 UObject，而实际数据库操作都委托给 FXSMysqlLink**

### 蓝图接口层：UXSMySQLLibrary

此类是插件的**蓝图可见 API 大集合**，整个插件的使用入口。

它的特点是：

#### ■ 完全静态（BlueprintCallable）

#### ■ 输入为 UXSMySQLObject

#### ■ 只是“跳板函数”，内部全部转发给 FXSMysqlLink

### 插件核心层：FXSMysqlLink

这是插件的 **真正核心**，包含了所有功能的实现。

#### ** A. MySQL 连接与底层交互**

* 封装 `mysql_real_connect`

* 查询执行 `mysql_real_query`

* 获取结果集 `mysql_store_result`

* 预处理语句（Prepare + Bind + Execute）

#### **B. SQL 操作逻辑**

内部提供大量 MySQL 高级封装，涵盖：

##### ✔ DDL（表结构）

* CreateTable

* DropTable

* ModifyField

* ChangeEngine

##### ✔ DML（数据）

* InsertTableData

* UpdateTableData

* DeleteFromTable

##### ✔ SELECT 查询（带条件、排序、分页等）

基于 `FXSMysqlQueryParameters`

#### **C. 事务处理**

* StartTransaction

* Commit

* Rollback

* SavePoint

#### **D. 自定义函数 / 存储过程**

允许 UE 生成 MySQL 函数与过程：

`CreateFunction() ExecuteFunction() DropFunction()`

#### **MySQL 内置函数（日期 / 字符串）**

如：

* YEAR

* WEEKOFYEAR

* CONCAT

* FIND_IN_SET

* FORMAT

* SEC_TO_TIME

所有封装成可蓝图调用。

### **辅助模块：XSMySQLTool**

负责构建 SQL 字符串逻辑

### 类型定义模块：XSMySQLLinkType

定义了所有公开使用的结构体和枚举，例如：

#### ■ 字段类型（FMysqlFieldType）

包括：

* 类型（INT、VARCHAR、DATE…）

* 长度

* 默认值

* 是否自增

* 是否 UNSIGNED

* 注释

#### ■ 查询结果（FMysqlResult）

`TMap<FString,FString> Rows;`

#### ■ SQL 比较条件（FMysqlWhereCondition）

#### ■ SQL 查询参数（FSimpleMysqlQueryParameters）

#### ■ 连接 ClientFlags

#### ■ 存储引擎类型（InnoDB/MyISAM）

#### ■ 字符集（UTF8/GBK 等）

这是插件全部 API 的“骨架”。

## 蓝图



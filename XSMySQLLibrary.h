// Copyright (C) XisShi.2025.All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Blueprint/XSMySQLObject.h"

#include "XSMySQLLibrary.generated.h"

UCLASS()
class XSMYSQLTOOL_API UXSMySQLLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "MySQLMain"))
    static void MySQLMain();

	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "XSMySQL"))
	static UXSMySQLObject* CreateMysqlObject(
		UObject* WorldContextObject,
		const FString& InHost,
		const FString& InUser,
		const FString& InPassword,
		const FString& InDatabase,
		const int32  InPort,
		const TArray<EClientFlags>& InClientFlag,
		const FString& UnixSocket = TEXT("")
		
		);
	// 查询
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	bool QueryLink(UXSMySQLObject* MySQLObject, const FString& SQL, FString& ErrMesg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool QueryLinkResult(UXSMySQLObject* MySQLObject, const FString& SQL, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool GetSelectTableData(UXSMySQLObject* MySQLObject, const FMysqlQueryParameters& QueryParam, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug, const bool PrintSQL = true);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool GetSelectTableDataSQL(UXSMySQLObject* MySQLObject, FString& SQL, const FMysqlQueryParameters& QueryParam, const bool PrintSQL = true);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool GetSelectTableDataStoreResult(UXSMySQLObject* MySQLObject, const FMysqlQueryParameters& QueryParam, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool GetSelectTableDataUseResult(UXSMySQLObject* MySQLObject, const FMysqlQueryParameters& QueryParam, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// ---------------------------------------------------------------------------
	
	// 数据库操作
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CreateDatabase(UXSMySQLObject* MySQLObject, const FString& DatabaseName, EMysqlCharset Charset, FString& ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DropDataBase(UXSMySQLObject* MySQLObject, const FString& DatabaseName, FString& ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool SelectNewDB(UXSMySQLObject* MySQLObject, const FString& NewDB, FString& ErrMesg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CreateAndSelectDataBase(UXSMySQLObject* MySQLObject, const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	// ---------------------------------------------------------------------------

	// 表操作
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CreateTable(UXSMySQLObject* MySQLObject, const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TArray<FString>& InPrimaryKeys, const FMysqlCreateTableParam& Param, FString& ErrorMsg);
 
	// 创建临时表
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CreateTempTable(UXSMySQLObject* MySQLObject, const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ShowTables(UXSMySQLObject* MySQLObject, const FString &TableName, EMysqlQuerySaveType SaveType, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug = FMysqlDebugResult());
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	bool CreateTableALikeB(UXSMySQLObject* MySQLObject, const FString &A, const FString &B, FString &ErrorMsg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	bool CreateTemporaryTableALikeB(UXSMySQLObject* MySQLObject, const FString &A, const FString &B, FString &ErrorMsg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CopyTableAToB(UXSMySQLObject *MySQLObject, const FString &A, const FString &B, const TArray<FString> &Fields, FString &ErrorMsg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CopyTableAToTemporaryB(UXSMySQLObject *MySQLObject, const FString &TableA, const FString &TemporaryTableB, const TArray<FString> &Fields, FString &ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CopyTableAToBFast(UXSMySQLObject *MySQLObject, const FString &CopySourceTable, const TMap<FString, FMysqlFieldType> &InsertFields, const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CopyTableAToTemporaryBFast(UXSMySQLObject *MySQLObject, const FString &CopySourceTable, const TMap<FString, FMysqlFieldType> &InsertFields, const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);

	// 元数据
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|NULL"))
	static bool GetSelectVersion(UXSMySQLObject *MySQLObject, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static bool GetSelectDatabaseName(UXSMySQLObject *MySQLObject, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static bool GetSelectUser(UXSMySQLObject *MySQLObject, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static bool GetShowStatus(UXSMySQLObject *MySQLObject, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static bool GetShowVariables(UXSMySQLObject *MySQLObject, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT);
	
	
	//将表彻底删除 释放内存 不支持回滚 Innodb 和 MyISAM 全部清除
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DropTable(UXSMySQLObject* MySQLObject, const FString& TableName, FString& ErrorMsg);

	//清除表数据但保留结构 不支持回滚 Innodb 和 MyISAM 全部清除
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool TruncateTable(UXSMySQLObject* MySQLObject, const FString& TableName, FString& ErrorMsg);

	// 逐行删除数据（保留表结构）可 回滚
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DeleteFromTable(UXSMySQLObject* MySQLObject, const FString& TableName, FString& ErrorMsg);

	// 整理表空间 / 重建索引
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool OptimiseTable(UXSMySQLObject* MySQLObject, const FString& TableName, FString& ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DeleteFromTableWhereData(UXSMySQLObject* MySQLObject, const FString& TableName, const TArray<FMysqlWhereCondition>& Condition, FString& ErrorMsg);
	// ---------------------------------------------------------------------------

	// 更新
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool UpdateTableData(UXSMySQLObject* MySQLObject, const FString& TableName, const TArray<FMysqlAssignment>& InFields, const TArray<FMysqlWhereCondition>& Condition, FString& ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ReplaceTableData(UXSMySQLObject* MySQLObject, const FString& TableName, const TArray<FMysqlReplaceParameters>& InReplaces, const TArray<FMysqlWhereCondition>& Condition, FString& ErrorMsg);
	// ---------------------------------------------------------------------------

	// 插入
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool InsertTableData(UXSMySQLObject* MySQLObject, const FString& TableName, const TMap<FString, FString>& InsetKeyValueDatas, const FMysqlQueryParameters& QueryParam, FString& ErrorMsg, bool bIgnore = false);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool SimpleInsertTableData(UXSMySQLObject* MySQLObject, const FString& TableName, const TArray<FString>& InsetValueDatas, const FMysqlQueryParameters& QueryParam, FString& ErrorMsg, bool bIgnore = false);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ReplaceIfExistence(UXSMySQLObject* MySQLObject, const FString& TableName, const TMap<FString, FString>& InsetKeyValueDatas, FString& ErrorMsg);
	// ---------------------------------------------------------------------------
	
	
	// 事务操作
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool StartTransaction(UXSMySQLObject *MySQLObject, FString &ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool SetAutoCommit(UXSMySQLObject *MySQLObject, bool bAuto, FString &ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool Commit(UXSMySQLObject *MySQLObject, FString &ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool SetSavePointName(UXSMySQLObject *MySQLObject, const FString &SaveName, FString &ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool Rollback(UXSMySQLObject *MySQLObject, const FString &SaveName, FString &ErrorMsg);

    UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
    static bool ReleaseSavePoint(UXSMySQLObject* MySQLObject, const FString& SaveName, FString& ErrorMsg);
    // ---------------------------------------------------------------------------

    // 常用函數
    UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
    static bool MySQLCommonFunctions(UXSMySQLObject* MySQLObject, TArray<FMysqlResult>& Results, FString& ErrMesg, 
    	const EMySQLCommonFunctions Function = EMySQLCommonFunctions::BIN, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult(),
    	const int64 BinValue = 0, const FString &Value = TEXT(""), int64 ConvF1 = 0, int64 ConvF2 = 0, EMysqlVariableType CastVariableType = EMysqlVariableType::MYSQL_INT, EMysqlCharset ConvertCharset = EMysqlCharset::None,
    	const FString &BinocularOperationExpression = TEXT(""), const FString& BinocularOperationValueA = TEXT(""), const FString& BinocularOperationValueB = TEXT(""),
    	const FString& IsNULLExpression = TEXT(""), const FString& NULLIfValueA = TEXT(""), const FString& NULLIfValueB = TEXT(""), const FString& CharsetExpression = TEXT(""));
	// ---------------------------------------------------------------------------
	
	// 日期时间
	// SELECT YEARWEEK('2020-01-15'); 返回 年+周，例如 201724
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool YearWeek(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT WEEKOFYEAR('2020-01-15'); 返回该日期在一年中是第几周（0~53）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool WeekOfYear(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT WEEKDAY('2020-01-15'); 返回该日期是星期几（0~6）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool WeekDay(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT YEAR('2023-11-20') As Result; 检索并返回给定日期或日期时间表达式的年份
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Year(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT WEEK('2022-11-20') As Result; 返回一个数值，范围从 0 到 53 或 1 到 53
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Week(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT TO_DAYS('0001-01-01 01:01:01'); 返回自公元 0000-01-01 以来的天数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool ToDays(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT TIMESTAMP('2017-07-23', '13:10:11'); 合并日期与时间，或日期加时间区间
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool TimeStamp(UXSMySQLObject *MySQLObject, const FString &InExpression, const FString& InInterval, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT TIMEDIFF('13:10:11', '12:00:00'); -- 01:10:11 两个时间的差值
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool TimeDiff(UXSMySQLObject *MySQLObject, const FString &InTimeA, const FString& InTimeB, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT TIME_TO_SEC('1:12:00'); 将时间转换为总秒数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool TimeToSec(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT TIME_FORMAT('11:11:11', '%r'); 格式化时间字符串
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool TimeFormat(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& InFormat, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT TIME('19:30:10'); -- 19:30:10 提取时间部分
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Time(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT SYSDATE(); -- 2025-06-19 20:59:41 返回当前系统时间（即时取值）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool SysDate(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT SUBTIME('2011-11-11 11:11:11', 5); -- 2011-11-11 11:11:06 时间减去秒数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool SubTime(UXSMySQLObject *MySQLObject, const FString &InTime, int64 InSecond, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT SUBDATE('2011-11-11 11:11:11', 1); -- 2011-11-10 11:11:11 日期减去天数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool SubDate(UXSMySQLObject *MySQLObject, const FString &InDate, int64 InDay, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT STR_TO_DATE('August 10 2017', '%M %d %Y'); -- 2017-08-10 按指定格式把字符串转换为日期
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool StringToDate(UXSMySQLObject *MySQLObject, const FString &InString, const FString& InFormat, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT SEC_TO_TIME(4320); -- 01:12:00 秒数转换为时间
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool SecToTime(UXSMySQLObject *MySQLObject, int64 InSeconds, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT SECOND('1:2:3'); -- 3 返回时间中的秒
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Second(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT QUARTER('2011-11-11 11:11:11'); -- 4 返回季度（1–4）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Quarter(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT PERIOD_DIFF(201710, 201703); -- 7 比较两个“年月”差异（按月）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool PeriodDiff(UXSMySQLObject *MySQLObject, const int64 InPeriodA, const int64 InPeriodB, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT PERIOD_ADD(201703, 5); -- 201708 年月周期加月份
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool PeriodAdd(UXSMySQLObject *MySQLObject, const int64 InPeriod, const int64 InMonth, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT NOW(); -- 2020-09-19 20:57:41 当前日期+时间（语句中固定）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Now(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT MINUTE('1:2:3'); -- 2 返回分钟部分
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Minute(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT MICROSECOND('2020-06-20 09:34:00.000023'); -- 23 返回微秒部分
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool MicroSecond(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT MAKETIME(11, 35, 4); -- 11:35:04 组合时间（hour, minute, second）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool MakeTime(UXSMySQLObject *MySQLObject, const FString &InData, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT MAKEDATE(2020, 3); -- 2020-01-03 根据“年份 + 年内天数”构造日期
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool MakeDate(UXSMySQLObject *MySQLObject, const int64 InYear, const int64 InDayOfYear, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT LOCALTIMESTAMP(); -- 2018-09-19 20:57:43 返回本地时间戳
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool LocalTimeStamp(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT LOCALTIME(); -- 2018-09-19 20:57:43 返回当前本地日期时间
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool LocalTime(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT LAST_DAY('2020-06-20'); -- 2020-06-30 返回该日期所在月份的最后一天
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool LastDay(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT HOUR('1:2:3'); -- 1 返回小时
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Hour(UXSMySQLObject *MySQLObject, const FString &InTime, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT FROM_DAYS(1111); -- 0003-01-16 从“自公元 0 年起的天数”转换回日期
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool FromDays(UXSMySQLObject *MySQLObject, const int64 InDays, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT EXTRACT(MINUTE FROM '2011-11-11 11:11:11'); -- 11 从日期中提取指定部分
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Extract(UXSMySQLObject *MySQLObject, const FString &InData, const EMysqlDateType DateType, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DAYOFYEAR('2011-11-11 11:11:11'); -- 315 返回日期在一年中的第几天
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DayOfYear(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DAYOFWEEK('2011-11-11 11:11:11'); -- 6 返回日期是星期几，星期天为 1
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DayOfWeek(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DAYOFMONTH('2011-11-11 11:11:11'); -- 11 返回月中的日
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DayOfMonth(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DAYNAME('2011-11-11 11:11:11'); -- 星期六 获取星期几
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DayName(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DAY('2017-06-15'); -- 15 返回日期部分的日（同 DAY() 函数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Day(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DATE_SUB('2011-11-11 11:11:11', INTERVAL 2 DAY); -- 2011-11-09 11:11:11 日期－指定时间区间（默认天）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DateSub(UXSMySQLObject *MySQLObject, const FString &InDate, const int64 InInterval, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DATE_FORMAT('2011-11-11 11:11:11','%Y-%m-%d %r'); -- 2011-11-11 11:11:11 AM 格式化日期
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DateFormat(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& InFormat, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT ADDDATE('2011-11-11 11:11:11', 1); -- 2011-11-12 11:11:11 日期 + 天数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool AddDate(UXSMySQLObject *MySQLObject, const FString &InDate, const int64 InInterval, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DATEDIFF('2001-01-01','2001-02-02'); -- 31 日期差
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool DateDiff(UXSMySQLObject *MySQLObject, const FString &InDate1, const FString &InDate2, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT DATE('2011-11-11 11:11:11'); -- 2011-11-11 获取日期部分
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool Date(UXSMySQLObject *MySQLObject, const FString &InDate, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT CURDATE(); -- 2025-6-8 获取当前日期
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool CurTime(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT CURRENT_TIME(); -- 19:59:02 获取当前时间
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool CurrentTime(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT CURRENT_TIMESTAMP(); -- 2025-6-8 19:59:02 获取当前时间戳
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool CurrentTimestamp(UXSMySQLObject *MySQLObject, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	// SELECT ADDTIME('2011-11-11 11:11:11', 5); -- 2011-11-11 11:16:16 时间 + 秒数
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Date"))
	static bool AddTime(UXSMySQLObject *MySQLObject, const FString &InDate, const int64 InSecond, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	// ---------------------------------------------------------------------------
	
	// 数字函数
	// SELECT ABS(225) As Result; -- 225 绝对值
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Number"))
	static bool Abs(UXSMySQLObject *MySQLObject, const int64 InNumber, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	// ---------------------------------------------------------------------------
	
	// 字符串函数
	// SELECT ASCII(str); 返回字符串 str 最左侧字符的 ASCII 码（十进制整数）
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "XSMySQL|Str"))
	static bool Ascii(UXSMySQLObject *MySQLObject, const FString& InString, const FString& AsName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	// ---------------------------------------------------------------------------
	
	// 自定义函数
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CreateFunction(UXSMySQLObject *MySQLObject, const FString &InFunctionName, const TMap<FString, FMysqlFieldType> &InParameter, const FString &InFunctionBody, FString& ErrMesg, EMysqlVariableType InReturnsType = EMysqlVariableType::MYSQL_INT, const FString &InComment = TEXT(""));
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ExecuteFunction(UXSMySQLObject *MySQLObject, const FString &InFunctionName, const TArray<FString> &InParameter, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DropFunction(UXSMySQLObject *MySQLObject, const FString &InFunctionName, FString& ErrMesg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ShowCreateFunction(UXSMySQLObject *MySQLObject, const FString &InFunctionName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ShowFunctionsStatus(UXSMySQLObject *MySQLObject, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	// ---------------------------------------------------------------------------
	
	// 自定义存储过程
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DefiningVariables(UXSMySQLObject *MySQLObject, const FString &InVariablesName, const FString &InValue, FString &ErrMesg);

	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool CreateProcedure(UXSMySQLObject *MySQLObject, const FString &InProcedureName, const TArray<FString>& InOut, const TMap<FString, FMysqlFieldType> &InParameter, const FString &InProcedureBody, FString& ErrMesg, const FString &InComment = TEXT(""));
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ExecuteProcedure(UXSMySQLObject *MySQLObject, const FString &InProcedureName, const TArray<FString> &InParameter, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DropProcedure(UXSMySQLObject *MySQLObject, const FString &InProcedureName, FString& ErrMesg);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ShowCreateProcedure(UXSMySQLObject *MySQLObject, const FString &InProcedureName, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ShowProceduresStatus(UXSMySQLObject *MySQLObject, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);
	// ---------------------------------------------------------------------------
	
	// ALTER
	// 修改表的存储引擎
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ChangeEngine(UXSMySQLObject *MySQLObject, const FString &InTableName, EMysqlSaveEngine InEngine, FString& ErrorMsg);
	
	// 删除字段
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool DropTableField(UXSMySQLObject *MySQLObject, const FString &InTableName, const TArray<FString> &InFieldsName,FString& ErrorMsg);
	
	// 新增字段
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool AddTableField(UXSMySQLObject *MySQLObject, const FString &InTableName, const TMap<FString, FMysqlFieldType> &InFields, FString& ErrorMsg);
	
	// 修改字段类型
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ModifyTableFieldType(UXSMySQLObject *MySQLObject, const FString &InTableName, const TMap<FString, FMysqlFieldType> &InFields, FString& ErrorMsg);
	
	// 修改字段名 + 类型
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool ChangeTableField(UXSMySQLObject *MySQLObject, const FString &InTableName, const TArray<FMysqlModifyField> &InChangeFields, FString& ErrorMsg);
	
	// 重命名表
	UFUNCTION(BlueprintCallable, meta = (Category = "XSMySQL"))
	static bool RenameTable(UXSMySQLObject *MySQLObject, const FString &InOldTableName,const FString &InNewTableName, FString &ErrorMsg);
	// ---------------------------------------------------------------------------
};

// Copyright (C) XisShi.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "mysql.h"
#include "Core/XSMySQLLinkType.h"
#include "Core/XSMySQLMacro.h"


struct XSMYSQLTOOL_API FXSMysqlLink : public TSharedFromThis<FXSMysqlLink>
{
	FXSMysqlLink(
		const FString& InHost,
		const FString& InUser,
		const FString& InPassword,
		const FString& InDatabase,
		const uint32  InPort,
		const FString& UnixSocket = TEXT(""),
		const TArray<EClientFlags>& InClientFlag = TArray<EClientFlags>());

    ~FXSMysqlLink();

public:
	// 查询连接
	bool QueryLink(const FString& SQL, FString& ErrMesg);

	bool QueryLinkResult(const FString& SQL, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType, const FMysqlDebugResult& Debug);

	bool GetSelectTableData(const FMysqlQueryParameters& QueryParam, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult(), const bool PrintSQL = true);

	bool GetSelectTableDataSQL(FString& SQL, const FMysqlQueryParameters& QueryParam, const bool PrintSQL = true);

	bool GetSelectTableDataStoreResult(const FMysqlQueryParameters& QueryParam, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());

	bool GetSelectTableDataUseResult(const FMysqlQueryParameters& QueryParam, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	

	// ----------------------------------------
	
	// 数据库操作
	bool CreateDatabase(const FString& DatabaseName, EMysqlCharset Charset, FString& ErrorMsg);

	bool DropDataBase(const FString& DatabaseName, FString& ErrorMsg);

	bool SelectNewDB(const FString &NewDB, FString &ErrMesg);

	bool CreateAndSelectDatabase(const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	// ----------------------------------------

	
	
	
	
	// 表操作
	bool CreateTable(const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TArray<FString>& InPrimaryKeys, const FMysqlCreateTableParam& Param, FString& ErrorMsg);

	// 临时表
	bool CreateTemporaryTable(const FString &TableName, const TMap<FString, FMysqlFieldType> &InFields, const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);

	bool ShowTables(const FString &TableName, EMysqlQuerySaveType SaveType, TArray<FMysqlResult> &Results, FString &ErrMesg, const FMysqlDebugResult &Debug = FMysqlDebugResult());
	
	bool CreateTableALikeB(const FString &A, const FString &B, FString &ErrorMsg);
	bool CreateTemporaryTableALikeB(const FString &A, const FString &B, FString &ErrorMsg);
	
	// 如果没有B创建B
	bool CopyTableAToB(const FString &A, const FString &B,const TArray<FString> &Fields, FString &ErrorMsg);
	bool CopyTableAToTemporaryB(const FString &TableA, const FString &TemporaryTableB, const TArray<FString> &Fields, FString &ErrorMsg);
	
	bool CopyTableAToBFast(const FString &CopySourceTable, const TMap<FString,FMysqlFieldType> &InsertFields ,const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);
	bool CopyTableAToTemporaryBFast(const FString &CopySourceTable,const TMap<FString, FMysqlFieldType> &InsertFields, const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);
	
	//将表彻底删除 释放内存 不支持回滚 Innodb 和 MyISAM 全部清除
	bool DropTable(const FString& TableName, FString& ErrorMsg);

	//清除表数据但保留结构 不支持回滚 Innodb 和 MyISAM 全部清除
	bool TruncateTable(const FString& TableName, FString& ErrorMsg);

	// 逐行删除数据（保留表结构）可 回滚
	bool DeleteFromTable(const FString& TableName, FString& ErrorMsg);

	// 整理表空间 / 重建索引
	bool OptimiseTable(const FString& TableName, FString& ErrorMsg);

	// 删除表数据where条件
	bool DeleteFromTableWhereData(const FString& TableName, const TArray<FMysqlWhereCondition>& Condition, FString& ErrorMsg);
	// ----------------------------------------
	
	// 更新
	bool UpdateTableData(const FString& TableName, const TArray<FMysqlAssignment>& InFields, const TArray<FMysqlWhereCondition>& Condition, FString& ErrorMsg);

	bool ReplaceTableData(const FString& TableName, const TArray<FMysqlReplaceParameters>& InReplaces, const TArray<FMysqlWhereCondition>& Condition, FString& ErrorMsg);
	// ----------------------------------------
	
	// 插入
	bool InsertTableData(const FString& TableName, const TMap<FString, FString>& InsetKeyValueDatas, const FMysqlQueryParameters& QueryParam, FString& ErrorMsg, bool bIgnore = false);
	
	bool SimpleInsertTableData(const FString& TableName, const TArray<FString>& InsetValueDatas, const FMysqlQueryParameters& QueryParam, FString& ErrorMsg, bool bIgnore = false);
	
	bool ReplaceIfExistence(const FString& TableName, const TMap<FString, FString>& InsetKeyValueDatas, FString& ErrorMsg);
	// --------------------------------------
	
	// 事务操作
	bool StartTransaction(FString &ErrorMsg);
	
	bool SetAutoCommit(bool bAuto, FString &ErrorMsg);
	
	bool Commit(FString &ErrorMsg);
	
	bool SetSavePointName(const FString &SaveName, FString &ErrorMsg);
	
	bool ReleaseSavePoint(const FString &SaveName, FString &ErrorMsg);
	
	bool Rollback(const FString &SaveName, FString &ErrorMsg);
	//----------------------------------------

	// 元数据
	bool GetSelectVersion(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool GetSelectDatabaseName(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool GetSelectUser(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool GetShowStatus(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool GetShowVariables(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// --------------------------------------

	// 常用函数
	// SELECT BIN(Value); 返回整数的 二进制字符串表示
	bool Bin(const int64 Value, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT BINARY 'abc'; 将字符串转为 BINARY 字符串（区分大小写）
	bool Binary(const FString &Value, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT CAST(Value AS INT); 把 Value 转换为指定 MySQL 数据类型
	bool Cast(const FString& Value, EMysqlVariableType VariableType,  TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT CONV(Value, F1, F2); 执行 进制转换
	bool Conv(const FString& Value, int64 F1, int64 F2, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT CONVERT('abc' USING utf8); 将字符串转换到指定 字符集
	bool Convert(const FString& InString, EMysqlCharset Charset, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT 5 + 7; 执行一个二元表达式
	bool BinocularOperation(const FString &Expression, const FString& ValueA, const FString& ValueB, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT ISNULL(Expression); 测试表达式是否为 NULL
	bool IsNULL(const FString& Expression, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT NULLIF(ValueA, ValueB); 如果两个值相等，则返回 NULL，否则返回 ValueA
	bool NULLIf(const FString& ValueA, const FString& ValueB, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT CHARSET(InExpression); 返回字符串的字符集
	bool Charset(const FString& InExpression, TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT CONNECTION_ID(); 返回当前连接的MySQL ID
	bool GetConnection_ID(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT CURRENT_USER(); 获取当前用户
	bool GetCurrent_user(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT LAST_INSERT_ID(); 获取最后插入的行ID
	bool GetLast_Insert_ID(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT SESSION_USER(); 获取当前会话的用户
	bool GetSession_user(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// SELECT SYSTEM_USER(); 获取当前会话的系统用户
	bool GetSystem_user(TArray<FMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	// --------------------------------------
	
	// 日期操作
	bool YearWeek(const FString &InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool WeekOfYear(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool WeekDay(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Year(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Week(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool ToDays(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool TimeStamp(const FString& InExpression, const FString& InInterval, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool TimeDiff(const FString& InTime1, const FString& InTime2, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool TimeToSec(const FString& InTime, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool TimeFormat(const FString& InTime,const FString& InFormat, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Time(const FString& InExpression, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool SysDate(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool SubTime(const FString& InTime,int64 InSecond,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool SubDate(const FString& InDate,int64 InDay,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool StringToDate(const FString& InString, const FString& InFormatMask,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool SecToTime(const int64 InSecond,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Second(const FString &InTime,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Quarter(const FString &InDate,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool PeriodDiff(const int64 Period1,const int64 Period2,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool PeriodAdd(const int64 InPeriod, const int64 InMonths, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Now(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Minute(const FString &InTime,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool MicroSecond(const FString &InDate,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool MakeTime(const FString &InDate,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool MakeDate(const int32 InYear,const int64 DayOfYear,MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool LocalTimeStamp(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool LocalTime(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool LastDay(const FString &InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Hour(const FString &InTime, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool FromDays(const int64 InDay, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Extract(const FString &InDate,const EMysqlDateType DateType, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool DayOfYear(const FString &InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool DayOfWeek(const FString &InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool DayOfMonth(const FString &InDate, MysqlFuntionParam , const FString& AsName= TEXT(""));
	bool DayName(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Day(const FString& InDate, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool DateSub(const FString& InDate,const int64 InInterval, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool DateFormat(const FString& InDate, const FString& InFormat, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool AddDate(const FString& InDate, const int64 InInterval, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool DateDiff(const FString& InD1, const FString& InD2, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool Date(const FString& InExpression, MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool CurTime(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool CurrentTime(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool CurrentTimeStamp(MysqlFuntionParam, const FString& AsName = TEXT(""));
	bool AddTime(const FString& InDate,const int64 InSecond, MysqlFuntionParam, const FString& AsName = TEXT(""));
	// -------------------------------------- 
	
	// 数字函数
	bool Abs(const int64 InNumber, MysqlFuntionParam, const FString& AsName = TEXT(""));
	// -------------------------------------- 
	
	// 字符串函数
	bool Ascii(const FString& InString, MysqlFuntionParam, const FString& AsName = TEXT(""));
	// -------------------------------------- 

	// 自定义函数
	bool CreateFunction(const FString &InFunctionName,const TMap<FString,FMysqlFieldType> &InParameter,const FString &InFunctionBody, FString& ErrMesg,EMysqlVariableType InReturnsType = EMysqlVariableType::MYSQL_INT,const FString &InComment = TEXT(""));
	bool ExecuteFunction(const FString &InFunctionName,const TArray<FString> &InParameter,MysqlFuntionParam);
	bool DropFunction(const FString &InFunctionName, FString& ErrMesg);
	bool ShowCreateFunction(const FString &InFunctionName, MysqlFuntionParam);
	bool ShowFunctionsStatus(MysqlFuntionParam);
	// -------------------------------------- 
	
	// 自定义存储过程
	bool DefiningVariables(const FString &InVariablesName,const FString &InValue,FString &ErrMesg);
	bool CreateProcedure(const FString &InProcedureName, const TArray<FString>& InOut, const TMap<FString, FMysqlFieldType> &InParameter, const FString &InProcedureBody, FString& ErrMesg, const FString &InComment = TEXT(""));
	bool ExecuteProcedure(const FString &InProcedureName, const TArray<FString> &InParameter, MysqlFuntionParam);
	bool DropProcedure(const FString &InProcedureName, FString& ErrMesg);
	bool ShowCreateProcedure(const FString &InProcedureName, MysqlFuntionParam);
	bool ShowProceduresStatus(MysqlFuntionParam);
	// -------------------------------------- 
	
	// ALTER
	bool ChangeEngine(const FString &InTableName, EMysqlSaveEngine InEngine, FString& ErrorMsg);
	bool DropTableField(const FString &InTableName, const TArray<FString> &InFieldsName,FString& ErrorMsg);
	bool AddTableField(const FString &InTableName, const TMap<FString, FMysqlFieldType> &InFields, FString& ErrorMsg);
	bool ModifyTableFieldType(const FString &InTableName, const TMap<FString, FMysqlFieldType> &InFields, FString& ErrorMsg);
	bool ChangeTableField(const FString &InTableName, const TArray<FMysqlModifyField> &InChangeFields, FString& ErrorMsg);
	bool RenameTable(const FString &InOldTableName,const FString &InNewTableName, FString &ErrorMsg);
	// --------------------------------------
protected:
	uint32 ToMySqlClientFlag(EClientFlags ClientFlags) const;

	// 打印结果
	bool PrintTOScreenOrLog(const FString& InString, bool bPrintToScreen, bool bPrintToLog, FColor InColor, float InDuration);

	bool PrintResult(const TArray<FMysqlResult>& Results, bool bPrintToScreen = true, bool bPrintToLog = true);

	// 结果集操作
	// 把 MySQL C API 返回的结果集（MYSQL_RES）转换为 UE 可读取的 TArray<FSimpleMysqlResult>
	void GetResult(struct MYSQL_RES* RES, TArray<FMysqlResult>& Results);

	bool GetStoreResult(TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool GetSelectTableDataByFuntion(const FString& SQL, EMysqlQuerySaveType SaveType, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	bool GetSelectTableDataByFuntionAsName(const FString& SQL, EMysqlQuerySaveType SaveType, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult(), const FString& AsName = TEXT(""));

	// 流式读取，适合大数据，不能随机访问
	bool GetUseResult(TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());

	bool QueryLinkStoreResult(const FString& SQL, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool QueryLinkUseResult(const FString& SQL, TArray<FMysqlResult>& Results, FString& ErrMesg, const FMysqlDebugResult& Debug = FMysqlDebugResult());
	
	bool CopyTableAToBFastInternal(FString &SQL,const FString &CopySourceTable, const FString &CopyTargetTable, const TMap<FString, FMysqlFieldType> &InsertFields, const FMysqlQueryParameters &QueryParam, FString &ErrorMsg);


private:
	const FString Host;
	const FString User;
	const FString Password;
	FString Database;
	const uint32  Port;
	const FString UnixSocket;
	uint32  ClientFlag;

    MYSQL* Mysql;

};
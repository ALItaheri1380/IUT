CREATE OR ALTER PROCEDURE usp_InsertFactDaily
    @InputDate DATE
AS
BEGIN

    DECLARE @start1 datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE Library_DW.[FinancialDataMart].[today];
    TRUNCATE TABLE Library_DW.[FinancialDataMart].[newData];
    TRUNCATE TABLE Library_DW.[FinancialDataMart].[newData2];
    TRUNCATE TABLE Library_DW.[FinancialDataMart].[result];
    TRUNCATE TABLE Library_DW.[FinancialDataMart].[scd_result];
    ---------------------------
    DECLARE @end1 datetime = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('today', 'truncate', @start1, @end1),
    ('newData', 'truncate', @start1, @end1),
    ('newData2', 'truncate', @start1, @end1),
    ('result', 'truncate', @start1, @end1),
    ('scd_result', 'truncate', @start1, @end1);

	DECLARE @TimeID INT = (SELECT FullDate FROM dimTime WHERE FullDateAlternateKey = @InputDate);

	SET @start1 = GETDATE();
    ---------------------------
	INSERT INTO Library_DW.[FinancialDataMart].[today]
    SELECT ta.[Branch_ID], @TimeID, ta.[Account_ID], 
        CASE WHEN ta.[Amount] > 0 THEN ta.[Amount] ELSE 0 END AS Income, 
        CASE WHEN ta.[Amount] < 0 THEN abs(ta.[Amount]) ELSE 0 END AS Expenses
    FROM [Library_SA].[dbo].[Transaction] AS ta 
    WHERE ta.TransactionDate >= @InputDate AND ta.TransactionDate < DATEADD(DAY, 1, @InputDate)
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('today', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO Library_DW.[FinancialDataMart].[newData]
    SELECT t.[BranchID], t.[TimeID], t.[AccountID],
        SUM(t.[Income]), 
        SUM(t.[Expenses]), 
        MAX(t.[Expenses]), 
        MIN(t.[Expenses]), 
        MAX(t.[Income]), 
        MIN(t.[Income])
    FROM Library_DW.[FinancialDataMart].[today] AS t
    GROUP BY t.[BranchID], t.[TimeID], t.[AccountID];
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('newData', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
	with a as(
        SELECT 
		    DISTINCT(b.ID) as BranchID,
		    a.ID as AccountID
	    FROM [Library_DW].[dbo].[dimAccount] a
	    CROSS JOIN [Library_DW].[dbo].[dimBranch] b
    )
    INSERT INTO Library_DW.[FinancialDataMart].[newData2]
    SELECT a.BranchID, 
        @TimeID, 
        a.[AccountID], 0,
        ISNULL(nd2.[TotalDailyIncome], 0), ISNULL(nd2.[TotalDailyExpenses], 0), 
        ISNULL(nd2.[MaxDailyExpenses], 0), ISNULL(nd2.[MinDailyExpenses], 0),
        ISNULL(nd2.[MaxDailyIncome], 0), ISNULL(nd2.[MinDailyIncome], 0),
        0, 0
    FROM a left join [Library_DW].[FinancialDataMart].[newData] as nd2 ON(a.[AccountID] = nd2.AccountID and a.BranchID = nd2.BranchID)
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('newData2', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO Library_DW.[FinancialDataMart].[result]
    SELECT t1.[BranchID], t1.[TimeID], t1.[AccountID], t1.yesterday_Balance + ISNULL(t1.[TotalDailyIncome], 0) - ISNULL(t1.[TotalDailyExpenses], 0),
        t1.[TotalDailyIncome] as TotalDailyIncome, t1.[TotalDailyExpenses] as TotalDailyExpenses, 
        t1.[MaxDailyExpenses], t1.[MinDailyExpenses],
        t1.[MaxDailyIncome], t1.[MinDailyIncome], 
        CASE WHEN t1.[MaxDailyIncome] > 0 THEN 0 ELSE 1 END as DaysWithoutIncome,
		CASE WHEN t1.[MaxDailyExpenses] > 0 THEN 0 ELSE 1 END as DaysWithoutExpenses
    FROM Library_DW.[FinancialDataMart].[newData2] AS t1 
    LEFT OUTER JOIN Library_DW.[FinancialDataMart].[newData] AS t2 
        ON t1.BranchID = t2.BranchID AND t1.AccountID = t2.AccountID
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('result', 'insert', @start1, @end1);
    
    SET @start1 = GETDATE();
    ---------------------------
	INSERT INTO Library_DW.[FinancialDataMart].[scd_result]
	SELECT b.[sur_key_ID], r.TimeID, r.AccountID, r.BranchID, r.Balance, 
			r.TotalDailyIncome, r.TotalDailyExpenses, r.MaxDailyExpenses,
			r.MinDailyExpenses, r.MaxDailyIncome, r.MinDailyIncome,
			r.DaysWithoutIncome, r.DaysWithoutExpenses
	FROM Library_DW.[FinancialDataMart].[result] as r JOIN [Library_DW].[dbo].[dimTime] as t ON(t.[FullDate] = r.TimeID)
		JOIN [Library_DW].[dbo].[dimBranch] as b ON(b.[ID] = r.BranchID )
	WHERE 	(b.[End_Date] IS NULL AND b.[Start_Date] <= t.[FullDateAlternateKey]) or
					 b.[End_Date] IS NOT NULL AND b.[End_Date] > t.[FullDateAlternateKey] AND b.[Start_Date] <= t.[FullDateAlternateKey]
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('scd_result', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO Library_DW.[FinancialDataMart].FinancialDailyFact (
        BranchID, TimeID, AccountID, BranchSourceID, Balance, TotalDailyIncome, TotalDailyExpenses,
        MaxDailyExpenses, MinDailyExpenses, MaxDailyIncome, MinDailyIncome, DaysWithoutIncome, DaysWithoutExpenses
    )
    SELECT 
        BranchID, TimeID, AccountID, BranchSourceID, Balance, TotalDailyIncome, TotalDailyExpenses,
        MaxDailyExpenses, MinDailyExpenses, MaxDailyIncome, MinDailyIncome, DaysWithoutIncome, DaysWithoutExpenses
    FROM Library_DW.[FinancialDataMart].[scd_result];
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('FinancialDailyFact', 'insert', @start1, @end1);

END;
GO

DECLARE @Today DATE = (select min(t.[TransactionDate]) from [Library_SA].[dbo].[Transaction] as t);
EXEC usp_InsertFactDaily @InputDate = @Today;

select* from [FinancialDataMart].FinancialDailyFact

CREATE OR ALTER PROCEDURE InsertFactDailyCurrent_Finantial
    @StartDate DATE,
    @EndDate DATE
AS
BEGIN
    
	DECLARE @TimeID INT;

    WHILE @StartDate <= @EndDate
    BEGIN
		
        set @TimeID  = (SELECT FullDate FROM dimTime WHERE FullDateAlternateKey = @StartDate)
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

		SET @TimeID = (SELECT FullDate FROM dimTime WHERE FullDateAlternateKey = @StartDate);

        SET @start1 = GETDATE();
        ---------------------------
        INSERT INTO Library_DW.[FinancialDataMart].[today]
        SELECT ta.[Branch_ID], @TimeID, ta.[Account_ID], 
            CASE WHEN ta.[Amount] > 0 THEN ta.[Amount] ELSE 0 END AS Income, 
            CASE WHEN ta.[Amount] < 0 THEN abs(ta.[Amount]) ELSE 0 END AS Expenses
        FROM [Library_SA].[dbo].[Transaction] AS ta 
        WHERE ta.TransactionDate >= @StartDate AND ta.TransactionDate < DATEADD(DAY, 1, @StartDate)
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
                BranchSourceID,
                AccountID,
                Balance,
				[DaysWithoutIncome],
				[DaysWithoutExpenses]
            FROM [Library_DW].[FinancialDataMart].[FinancialDailyFact] as fd JOIN [Library_DW].[dbo].[dimTime] as t
					on(fd.TimeID = t.[FullDate])
			Where t.[FullDateAlternateKey] = DATEADD(DAY, -1, @StartDate)
        )
        INSERT INTO Library_DW.[FinancialDataMart].[newData2]
        SELECT a.BranchSourceID, 
            @TimeID, 
            a.[AccountID],
            a.Balance,
            ISNULL(nd2.[TotalDailyIncome], 0), ISNULL(nd2.[TotalDailyExpenses], 0), 
            ISNULL(nd2.[MaxDailyExpenses], 0), ISNULL(nd2.[MinDailyExpenses], 0),
            ISNULL(nd2.[MaxDailyIncome], 0), ISNULL(nd2.[MinDailyIncome], 0),
			a.[DaysWithoutIncome],
			a.[DaysWithoutExpenses]
        FROM a left join [Library_DW].[FinancialDataMart].[newData] as nd2 ON(a.[AccountID] = nd2.AccountID and a.BranchSourceID = nd2.BranchID)
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
            CASE WHEN t2.[MaxDailyIncome] > 0 THEN 0 ELSE t1.yesterday_DaysWithoutIncome+1 END as DaysWithoutIncome,
            CASE WHEN t2.[MaxDailyExpenses] > 0 THEN 0 ELSE t1.yesterday_DaysWithoutExpenses+1 END as DaysWithoutExpenses
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
		JOIN [Library_DW].[dbo].[dimBranch] as b ON(b.[ID] = r.BranchID) 
        WHERE
			(b.[End_Date] IS NULL AND b.[Start_Date] <= t.[FullDateAlternateKey]) or
			(b.[End_Date] IS NOT NULL AND b.[End_Date] > t.[FullDateAlternateKey] AND b.[Start_Date] <= t.[FullDateAlternateKey])
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

        SET @StartDate = DATEADD(day, 1, @StartDate);
    END;

END;
GO

-- DECLARE @Start DATE = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM Library_DW.[FinancialDataMart].FinancialDailyFact AS bb) AS VARCHAR), 120));DECLARE @End DATE = (SELECT MAX(TransactionDate) FROM [Library_SA].[dbo].[Transaction]);
-- EXEC InsertFactDailyCurrent_Finantial @StartDate = @Start, @EndDate = @End;
-- select* FROM Library_DW.[FinancialDataMart].FinancialDailyFactorder by timeID, BranchID, AccountID
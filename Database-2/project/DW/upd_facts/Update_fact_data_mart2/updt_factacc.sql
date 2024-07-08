CREATE OR ALTER PROCEDURE SP_UpdateFactAcc
AS
BEGIN
    DECLARE @start1 datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE [FinancialDataMart].FinancialAccFact;
    ---------------------------
    DECLARE @end1 datetime = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('FinancialAccFact', 'truncate', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [FinancialDataMart].FinancialAccFact (BranchID, AccountID, MaxExpenses, MinExpenses, MaxIncome, 
                                    MinIncome, TotalIncome, TotalExpenses, DaysWithoutIncome, DaysWithoutExpenses)
    SELECT BranchSourceID,
        AccountID,
        MAX(MaxDailyExpenses) AS MaxExpenses,
        MIN(MinDailyExpenses) AS MinExpenses,
        MAX(MaxDailyIncome) AS MaxIncome,
        MIN(MinDailyIncome) AS MinIncome,
        SUM(TotalDailyIncome) AS TotalIncome,
        SUM(TotalDailyExpenses) AS TotalExpenses,
		   (SELECT TOP 1 [DaysWithoutIncome]
                FROM [FinancialDataMart].[FinancialDailyFact] fd
                WHERE fd.[BranchSourceID] = f.[BranchSourceID] AND
                      fd.AccountID = f.AccountID
                ORDER BY TimeID DESC) AS DaysWithoutIncome,
			(SELECT TOP 1 [DaysWithoutExpenses]
                FROM [FinancialDataMart].[FinancialDailyFact] fd
                WHERE fd.[BranchSourceID] = f.[BranchSourceID] AND
                      fd.AccountID = f.AccountID
                ORDER BY TimeID DESC) AS DaysWithoutExpenses
    FROM [FinancialDataMart].[FinancialDailyFact] f
    GROUP BY BranchSourceID, AccountID;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('FinancialAccFact', 'insert', @start1, @end1);
END;
GO

-- EXEC SP_UpdateFactAcc;
-- GO
-- select * from [FinancialDataMart].FinancialAccFact



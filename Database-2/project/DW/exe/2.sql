CREATE OR ALTER PROCEDURE UpdateDW2
AS
BEGIN
    EXEC UpdateDimAccount;

    DECLARE @Start DATE = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM [FinancialDataMart].[FinancialDailyFact] AS bb) AS VARCHAR), 120));
    DECLARE @End DATE = (SELECT MAX(TransactionDate) FROM [Library_SA].[dbo].[Transaction]);
    EXEC InsertFactDailyCurrent_Finantial @StartDate = @Start, @EndDate = @End;

    SET @Start = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM [FinancialDataMart].[FinancialTransactionFact] AS bb) AS VARCHAR), 120));
    SET @End = (SELECT MAX(TransactionDate) FROM [Library_SA].[dbo].[Transaction]);
    EXEC UpdateFinancialTransactionFact @StartDate = @Start, @EndDate = @End;

    EXEC SP_UpdateFactAcc;
END
GO
EXEC UpdateDW2

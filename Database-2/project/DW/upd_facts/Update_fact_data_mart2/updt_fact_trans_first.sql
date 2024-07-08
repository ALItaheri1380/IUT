CREATE OR ALTER PROCEDURE UpdateFinancialTransactionFact
@InputDate DATE
AS
BEGIN

    DECLARE @start1 datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE [FinancialDataMart].TempTransactions;
    TRUNCATE TABLE [FinancialDataMart].Temp2Transactions;
    ---------------------------
    DECLARE @end1 datetime = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('TempTransactions', 'truncate', @start1, @end1),
    ('Temp2Transactions', 'truncate', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [FinancialDataMart].TempTransactions 
	SELECT 
        t.ID,
        t.TransactionDate, 
        t.TransactionType, 
        t.Amount, 
        db.ID, 
        t.Account_ID, 
        t.PaymentMethod_ID, 
        t.Description
    FROM 
        [Library_SA].dbo.[Transaction] t
    INNER JOIN 
        [dimBranch] db ON db.ID = t.Branch_ID
    WHERE 
        t.TransactionDate >= @InputDate
        AND t.TransactionDate < DATEADD(day, 1, @InputDate)
        AND (
            (db.[End_Date] IS NULL AND db.[Start_Date] <= t.TransactionDate) 
            OR (db.[End_Date] IS NOT NULL AND db.[End_Date] > t.TransactionDate AND db.[Start_Date] <= t.TransactionDate)
            );
         ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('TempTransactions', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [FinancialDataMart].Temp2Transactions
    SELECT 
        t1.ID, 
        CAST(t1.TransactionDate AS DATE) AS TransactionDate, 
        t1.TransactionType, 
        t1.Amount, 
        CASE WHEN t1.Amount > 0 THEN t1.Amount ELSE 0 END AS Income,
        CASE WHEN t1.Amount < 0 THEN ABS(t1.Amount) ELSE 0 END AS Expenses,
        t1.BrancID,
        t1.Account_ID, 
        t1.PaymentMethod_ID, 
        t1.Description, 
        SUM(t2.Amount) AS Balance
    FROM 
        [FinancialDataMart].TempTransactions t1
    INNER JOIN 
        [FinancialDataMart].TempTransactions t2 ON t1.ID = t2.ID 
        AND t1.TransactionDate >= t2.TransactionDate
    GROUP BY 
        t1.ID, 
        t1.TransactionDate, 
        t1.TransactionType, 
        t1.Amount,
        t1.BrancID,
        t1.Account_ID, 
        t1.PaymentMethod_ID, 
        t1.Description
    ORDER BY 
        t1.ID;
    ---------------------------
    set @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('Temp2Transactions', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [FinancialDataMart].FinancialTransactionFact
	SELECT 
		dch.sur_key_ID, 
		dt.FullDate,        
		t.Account_ID, 
		dch.ID,       
		t.Income, 
		t.Expenses,        
		t.Balance + ac.Balance AS BalanceAfterTransaction 
	FROM 
		[FinancialDataMart].Temp2Transactions t    
	JOIN 
		Library_SA.dbo.Account ac ON t.Account_ID = ac.ID    
	JOIN 
		dimTime dt ON dt.FullDateAlternateKey = t.TransactionDate    
	JOIN 
		dimBranch dch ON dch.ID = t.BrancID
	WHERE 
		(dch.[End_Date] IS NULL AND dch.[Start_Date] <= t.TransactionDate) 
		OR (dch.[End_Date] IS NOT NULL AND dch.[End_Date] > t.TransactionDate AND dch.[Start_Date] <= t.TransactionDate) 

        ---------------------------
        set @end1 = GETDATE();
        insert into [FinancialDataMart].log_dm2
        values('FinancialTransactionFact', 'insert', @start1, @end1);

    SELECT * FROM [FinancialDataMart].FinancialTransactionFact;
END;
Go
DECLARE @MinBorrowDate DATE = (SELECT MIN(bb.[BorrowDate]) FROM [Library_SA].[dbo].[BorrowedBooks] bb);
EXEC UpdateFinancialTransactionFact @MinBorrowDate;
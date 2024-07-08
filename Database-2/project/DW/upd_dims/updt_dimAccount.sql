Go
CREATE OR ALTER PROCEDURE UpdateDimAccount
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM dimAccountTemp) AND EXISTS (SELECT 1 FROM dimAccount)
	BEGIN
		PRINT 'The procedure terminated because dimAccount is empty and dimAccountTemp is not empty.'
		RETURN;
	END
	TRUNCATE TABLE dimAccountTemp

    DECLARE @start1 datetime = GETDATE();
    ---------------------------
    INSERT INTO dimAccountTemp
    SELECT * FROM dimAccount;
    ---------------------------
    DECLARE @end1 datetime = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('dimAccountTemp', 'insert', @start1, @end1);

    TRUNCATE TABLE dimAccount;

    SELECT 
        ISNULL(src.ID, dim.ID) AS ID,
        ISNULL(src.OpenDate, dim.OpenDate) AS OpenDate,
        ISNULL(src.CloseDate, dim.CloseDate) AS CloseDate,
        ISNULL(src.Balance, dim.Balance) AS Balance,
        ISNULL(src.Currency, dim.Currency) AS Currency,
        ISNULL(src.Name, dim.Name) AS Name,
        CASE 
            WHEN dim.ID IS NOT NULL AND src.ID IS NOT NULL AND dim.Current_Phone != src.phone THEN dim.Current_Phone 
            ELSE dim.Original_phone 
        END AS Original_phone,
        ISNULL(src.phone, dim.Current_Phone) AS Current_Phone,
        CASE 
            WHEN dim.ID IS NOT NULL AND src.ID IS NOT NULL AND dim.Current_Phone != src.phone THEN GETDATE()
            ELSE dim.Effective_Date
        END AS Effective_Date,
        ISNULL(src.address, dim.address) AS address
    INTO #MergedData
    FROM dimAccountTemp AS dim
    FULL OUTER JOIN (
        SELECT 
            a.ID,
            a.OpenDate,
            a.CloseDate,
            a.Balance,
            a.Currency,
            ai.Name,
            ai.phone,
            ai.address,
            GETDATE() AS Effective_Date
        FROM Library_SA.dbo.Account a
        JOIN Library_SA.dbo.Account_Info ai ON a.Account_Info_ID = ai.ID
    ) AS src
    ON dim.ID = src.ID;

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO dimAccount (
        ID, 
        OpenDate, 
        CloseDate, 
        Balance, 
        Currency, 
        Name, 
        Original_phone, 
        Current_Phone, 
        Effective_Date, 
        address
    )
    SELECT 
        ID, 
        OpenDate, 
        CloseDate, 
        Balance, 
        Currency, 
        Name, 
        Original_phone, 
        Current_Phone, 
        Effective_Date, 
        address
    FROM #MergedData;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [FinancialDataMart].log_dm2
    values('dimAccount', 'insert', @start1, @end1);

    TRUNCATE TABLE dimAccountTemp;
    TRUNCATE TABLE #MergedData;

END;
GO
--EXEC UpdateDimAccount;
--select* from dimAccount
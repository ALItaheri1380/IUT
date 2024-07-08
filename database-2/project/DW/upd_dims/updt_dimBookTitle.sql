
Go
CREATE OR ALTER PROCEDURE UpdateDimBookTitle
AS
BEGIN
    IF EXISTS (SELECT 1 FROM TempBookTitle)
       AND NOT EXISTS (SELECT 1 FROM dimBookTitle)
    BEGIN
		RAISERROR ('Dimension table (dimBook) is empty while temporary table (tempBook) is populated. Execution halted.', 16, 1)
        RETURN
    END

	DECLARE @start datetime = GETDATE()
	---------------------------
	TRUNCATE TABLE TempBookTitle
	---------------------------
	DECLARE @end datetime = GETDATE()
    insert into [LendingsDataMart].[log_dm1]
    values('TempBookTitle', 'truncate', @start, @end);

	SET @start = GETDATE();
	---------------------------
	INSERT INTO TempBookTitle(ID, Title)
	SELECT ID, Title
	FROM [Library_SA].[dbo].Book_title;
	---------------------------
	SET @end = GETDATE();
	---------------------------
    insert into [LendingsDataMart].[log_dm1]
	---------------------------
    values('TempBookTitle', 'insert', @start, @end);

	SET @start = GETDATE();
	---------------------------
	TRUNCATE TABLE dimBookTitle;
	---------------------------
	SET @end = GETDATE();
    insert into [LendingsDataMart].[log_dm1]
    values('dimBookTitle', 'truncate', @start, @end);

	SET @start = GETDATE();
	---------------------------
	INSERT INTO dimBookTitle (ID, Title)
	SELECT ID, Title
	FROM TempBookTitle
	---------------------------
	SET @end = GETDATE();
    insert into [LendingsDataMart].[log_dm1]
    values('dimBookTitle', 'insert', @start, @end);

END;
Go
-- EXECUTE UpdateDimBookTitle;
-- select* from dimBookTitle
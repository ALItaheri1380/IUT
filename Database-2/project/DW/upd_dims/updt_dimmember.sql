CREATE OR ALTER PROCEDURE updt_DimMember AS
BEGIN

    DECLARE @start datetime = GETDATE();
    --------------------------
    truncate table dimAll;
    --------------------------
    DECLARE @end datetime = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('dimAll', 'truncate', @start, @end);

    SET @start = GETDATE();
    --------------------------
    truncate table srcAll;
    --------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('srcAll', 'truncate', @start, @end);

    SET @start = GETDATE();
    --------------------------
    truncate table tmpDim;
    --------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('tmpDim', 'truncate', @start, @end);

    SET @start = GETDATE();
    --------------------------
    truncate table mergedDim;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('mergedDim', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO dimAll SELECT * FROM dimmember;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('dimAll', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO srcAll SELECT * FROM (
        SELECT
            m.ID,
            m.Fullname,
            m.NationalCode,
            m.[Address],
            m.Phone,
            m.Registration_Date,
            m.Registration_Valid_Date,
            g.Name AS Gender_Name,
            m.Gender_ID,
            b.ID AS Branch_ID,
            b.[Name] AS Branch_Name,
            b.BranchCode AS Branch_BranchCode
        FROM
            [Library_SA].[dbo].Member m
            JOIN [Library_SA].[dbo].Gender g ON m.Gender_ID = g.ID
            JOIN [Library_SA].[dbo].Branch b ON m.Branch_ID = b.ID
    ) AS src;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('srcAll', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    TRUNCATE TABLE dimmember;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('dimmember', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO tmpDim SELECT * FROM dimAll;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('tmpDim', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO mergedDim
	SELECT 
		ISNULL(src.ID, dim.ID) AS ID,
        ISNULL(src.Fullname, dim.Fullname) AS Fullname,
        ISNULL(src.NationalCode, dim.NationalCode) AS NationalCode,
        ISNULL(src.[Address], dim.[Address]) AS [Address],
        CASE
            WHEN dim.Current_Phone IS NULL THEN NULL
            WHEN src.Phone != dim.Current_Phone THEN dim.Current_Phone
            ELSE dim.Original_Phone
        END AS Original_Phone,
        ISNULL(src.Phone, dim.Current_Phone) AS Current_Phone,
        CASE
            WHEN src.Phone != dim.Current_Phone THEN GETDATE()
            ELSE dim.Effective_Date
        END AS Effective_Date,
        ISNULL(src.Registration_Date, dim.Registration_Date) AS Registration_Date,
        ISNULL(src.Registration_Valid_Date, dim.Registration_Valid_Date) AS Registration_Valid_Date,
        ISNULL(src.Gender_ID, dim.Gender_ID) AS Gender_ID,
        ISNULL(src.Gender_Name, dim.Gender_Name) AS Gender_Name,
        ISNULL(src.Branch_ID, dim.Branch_ID) AS Branch_ID,
        ISNULL(src.Branch_Name, dim.Branch_Name) AS Branch_Name,
        ISNULL(src.Branch_BranchCode, dim.Branch_BranchCode) AS Branch_BranchCode
    FROM 
        srcAll src
    FULL OUTER JOIN 
        tmpDim dim ON src.ID = dim.ID;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('mergedDim', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO dimmember (
        ID, 
        Fullname,
        NationalCode,
        [Address],
        Original_Phone,
        Current_Phone,
        Effective_Date,
        Registration_Date,
        Registration_Valid_Date,
        Gender_ID,
        Gender_Name,
        Branch_ID,
        Branch_Name,
        Branch_BranchCode
    )
    SELECT 
        ID, 
        Fullname,
        NationalCode,
        [Address],
        Original_Phone,
        Current_Phone,
        Effective_Date,
        Registration_Date,
        Registration_Valid_Date,
        Gender_ID,
        Gender_Name,
        Branch_ID,
        Branch_Name,
        Branch_BranchCode
    FROM 
        mergedDim;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('dimmember', 'insert', @start, @end);

END
Go
-- EXEC updt_DimMember;
-- SELECT * FROM dimmember;
CREATE OR ALTER PROCEDURE UpdateDimBranch
AS
BEGIN
    IF EXISTS (SELECT 1 FROM TempDimBranch) AND NOT EXISTS (SELECT 1 FROM dimBranch)
    BEGIN
        PRINT N'Warning: TempDimBranch has data and dimBranch is empty. The procedure will not be executed.';
        RETURN;
    END

    DECLARE @start datetime = GETDATE()
    ---------------------------
    TRUNCATE TABLE TempBranch;
    ---------------------------
    DECLARE @end datetime = GETDATE();
    insert into shared_log
    values('TempBranch', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    TRUNCATE TABLE TempDimBranch;
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('TempDimBranch', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO TempDimBranch (
        sur_key_ID, ID, Name, Address, Start_Date, End_Date, cur_flag, 
        BranchCode, Branch_Phone, Branch_type_ID, Branch_type_type
    )
    SELECT 
        sur_key_ID, ID, Name, Address, Start_Date, End_Date, cur_flag, 
        BranchCode, Branch_Phone, Branch_type_ID, Branch_type_type
    FROM 
        dimBranch;
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('TempDimBranch', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO TempBranch (
        ID, Name, Address, [Start_Date], [End_Date], BranchCode, Branch_Phone, Branch_type_ID, Branch_type_type
    )
    SELECT 
        B.ID, B.Name, B.Address, B.[Start_Date], B.[End_Date], B.BranchCode, B.Phone AS Branch_Phone, 
        BT.ID AS Branch_type_ID, BT.brnch_type AS Branch_type_type
    FROM 
        Library_SA.dbo.Branch B
    INNER JOIN 
        Library_SA.dbo.Branch_type BT ON B.brnch_type_id = BT.ID;
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('TempBranch', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    TRUNCATE TABLE dimBranch;
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('dimBranch', 'truncate', @start, @end);

    UPDATE D
    SET 
        D.End_Date = GETDATE(),
        D.cur_flag = 0
    FROM 
        TempDimBranch D
    INNER JOIN 
        TempBranch T ON D.ID = T.ID
    WHERE 
        D.cur_flag = 1
        AND D.Address <> T.Address;

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO TempDimBranch (
        ID, Name, Address, Start_Date, End_Date, cur_flag, BranchCode, 
        Branch_Phone, Branch_type_ID, Branch_type_type
    )
    SELECT 
        T.ID, T.Name, T.Address, GETDATE(), NULL, 1,
        T.BranchCode, T.Branch_Phone, T.Branch_type_ID, T.Branch_type_type
    FROM 
        TempBranch T
    WHERE 
        EXISTS (
            SELECT 1 
            FROM TempDimBranch D 
            WHERE D.ID = T.ID 
            AND D.cur_flag = 0
        )
        AND NOT EXISTS (
            SELECT 1
            FROM TempDimBranch D
            WHERE D.ID = T.ID
            AND D.cur_flag = 1
        );
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('TempDimBranch', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO TempDimBranch (
        ID, Name, Address, Start_Date, End_Date, cur_flag, BranchCode, 
        Branch_Phone, Branch_type_ID, Branch_type_type
    )
    SELECT 
        T.ID, T.Name, T.Address, Start_Date, End_Date, 1,
        T.BranchCode, T.Branch_Phone, T.Branch_type_ID, T.Branch_type_type
    FROM 
        TempBranch T
    WHERE 
        NOT EXISTS (
            SELECT 1 
            FROM TempDimBranch D 
            WHERE D.ID = T.ID
        );
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('TempDimBranch', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO dimBranch (
        ID, Name, Address, [Start_Date], End_Date, cur_flag, 
        BranchCode, Branch_Phone, Branch_type_ID, Branch_type_type
    )
    SELECT 
        ID, Name, Address, Start_Date, End_Date, cur_flag, 
        BranchCode, Branch_Phone, Branch_type_ID, Branch_type_type
    FROM 
        TempDimBranch;
    ---------------------------
    SET @end = GETDATE();
    insert into shared_log
    values('dimBranch', 'insert', @start, @end);

END;
GO
-- EXEC UpdateDimBranch;
-- SELECT * FROM dimBranch;
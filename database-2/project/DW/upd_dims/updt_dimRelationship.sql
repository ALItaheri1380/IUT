GO
CREATE OR ALTER PROCEDURE UpdateDimRelationshipType
AS
BEGIN
    IF EXISTS (SELECT 1 FROM FinalDimRelationshipType) AND NOT EXISTS (SELECT 1 FROM dimRelationshipType)
    BEGIN
        RAISERROR('The situation is critical: FinalDimRelationshipType is populated while dimRelationshipType is empty.', 16, 1);
        RETURN;
    END

    DECLARE @start datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE TempDimRelationshipType;
    ---------------------------
    DECLARE @end datetime = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('TempDimRelationshipType', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    TRUNCATE TABLE FinalDimRelationshipType;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('FinalDimRelationshipType', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO TempDimRelationshipType (ID, Description)
    SELECT ID, Description
    FROM dimRelationshipType;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('TempDimRelationshipType', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO FinalDimRelationshipType (ID, Description)
    SELECT 
        ISNULL(t.ID, (SELECT ISNULL(MAX(ID), 0) FROM TempDimRelationshipType) + ROW_NUMBER() OVER (ORDER BY s.Description)) AS ID,
        ISNULL(t.Description, s.Description) AS Description
    FROM TempDimRelationshipType s
    FULL OUTER JOIN [Library_SA].[dbo].RelationshipType t
    ON t.Description = s.Description;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('FinalDimRelationshipType', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    TRUNCATE TABLE dimRelationshipType;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('dimRelationshipType', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO dimRelationshipType (ID, Description)
    SELECT ID, Description
    FROM FinalDimRelationshipType;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('dimRelationshipType', 'insert', @start, @end);

END;
GO
-- EXEC UpdateDimRelationshipType
-- SELECT * FROM dimRelationshipType;

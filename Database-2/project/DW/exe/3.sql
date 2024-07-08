CREATE OR ALTER PROCEDURE UpdateDW_common
AS
BEGIN
    EXEC UpdateDimBranch;
    SELECT * FROM dimBranch;
END

GO
EXEC UpdateDW_common
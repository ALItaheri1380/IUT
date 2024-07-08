CREATE OR ALTER PROCEDURE UpdateDW1
AS
BEGIN
    EXEC Update_dimBook

    EXECUTE UpdateDimBookTitle

    EXEC UpdateDimEmployee

    EXEC updt_DimMember

    EXEC UpdateDimRelationshipType

    DECLARE @Start DATE;
    DECLARE @End DATE;
    SELECT @Start = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM [LendingsDataMart].[FactDaily] AS bb) AS VARCHAR), 120));
    SELECT @End = (SELECT MAX(BorrowDate) FROM [Library_SA].[dbo].[BorrowedBooks]);

    EXEC usp_InsertFactDailyCurrent @StartDate = @Start, @EndDate = @End
    
    SELECT @Start = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM [LendingsDataMart].[FactTransaction] AS bb) AS VARCHAR), 120));
    SELECT @End = (SELECT MAX(BorrowDate) FROM [Library_SA].[dbo].[BorrowedBooks]);

    EXEC DW_Fact_Tran_dm1_Second @Start, @End;
    select * from [Library_DW].[LendingsDataMart].[FactTransaction];

    EXEC SP_UpdateFactAcc;
    select* from [LendingsDataMart].[FactAcc];

    exec DW_Fact_Factless
    select* from [LendingsDataMart].Factless;
END;
GO

EXEC UpdateDW1;
CREATE OR ALTER PROCEDURE Update_dimBook
AS
BEGIN
    IF (NOT EXISTS (SELECT 1 FROM dimBook)) AND (EXISTS (SELECT 1 FROM [tempBook]))
    BEGIN
        RAISERROR ('Dimension table (dimBook) is empty while temporary table (tempBook) is populated. Execution halted.', 16, 1)
        RETURN
    END

    DECLARE @start datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE [tempBook];
    ---------------------------
    DECLARE @end datetime = GETDATE();
    insert into [LendingsDataMart].[log_dm1]
    values('tempBook', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO [tempBook]
    SELECT
        ID, Title_ID, Book_title_Title, BranchID, BranchName, ISBN, Title, [Description],
        [Year], RepublicationNo, NumOfPages, NumOfEditions, NumOfCopiesPrinted, Category_ID,
        Category_Name, Publisher_ID, Publisher_Name, Editor_ID, Editor_FullName, Language_ID,
        Language_Name, Language_Abbreviation, Translator_ID, Translator_FullName, Age_Range_ID,
        Age_Range_Title, Age_Range_Description
    FROM dimBook;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].[log_dm1]
    values('tempBook', 'insert', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    TRUNCATE TABLE dimBook;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].[log_dm1]
    values('dimBook', 'truncate', @start, @end);

    SET @start = GETDATE();
    ---------------------------
    INSERT INTO dimBook (
        ID,
        Title_ID,
        Book_title_Title,
        BranchID,
        BranchName,
        ISBN,
        Title,
        [Description],
        [Year],
        RepublicationNo,
        NumOfPages,
        NumOfEditions,
        NumOfCopiesPrinted,
        Category_ID,
        Category_Name,
        Publisher_ID,
        Publisher_Name,
        Editor_ID,
        Editor_FullName,
        Language_ID,
        Language_Name,
        Language_Abbreviation,
        Translator_ID,
        Translator_FullName,
        Age_Range_ID,
        Age_Range_Title,
        Age_Range_Description
    )
    SELECT
        ISNULL(src.ID, temp.ID) AS ID,
        ISNULL(src.Title_ID, temp.Title_ID) AS Title_ID,
        ISNULL(src.Book_title_Title, temp.Book_title_Title) AS Book_title_Title,
        ISNULL(src.BranchID, temp.BranchID) AS BranchID,
        ISNULL(src.[Name], temp.BranchName) AS BranchName,
        ISNULL(src.ISBN, temp.ISBN) AS ISBN,
        ISNULL(src.Book_title_Title, temp.Book_title_Title) AS Title,
        ISNULL(src.[Description], temp.[Description]) AS [Description],
        ISNULL(src.[Year], temp.[Year]) AS [Year],
        ISNULL(src.RepublicationNo, temp.RepublicationNo) AS RepublicationNo,
        ISNULL(src.NumOfPages, temp.NumOfPages) AS NumOfPages,
        ISNULL(src.NumOfEditions, temp.NumOfEditions) AS NumOfEditions,
        ISNULL(src.NumOfCopiesPrinted, temp.NumOfCopiesPrinted) AS NumOfCopiesPrinted,
        ISNULL(src.Category_ID, temp.Category_ID) AS Category_ID,
        ISNULL(src.Category_Name, temp.Category_Name) AS Category_Name,
        ISNULL(src.Publisher_ID, temp.Publisher_ID) AS Publisher_ID,
        ISNULL(src.Publisher_Name, temp.Publisher_Name) AS Publisher_Name,
        ISNULL(src.Editor_ID, temp.Editor_ID) AS Editor_ID,
        ISNULL(src.Editor_FullName, temp.Editor_FullName) AS Editor_FullName,
        ISNULL(src.Language_ID, temp.Language_ID) AS Language_ID,
        ISNULL(src.Language_Name, temp.Language_Name) AS Language_Name,
        ISNULL(src.Language_Abbreviation, temp.Language_Abbreviation) AS Language_Abbreviation,
        ISNULL(src.Translator_ID, temp.Translator_ID) AS Translator_ID,
        ISNULL(src.Translator_FullName, temp.Translator_FullName) AS Translator_FullName,
        ISNULL(src.Age_Range_ID, temp.Age_Range_ID) AS Age_Range_ID,
        ISNULL(src.Age_Range_Title, temp.Age_Range_Title) AS Age_Range_Title,
        ISNULL(src.Age_Range_Description, temp.Age_Range_Description) AS Age_Range_Description
    FROM
        (SELECT
            b.ID,
            b.ISBN,
            bt.Title AS Book_title_Title,
            b.Title_ID,
            b.BranchID,
            br.[Name],
            b.[Description],
            b.[Year],
            b.RepublicationNo,
            b.NumOfPages,
            b.NumOfEditions,
            b.NumOfCopiesPrinted,
            c.ID AS Category_ID,
            c.Name AS Category_Name,
            p.ID AS Publisher_ID,
            p.[Name] AS Publisher_Name,
            e.ID AS Editor_ID,
            e.FullName AS Editor_FullName,
            l.ID AS Language_ID,
            l.[Name] AS Language_Name,
            l.abbreviation AS Language_Abbreviation,
            t.ID AS Translator_ID,
            t.FullName AS Translator_FullName,
            ar.ID AS Age_Range_ID,
            ar.Title AS Age_Range_Title,
            ar.[Description] AS Age_Range_Description
        FROM
            [Library_SA].[dbo].Book b
        JOIN [Library_SA].[dbo].Branch br ON br.ID = b.BranchID
        JOIN [Library_SA].[dbo].Book_title bt ON b.Title_ID = bt.ID
        JOIN [Library_SA].[dbo].Category c ON b.Category_ID = c.ID
        JOIN [Library_SA].[dbo].Publisher p ON b.Publisher_ID = p.ID
        JOIN [Library_SA].[dbo].Editor e ON b.Editor_ID = e.ID
        JOIN [Library_SA].[dbo].[Language] l ON b.Language_ID = l.ID
        JOIN [Library_SA].[dbo].Translator t ON b.Translator_ID = t.ID
        JOIN [Library_SA].[dbo].Age_Range ar ON b.Age_Range_ID = ar.ID
    ) AS src
    FULL OUTER JOIN [tempBook] AS temp
    ON src.ID = temp.ID;
    ---------------------------
    SET @end = GETDATE();
    insert into [LendingsDataMart].[log_dm1]
    values('dimBook', 'insert', @start, @end);
END;
GO

--EXEC Update_dimBook;
--select* from dimBook
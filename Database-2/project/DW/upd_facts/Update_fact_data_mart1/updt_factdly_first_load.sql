GO
CREATE OR ALTER PROCEDURE usp_InsertFactDaily
    @InputDate DATE
AS
BEGIN

    DECLARE @start1 datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE [LendingsDataMart].temp1_trns;
    TRUNCATE TABLE [LendingsDataMart].temp2_trns;
    TRUNCATE TABLE [LendingsDataMart].temp_BookCounts;
    ---------------------------
    DECLARE @end1 datetime = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('[LendingsDataMart].temp1_trns', 'truncate', @start1, @end1),
    ('[LendingsDataMart].temp2_trns', 'truncate', @start1, @end1),
    ('[LendingsDataMart].temp_BookCounts', 'truncate', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [LendingsDataMart].temp1_trns (BranchID, Title_ID, BorrowedCount, ReturnedCount)
    SELECT db.ID, b.Title_ID, COUNT(*) AS BorrowedCount, COUNT(*) AS ReturnedCount
    FROM [Library_SA].[dbo].[BorrowedBooks] br
    INNER JOIN [Library_SA].[dbo].[Book] b ON br.BookID = b.ID
    INNER JOIN [dimBranch] db ON(db.ID = b.BranchID)
    WHERE (br.BorrowDate >= @InputDate AND br.BorrowDate < DATEADD(DAY, 1, @InputDate))
      AND br.ReturnDate IS NOT NULL AND ((db.[End_Date] IS NULL AND db.[Start_Date] <= br.[BorrowDate]) OR (db.[End_Date] IS NOT NULL AND db.[End_Date] > br.[BorrowDate] AND db.[Start_Date] <= br.[BorrowDate]))
    GROUP BY db.ID, b.Title_ID;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('[LendingsDataMart].temp1_trns', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [LendingsDataMart].temp2_trns (BranchID, Title_ID, BorrowedCount)
    SELECT db.ID, b.Title_ID, COUNT(*) AS BorrowedCount
    FROM [Library_SA].[dbo].[BorrowedBooks] br
    INNER JOIN [Library_SA].[dbo].[Book] b ON br.BookID = b.ID
    INNER JOIN [dimBranch] db ON(db.ID = b.BranchID)
    WHERE (br.BorrowDate >= @InputDate AND br.BorrowDate < DATEADD(DAY, 1, @InputDate))
      AND br.ReturnDate IS NULL AND ((db.[End_Date] IS NULL AND db.[Start_Date] <= br.[BorrowDate]) OR (db.[End_Date] IS NOT NULL AND db.[End_Date] > br.[BorrowDate] AND db.[Start_Date] <= br.[BorrowDate]))
    GROUP BY db.ID, b.Title_ID;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('[LendingsDataMart].temp2_trns', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [LendingsDataMart].temp_BookCounts (BranchID, Title_ID, TotalCount)
    SELECT BranchID, Title_ID, COUNT(*) AS TotalCount
    FROM [dimBook] db
    GROUP BY BranchID, Title_ID;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('[LendingsDataMart].temp_BookCounts', 'insert', @start1, @end1);
	
    SELECT 
        bch.sur_key_ID,
        bc.BranchID,
        bc.Title_ID,
        bc.TotalCount,
        bc.TotalCount + ISNULL(t1.ReturnedCount, 0) - ISNULL(t2.BorrowedCount, 0) - ISNULL(t1.BorrowedCount, 0) AS available,
        ISNULL(t1.BorrowedCount, 0) + ISNULL(t2.BorrowedCount, 0) AS BorrowedCount,
        ISNULL(t1.ReturnedCount, 0) AS ReturnedCount,
        CASE 
            WHEN t1.BranchID IS NULL AND t2.BranchID IS NULL THEN 1
            ELSE 0
        END AS NoTransaction
    INTO res2Table
    FROM [LendingsDataMart].temp_BookCounts bc
    INNER JOIN dimBranch bch ON bch.ID = bc.BranchID
    LEFT  JOIN [LendingsDataMart].temp1_trns t1 ON t1.BranchID = bc.BranchID AND bc.Title_ID = t1.Title_ID
    LEFT  JOIN [LendingsDataMart].temp2_trns t2 ON t2.BranchID = bc.BranchID AND bc.Title_ID = t2.Title_ID

    WHERE (bch.[End_Date] IS NULL AND bch.[Start_Date] <= @InputDate) 
			  OR (bch.[End_Date] IS NOT NULL AND bch.[End_Date] > @InputDate AND bch.[Start_Date] <= @InputDate) 

    SET @start1 = GETDATE();
    ---------------------------

    INSERT INTO [LendingsDataMart].[FactDaily] (dimBookTitle, BranchID, TimeID, BranchSourceID, borrowed_books_count, available_books_count, numberOfDaysWithoutRequests, return_count)
    SELECT
        tr.Title_ID AS dimBookTitle,
        tr.sur_key_ID,
        dt.FullDate AS TimeID,
		tr.BranchID,
        tr.BorrowedCount AS borrowed_books_count,
        tr.available AS available_books_count,
        tr.NoTransaction AS numberOfDaysWithoutRequests,
        tr.ReturnedCount AS return_count
    FROM res2Table tr
    INNER JOIN dimTime dt ON dt.FullDateAlternateKey = @InputDate;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('[LendingsDataMart].[FactDaily]', 'insert', @start1, @end1);

    DROP TABLE res2Table;

END
GO

-- DECLARE @InputDate DATE = (SELECT MIN(bb.[BorrowDate]) FROM [Library_SA].[dbo].[BorrowedBooks] bb);
-- EXEC usp_InsertFactDaily @InputDate = @InputDate;
-- SELECT * FROM [LendingsDataMart].[FactDaily];
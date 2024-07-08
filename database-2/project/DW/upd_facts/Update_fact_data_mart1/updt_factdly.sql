
CREATE OR ALTER PROCEDURE usp_InsertFactDailyCurrent
    @StartDate DATE,
    @EndDate DATE
AS
BEGIN
    WHILE @StartDate <= @EndDate
    BEGIN
        DECLARE @start1 datetime = GETDATE();
        ---------------------------
        TRUNCATE TABLE [LendingsDataMart].[temp1_trns_scnd];
        TRUNCATE TABLE [LendingsDataMart].[temp2_trns_scnd];
        TRUNCATE TABLE [LendingsDataMart].[temp_BookCounts_scnd];
        ---------------------------
        DECLARE @end1 datetime = GETDATE();
        insert into [LendingsDataMart].[log_dm1]
        values('[LendingsDataMart].[temp1_trns_scnd]', 'truncate', @start1, @end1),
        ('[LendingsDataMart].[temp2_trns_scnd]', 'truncate', @start1, @end1),
        ('[LendingsDataMart].[temp_BookCounts_scnd]', 'truncate', @start1, @end1);

        SET @start1 = GETDATE();
        ---------------------------
        INSERT INTO [LendingsDataMart].[temp1_trns_scnd] (BranchID, Title_ID, BorrowedCount, ReturnedCount)
        SELECT db.ID, b.Title_ID, COUNT(*) AS BorrowedCount, COUNT(*) AS ReturnedCount
        FROM [Library_SA].[dbo].[BorrowedBooks] br
        INNER JOIN [Library_SA].[dbo].[Book] b ON br.BookID = b.ID
		INNER JOIN [dimBranch] db ON(db.ID = b.BranchID)
		WHERE (br.BorrowDate >= @StartDate AND br.BorrowDate < DATEADD(DAY, 1, @StartDate))
		 AND br.ReturnDate IS NOT NULL AND ((db.[End_Date] IS NULL AND db.[Start_Date] <= br.[BorrowDate]) OR (db.[End_Date] IS NOT NULL AND db.[End_Date] > br.[BorrowDate] AND db.[Start_Date] <= br.[BorrowDate]))
		GROUP BY db.ID, b.Title_ID;
        ---------------------------
        SET @end1 = GETDATE();
        insert into [LendingsDataMart].[log_dm1]
        values('[LendingsDataMart].[temp1_trns_scnd]', 'insert', @start1, @end1);

        SET @start1 = GETDATE();
        ---------------------------
        INSERT INTO [LendingsDataMart].[temp2_trns_scnd] (BranchID, Title_ID, BorrowedCount)
        SELECT db.ID, b.Title_ID, COUNT(*) AS BorrowedCount
        FROM [Library_SA].[dbo].[BorrowedBooks] br
        INNER JOIN [Library_SA].[dbo].[Book] b ON br.BookID = b.ID
		INNER JOIN [dimBranch] db ON(db.ID = b.BranchID)
		WHERE (br.BorrowDate >= @StartDate AND br.BorrowDate < DATEADD(DAY, 1, @StartDate))
		  AND br.ReturnDate IS NULL AND ((db.[End_Date] IS NULL AND db.[Start_Date] <= br.[BorrowDate]) OR (db.[End_Date] IS NOT NULL AND db.[End_Date] > br.[BorrowDate] AND db.[Start_Date] <= br.[BorrowDate]))
		GROUP BY db.ID, b.Title_ID;
        ---------------------------
        SET @end1 = GETDATE();
        insert into [LendingsDataMart].[log_dm1]
        values('[LendingsDataMart].[temp2_trns_scnd]', 'insert', @start1, @end1);

        SET @start1 = GETDATE();
        ---------------------------
        INSERT INTO [LendingsDataMart].[temp_BookCounts_scnd] (BranchID, Title_ID, TotalCount, numberOfDaysWithoutRequests)
        SELECT fd.BranchSourceID, fd.dimBookTitle AS Title_ID, fd.available_books_count AS TotalCount, numberOfDaysWithoutRequests
        FROM [LendingsDataMart].[FactDaily] fd
        INNER JOIN dimTime dt ON fd.TimeID = dt.FullDate
        WHERE dt.FullDateAlternateKey = DATEADD(DAY, -1, @StartDate);
        ---------------------------
        SET @end1 = GETDATE();
        insert into [LendingsDataMart].[log_dm1]
        values('[LendingsDataMart].[temp_BookCounts_scnd]', 'insert', @start1, @end1);

		SELECT 
			bch.sur_key_ID,
			bc.BranchID,
			bc.Title_ID,            
			bc.TotalCount,
			bc.TotalCount + ISNULL(t1.ReturnedCount, 0) - ISNULL(t2.BorrowedCount, 0) - ISNULL(t1.BorrowedCount, 0) AS available,            
			ISNULL(t1.BorrowedCount, 0) + ISNULL(t2.BorrowedCount, 0) AS BorrowedCount,
			ISNULL(t1.ReturnedCount, 0) AS ReturnedCount,            
			CASE 
				WHEN t1.BranchID IS NULL THEN numberOfDaysWithoutRequests + 1                
				ELSE numberOfDaysWithoutRequests
			END AS NoTransaction        
		INTO #resTable
		FROM [LendingsDataMart].[temp_BookCounts_scnd] bc  
		INNER JOIN dimBranch bch ON bch.ID = bc.BranchID
		LEFT  JOIN [LendingsDataMart].[temp1_trns_scnd] t1 ON t1.BranchID = bc.BranchID AND bc.Title_ID = t1.Title_ID        
		LEFT  JOIN [LendingsDataMart].[temp2_trns_scnd] t2 ON t2.BranchID = bc.BranchID AND bc.Title_ID = t2.Title_ID
		WHERE (bch.[End_Date] IS NULL AND bch.[Start_Date] <= @StartDate) 
			  OR (bch.[End_Date] IS NOT NULL AND bch.[End_Date] > @StartDate AND bch.[Start_Date] <= @StartDate) 

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
        FROM #resTable tr
        INNER JOIN dbo.dimTime dt ON dt.FullDateAlternateKey = @StartDate;
        ---------------------------
        SET @end1 = GETDATE();
        insert into [LendingsDataMart].[log_dm1]
        values('FactDaily', 'insert', @start1, @end1);

        DROP TABLE #resTable;

        SET @StartDate = DATEADD(DAY, 1, @StartDate); 
    END
END
GO

-- DECLARE @Start DATE = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM [LendingsDataMart].[FactDaily] AS bb) AS VARCHAR), 120));
-- DECLARE @End DATE = (SELECT MAX(BorrowDate) FROM [Library_SA].[dbo].[BorrowedBooks]);
-- EXEC usp_InsertFactDailyCurrent @StartDate = @Start, @EndDate = @End;
-- select* from [LendingsDataMart].FactDaily
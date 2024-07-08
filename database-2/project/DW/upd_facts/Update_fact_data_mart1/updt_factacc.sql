CREATE OR ALTER PROCEDURE SP_UpdateFactAcc
AS
BEGIN

    DECLARE @start1 datetime = GETDATE();
    ---------------------------
    TRUNCATE TABLE [LendingsDataMart].[FactAcc];
    ---------------------------
    DECLARE @end1 datetime = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('FactAcc', 'truncate', @start1, @end1)

    SET @start1 = GETDATE();
    ---------------------------
    INSERT INTO [LendingsDataMart].[FactAcc] (dimBookTitle, BranchID, maxreturncount, minreturncount, avgreturncount, maxBooksBorrowed,
                         minBooksBorrowed, avgBooksBorrowed, maxavailablebook, minavailablebook, avgavailablebook,
                         Total_return_count, Total_borrowed_books_count, numberOfDaysWithoutRequests)
    SELECT dimBookTitle, BranchSourceID,
           MAX(return_count) AS maxreturncount, MIN(return_count) AS minreturncount,
           AVG(return_count) AS avgreturncount, MAX(borrowed_books_count) AS maxBooksBorrowed,
           MIN(borrowed_books_count) AS minBooksBorrowed, AVG(borrowed_books_count) AS avgBooksBorrowed,
           MAX(available_books_count) AS maxavailablebook, MIN(available_books_count) AS minavailablebook,
           AVG(available_books_count) AS avgavailablebook, SUM(return_count) AS Total_return_count,
           SUM(borrowed_books_count) AS Total_borrowed_books_count,
		   (SELECT TOP 1 numberOfDaysWithoutRequests 
                FROM FactDaily fd 
                WHERE fd.dimBookTitle = f.dimBookTitle AND 
                      fd.BranchID = f.BranchID 
                ORDER BY TimeID DESC) AS numberOfDaysWithoutRequests
    FROM [LendingsDataMart].[FactDaily] f
    GROUP BY dimBookTitle, BranchSourceID;
    ---------------------------
    SET @end1 = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('FactAcc', 'insert', @start1, @end1);
END;
GO

-- EXEC SP_UpdateFactAcc;
-- GO
-- select* from [LendingsDataMart].[FactAcc]
-- order by BranchID, dimBookTitle
CREATE PROCEDURE DeleteInvalidRecords
AS
BEGIN
    DELETE BB
    FROM BorrowedBooks BB
    INNER JOIN (
        SELECT BookID
        FROM BorrowedBooks
        WHERE ReturnDate IS NULL
        GROUP BY BookID
        HAVING COUNT(*) > 1
    ) AS InvalidBooks
    ON BB.BookID = InvalidBooks.BookID
    WHERE BB.ReturnDate IS NULL;

    DELETE BB
    FROM BorrowedBooks BB
    INNER JOIN BorrowedBooks BBPrev
    ON BB.BookID = BBPrev.BookID
    WHERE BBPrev.ReturnDate IS NULL
    AND BB.BorrowDate > BBPrev.BorrowDate;

    DELETE bb 
    FROM BorrowedBooks bb
    JOIN Book b ON bb.BookID = b.ID
    JOIN Branch br ON b.BranchID = br.ID
    WHERE bb.BorrowDate < br.Start_Date;

END;
Go
EXEC DeleteInvalidRecords

select* from BorrowedBooks
USE Library_DW
GO
CREATE OR ALTER PROCEDURE DW_Fact_Tran_dm1_Second
  @start date,
  @endINPUT   date
AS
BEGIN

  
  DECLARE @TimeID INT;
  WHILE @start <= @endINPUT
    BEGIN

  DECLARE @start1 datetime = GETDATE();
  ---------------------------
  truncate table Library_DW.[LendingsDataMart].[todayStock];
  truncate table Library_DW.[LendingsDataMart].[newData];
  truncate table Library_DW.[LendingsDataMart].[newData2];
  ---------------------------
  DECLARE @end1 datetime = GETDATE();
  insert into [LendingsDataMart].log_dm1
  values('todayStock', 'truncate', @start1, @end1),
  ('newData', 'truncate', @start1, @end1),
  ('newData2', 'truncate', @start1, @end1);

    set @TimeID = (SELECT FullDate FROM dimTime WHERE FullDateAlternateKey = @start);

    SET @start1 = GETDATE();
    ---------------------------
    insert into Library_DW.[LendingsDataMart].[todayStock] (BranchID,BookTitleID,total_cnt)
    SELECT [BranchSourceID]
      ,[dimBookTitle]
      ,[available_books_count]
    FROM [Library_DW].[LendingsDataMart].[FactDaily] as f join [Library_DW].[dbo].[dimTime] as t ON(f.[TimeID] = t.[FullDate])
    where t.[FullDateAlternateKey] >= DATEADD(DAY, -1, @start) and t.[FullDateAlternateKey] < @start
    ORDER BY [dimBookTitle], [BranchID];
    ---------------------------
    SET @end1 = GETDATE();
    insert into [LendingsDataMart].log_dm1
    values('todayStock', 'insert', @start, @end1);


      SET @start1 = GETDATE();
      ---------------------------
      WITH a AS(
      SELECT distinct(t1.[UserID])
        ,t1.[EmployeeID]
        ,t1.[BookID]
        ,t1.[BorrowDate]
        ,t1.[ReturnDate]
        ,t1.[BranchID]
        ,t1.[Borrowday]
        ,t1.Title_ID
        ,sum(case when t1.ReturnDate > DATEADD(DAY, 1, @Start) then 1 else 0 end) 
        OVER(PARTITION BY t1.Title_ID, t1.BranchID, t1.ID ORDER BY t1.ID) as borrowed_count
        ,sum(case when t1.ReturnDate > DATEADD(DAY, 1, @Start) then 0 else 1 end)
        OVER(PARTITION BY t1.Title_ID, t1.BranchID, t1.ID ORDER BY t1.ID) as returned_count
      FROM (
         select bb1.ID
          ,bb1.[UserID]
          ,bb1.[EmployeeID]
          ,bb1.[BookID]
          ,bb1.[BorrowDate]
          ,bb1.[ReturnDate]
          ,bb1.[Borrowday]
          ,b1.[BranchID] 
          ,b1.Title_ID
         from [Library_SA].[dbo].[BorrowedBooks] as bb1 JOIN 
        [Library_SA].[dbo].[Book] as b1 ON b1.[ID] = bb1.BookID
         WHERE bb1.[BorrowDate] >= @start and bb1.[BorrowDate] < DATEADD(DAY, 1, @start)) as t1 
      JOIN
         (
         select bb2.ID
          ,bb2.[UserID]
          ,bb2.[EmployeeID]
          ,bb2.[BookID]
          ,bb2.[BorrowDate]
          ,bb2.[ReturnDate]
          ,b2.[BranchID] 
          ,b2.Title_ID
         from [Library_SA].[dbo].[BorrowedBooks] as bb2 JOIN 
        [Library_SA].[dbo].[Book] as b2 ON b2.[ID] = bb2.BookID
         WHERE bb2.[BorrowDate] >= @start and bb2.[BorrowDate] < DATEADD(DAY, 1, @start)) as t2
       ON(t1.Title_ID = t2.Title_ID and t1.BranchID = t2.BranchID and t1.ID >= t2.ID)
       )
      INSERT INTO [Library_DW].[LendingsDataMart].[newData] 
      SELECT a.[UserID], a.[BookID], e.[sur_key_ID], a.[BranchID], a.[Title_ID], @TimeID
         , a.[BorrowDate], a.[Borrowday], a.[borrowed_count], a.[returned_count]  
      FROM a JOIN [Library_DW].[dbo].[dimEmployee] as e ON(e.ID = a.[EmployeeID])
	WHERE 
	      (e.[EndDate] IS NULL AND e.[StartDate] <= a.[BorrowDate]) OR 
          (e.[EndDate] IS NOT NULL AND e.[EndDate] > a.[BorrowDate] AND e.[StartDate] <= a.[BorrowDate])
      ---------------------------
      SET @end1 = GETDATE();
      insert into [LendingsDataMart].log_dm1
      values('newData', 'insert', @start1, @end1);

      SET @start1 = GETDATE();
      ---------------------------
      INSERT INTO [Library_DW].[LendingsDataMart].[newData2] 
        SELECT nd.[MemberID], nd.[BookID], nd.[EmployeeID], db.[sur_key_ID], nd.[TimeID], db.[ID], nd.[borrowed_days], 
           ts.[total_cnt] - nd.[borrowed_count] + nd.[returned_count]
        FROM [Library_DW].[LendingsDataMart].[newData] as nd INNER JOIN Library_DW.[LendingsDataMart].[todayStock] as ts ON(nd.Title_ID = ts.[BookTitleID] and nd.[BranchID] = ts.[BranchID])
        JOIN [Library_DW].[dbo].[dimBranch] as db ON(db.[ID] = nd.[BranchID] and 
              ((db.[End_Date] is null and db.[Start_Date] <= nd.[BorrowDate]) OR
               (db.[End_Date] is not null and db.[End_Date] > nd.[BorrowDate] AND db.[Start_Date] <= nd.[BorrowDate])))
      ---------------------------
      SET @end1 = GETDATE();
      insert into [LendingsDataMart].log_dm1
      values('newData2', 'insert', @start1, @end1);

    SET @start1 = GETDATE();
    ---------------------------
	  insert into [Library_DW].[LendingsDataMart].[FactTransaction]
      select [MemberID]
        ,[BookID]
        ,[EmployeeID]
        ,[BranchID]
        ,[TimeID]
        ,[BranchSourceID]
        ,[borrowed_days]
        ,[Remaining_same_Book]
      FROM [Library_DW].[LendingsDataMart].[newData2] 
      ---------------------------
      SET @end1 = GETDATE();
      insert into [LendingsDataMart].log_dm1
      values('FactTransaction', 'insert', @start1, @end1);

      SET @start = DATEADD(DAY, 1, @start); 
    END

end

-- DECLARE @Start DATE = DATEADD(DAY, 1, CONVERT(DATE, CAST((SELECT MAX(bb.[TimeID]) FROM [LendingsDataMart].[FactTransaction] AS bb) AS VARCHAR), 120));
-- DECLARE @end date = DECLARE @End DATE = (SELECT MAX(BorrowDate) FROM [Library_SA].[dbo].[BorrowedBooks]);
-- EXEC DW_Fact_Tran_dm1_Second
--    @start,
--    @end;

--   select * from [Library_DW].[LendingsDataMart].[FactTransaction]
--   order by TimeID
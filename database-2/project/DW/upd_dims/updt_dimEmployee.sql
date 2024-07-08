Go 
CREATE OR ALTER PROCEDURE UpdateDimEmployee 
AS 
BEGIN 
  
 IF EXISTS (SELECT 1 FROM TempDimEmployee) AND NOT EXISTS (SELECT 1 FROM dimEmployee) 
    BEGIN 
        PRINT N'Warning: TempDimEmployee has data and dimEmployee is empty. The procedure will not be executed.'; 
        RETURN; 
    END 
 
    DECLARE @start datetime = GETDATE(); 
    --------------------------- 
 TRUNCATE TABLE TempDimEmployee 
    --------------------------- 
    DECLARE @end datetime = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('TempDimEmployee', 'truncate', @start, @end); 
 
    SET @start = GETDATE(); 
    --------------------------- 
 TRUNCATE TABLE TempEmployee 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('TempEmployee', 'truncate', @start, @end); 
 
    SET @start = GETDATE(); 
    --------------------------- 
    INSERT INTO TempDimEmployee 
    SELECT  
        sur_key_ID, ID, FullName, NationalCode, [Address], Phone, Hire_Date,  
        Employee_No, YearOfPassing, MaritalStatus, Gender_ID, Gender_Name,  
        Branch_ID, Branch_Name, Position_ID, Position_Title, StartDate, EndDate, cur_flag 
    FROM dimEmployee; 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('TempDimEmployee', 'insert', @start, @end); 
 
    SET @start = GETDATE(); 
    --------------------------- 
    INSERT INTO TempEmployee 
    SELECT  
        E.ID, E.FullName, E.NationalCode, E.[Address], E.Phone, E.Hire_Date,  
        E.Employee_No, E.YearOfPassing, E.MaritalStatus, G.ID AS Gender_ID, G.Name AS Gender_Name, 
        B.ID AS Branch_ID, B.Name AS Branch_Name, P.ID AS Position_ID, P.Title AS Position_Title 
    FROM [Library_SA].[dbo].Employee E 
    INNER JOIN [Library_SA].[dbo].Gender G ON E.Gender_ID = G.ID 
    INNER JOIN [Library_SA].[dbo].Branch B ON E.Branch_ID = B.ID 
    INNER JOIN [Library_SA].[dbo].Position P ON E.Position_ID = P.ID; 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('TempEmployee', 'insert', @start, @end); 
 
    SET @start = GETDATE(); 
    --------------------------- 
 TRUNCATE TABLE dimEmployee 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('dimEmployee', 'truncate', @start, @end); 
 
    UPDATE D 
    SET D.EndDate = GETDATE(), D.cur_flag = 0 
    FROM TempDimEmployee D 
    INNER JOIN TempEmployee T ON D.ID = T.ID 
    WHERE D.cur_flag = 1 AND D.Position_ID <> T.Position_ID; 
 
    SET @start = GETDATE(); 
    --------------------------- 
    INSERT INTO TempDimEmployee ( 
        ID, FullName, NationalCode, [Address], Phone, Hire_Date, Employee_No,  
        YearOfPassing, MaritalStatus, Gender_ID, Gender_Name, Branch_ID,  
        Branch_Name, Position_ID, Position_Title, StartDate, EndDate, cur_flag 
    ) 
    SELECT  
        T.ID, T.FullName, T.NationalCode, T.[Address], T.Phone, T.Hire_Date,  
        T.Employee_No, T.YearOfPassing, T.MaritalStatus, T.Gender_ID, T.Gender_Name,  
        T.Branch_ID, T.Branch_Name, T.Position_ID, T.Position_Title, GETDATE(), NULL, 1 
    FROM TempEmployee T 
    WHERE EXISTS ( 
        SELECT 1 FROM TempDimEmployee D WHERE D.ID = T.ID AND D.cur_flag = 0 
    ) AND NOT EXISTS ( 
        SELECT 1 FROM TempDimEmployee D WHERE D.ID = T.ID AND D.cur_flag = 1 
    ); 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('TempDimEmployee', 'insert', @start, @end); 
 
    SET @start = GETDATE(); 
    --------------------------- 
    INSERT INTO TempDimEmployee ( 
        ID, FullName, NationalCode, [Address], Phone, Hire_Date, Employee_No,  
        YearOfPassing, MaritalStatus, Gender_ID, Gender_Name, Branch_ID,  
        Branch_Name, Position_ID, Position_Title, StartDate, EndDate, cur_flag 
    ) 
    SELECT  
        T.ID, T.FullName, T.NationalCode, T.[Address], T.Phone, T.Hire_Date,  
        T.Employee_No, T.YearOfPassing, T.MaritalStatus, T.Gender_ID, T.Gender_Name,  
        T.Branch_ID, T.Branch_Name, T.Position_ID, T.Position_Title, T.Hire_Date, NULL, 1 
    FROM TempEmployee T 
    WHERE NOT EXISTS ( 
        SELECT 1 FROM TempDimEmployee D WHERE D.ID = T.ID 
    ); 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('TempDimEmployee', 'insert', @start, @end); 
 
    SET @start = GETDATE(); 
    --------------------------- 
    INSERT INTO dimEmployee ( 
        ID, FullName, NationalCode, [Address], Phone, Hire_Date,  
        Employee_No, YearOfPassing, MaritalStatus, Gender_ID, Gender_Name,  
        Branch_ID, Branch_Name, Position_ID, Position_Title, StartDate, EndDate, cur_flag 
    ) 
    SELECT  
        ID, FullName, NationalCode, [Address], Phone, Hire_Date,  
        Employee_No, YearOfPassing, MaritalStatus, Gender_ID, Gender_Name,  
        Branch_ID, Branch_Name, Position_ID, Position_Title, StartDate, EndDate, cur_flag 
    FROM TempDimEmployee; 
    --------------------------- 
    SET @end = GETDATE(); 
    insert into [LendingsDataMart].log_dm1 
    values('dimEmployee', 'insert', @start, @end); 
 
END; 
GO 
 
-- EXEC UpdateDimEmployee; 
-- SELECT * FROM dimEmployee;
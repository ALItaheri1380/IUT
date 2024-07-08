USE Library_DW
Go

--==================== Dim ====================--
CREATE TABLE dimmember(
    ID int primary key,
    Fullname VARCHAR(300),
    NationalCode varchar(15),
    Address varchar(500),
    Original_Phone varchar(20), --SCD 3
    Current_Phone varchar(20),-- SCD 3
    Effective_Date date, -- SCD 3
    Registration_Date date,
    Registration_Valid_Date date,
    Gender_ID int,
    Gender_Name varchar(200),
    Branch_ID int,
    Branch_Name varchar(200),
    Branch_BranchCode int
);
--===============================================
create table dimBookTitle
(
  ID int primary key,
  Title varchar(200)
)
--===============================================
CREATE TABLE dimBook( 
    ID int primary key,
    Title_ID int,
    Book_title_Title varchar(200),
    branchID int,
    branchName varchar(200),
    ISBN varchar(20) UNIQUE, 
    Title varchar(200),
    Description varchar(500),
    Year int,
    RepublicationNo int,
    NumOfPages int,
    NumOfEditions int,    -- SCD 1 
    NumOfCopiesPrinted int,
    Category_ID int,
    Category_Name varchar(200),
    Publisher_ID int,
    Publisher_Name varchar(200),
    Editor_ID int,
    Editor_FullName VARCHAR(400),
    Language_ID int,
    Language_Name varchar(200),
    Language_Abbreviation varchar(20),
    Translator_ID int,
    Translator_FullName VARCHAR(400),
    Age_Range_ID int,
    Age_Range_Title varchar(200),
    Age_Range_Description varchar(500)
);
--================================================
CREATE TABLE dimEmployee( 
    sur_key_ID int primary key identity(1,1),
    ID int,
    FullName varchar(300),
    NationalCode varchar(10),
    Address varchar(500),
    Phone varchar(20),
    Hire_Date date,
    Employee_No varchar(20),
    YearOfPassing int,
    MaritalStatus VARCHAR(20),
    Gender_ID int,
    Gender_Name varchar(200),
    Branch_ID int,
    Branch_Name varchar(200),
    Position_ID int,
    Position_Title varchar(200), --SCD 2
    StartDate date,
    EndDate date,
    cur_flag bit default 1
);
--=================================================
CREATE TABLE dimTime (
    FullDate INT PRIMARY KEY,
    FullDateAlternateKey DATE,
    DayNumberOfWeek TINYINT,
    EnglishDayNameOfWeek VARCHAR(50),
    DayNumberOfMonth TINYINT,
    DayNumberOfYear SMALLINT,
    WeekNumberOfYear TINYINT,
    EnglishMonthName VARCHAR(50),
    MonthNumberOfYear TINYINT,
    CalendarQuarter TINYINT,
    CalendarYear SMALLINT,
    CalendarSemester TINYINT,
);
--=================================================
CREATE TABLE dimBranch(
    sur_key_ID int primary key identity(1,1),
    ID int,
    Name varchar(200),     
    Address varchar(500), -- scd 2
    Start_Date date, -- scd 2
    End_Date date, -- scd 2
    cur_flag bit default 1,  -- scd 2
    BranchCode int,
    Branch_Phone varchar(20),
    Branch_type_ID int,
    Branch_type_type varchar(20)
);
--=================================================
CREATE TABLE dimRelationshipType(
	ID int primary key,
	Description  varchar(500)
);
--====================================================================
CREATE TABLE dimAccount(
    ID int PRIMARY KEY,
    OpenDate date,
    CloseDate date,
    Balance decimal(18,2),
    Currency varchar(3),
    Name varchar(50),
    Original_phone varchar(50), --scd 3
    Current_Phone varchar(50), --scd 3
    Effective_Date date, 
    address varchar(200)
);

CREATE TABLE [LendingsDataMart].log_dm1(
    table_name VARCHAR(100),
    explanation VARCHAR(200),
    startDate  datetime,
    endDate datetime
)


--%%%%%%%%%%%%%%%%% updt_dimBook %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].tempBook (
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
    NumOfEditions int,    
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


--%%%%%%%%%%%%%%%%% updt_dimBookTitle %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].TempBookTitle (
  ID int,
  Title varchar(500)
);


--%%%%%%%%%%%%%%%%% updt_dimBranch %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].TempDimBranch (
    sur_key_ID INT,
    ID INT,
    Name VARCHAR(200),
    Address VARCHAR(500),
    Start_Date DATE,
    End_Date DATE,
    cur_flag BIT,
    BranchCode INT,
    Branch_Phone VARCHAR(20),
    Branch_type_ID INT,
    Branch_type_type VARCHAR(20)
);

CREATE TABLE [dbo].TempBranch (
    ID INT,
    Name VARCHAR(255),
    Address VARCHAR(500),
    Start_Date DATE,
    End_Date DATE,
    BranchCode VARCHAR(50),
    Branch_Phone VARCHAR(20),
    Branch_type_ID INT,
    Branch_type_type VARCHAR(50)
);

--%%%%%%%%%%%%%%%%% updt_dimMember %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].dimAll(
	[ID] [int],
	[Fullname] [varchar](300),
	[NationalCode] [varchar](15),
	[Address] [varchar](500),
	[Original_Phone] [varchar](20),
	[Current_Phone] [varchar](20),
	[Effective_Date] [date],
	[Registration_Date] [date],
	[Registration_Valid_Date] [date],
	[Gender_ID] [int],
	[Gender_Name] [varchar](200),
	[Branch_ID] [int],
	[Branch_Name] [varchar](200),
	[Branch_BranchCode] [int]
)

CREATE TABLE [dbo].[srcAll](
	[ID] [int],
	[Fullname] [varchar](300),
	[NationalCode] [varchar](15),
	[Address] [varchar](500),
	[Phone] [varchar](20),
	[Registration_Date] [date],
	[Registration_Valid_Date] [date],
	[Gender_Name] [varchar](200),
	[Gender_ID] [int],
	[Branch_ID] [int],
	[Branch_Name] [varchar](200),
	[Branch_BranchCode] [int]
)

CREATE TABLE [dbo].[tmpDim](
	[ID] [int],
	[Fullname] [varchar](300) ,
	[NationalCode] [varchar](15) ,
	[Address] [varchar](500) ,
	[Original_Phone] [varchar](20) ,
	[Current_Phone] [varchar](20) ,
	[Effective_Date] [date] ,
	[Registration_Date] [date] ,
	[Registration_Valid_Date] [date] ,
	[Gender_ID] [int] ,
	[Gender_Name] [varchar](200) ,
	[Branch_ID] [int] ,
	[Branch_Name] [varchar](200) ,
	[Branch_BranchCode] [int] 
)

CREATE TABLE [dbo].[mergedDim](
	[ID] [int],
	[Fullname] [varchar](300),
	[NationalCode] [varchar](15),
	[Address] [varchar](500),
	[Original_Phone] [varchar](20),
	[Current_Phone] [varchar](20),
	[Effective_Date] [datetime],
	[Registration_Date] [date],
	[Registration_Valid_Date] [date],
	[Gender_ID] [int],
	[Gender_Name] [varchar](200),
	[Branch_ID] [int],
	[Branch_Name] [varchar](200),
	[Branch_BranchCode] [int]
) 

--%%%%%%%%%%%%%%%%% updt_dimRelationship %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].TempDimRelationshipType (
    ID int,
    Description varchar(500)
);

CREATE TABLE [dbo].FinalDimRelationshipType (
    ID int,
    Description varchar(500)
);

--%%%%%%%%%%%%%%%%% updt_dimEmployee %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].TempDimEmployee (
    sur_key_ID INT,
    ID INT,
    FullName NVARCHAR(100),
    NationalCode NVARCHAR(50),
    [Address] NVARCHAR(200),
    Phone NVARCHAR(50),
    Hire_Date DATE,
    Employee_No NVARCHAR(50),
    YearOfPassing INT,
    MaritalStatus NVARCHAR(50),
    Gender_ID INT,
    Gender_Name NVARCHAR(50),
    Branch_ID INT,
    Branch_Name NVARCHAR(100),
    Position_ID INT,
    Position_Title NVARCHAR(100),
    StartDate DATE,
    EndDate DATE,
    cur_flag BIT
);

CREATE TABLE [dbo].TempEmployee (
    ID INT,
    FullName NVARCHAR(100),
    NationalCode NVARCHAR(50),
    [Address] NVARCHAR(200),
    Phone NVARCHAR(50),
    Hire_Date DATE,
    Employee_No NVARCHAR(50),
    YearOfPassing INT,
    MaritalStatus NVARCHAR(50),
    Gender_ID INT,
    Gender_Name NVARCHAR(50),
    Branch_ID INT,
    Branch_Name NVARCHAR(100),
    Position_ID INT,
    Position_Title NVARCHAR(100)
);

--@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

--%%%%%%%%%%%%%%%%% DW_Fact_Tran_dm1 %%%%%%%%%%%%%%%%%
CREATE TABLE Library_DW.[LendingsDataMart].[newData](
    MemberID       int,
    BookID         int,
    EmployeeID     int, 
    BranchID       int,
    Title_ID     int,
    TimeID         int,
    [BorrowDate]   date,
    
    borrowed_days       int,
    borrowed_count      int,
    returned_count    int
  );

  CREATE TABLE Library_DW.[LendingsDataMart].[newData2](
    MemberID       int,
    BookID         int,
    EmployeeID     int, 
    BranchID       int,
    TimeID         int,
    
    BranchSourceID int,
    borrowed_days       int,
    Remaining_same_Book int,
    
  );

  CREATE TABLE Library_DW.[LendingsDataMart].[todayStock](
    [BranchID] [int],
    [BookTitleID] [varchar](20),
    [total_cnt] [int]
  );

  --%%%%%%%%%%%%%%%%% usp_InsertFactDaily_first %%%%%%%%%%%%%%%%%
CREATE TABLE [LendingsDataMart].temp1_trns (
    BranchID INT,
    Title_ID INT,
    BorrowedCount INT,
    ReturnedCount INT
);

CREATE TABLE [LendingsDataMart].temp2_trns (
    BranchID INT,
    Title_ID INT,
    BorrowedCount INT
);

CREATE TABLE [LendingsDataMart].temp_BookCounts (
    BranchID INT,
    Title_ID INT,
    TotalCount INT
);

  --%%%%%%%%%%%%%%%%% usp_InsertFactDaily_sec %%%%%%%%%%%%%%%%%
CREATE TABLE [LendingsDataMart].temp1_trns_scnd (
    BranchID INT,
    Title_ID INT,
    BorrowedCount INT,
    ReturnedCount INT
);

CREATE TABLE [LendingsDataMart].temp2_trns_scnd (
    BranchID INT,
    Title_ID INT,
    BorrowedCount INT
);

CREATE TABLE [LendingsDataMart].temp_BookCounts_scnd (
    BranchID INT,
    Title_ID INT,
    TotalCount INT,
    numberOfDaysWithoutRequests int
);
GO

 --%%%%%%%%%%%%%%%%% Library_DW Factless Fact %%%%%%%%%%%%%%%%%
 create table [Library_DW].[LendingsDataMart].factlessTmp (
   MemberID          INT,
   Member_identifier INT,
   RelationshipType  INT
);

create table [LIBRARY_DW].[LendingsDataMart].factlessTmp2 (
   MemberID          INT,
   Member_identifier INT,
   [Description]  varchar(500)
);
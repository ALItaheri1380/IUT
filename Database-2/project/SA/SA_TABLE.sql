USE Library_SA
GO

CREATE OR ALTER PROCEDURE SA_TABLE
AS
BEGIN
  -- Check and create tables if they do not exist

  IF OBJECT_ID('Branch_type', 'U') IS NULL
  BEGIN
    CREATE TABLE Branch_type (
      ID INT PRIMARY KEY IDENTITY(1,1),
      brnch_type VARCHAR(20)
    );
  END

  IF OBJECT_ID('Branch', 'U') IS NULL
  BEGIN
    CREATE TABLE Branch
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      [Name] VARCHAR(200),
      [Address] VARCHAR(500),
      BranchCode INT UNIQUE,
      Phone VARCHAR(20),
      Start_Date DATE,
	    END_Date   DAte,
      brnch_type_id INT FOREIGN KEY REFERENCES Branch_type(ID)
    );
  END

  IF OBJECT_ID('Account_Info', 'U') IS NULL
  BEGIN
    CREATE TABLE Account_Info
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      Name VARCHAR(50),
      phone VARCHAR(50),
      address VARCHAR(200)
    );
  END

  IF OBJECT_ID('Account', 'U') IS NULL
  BEGIN
    CREATE TABLE Account
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      OpenDate DATE,
      CloseDate DATE,
      Balance DECIMAL(18,2),
      Currency VARCHAR(3),
      Account_Info_ID INT FOREIGN KEY REFERENCES Account_Info(ID)
    );
  END

  IF OBJECT_ID('PaymentMethod', 'U') IS NULL
  BEGIN
    CREATE TABLE PaymentMethod
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      PaymentMethod VARCHAR(50),
      ProviderName VARCHAR(100)
    );
  END

  IF OBJECT_ID('[Transaction]', 'U') IS NULL
  BEGIN
    create table [Transaction]
    (
        ID int primary key identity(1,1),
        TransactionDate DATETIME,
        TransactionType varchar(50),
        Amount decimal(18,2),
        Branch_ID  int foreign key references Branch(ID),
        Account_ID int foreign key references Account(ID),
        PaymentMethod_ID int foreign key references PaymentMethod(ID),
        Description varchar(500)
    );
  END

  IF OBJECT_ID('Gender', 'U') IS NULL
  BEGIN
    CREATE TABLE Gender
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      Name VARCHAR(200)
    );
  END

  IF OBJECT_ID('Member', 'U') IS NULL
  BEGIN
    CREATE TABLE Member
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      Fullname VARCHAR(300),
      NationalCode VARCHAR(15) UNIQUE,
      [Address] VARCHAR(500),
      Phone VARCHAR(20),
      Registration_Date DATE,
      Branch_ID INT FOREIGN KEY REFERENCES Branch(ID),
      Registration_Valid_Date DATE,
      Gender_ID INT FOREIGN KEY REFERENCES Gender(ID)
    ); 
  END

  IF OBJECT_ID('Category', 'U') IS NULL
  BEGIN
    CREATE TABLE Category
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      Name VARCHAR(200) 
    );
  END

  IF OBJECT_ID('Publisher', 'U') IS NULL
  BEGIN
    CREATE TABLE Publisher
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      [Name] VARCHAR(200),
      Phone VARCHAR(20)
    );
  END

  IF OBJECT_ID('Editor', 'U') IS NULL
  BEGIN
    CREATE TABLE Editor
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      FullName VARCHAR(400)
    );
  END

  IF OBJECT_ID('[Language]', 'U') IS NULL
  BEGIN
    CREATE TABLE [Language]
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      [Name] VARCHAR(200),
      abbreviation VARCHAR(20)
    );
  END

  IF OBJECT_ID('Translator', 'U') IS NULL
  BEGIN
    CREATE TABLE Translator
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      FullName VARCHAR(400)
    );
  END

  IF OBJECT_ID('Age_Range', 'U') IS NULL
  BEGIN
    CREATE TABLE Age_Range
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      Title VARCHAR(200),
      Description VARCHAR(500)
    );
  END

  IF OBJECT_ID('Book_title', 'U') IS NULL
  BEGIN
    CREATE TABLE Book_title
    (
      ID int primary key identity(1,1),
      Title varchar(200)
    );
    
  END
  IF OBJECT_ID('Book', 'U') IS NULL
  BEGIN
    CREATE TABLE Book
    (
      ID int primary key identity(1,1),
      ISBN varchar(20) UNIQUE,
      Title_ID int foreign key references Book_title(ID),
      BranchID int,
      [Description] varchar(500),
      [Year] int,
      Publisher_ID int foreign key references Publisher(ID),
      Category_ID int foreign key references Category(ID),
      Age_Range_ID int foreign key references Age_Range(ID),
      Translator_ID int foreign key references Translator(ID),
      Editor_ID int foreign key references Editor(ID),
      Language_ID int foreign key references [Language](ID),
      RepublicationNo int,
      NumOfPages int,
      NumOfEditions int,
      NumOfCopiesPrinted int
    );
  END

  IF OBJECT_ID('Position', 'U') IS NULL
  BEGIN
    CREATE TABLE Position
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      Title VARCHAR(200),
      Salary BIGINT
    );
  END

  IF OBJECT_ID('Employee', 'U') IS NULL
  BEGIN
    CREATE TABLE Employee
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      FullName VARCHAR(300),
      NationalCode VARCHAR(10),
      [Address] VARCHAR(500),
      Phone VARCHAR(20),
      Hire_Date DATE,
      Branch_ID INT FOREIGN KEY REFERENCES Branch(ID),
      Position_ID INT FOREIGN KEY REFERENCES Position(ID),
      Gender_ID INT FOREIGN KEY REFERENCES Gender(ID),
      Employee_No VARCHAR(20),
      YearOfPassing INT,
      MaritalStatus VARCHAR(20)
    );
  END

  IF OBJECT_ID('BorrowedBooks', 'U') IS NULL
  BEGIN
    CREATE TABLE BorrowedBooks
    (
      ID INT PRIMARY KEY IDENTITY(1,1),
      UserID INT FOREIGN KEY REFERENCES Member(ID),
      EmployeeID INT FOREIGN KEY REFERENCES Employee(ID),
      BookID INT FOREIGN KEY REFERENCES Book(ID),
      BorrowDate DATETIME NOT NULL,
      ReturnDate DATETIME,
	    Borrowday  INT
    );
  END

  IF OBJECT_ID('RelationshipType', 'U') IS NULL
  BEGIN
    CREATE TABLE RelationshipType
    (
      ID           INT PRIMARY KEY FOREIGN KEY REFERENCES Member(ID),
	    identifier   int FOREIGN KEY REFERENCES Member(ID),
      Description  varchar(500)
    );
  END
END;
GO
EXEC SA_TABLE;
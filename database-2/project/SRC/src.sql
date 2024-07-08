USE OP_database
GO

create table Branch_type
(
    ID int primary key identity(1,1),
    brnch_type varchar(20) 
)

create table Branch
(
	ID int primary key identity(1,1),
	[Name] varchar(200),
	[Address] varchar(500),
	BranchCode int UNIQUE,
	Phone varchar(20),
	Start_Date DATE,
	END_Date   DAte,
    brnch_type_id int foreign key references Branch_type(ID)
)

create table Account_Info
(
    ID int primary key identity(1,1),
    Name varchar(50),
    phone varchar(50),
    address varchar(200)
)

create table Account
(
    ID int primary key identity(1,1),
    OpenDate date,
    CloseDate date,
    Balance decimal(18,2),
    Currency varchar(3),
    Account_Info_ID int foreign key references Account_Info(ID)
)

create table PaymentMethod
(
    ID int primary key identity(1,1),
    PaymentMethod varchar(50),
    ProviderName varchar(100)
)

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
)

create table Gender
(
	ID int primary key identity(1,1),
	Name varchar(200)
)

create table Member
(
	ID int primary key identity(1,1),
	Firstname varchar(200),
	Lastname varchar(200),
	NationalCode varchar(15) UNIQUE,
	[Address] varchar(500),
	Phone varchar(20),
	Registration_Date date,
	Branch_ID int foreign key references Branch(ID),
	Registration_Valid_Date date,
	Gender_ID int foreign key references Gender(ID)
)

create table Category
(
	ID int primary key identity(1,1),
	Name varchar(200) 
)

create table Publisher
(
	ID int primary key identity(1,1),
	[Name] varchar(200),
	Phone varchar(20)
)

create table Editor
(
	ID int primary key identity(1,1),
	Firstname varchar(200),
	Lastname varchar(200)
)

create table [Language]
(
	ID int primary key identity(1,1),
	[Name] varchar(200),
	abbreviation varchar(20)
)

create table Translator
(
	ID int primary key identity(1,1),
	Firstname varchar(200),
	Lastname varchar(200)
)

create table Age_Range
(
	ID int primary key identity(1,1),
	Title varchar(200),
	Description varchar(500)
)

create table Book_title
(
  ID int primary key identity(1,1),
  Title varchar(200)
)

create table Book
(
	ID int primary key identity(1,1),
	ISBN varchar(20) UNIQUE,
	Title_ID int foreign key references Book_title(ID),
	BranchID int foreign key references branch(ID),
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
)

create table Position
(
	ID int primary key identity(1,1),
	Title varchar(200),
	Salary bigint
)

create table Employee
(
	ID int primary key identity(1,1),
	Firstname varchar(200),
	Lastname varchar(200),
	NationalCode varchar(10),
	[Address] varchar(500),
	Phone varchar(20),
	Hire_Date date,
	Branch_ID int foreign key references Branch(ID),
	Position_ID int foreign key references Position(ID),
	Gender_ID int foreign key references Gender(ID),
	Employee_No varchar(20),
	YearOfPassing int,
	MaritalStatus bit
)

CREATE TABLE BorrowedBooks (
    ID              INT PRIMARY KEY identity(1,1),
    UserID          INT FOREIGN KEY REFERENCES Member(ID),
    EmployeeID      INT FOREIGN KEY REFERENCES Employee(ID),
    BookID          INT FOREIGN KEY REFERENCES Book(ID),
    BorrowDate      DATETIME NOT NULL,
    ReturnDate      DATETIME,
	Borrowday		INT
)

CREATE TABLE RelationshipType(

    ID           INT PRIMARY KEY FOREIGN KEY REFERENCES Member(ID),
	identifier   int FOREIGN KEY REFERENCES Member(ID),
    Description  varchar(500)
)
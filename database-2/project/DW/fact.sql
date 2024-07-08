--========================== Fact ====================================

--@@@@@@@@@@@@@@@@@@@ DATA MART1 @@@@@@@@@@@@@@@@@@@@@@

--create schema LendingsDataMart;
--====================== Fact ======================

CREATE TABLE [LendingsDataMart].FactTransaction(
    MemberID       int NOT NULL,
    BookID         int NOT NULL,
    EmployeeID     int NOT NULL, 
    BranchID       int NOT NULL,
    TimeID         int NOT NULL,
    
    BranchSourceID int,
    borrowed_days       int, -- برای چند روز کتاب را قرض گرفته است
    Remaining_same_Book int
);
--=================================================

CREATE TABLE [LendingsDataMart].FactDaily (
    dimBookTitle   int NOT NULL,
    BranchID       int NOT NULL,
    TimeID         int NOT NULL,

    BranchSourceID              int,
    borrowed_books_count        int,
    available_books_count       int,
    numberOfDaysWithoutRequests int,
    return_count                int
);
--=================================================
CREATE TABLE [LendingsDataMart].FactAcc (
    dimBookTitle   int NOT NULL,
    BranchID       int NOT NULL,

    maxreturncount              int,
    minreturncount              int,
    avgreturncount              int,

    maxBooksBorrowed            int,
    minBooksBorrowed            int,
    avgBooksBorrowed            int,
    
    maxavailablebook            int,
    minavailablebook            int,
    avgavailablebook            int,
    
    Total_return_count          int,
    Total_borrowed_books_count  int,
    numberOfDaysWithoutRequests int
);
--=================================================
CREATE TABLE [LendingsDataMart].factLess(
    MemberID          INT NOT NULL,
    Member_identifier INT NOT NULL,
    RelationshipType  INT NOT NULL
);


--@@@@@@@@@@@@@@@@@@@ DATA MART2 @@@@@@@@@@@@@@@@@@@@@

--create schema FinancialDataMart
CREATE TABLE [FinancialDataMart].FinancialTransactionFact (
    BranchID int,
    TimeID INT,
    AccountID int,
    
    BranchSourceID int,
    Income decimal(18,2),
    Expenses decimal(18,2),
    BalanceAfterTransaction decimal(18,2)
);
--====================================================================
CREATE TABLE [FinancialDataMart].FinancialDailyFact(
    BranchID int,
    TimeID INT,
    AccountID int,
    
    BranchSourceID int,
    Balance          decimal(18,2),
    TotalDailyIncome decimal(18,2),
    TotalDailyExpenses decimal(18,2),
    MaxDailyExpenses decimal(18,2),
    MinDailyExpenses decimal(18,2),
    MaxDailyIncome decimal(18,2),
    MinDailyIncome decimal(18,2),
    DaysWithoutIncome int,
    DaysWithoutExpenses int
);
--====================================================================
CREATE TABLE [FinancialDataMart].FinancialAccFact(
    BranchID int,
    AccountID int,

    MaxExpenses decimal(18,2),
    MinExpenses decimal(18,2),
    MaxIncome decimal(18,2),
    MinIncome decimal(18,2),
    TotalIncome decimal(18,2),
    TotalExpenses decimal(18,2),
    DaysWithoutIncome int,
    DaysWithoutExpenses int
);
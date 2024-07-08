CREATE TABLE Branch (
    BranchCode     INT PRIMARY KEY,
    BranchName     VARCHAR(255),
    SupervisorCode INT,
    FOREIGN KEY (SupervisorCode) REFERENCES Supervisor(SupervisorCode)
);

CREATE TABLE Supervisor (
    SupervisorCode        INT PRIMARY KEY,
    SupervisorDescription VARCHAR(255),
    ProvinceCode          INT,
    FOREIGN KEY (ProvinceCode) REFERENCES Province(ProvinceCode)
);

CREATE TABLE Province (
    ProvinceCode        INT PRIMARY KEY,
    ProvinceDescription VARCHAR(255)
);

CREATE TABLE Loan (
    LoanNumber   INT PRIMARY KEY,
    CustomerID   INT,
    LoanSubType  INT,
    BranchCode   INT,
    CurrencyCode INT,
    ApprovalDate DATE,
    Amount       DECIMAL(18,2),
    LoanTerm     INT,
    Status       VARCHAR(255),
    FOREIGN KEY (CustomerID)   REFERENCES Customer(CustomerID),
    FOREIGN KEY (LoanSubType)  REFERENCES LoanType(LoanSubType),
    FOREIGN KEY (BranchCode)   REFERENCES Branch(BranchCode),
    FOREIGN KEY (CurrencyCode) REFERENCES Currency(CurrencyCode)
);

CREATE TABLE Installment (
    LoanNumber        INT,
    InstallmentNumber INT,
    DueDate           DATE,
    PrincipalAmount   DECIMAL(18,2),
    InterestAmount    DECIMAL(18,2),
    PRIMARY KEY (LoanNumber, InstallmentNumber),
    FOREIGN KEY (LoanNumber) REFERENCES Loan(LoanNumber) 
);

CREATE TABLE Customer (
    CustomerID   INT PRIMARY KEY,
    CustomerName VARCHAR(255),
    BranchCode   INT,
    CustomerType INT,
    NationalID   VARCHAR(20),
    Occupation   VARCHAR(255),
    PhoneNumber  VARCHAR(20),
    FOREIGN KEY (BranchCode)   REFERENCES Branch(BranchCode),
    FOREIGN KEY (CustomerType) REFERENCES CustomerType(CustomerType)
);

CREATE TABLE LoanType (
    LoanSubType            INT PRIMARY KEY,
    LoanSubTypeDescription VARCHAR(255),
    LoanType               INT,
    LoanTypeDescription    VARCHAR(255) 
);

CREATE TABLE Currency (
    CurrencyCode        INT PRIMARY KEY,
    CurrencyDescription VARCHAR(255)
);

CREATE TABLE CustomerType (
    CustomerType            INT PRIMARY KEY,
    CustomerTypeDescription VARCHAR(255)
);

CREATE TABLE CustomerLoanRelationship (
    CustomerID       INT,
    LoanNumber       INT,
    RelationshipType INT,
    PRIMARY KEY (CustomerID, LoanNumber),
    FOREIGN KEY (CustomerID)       REFERENCES Customer(CustomerID),
    FOREIGN KEY (LoanNumber)       REFERENCES Loan(LoanNumber),
    FOREIGN KEY (RelationshipType) REFERENCES RelationshipType(RelationshipType)
);

CREATE TABLE RelationshipType (
    RelationshipType            INT PRIMARY KEY,
    RelationshipTypeDescription VARCHAR(255)
);

CREATE TABLE BankPayment (
    LoanNumber      INT,
    PaymentDate     DATE,
    PaymentAmount   DECIMAL(18,2),
    PRIMARY KEY (LoanNumber, PaymentDate),
    FOREIGN KEY (LoanNumber) REFERENCES Loan(LoanNumber)
);

CREATE TABLE CustomerPayment (
    LoanNumber        INT,
    InstallmentNumber INT,
    PaymentDate       DATE,
    PrincipalPayment  DECIMAL(18,2),
    InterestPayment   DECIMAL(18,2),
    PenaltyPayment    DECIMAL(18,2),
    PRIMARY KEY (LoanNumber, InstallmentNumber, PaymentDate),
    FOREIGN KEY (LoanNumber, InstallmentNumber) REFERENCES Installment(LoanNumber, InstallmentNumber)
);
--=======================================================================
INSERT INTO Province (ProvinceCode, ProvinceDescription) VALUES
(1, 'Tehran'), (2, 'Khorasan Razavi'), (3, 'Isfahan');

INSERT INTO Supervisor (SupervisorCode, SupervisorDescription, ProvinceCode) VALUES
(101, 'John Smith', 1), (102, 'Alice Johnson', 2), (103, 'Bob Williams', 3);

INSERT INTO Branch (BranchCode, BranchName, SupervisorCode) VALUES
(1001, 'Central Tehran Branch', 101), (1002, 'Mashhad Branch', 102), (1003, 'Isfahan City Branch', 103);

INSERT INTO CustomerType (CustomerType, CustomerTypeDescription) VALUES 
(1, 'Individual'), (2, 'Company');

INSERT INTO Customer (CustomerID, CustomerName, BranchCode, CustomerType, NationalID, Occupation, PhoneNumber) VALUES
(2001, 'Mohammad Reza', 1001, 1, '1234567890', 'Engineer', '09121234567'),
(2002, 'Fatima Zahra', 1002, 1, '9876543210', 'Teacher', '09159876543'),
(2003, 'ABC Company', 1003, 2, '1112223334', 'Technology', '03131234567');

INSERT INTO Currency (CurrencyCode, CurrencyDescription) VALUES
(1, 'Rial'), (2, 'US Dollar');

INSERT INTO LoanType (LoanSubType, LoanSubTypeDescription, LoanType, LoanTypeDescription) VALUES
(1, 'Personal Loan', 10, 'Consumer Loans'),
(2, 'Home Loan', 20, 'Mortgage Loans');

INSERT INTO Loan (LoanNumber, CustomerID, LoanSubType, BranchCode, CurrencyCode, ApprovalDate, Amount, LoanTerm, Status) VALUES 
(3001, 2001, 1, 1001, 1, '2023-01-15', 10000000.00, 36, 'Active'),
(3002, 2002, 2, 1002, 1, '2023-02-20', 50000000.00, 60, 'Active');

INSERT INTO Installment (LoanNumber, InstallmentNumber, DueDate, PrincipalAmount, InterestAmount) VALUES
(3001, 1, '2023-02-15', 300000.00, 50000.00),
(3001, 2, '2023-03-15', 300000.00, 45000.00),
(3002, 1, '2023-03-20', 800000.00, 100000.00);

INSERT INTO RelationshipType (RelationshipType, RelationshipTypeDescription) VALUES
(1, 'Guarantor'), (2, 'Co-borrower');

INSERT INTO CustomerLoanRelationship (CustomerID, LoanNumber, RelationshipType) VALUES
(2003, 3002, 1);

INSERT INTO BankPayment (LoanNumber, PaymentDate, PaymentAmount) VALUES
(3001, '2023-02-10', 350000.00);

INSERT INTO CustomerPayment (LoanNumber, InstallmentNumber, PaymentDate, PrincipalPayment, InterestPayment, PenaltyPayment) VALUES
(3001, 1, '2023-02-15', 300000.00, 50000.00, 0.00),
(3002, 1, '2023-03-20', 800000.00, 100000.00, 0.00); 

--================================ Dim ==================================
CREATE TABLE dimBranch(
    BranchCode              INT PRIMARY KEY,
    BranchName              VARCHAR(255),
    SupervisorCode          INT,
    Supervisor_Description  VARCHAR(255),
    Supervisor_ProvinceCode INT,
    Province_Description    VARCHAR(255)
);

CREATE TABLE dimLoan (
    LoanNumber                      INT PRIMARY KEY,
    CustomerID                      INT,
    LoanSubType                     INT,
    BranchCode                      INT,
    CurrencyCode                    INT,
    ApprovalDate                    DATE,
    Amount                          DECIMAL(18,2),
    LoanTerm                        INT,
    Status                          VARCHAR(255),
    LoanType_LoanSubTypeDescription VARCHAR(255),
    LoanType_LoanType               INT,
    LoanType_LoanTypeDescription    VARCHAR(255),
    Currency_Description            VARCHAR(255),
    Customer_Name                   VARCHAR(255)
);
CREATE TABLE dimLoanType (
    LoanSubType            INT PRIMARY KEY,
    LoanSubTypeDescription VARCHAR(255),
    LoanType               INT,
    LoanTypeDescription    VARCHAR(255) 
);
CREATE TABLE dimInstallment (
    InstallmentNumber INT PRIMARY KEY,
    DueDate           DATE,
    PrincipalAmount   DECIMAL(18,2),
    InterestAmount    DECIMAL(18,2),
    LoanNumber        INT,
    Loan_CustomerID   INT,
    Loan_LoanSubType  INT,
    Loan_BranchCode   INT,
    Loan_CurrencyCode INT,
    Loan_ApprovalDate DATE,
    Loan_Amount       DECIMAL(18,2),
    Loan_LoanTerm     INT,
    Loan_Status       VARCHAR(255)
);

CREATE TABLE dimCustomer (
    surg_key                 INT PRIMARY KEY IDENTITY (1,1),
    CustomerID               INT,
    CustomerName             VARCHAR(255),
    BranchCode               INT,
    CustomerType             INT,
    NationalID               VARCHAR(20),
    Occupation               VARCHAR(255),
    PhoneNumber              VARCHAR(20),
    StartDate                DATE NOT NULL,
    EndDate                  DATE,
    cur_flag                 BIT,
    CustomerType_Description VARCHAR(255)
);

CREATE TABLE dimRelationship (
    RelationshipType            INT PRIMARY KEY,
    RelationshipTypeDescription VARCHAR(255)
);

CREATE TABLE dimTime (
    Key_Date        DATE PRIMARY KEY,
    Key_Date_Shamsi DATE,
    Year_AD         INT,
    Year_Shamsi     INT,
    Quarter_AD      INT,
    Quarter_Shamsi  INT,
    Month_AD        INT,
    Month_Shamsi    INT,
    Day_Week_AD     INT,
    Day_Week_Shamsi INT
);


--============================ END OF Dim ===============================                                       
--=============================== FACT ==================================

CREATE TABLE Fact_trn_bank(
    LoanNumber          INT,
    BranchCode          INT,
    CustomerID          INT,
    LoanSubType         INT,
    Key_Date            DATE,

    BankPaymentAmount   DECIMAL(18,2),
	Num_of_installments TINYINT,

    FOREIGN KEY (Key_Date)          REFERENCES dimTime(Key_Date),
    FOREIGN KEY (BranchCode)        REFERENCES dimBranch(BranchCode),
    FOREIGN KEY (LoanNumber)        REFERENCES dimLoan(LoanNumber),
    FOREIGN KEY (CustomerID)        REFERENCES dimCustomer(surg_key),
    FOREIGN KEY (LoanSubType)       REFERENCES dimLoanType(LoanSubType)
);

CREATE TABLE Fact_trn_customer(
    LoanNumber            INT,
    BranchCode            INT,
    CustomerID            INT,
    LoanSubType           INT,
    InstallmentNumber     INT,
    Key_Date              DATE,

    PrincipalPayment      DECIMAL(18,2),
    InterestPayment       DECIMAL(18,2),
    PenaltyPayment        DECIMAL(18,2),
	remainingInstallments INT,
    remainingDebtAmount   INT,

    FOREIGN KEY (Key_Date)          REFERENCES dimTime(Key_Date),
    FOREIGN KEY (BranchCode)        REFERENCES dimBranch(BranchCode),
    FOREIGN KEY (LoanNumber)        REFERENCES dimLoan(LoanNumber),
    FOREIGN KEY (CustomerID)        REFERENCES dimCustomer(surg_key),
    FOREIGN KEY (LoanSubType)       REFERENCES dimLoanType(LoanSubType),
    FOREIGN KEY (InstallmentNumber) REFERENCES dimInstallment(InstallmentNumber)
);

--================================================================================
CREATE TABLE Fact_daily_Bank (
    Key_Date DATE,
    BranchCode INT,
    LoanSubType INT,

	loans_issued_count  DECIMAL(18,2),
    BankTotalPayment    DECIMAL(18,2),
	BankMaxPayment      DECIMAL(18,2),
	BankMinPayment      DECIMAL(18,2),
	BankAvgPayment      DECIMAL(18,2), 
	daysWithoutLoans    INT, --Number of days without issuing a loan(in this type)

    FOREIGN KEY (Key_Date) REFERENCES dimTime(Key_Date),
    FOREIGN KEY (BranchCode) REFERENCES dimBranch(BranchCode),
    FOREIGN KEY (LoanSubType) REFERENCES dimLoanType(LoanSubType)
);

CREATE TABLE Fact_daily_customer(
    CustomerID  INT,
    Key_Date    DATE,
    LoanNumber  INT,
    BranchCode  INT,
    LoanSubType INT,

	Total_PrincipalPayment  DECIMAL(18,2),
    Total_InterestPayment   DECIMAL(18,2),
    Total_PenaltyPayment    DECIMAL(18,2),
	max_PrincipalPayment  DECIMAL(18,2),
    max_InterestPayment   DECIMAL(18,2),
    max_PenaltyPayment    DECIMAL(18,2),
	min_PrincipalPayment  DECIMAL(18,2),
    min_InterestPayment   DECIMAL(18,2),
    min_PenaltyPayment    DECIMAL(18,2),

	UnpaidDays                  INT,
	Total_remainingInstallments INT,
    Total_remainingDebtAmount   INT,

    FOREIGN KEY (Key_Date)    REFERENCES dimTime(Key_Date),
    FOREIGN KEY (CustomerID)  REFERENCES dimCustomer(surg_key),
	FOREIGN KEY (BranchCode)  REFERENCES dimBranch(BranchCode),
    FOREIGN KEY (LoanNumber)  REFERENCES dimLoan(LoanNumber),
    FOREIGN KEY (LoanSubType) REFERENCES dimLoanType(LoanSubType)
);

--================================================================================

CREATE TABLE Fact_Acc_Bank (
    BranchCode INT,
    LoanSubType INT,

	Total_loans_issued_count  DECIMAL(18,2), --From the beginning until now
    BankTotalPayment		  DECIMAL(18,2), --From the beginning until now
	BankMaxPayment			  DECIMAL(18,2), --From the beginning until now
	BankMinPayment			  DECIMAL(18,2), --From the beginning until now
	BankAvgPayment			  DECIMAL(18,2), --From the beginning until now 
	daysWithoutLoans		  INT, --Number of days without issuing a loan(in this type), From the beginning until now

    FOREIGN KEY (BranchCode)  REFERENCES dimBranch(BranchCode),
    FOREIGN KEY (LoanSubType) REFERENCES dimLoanType(LoanSubType)
);

CREATE TABLE Fact_Acc_customer(
    CustomerID  INT,
    LoanNumber  INT,
    BranchCode  INT,
    LoanSubType INT,

	Total_PrincipalPayment  DECIMAL(18,2), --From the first donation of this loan until now
    Total_InterestPayment   DECIMAL(18,2), --From the first donation of this loan until now
    Total_PenaltyPayment    DECIMAL(18,2), --From the first donation of this loan until now
	max_PrincipalPayment    DECIMAL(18,2), --From the first donation of this loan until now
    max_InterestPayment		DECIMAL(18,2), --From the first donation of this loan until now
    max_PenaltyPayment		DECIMAL(18,2), --From the first donation of this loan until now
	min_PrincipalPayment	DECIMAL(18,2), --From the first donation of this loan until now
    min_InterestPayment		DECIMAL(18,2), --From the first donation of this loan until now
    min_PenaltyPayment		DECIMAL(18,2), --From the first donation of this loan until now

	UnpaidDays                  INT,
	Total_remainingInstallments INT,
    Total_remainingDebtAmount   INT,

    FOREIGN KEY (CustomerID)  REFERENCES dimCustomer(surg_key),
	FOREIGN KEY (BranchCode)  REFERENCES dimBranch(BranchCode),
    FOREIGN KEY (LoanNumber)  REFERENCES dimLoan(LoanNumber),
    FOREIGN KEY (LoanSubType) REFERENCES dimLoanType(LoanSubType)
);

--================================================================================

CREATE TABLE FACTless(
    CustomerID       INT,
    LoanNumber       INT,
    RelationshipType INT,
    FOREIGN KEY (RelationshipType) REFERENCES dimRelationship(RelationshipType),
    FOREIGN KEY (LoanNumber)       REFERENCES dimLoan(LoanNumber),
    FOREIGN KEY (CustomerID)       REFERENCES dimCustomer(surg_key)
);
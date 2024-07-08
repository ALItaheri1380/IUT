--create schema FinancialDataMart;

CREATE TABLE [FinancialDataMart].log_dm2(
    table_name VARCHAR(100),
    explanation VARCHAR(200),
    startDate  datetime,
    endDate datetime
)


--%%%%%%%%%%%%%%%%% UpdateDimAccount %%%%%%%%%%%%%%%%%
CREATE TABLE [dbo].dimAccountTemp(
    ID INT,
    OpenDate DATETIME,
    CloseDate DATETIME,
    Balance DECIMAL(18, 2),
    Currency VARCHAR(10),
    Name VARCHAR(100),
    Original_phone VARCHAR(20),
    Current_Phone VARCHAR(20),
    Effective_Date DATETIME,
    address VARCHAR(255)
);


--@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

--%%%%%%%%%%%%%%%%% InsertFactDailyCurrent_Finantial %%%%%%%%%%%%%%%%%
CREATE TABLE Library_DW.[FinancialDataMart].[newData](
        BranchID          int,
        TimeID            int,
        AccountID         int,
        TotalDailyIncome  decimal(18,2),
        TotalDailyExpenses decimal(18,2),
        MaxDailyExpenses  decimal(18,2),
        MinDailyExpenses  decimal(18,2),
        MaxDailyIncome    decimal(18,2),
        MinDailyIncome    decimal(18,2)
    );

    CREATE TABLE Library_DW.[FinancialDataMart].[newData2](
        BranchID          int,
        TimeID            int,
        AccountID         int,
        yesterday_Balance int,
        TotalDailyIncome  decimal(18,2),
        TotalDailyExpenses decimal(18,2),
        MaxDailyExpenses  decimal(18,2),
        MinDailyExpenses  decimal(18,2),
        MaxDailyIncome    decimal(18,2),
        MinDailyIncome    decimal(18,2),
		    yesterday_DaysWithoutIncome int,
		    yesterday_DaysWithoutExpenses int
    );

    CREATE TABLE Library_DW.[FinancialDataMart].[result](
		BranchID int,
		TimeID INT,
		AccountID int,
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

	CREATE TABLE Library_DW.[FinancialDataMart].[today](
        BranchID       int,
        TimeID         int,
        AccountID      int, 
        Income         int,
        Expenses       int
    );

	CREATE TABLE Library_DW.[FinancialDataMart].[scd_result](
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


    --%%%%%%%%%%%%%%%%% UpdateFinancialTransactionFact %%%%%%%%%%%%%%%%%
CREATE TABLE [FinancialDataMart].TempTransactions ( 
    ID                 INT, 
    TransactionDate    DATETIME, 
    TransactionType    VARCHAR(50), 
    Amount             DECIMAL(18, 2), 
    BrancID            INT, 
    Account_ID         INT, 
    PaymentMethod_ID   INT, 
    Description        NVARCHAR(255) 
); 
CREATE TABLE [FinancialDataMart].Temp2Transactions ( 
    ID                    INT, 
    TransactionDate       DATETIME, 
    TransactionType       VARCHAR(255), 
    Amount                DECIMAL(18, 2), 
    Income                DECIMAL(18, 2), 
    Expenses              DECIMAL(18, 2), 
    BrancID               INT, 
    Account_ID            INT, 
    PaymentMethod_ID      INT, 
    Description           NVARCHAR(500), 
    Balance               DECIMAL(18, 2) 
); 
Go 
 
 
CREATE TABLE [FinancialDataMart].temp_FinancialDailyFact ( 
  BranchID int,  
  TimeID INT,  
  AccountID int,  
     
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
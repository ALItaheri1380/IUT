INSERT INTO Gender (Name) VALUES ('Male');
INSERT INTO Gender (Name) VALUES ('Female');
INSERT INTO Gender (Name) VALUES ('Other');

INSERT INTO Branch_type (brnch_type) VALUES ('Main');
INSERT INTO Branch_type (brnch_type) VALUES ('Sub');
INSERT INTO Branch_type (brnch_type) VALUES ('Regional');

INSERT INTO Age_Range (Title, Description) VALUES ('Children', 'Suitable for ages 0-12');
INSERT INTO Age_Range (Title, Description) VALUES ('Teen', 'Suitable for ages 13-19');
INSERT INTO Age_Range (Title, Description) VALUES ('Adult', 'Suitable for ages 20-35');
INSERT INTO Age_Range (Title, Description) VALUES ('Middle Age', 'Suitable for ages 36-55');
INSERT INTO Age_Range (Title, Description) VALUES ('Senior', 'Suitable for ages 55+');

INSERT INTO Position (Title, Salary) VALUES ('Manager', 80000);
INSERT INTO Position (Title, Salary) VALUES ('Assistant Manager', 60000);
INSERT INTO Position (Title, Salary) VALUES ('Clerk', 40000);

INSERT INTO Category (Name) VALUES ('Fiction');
INSERT INTO Category (Name) VALUES ('Non-Fiction');
INSERT INTO Category (Name) VALUES ('Science');
INSERT INTO Category (Name) VALUES ('History');

INSERT INTO Publisher ([Name], Phone) VALUES ('Penguin Books', '123-456-7890');
INSERT INTO Publisher ([Name], Phone) VALUES ('HarperCollins', '098-765-4321');

INSERT INTO [Language] ([Name], abbreviation) VALUES ('English', 'EN');
INSERT INTO [Language] ([Name], abbreviation) VALUES ('French', 'FR');
INSERT INTO [Language] ([Name], abbreviation) VALUES ('Spanish', 'ES');

INSERT INTO PaymentMethod (PaymentMethod, ProviderName) VALUES ('Credit Card', 'Visa');
INSERT INTO PaymentMethod (PaymentMethod, ProviderName) VALUES ('Credit Card', 'MasterCard');
INSERT INTO PaymentMethod (PaymentMethod, ProviderName) VALUES ('Bank Transfer', 'Local Bank');

INSERT INTO Translator (Firstname, Lastname) VALUES ('John', 'Doe');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Jane', 'Smith');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Michael', 'Brown');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Emily', 'Davis');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Christopher', 'Wilson');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Amanda', 'Johnson');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Daniel', 'Lee');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Laura', 'White');
INSERT INTO Translator (Firstname, Lastname) VALUES ('James', 'Harris');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Sophia', 'Clark');
INSERT INTO Translator (Firstname, Lastname) VALUES ('William', 'Lewis');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Olivia', 'Walker');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Ethan', 'Hall');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Isabella', 'Allen');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Mason', 'Young');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Charlotte', 'Hernandez');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Logan', 'King');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Mia', 'Wright');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Benjamin', 'Lopez');
INSERT INTO Translator (Firstname, Lastname) VALUES ('Ava', 'Hill');


DECLARE @i INT = 1;
WHILE @i <= 4
BEGIN
    INSERT INTO Branch ([Name], [Address], BranchCode, Phone, Start_Date, END_Date, brnch_type_id)
    VALUES (
        'Branch' + CAST(@i AS VARCHAR),
        'Address ' + CAST(@i AS VARCHAR),
        ABS(CHECKSUM(NEWID()) % 1000) + 1000,
        'Phone ' + CAST(@i AS VARCHAR),
        DATEADD(YEAR, -5, GETDATE()),
        NULL,
        ABS(CHECKSUM(NEWID()) % 3) + 1
    );
    SET @i = @i + 1;
END

DECLARE @i INT = 1;
WHILE @i <= 2000
BEGIN
    INSERT INTO Member (Firstname, Lastname, NationalCode, [Address], Phone, Registration_Date, Branch_ID, Registration_Valid_Date, Gender_ID)
    VALUES (
        'FirstName' + CAST(@i AS VARCHAR),
        'LastName' + CAST(@i AS VARCHAR),
        RIGHT('0000000000' + CAST(ABS(CHECKSUM(NEWID())) % 10000000000 AS VARCHAR), 10),
        'Address ' + CAST(@i AS VARCHAR),
        'Phone ' + CAST(@i AS VARCHAR),
        DATEADD(DAY, -ABS(CHECKSUM(NEWID()) % 365), GETDATE()),
        ABS(CHECKSUM(NEWID()) % 4) + 1,
        DATEADD(YEAR, 1, DATEADD(DAY, -ABS(CHECKSUM(NEWID()) % 365), GETDATE())),
        ABS(CHECKSUM(NEWID()) % 3) + 1
    );
    SET @i = @i + 1;
END

DECLARE @i INT = 1;
WHILE @i <= 50
BEGIN
    INSERT INTO Employee (Firstname, Lastname, NationalCode, [Address], Phone, Hire_Date, Branch_ID, Position_ID, Gender_ID, Employee_No, YearOfPassing, MaritalStatus)
    VALUES (
        'FirstName' + CAST(@i AS VARCHAR),
        'LastName' + CAST(@i AS VARCHAR),
        RIGHT('0000000000' + CAST(ABS(CHECKSUM(NEWID())) % 10000000000 AS VARCHAR), 10),
        'Address ' + CAST(@i AS VARCHAR),
        'Phone ' + CAST(@i AS VARCHAR),
        DATEADD(DAY, -ABS(CHECKSUM(NEWID()) % 3650), GETDATE()),
        ABS(CHECKSUM(NEWID()) % 4) + 1,
        ABS(CHECKSUM(NEWID()) % 3) + 1,
        ABS(CHECKSUM(NEWID()) % 3) + 1,
        'E' + RIGHT('0000' + CAST(ABS(CHECKSUM(NEWID())) % 10000 AS VARCHAR), 4),
        2000 + ABS(CHECKSUM(NEWID()) % 24),
        CAST(ROUND(RAND(), 0) AS BIT)
    );
    SET @i = @i + 1;
END

DECLARE @i INT = 1;
DECLARE @max INT = 100;
WHILE @i <= @max
BEGIN
    INSERT INTO Editor (Firstname, Lastname)
    VALUES (
        CHAR(65 + ABS(CHECKSUM(NEWID()) % 26)) + CHAR(97 + ABS(CHECKSUM(NEWID()) % 26)) + CHAR(97 + ABS(CHECKSUM(NEWID()) % 26)),
        CHAR(65 + ABS(CHECKSUM(NEWID()) % 26)) + CHAR(97 + ABS(CHECKSUM(NEWID()) % 26)) + CHAR(97 + ABS(CHECKSUM(NEWID()) % 26))
    );
    SET @i = @i + 1;
END

DECLARE @i INT = 1;
WHILE @i <= 25
BEGIN
    INSERT INTO Book_title (Title)
    VALUES ('Title ' + CAST(@i AS VARCHAR));
    SET @i = @i + 1;
END

DECLARE @j INT = 1;
WHILE @j <= 1000000
BEGIN
    INSERT INTO Book (ISBN, Title_ID, BranchID, [Description], [Year], Publisher_ID, Category_ID, Age_Range_ID, Translator_ID, Editor_ID, Language_ID, RepublicationNo, NumOfPages, NumOfEditions, NumOfCopiesPrinted)
    VALUES (
        RIGHT('0000000000000' + CAST(ABS(CHECKSUM(NEWID())) % 1000000000000 AS VARCHAR), 13), 
        ABS(CHECKSUM(NEWID()) % 25) + 1, 
        ABS(CHECKSUM(NEWID()) % 4) + 1,
        'Description ' + CAST(@j AS VARCHAR), 
        2000 + ABS(CHECKSUM(NEWID()) % 24), 
        ABS(CHECKSUM(NEWID()) % 2) + 1,
        ABS(CHECKSUM(NEWID()) % 4) + 1, 
        ABS(CHECKSUM(NEWID()) % 5) + 1, 
        ABS(CHECKSUM(NEWID()) % 20) + 1, 
        ABS(CHECKSUM(NEWID()) % 100) + 1, 
        ABS(CHECKSUM(NEWID()) % 3) + 1,
        ABS(CHECKSUM(NEWID()) % 5) + 1, 
        ABS(CHECKSUM(NEWID()) % 1000) + 100,
        ABS(CHECKSUM(NEWID()) % 10) + 1, 
        ABS(CHECKSUM(NEWID()) % 10000) + 1000 
    );

    SET @j = @j + 1;
END


DECLARE @i INT = 1;
DECLARE @max INT = 500000; 

WHILE @i <= @max
BEGIN
    INSERT INTO BorrowedBooks (UserID, EmployeeID, BookID, BorrowDate, ReturnDate, Borrowday)
    VALUES (
        ABS(CHECKSUM(NEWID()) % 2000) + 1,      
        ABS(CHECKSUM(NEWID()) % 50) + 1,       
        ABS(CHECKSUM(NEWID()) % 1000000) + 1,    
        DATEADD(MINUTE, ABS(CHECKSUM(NEWID()) % 1440), DATEADD(DAY, ABS(CHECKSUM(NEWID()) % 365), GETDATE())), 
        DATEADD(MINUTE, ABS(CHECKSUM(NEWID()) % 1440), DATEADD(DAY, ABS(CHECKSUM(NEWID()) % 30), DATEADD(DAY, ABS(CHECKSUM(NEWID()) % 365), GETDATE()))), 
        ABS(CHECKSUM(NEWID()) % 8) + 7 
    );

    SET @i = @i + 1;
END


DECLARE @counter INT = 1;
WHILE @counter <= 100
BEGIN
    INSERT INTO Account_Info (Name, phone, address)
    VALUES (CONCAT('Name_', @counter), CONCAT('555-1234-', @counter), CONCAT('Address_', @counter));
    SET @counter = @counter + 1;
END

DECLARE @counter INT = 1;
DECLARE @AccountInfoID INT = 1;

WHILE @counter <= 100
BEGIN
    INSERT INTO Account (OpenDate, CloseDate, Balance, Currency, Account_Info_ID)
    VALUES (
        DATEADD(DAY, -@counter, GETDATE()),  
        NULL,  
        ROUND(RAND() * 8000000, 2),  
        'USD', 
        @AccountInfoID
    );
    
    SET @counter = @counter + 1;
    SET @AccountInfoID = @AccountInfoID + 1;
END

DECLARE @i INT = 1;
DECLARE @maxTransactions INT = 1000000;
WHILE @i <= @maxTransactions
BEGIN
    INSERT INTO [Transaction] 
    (TransactionDate, TransactionType, Amount, Branch_ID, Account_ID, PaymentMethod_ID, Description)
    VALUES (
        DATEADD(MINUTE, ABS(CHECKSUM(NEWID()) % 1440), DATEADD(DAY, ABS(CHECKSUM(NEWID()) % 365), GETDATE())), 
        CASE ABS(CHECKSUM(NEWID()) % 3) 
            WHEN 0 THEN 'Deposit' 
            WHEN 1 THEN 'Withdrawal' 
            ELSE 'Transfer' 
        END, 
        ABS(CHECKSUM(NEWID()) % 200) + 1, 
        ABS(CHECKSUM(NEWID()) % 4) + 1, 
        (SELECT TOP 1 ID FROM Account ORDER BY NEWID()), 
        ABS(CHECKSUM(NEWID()) % 3) + 1, 
        'Description for transaction ' + CAST(@i AS VARCHAR) 
    );
    SET @i = @i + 1;
END


INSERT INTO RelationshipType (ID, identifier, Description) VALUES (1, 2, 'Friend');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (2, 3, 'Family');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (3, 4, 'Colleague');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (4, 5, 'Neighbor');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (5, 6, 'Classmate');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (6, 7, 'Relative');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (7, 8, 'Acquaintance');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (8, 9, 'Mentor');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (9, 10, 'Teammate');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (10, 11, 'Roommate');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (11, 12, 'Co-worker');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (12, 13, 'Business Partner');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (13, 14, 'Spouse');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (14, 15, 'Sibling');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (15, 16, 'Parent');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (16, 17, 'Child');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (17, 18, 'Grandparent');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (18, 19, 'Grandchild');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (19, 20, 'Cousin');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (20, 21, 'Uncle/Aunt');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (21, 22, 'Nephew/Niece');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (22, 23, 'In-law');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (23, 24, 'Friend of Family');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (24, 25, 'Former Colleague');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (25, 26, 'Ex-Spouse');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (26, 27, 'Former Neighbor');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (27, 28, 'Former Classmate');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (28, 29, 'Former Teammate');
INSERT INTO RelationshipType (ID, identifier, Description) VALUES (29, 30, 'Former Roommate');



WITH RandomRows AS (
  SELECT TOP 400000
    ID 
  FROM [Transaction]
  ORDER BY NEWID()
)
UPDATE [Transaction]
SET Amount = Amount * -1
FROM RandomRows
WHERE [Transaction].ID = RandomRows.ID;

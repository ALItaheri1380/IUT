USE Library_SA
Go

create or alter procedure ETL
AS
BEGIN
	ALTER TABLE [Library_SA].[dbo].[BorrowedBooks] NOCHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Employee] NOCHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Branch] NOCHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Account] NOCHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Transaction] NOCHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Book] NOCHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Member] NOCHECK CONSTRAINT ALL;

	DELETE FROM [Library_SA].[dbo].[Employee];
	DELETE FROM [Library_SA].[dbo].[Account];
	DELETE FROM [Library_SA].[dbo].[Account_Info];
	DELETE FROM [Library_SA].[dbo].[Branch];
	DELETE FROM [Library_SA].[dbo].[Branch_type];
	DELETE FROM [Library_SA].[dbo].[Position];
	DELETE FROM [Library_SA].[dbo].[Gender];
	DELETE FROM [Library_SA].[dbo].[Category];
	DELETE FROM [Library_SA].[dbo].[Publisher];
	DELETE FROM [Library_SA].[dbo].[Editor];
	DELETE FROM [Library_SA].[dbo].[Translator];
	DELETE FROM [Library_SA].[dbo].[Language];
	DELETE FROM [Library_SA].[dbo].[Age_Range];
	DELETE FROM [Library_SA].[dbo].[PaymentMethod];
	DELETE FROM [Library_SA].[dbo].[RelationshipType];

	ALTER TABLE [Library_SA].[dbo].[BorrowedBooks] CHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Employee] CHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Branch] CHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Account] CHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Transaction] CHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Book] CHECK CONSTRAINT ALL;
	ALTER TABLE [Library_SA].[dbo].[Member] CHECK CONSTRAINT ALL;


	SET IDENTITY_INSERT [Library_SA].[dbo].[Branch_type] ON;
	INSERT INTO [Library_SA].[dbo].[Branch_type] (id, brnch_type)
	SELECT id, brnch_type
	FROM [OP_database].[dbo].[Branch_type];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Branch_type] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Branch_type]', RESEED, 0);


	SET IDENTITY_INSERT [Library_SA].[dbo].[Branch] ON;
	INSERT INTO [Library_SA].[dbo].[Branch] (ID, Name, Address, BranchCode, Phone, Start_Date, END_Date, brnch_type_id)
	SELECT ID, Name, Address, BranchCode, Phone, Start_Date, END_Date, brnch_type_id
	FROM [OP_database].[dbo].[Branch];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Branch] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Branch]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Account_Info] ON;
	INSERT INTO [Library_SA].[dbo].[Account_Info] (ID, Name, phone, address)
	SELECT ai.ID, ai.Name, ai.phone, ai.address
	FROM [OP_database].[dbo].[Account_Info] ai;
	SET IDENTITY_INSERT [Library_SA].[dbo].[Account_Info] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Account_Info]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Gender] ON;
	INSERT INTO [Library_SA].[dbo].[Gender] (ID, Name)
	SELECT ID, Name
	FROM [OP_database].[dbo].[Gender];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Gender] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Gender]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Category] ON;
	INSERT INTO [Library_SA].[dbo].[Category] (ID, Name)
	SELECT ID, Name
	FROM [OP_database].[dbo].[Category];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Category] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Category]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Publisher] ON;
	INSERT INTO [Library_SA].[dbo].[Publisher] (ID, [Name], Phone)
	SELECT ID, [Name], Phone
	FROM [OP_database].[dbo].[Publisher];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Publisher] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Publisher]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Editor] ON;
	INSERT INTO [Library_SA].[dbo].[Editor] (ID, FullName)
	SELECT ID, Firstname + ' ' + Lastname
	FROM [OP_database].[dbo].[Editor];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Editor] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Editor]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Translator] ON;
	INSERT INTO [Library_SA].[dbo].[Translator] (ID, FullName)
	SELECT ID, Firstname + ' ' + Lastname
	FROM [OP_database].[dbo].[Translator];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Translator] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Translator]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Language] ON;
	INSERT INTO [Library_SA].[dbo].[Language] (ID, [Name], abbreviation)
	SELECT ID, [Name], abbreviation
	FROM [OP_database].[dbo].[Language];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Language] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Language]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Age_Range] ON;
	INSERT INTO [Library_SA].[dbo].[Age_Range] (ID, Title, Description)
	SELECT ID, Title, Description
	FROM [OP_database].[dbo].[Age_Range];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Age_Range] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Age_Range]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[PaymentMethod] ON;
	INSERT INTO [Library_SA].[dbo].[PaymentMethod] (ID, PaymentMethod, ProviderName)
	SELECT ID, PaymentMethod, ProviderName
	FROM [OP_database].[dbo].[PaymentMethod];
	SET IDENTITY_INSERT [Library_SA].[dbo].[PaymentMethod] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[PaymentMethod]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Position] ON;
	INSERT INTO [Library_SA].[dbo].[Position] (ID, Title, Salary)
	SELECT ID, Title, Salary
	FROM [OP_database].[dbo].[Position];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Position] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Position]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Account] ON;
	INSERT INTO [Library_SA].[dbo].[Account] (ID, OpenDate, CloseDate, Balance, Currency, Account_Info_ID)
	SELECT ID, OpenDate, CloseDate, Balance, Currency, Account_Info_ID
	FROM [OP_database].[dbo].[Account];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Account] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Account]', RESEED, 0);
	--=====================================================================--
	SET IDENTITY_INSERT [Library_SA].[dbo].[Member] ON;
	MERGE INTO [Library_SA].[dbo].[Member] AS Target
	USING [OP_database].[dbo].[Member] AS Source
	ON Target.NationalCode = Source.NationalCode
	WHEN MATCHED THEN
		UPDATE SET
			Target.Fullname = Source.Firstname + ' ' + Source.Lastname,
			Target.[Address] = Source.[Address],
			Target.Phone = Source.Phone,
			Target.Registration_Date = Source.Registration_Date,
			Target.Branch_ID = Source.Branch_ID,
			Target.Registration_Valid_Date = Source.Registration_Valid_Date,
			Target.Gender_ID = Source.Gender_ID
	WHEN NOT MATCHED BY TARGET THEN
		INSERT (ID, Fullname, NationalCode, [Address], Phone, Registration_Date, Branch_ID, Registration_Valid_Date, Gender_ID)
		VALUES (Source.ID, Source.Firstname + ' ' + Source.Lastname, Source.NationalCode, Source.[Address], Source.Phone, Source.Registration_Date, Source.Branch_ID, Source.Registration_Valid_Date, Source.Gender_ID)
	WHEN NOT MATCHED BY Source THEN DELETE;
	SET IDENTITY_INSERT [Library_SA].[dbo].[Member] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Member]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Employee] ON;
	INSERT INTO [Library_SA].[dbo].[Employee] 
	(ID, FullName, NationalCode, [Address], Phone, Hire_Date, Branch_ID, Position_ID, Gender_ID, Employee_No, YearOfPassing, MaritalStatus)
	SELECT 
	  ID,
	  CONCAT(Firstname, ' ', Lastname) AS FullName, 
	  NationalCode, 
	  [Address], 
	  Phone, 
	  Hire_Date, 
	  Branch_ID, 
	  Position_ID, 
	  Gender_ID, 
	  Employee_No, 
	  YearOfPassing, 
	  CASE 
		WHEN MaritalStatus = 1 THEN 'Married' 
		ELSE 'Single' 
	  END AS MaritalStatus
	FROM [OP_database].[dbo].[Employee];
	SET IDENTITY_INSERT [Library_SA].[dbo].[Employee] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[Employee]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Book_title] ON;
    MERGE INTO [Library_SA].[dbo].[Book_title] AS Target
    USING [OP_database].[dbo].[Book_title] AS Source
    ON Target.Title = Source.Title
    WHEN MATCHED THEN 
        UPDATE SET Target.Title = Source.Title
    WHEN NOT MATCHED BY TARGET THEN
        INSERT (ID, Title)
        VALUES (Source.ID, Source.Title)
	WHEN NOT MATCHED BY Source THEN DELETE;
    SET IDENTITY_INSERT [Library_SA].[dbo].[Book_title] OFF;
    DBCC CHECKIDENT ('[Library_SA].[dbo].[Book_title]', RESEED, 0);

    SET IDENTITY_INSERT [Library_SA].[dbo].[Book] ON;
    MERGE INTO [Library_SA].[dbo].[Book] AS Target
    USING [OP_database].[dbo].[Book] AS Source
    ON Target.ISBN = Source.ISBN
    WHEN MATCHED AND (
        Target.Title_ID <> Source.Title_ID OR
		Target.BranchID <> Source.BranchID OR
        Target.[Description] <> Source.[Description] OR
        Target.[Year] <> Source.[Year] OR
        Target.Publisher_ID <> Source.Publisher_ID OR
        Target.Category_ID <> Source.Category_ID OR
        Target.Age_Range_ID <> Source.Age_Range_ID OR
        Target.Translator_ID <> Source.Translator_ID OR
        Target.Editor_ID <> Source.Editor_ID OR
        Target.Language_ID <> Source.Language_ID OR
        Target.RepublicationNo <> Source.RepublicationNo OR
        Target.NumOfPages <> Source.NumOfPages OR
        Target.NumOfEditions <> Source.NumOfEditions OR
        Target.NumOfCopiesPrinted <> Source.NumOfCopiesPrinted
    ) THEN
        UPDATE SET
            Target.Title_ID = Source.Title_ID,
			Target.BranchID = Source.BranchID,
            Target.[Description] = Source.[Description],
            Target.[Year] = Source.[Year],
            Target.Publisher_ID = Source.Publisher_ID,
            Target.Category_ID = Source.Category_ID,
            Target.Age_Range_ID = Source.Age_Range_ID,
            Target.Translator_ID = Source.Translator_ID,
            Target.Editor_ID = Source.Editor_ID,
            Target.Language_ID = Source.Language_ID,
            Target.RepublicationNo = Source.RepublicationNo,
            Target.NumOfPages = Source.NumOfPages,
            Target.NumOfEditions = Source.NumOfEditions,
            Target.NumOfCopiesPrinted = Source.NumOfCopiesPrinted
    WHEN NOT MATCHED BY TARGET THEN
        INSERT (ID, ISBN, Title_ID, BranchID, [Description], [Year], Publisher_ID, Category_ID, Age_Range_ID, Translator_ID, Editor_ID, Language_ID, RepublicationNo, NumOfPages, NumOfEditions, NumOfCopiesPrinted)
        VALUES (Source.ID, Source.ISBN, Source.Title_ID, BranchID, Source.[Description], Source.[Year], Source.Publisher_ID, Source.Category_ID, Source.Age_Range_ID, Source.Translator_ID, Source.Editor_ID, Source.Language_ID, Source.RepublicationNo, Source.NumOfPages, Source.NumOfEditions, Source.NumOfCopiesPrinted)
	WHEN NOT MATCHED BY Source THEN DELETE;
    SET IDENTITY_INSERT [Library_SA].[dbo].[Book] OFF;
    DBCC CHECKIDENT ('[Library_SA].[dbo].[Book]', RESEED, 0);

	SET IDENTITY_INSERT [Library_SA].[dbo].[Transaction] ON;

	MERGE INTO [Library_SA].[dbo].[Transaction] AS Target
	USING [OP_database].[dbo].[Transaction] AS Source
	ON 
	Target.TransactionDate = Source.TransactionDate AND 
	Target.TransactionType = Source.TransactionType AND 
	Target.Amount = Source.Amount AND 
	Target.Account_ID = Source.Account_ID AND 
	Target.PaymentMethod_ID = Source.PaymentMethod_ID AND 
	Target.Description = Source.Description AND 
	Target.Branch_ID = Source.Branch_ID
	WHEN MATCHED AND (
	Target.TransactionDate <> Source.TransactionDate OR
	Target.TransactionType <> Source.TransactionType OR
	Target.Amount <> Source.Amount OR
	Target.Account_ID <> Source.Account_ID OR
	Target.PaymentMethod_ID <> Source.PaymentMethod_ID OR
	Target.Description <> Source.Description OR
	Target.Branch_ID <> Source.Branch_ID
	) THEN
	UPDATE SET
		Target.TransactionDate = Source.TransactionDate,
		Target.TransactionType = Source.TransactionType,
		Target.Amount = Source.Amount,
		Target.Account_ID = Source.Account_ID,
		Target.PaymentMethod_ID = Source.PaymentMethod_ID,
		Target.Description = Source.Description,
		Target.Branch_ID = Source.Branch_ID
	WHEN NOT MATCHED BY TARGET THEN
	INSERT (ID, TransactionDate, TransactionType, Amount, Branch_ID, Account_ID, PaymentMethod_ID, Description)
	VALUES (Source.ID, Source.TransactionDate, Source.TransactionType, Source.Amount, Source.Branch_ID, Source.Account_ID, Source.PaymentMethod_ID, Source.Description)
	WHEN NOT MATCHED BY Source THEN DELETE;
	SET IDENTITY_INSERT [Library_SA].[dbo].[Transaction] OFF;

	SET IDENTITY_INSERT [Library_SA].[dbo].[BorrowedBooks] ON;
	MERGE INTO [Library_SA].[dbo].[BorrowedBooks] AS Target
	USING [OP_database].[dbo].[BorrowedBooks] AS Source
	ON Target.UserID = Source.UserID AND Target.EmployeeID = Source.EmployeeID AND Target.BookID = Source.BookID
	WHEN MATCHED AND (
		Target.BorrowDate <> Source.BorrowDate OR
		Target.ReturnDate <> Source.ReturnDate OR
		Target.Borrowday <> Source.Borrowday 
	) THEN
		UPDATE SET
		Target.BorrowDate = Source.BorrowDate,
		Target.ReturnDate = Source.ReturnDate,
		Target.Borrowday = Source.Borrowday  
	WHEN NOT MATCHED BY TARGET THEN
		INSERT (ID, UserID, EmployeeID, BookID, BorrowDate, ReturnDate, Borrowday) 
		VALUES (Source.ID, Source.UserID, Source.EmployeeID, Source.BookID, Source.BorrowDate, Source.ReturnDate, Source.Borrowday)
	WHEN NOT MATCHED BY Source THEN DELETE;
	SET IDENTITY_INSERT [Library_SA].[dbo].[BorrowedBooks] OFF;
	DBCC CHECKIDENT ('[Library_SA].[dbo].[BorrowedBooks]', RESEED, 0);


	MERGE INTO [Library_SA].[dbo].[RelationshipType] AS Target
	USING [OP_database].[dbo].[RelationshipType] AS Source
	ON Target.[ID] = Source.[ID]
	WHEN MATCHED AND (
		Target.[identifier] <> Source.[identifier] OR
		Target.[Description] <> Source.[Description]
	) THEN
		UPDATE SET
			Target.[identifier] = Source.[identifier],
			Target.[Description] = Source.[Description]
	WHEN NOT MATCHED BY TARGET THEN
		INSERT (ID, identifier, Description)
		VALUES (Source.ID, Source.identifier, Source.Description)
	WHEN NOT MATCHED BY Source THEN DELETE;
	
END;
GO
EXEC ETL
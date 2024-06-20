CREATE OR ALTER PROCEDURE Update_dimLoan
AS
BEGIN
    MERGE dimLoan AS Target
    USING (
        SELECT L.LoanNumber, L.CustomerID, L.LoanSubType,
			   L.BranchCode, L.CurrencyCode, L.ApprovalDate,
			   L.Amount, L.LoanTerm, L.Status,

			   LT.LoanSubTypeDescription, LT.LoanType, LT.LoanTypeDescription,

			   CR.CurrencyDescription,

			   CU.CustomerName
        FROM Loan L
                 INNER JOIN LoanType LT ON L.LoanSubType = LT.LoanSubType
                 INNER JOIN Currency CR ON CR.CurrencyCode = L.CurrencyCode
				 INNER JOIN Customer CU ON L.CustomerID = CU.CustomerID
    ) AS Source
    ON (Target.LoanNumber = Source.LoanNumber)

    WHEN MATCHED AND Target.Amount <> Source.Amount THEN
        UPDATE
        SET Target.Amount = Source.Amount

    WHEN NOT MATCHED THEN
        INSERT (LoanNumber, CustomerID, LoanSubType, BranchCode, CurrencyCode, ApprovalDate,
				Amount, LoanTerm, Status, LoanType_LoanSubTypeDescription, LoanType_LoanType,
				LoanType_LoanTypeDescription, Currency_Description, Customer_Name)

        VALUES (Source.LoanNumber, Source.CustomerID, Source.LoanSubType, Source.BranchCode, Source.CurrencyCode,
				Source.ApprovalDate, Source.Amount, Source.LoanTerm, Source.Status, Source.LoanSubTypeDescription,
				Source.LoanType, Source.LoanTypeDescription, Source.CurrencyDescription, Source.CustomerName);
END;
GO

EXEC Update_dimLoan;
SELECT * FROM dimLoan;

UPDATE Loan
SET Amount = 55555555
WHERE LoanNumber = 3002;

EXEC Update_dimLoan;
SELECT * FROM dimLoan;

INSERT INTO Loan (LoanNumber, CustomerID, LoanSubType, BranchCode, CurrencyCode, ApprovalDate, Amount, LoanTerm, Status) 
VALUES (3005, 2001, 1, 1001, 1, '2023-06-01', 25000000.00, 50, 'Active');

EXEC Update_dimLoan;
SELECT * FROM dimLoan;
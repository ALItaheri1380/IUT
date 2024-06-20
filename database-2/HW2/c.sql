CREATE OR ALTER PROCEDURE Update_dimCustomer
AS
BEGIN
    MERGE dimCustomer AS Target
    USING (
        SELECT CS.CustomerID AS TEMP, CS.CustomerID, CS.CustomerName, CS.BranchCode,
            CS.CustomerType, CS.NationalID, CS.Occupation,
            CS.PhoneNumber, CT.CustomerTypeDescription
        FROM Customer CS
        INNER JOIN CustomerType CT ON CS.CustomerType = CT.CustomerType
        UNION
        SELECT -1 AS TEMP, CS.CustomerID, CS.CustomerName, CS.BranchCode,
            CS.CustomerType, CS.NationalID, CS.Occupation,
            CS.PhoneNumber, CT.CustomerTypeDescription
        FROM Customer CS
        INNER JOIN CustomerType CT ON CS.CustomerType = CT.CustomerType 
        INNER JOIN dimCustomer DC ON DC.CustomerID = CS.CustomerID
        WHERE CS.Occupation <> DC.Occupation AND DC.cur_flag = 1
    ) AS Source
    ON (Target.CustomerID = Source.TEMP)
    WHEN MATCHED AND Target.Occupation <> Source.Occupation AND Target.cur_flag = 1 THEN
        UPDATE
        SET Target.cur_flag = 0,
            Target.EndDate = GETDATE()
    WHEN NOT MATCHED THEN
        INSERT (CustomerID, CustomerName, BranchCode, CustomerType,
            NationalID, Occupation, PhoneNumber, StartDate,
            EndDate, cur_flag, CustomerType_Description)
        VALUES (Source.CustomerID, Source.CustomerName, Source.BranchCode, Source.CustomerType, 
            Source.NationalID, Source.Occupation, Source.PhoneNumber, GETDATE(), NULL,
            1, Source.CustomerTypeDescription);
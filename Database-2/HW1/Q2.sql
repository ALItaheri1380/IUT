ADROP TABLE IF EXISTS [Trn_Des_Src]

CREATE TABLE [Trn_Des_Src]
(
    [VoucherId] [varchar](21) NULL,
    [TrnDate]   [date]        NULL,
    [TrnTime]   [varchar](6)  NULL,
    [Amount]    [bigint]      NULL,
    [SourceDep] [int]         NULL,
    [DesDep]    [int]         NULL
);

INSERT INTO Trn_Des_Src (VoucherId, TrnDate, TrnTime, Amount, SourceDep, DesDep)
VALUES 
('10', '2019-01-01', '101000', 1000, 45, 23),
('11', '2019-01-01', '101000', 1000, 45, 23),
('12', '2019-01-01', '091000', 200, 345, NULL),
('14', '2019-01-02', '080023', 300, NULL, 45),
('15', '2019-01-05', '151201', 700, 438, 259),
('16', '2019-01-05', '151201', 700, 438, 259),
('25', '2019-02-15', '132022', 1700, 876, 2000);

GO
CREATE OR ALTER PROCEDURE changeDuplicatedTransactions
AS
BEGIN
    SELECT STRING_AGG(VoucherId, '|') AS VoucherId, TrnDate, TrnTime, Amount, SourceDep, DesDep
    INTO Temp
    FROM Trn_Des_Src
    GROUP BY TrnTime, TrnDate, Amount, SourceDep, DesDep;

  DELETE FROM Trn_Des_Src;

    INSERT INTO Trn_Des_Src (VoucherId, TrnDate, TrnTime, Amount, SourceDep, DesDep)
    SELECT VoucherId, TrnDate, TrnTime, Amount, SourceDep, DesDep
    FROM Temp;

    DROP TABLE Temp;
End;
GO

SELECT * FROM Trn_Des_Src ORDER BY VoucherId;

EXEC changeDuplicatedTransactions;

SELECT * FROM Trn_Des_Src ORDER BY VoucherId;
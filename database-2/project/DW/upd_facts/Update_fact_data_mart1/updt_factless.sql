-----------------###### Library_DW Factless Fact ######---------------
USE Library_DW
GO

GO
CREATE OR ALTER PROCEDURE DW_Fact_Factless
AS
BEGIN
DECLARE @start1 datetime = GETDATE();
---------------------------
truncate table [LendingsDataMart].factlessTmp
truncate table [LendingsDataMart].factlessTmp2
---------------------------
DECLARE @end1 datetime = GETDATE();
insert into [LendingsDataMart].[log_dm1]
values('factlessTmp', 'truncate', @start1, @end1),
('factlessTmp2', 'truncate', @start1, @end1);

SET @start1 = GETDATE();
---------------------------
insert into [Library_DW].[LendingsDataMart].factlessTmp2 (MemberID, Member_identifier, [Description])
 select r.ID, r.identifier, r.[Description]
 from Library_SA.dbo.RelationshipType as r 
 where r.ID not in (select ID from [Library_DW].[LendingsDataMart].[Factless])
---------------------------
SET @end1 = GETDATE();
insert into [LendingsDataMart].[log_dm1]
values('factlessTmp2', 'insert', @start1, @end1);
 
 SET @start1 = GETDATE();
 ---------------------------
 insert into [Library_DW].[LendingsDataMart].factlessTmp (MemberID, Member_identifier, RelationshipType)
 select nd.MemberID, nd.Member_identifier, dr.ID
 from [Library_DW].[LendingsDataMart].factlessTmp2 as nd 
    inner join [Library_DW].[dbo].dimRelationshipType as dr ON dr.Description = nd.Description
---------------------------
SET @end1 = GETDATE();
insert into [LendingsDataMart].[log_dm1]
values('factlessTmp', 'insert', @start1, @end1);
 
 SET @start1 = GETDATE();
---------------------------
 insert into [Library_DW].[LendingsDataMart].[Factless] (MemberID, Member_identifier, RelationshipType)
 select MemberID, Member_identifier, RelationshipType
 from [Library_DW].[LendingsDataMart].[factlessTmp] 
 ---------------------------
SET @end1 = GETDATE();
insert into [LendingsDataMart].[log_dm1]
values('Factless', 'insert', @start1, @end1);

END;
Go
-- exec DW_Fact_Factless
-- select* from [LendingsDataMart].Factless
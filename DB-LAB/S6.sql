CREATE TABLE [Production].[prdlg](
[ProductID] [int] ,
[Name] [dbo].[Name] NOT NULL,
[ProductNumber] [nvarchar](25) NOT NULL,
[MakeFlag] [dbo].[Flag] NOT NULL,
[FinishedGoodsFlag] [dbo].[Flag] NOT NULL,
[Color] [nvarchar](15) NULL,
[SafetyStockLevel] [smallint] NOT NULL,
[ReorderPoint] [smallint] NOT NULL,
[StandardCost] [money] NOT NULL,
[ListPrice] [money] NOT NULL,
[Size] [nvarchar](5) NULL,
[SizeUnitMeasureCode] [nchar](3) NULL,
[WeightUnitMeasureCode] [nchar](3) NULL,
[Weight] [decimal](8, 2) NULL,
[DaysToManufacture] [int] NOT NULL,
[ProductLine] [nchar](2) NULL,
[Class] [nchar](2) NULL,
[Style] [nchar](2) NULL,
[ProductSubcategoryID] [int] NULL,
[ProductModelID] [int] NULL,
[SellStartDate] [datetime] NOT NULL,
[SellEndDate] [datetime] NULL,
[DiscontinuedDate] [datetime] NULL,
[rowguid] [uniqueidentifier] ROWGUIDCOL NOT NULL,
[ModifiedDate] [datetime] NOT NULL,
[change_type] [char] (10),
)




create TRIGGER [product_update]
ON [Production].[Product]
instead of update
as
insert into Production.[prdlg] select * , 'UPDATED-i' from inserted
insert into Production.[prdlg] select * , 'UPDATED-d' from deleted


CREATE TRIGGER [production].[prd_delete]
ON [Production].[Product]
instead of delete
as
insert into Production.[prdlg] select * , 'DELETED' from deleted


CREATE TRIGGER [production].[prd_insrt]
ON [Production].[Product]
instead of insert
as
insert into Production.ProductLogs select * , 'INSERTED' from inserted
Go



update Production.Product set Name= 'up' where ProductID = 2
update Production.Product set Color = 'Black' where ProductID = 4
delete from Production.Product where ProductID = 3
delete from Production.Product where ProductNumber = 'CA-6738'


select * from Production.prdlg
select * from Production.Product

-------- Q2 --------------

select * into temp_table from Production.prdlg

select * from temp_table

update temp_table set Name= 'ali tahei' where ProductID = 4

select* from temp_table

----- Q3 -------

create procedure dif_data
as
begin
insert into Production.temp_dif
select * from Production.prdlg
except
select * from temp_table
end
go

exec dif_data
select * from Production.temp_dif
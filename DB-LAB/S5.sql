--%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
select [Name], [Europe], [North America], [Pacific]
from (select pp.[Name], sst.[Group]
	from Production.Product pp JOIN Sales.SalesOrderDetail ssd on ssd.ProductID = pp.ProductID JOIN
	Sales.SalesOrderHeader ssh on ssh.SalesOrderID = ssd.SalesOrderID JOIN
	Sales.SalesTerritory sst on sst.TerritoryID = ssh.TerritoryID)
as src_table
pivot(
	COUNT([Group])
	for [Group] IN
	([Europe], [North America], [Pacific])
)as pvt
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%--

select PersonType, [M], [F]
from
(
	select PersonType, [Gender]
	from Person.Person
	join HumanResources.Employee on Person.BusinessEntityID = Employee.BusinessEntityID
) src
pivot
(
	count([Gender])
	for [Gender] in ([M], [F])
) as pvt;
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%--

SELECT [Name]
FROM Production.Product AS pp
WHERE LEN([Name]) < 15 and SUBSTRING([Name], LEN([Name])-1, 1) = 'e'

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q4 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
DROP FUNCTION IF EXISTS dbo.DateConversion;
GO

CREATE FUNCTION dbo.DateConversion(@date char(10))
returns nvarchar(120)
as
begin
	if (@date not like '____/__/__')
	return N'تاریخ معتبر نیست'

	if not(SUBSTRING(@Date, 1, 4) BETWEEN 1000 AND 9999
	and SUBSTRING(@Date, 6, 2) BETWEEN 1 AND 12
	and SUBSTRING(@Date, 9, 2) BETWEEN 1 AND 31)
	return N'تاریخ معتبر نیست'


	declare @res nvarchar(120);
	declare @m nvarchar(40);
	declare @y nvarchar(40);
	declare @d nvarchar(40);

	set @d = SUBSTRING(@Date, 9, 2);
	set @y = SUBSTRING(@Date, 1, 4);

	SET @m =CASE
	WHEN SUBSTRING(@Date,6,2) ='01' THEN N'فروردین'
	WHEN SUBSTRING(@Date,6,2) ='02' THEN N'اردبهشت'
	WHEN SUBSTRING(@Date,6,2) ='03' THEN N'خرداد'
	WHEN SUBSTRING(@Date,6,2) ='04' THEN N'تیر'
	WHEN SUBSTRING(@Date,6,2) ='05' THEN N'مرداد'
	WHEN SUBSTRING(@Date,6,2) ='06' THEN N'شهریور'
	WHEN SUBSTRING(@Date,6,2) ='07' THEN N'مهر'
	WHEN SUBSTRING(@Date,6,2) ='08' THEN N'آبان'
	WHEN SUBSTRING(@Date,6,2) ='09' THEN N'آذر'
	WHEN SUBSTRING(@Date,6,2) ='10' THEN N'دی'
	WHEN SUBSTRING(@Date,6,2) ='11' THEN N'بهمن'
	WHEN SUBSTRING(@Date,6,2) ='12' THEN N'اسفند'
	end

	set @res = @d + @m + N' ماه ' + @y + N' شمسی';

	return @res;

end

GO
SELECT dbo.DateConversion('1400/06/31')
GO
SELECT dbo.DateConversion('140a/6/3')
Go 
SELECT dbo.DateConversion('10000');
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q5 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%--
DROP FUNCTION IF EXISTS dbo.func;
Go
CREATE FUNCTION dbo.func(@P_name varchar(200), @Year int, @Month int)
RETURNS TABLE
AS
RETURN
(
	select distinct sst.[Name] from Sales.SalesOrderHeader ssh JOIN Sales.SalesOrderDetail ssd ON ssd.SalesOrderID = ssh.SalesOrderID JOIN
	Sales.SalesTerritory sst ON sst.TerritoryID = ssh.TerritoryID JOIN Production.Product pp ON pp.ProductID = ssd.ProductID
	where pp.[Name] = @P_name AND YEAR(ssh.OrderDate) = @Year AND MONTH(ssh.OrderDate) = @Month
);
Go
SELECT * from dbo.func('LL Road Frame - Black, 58', 2006, 9);

--@@@@@@@@@@@@@@@@@@@@@@@@@ END @@@@@@@@@@@@@@@@@@@@@@@@@--
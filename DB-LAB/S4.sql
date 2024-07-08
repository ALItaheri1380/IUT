--%%%%%%%%%%%%%%%%%%%% Q1 %%%%%%%%%%%%%%%%%%%%

--همه فاکتور ها رو بر اساس مشتریهاش گروه بندی میکنه و هر گروه رو بر اساس تاریخ و بعد ای دی سورت میکنه و قیمت محصول هر سطر رو با قیمت محصولات در دو سطر قبلی میانگین میگیره و در ستون آخر میگذاره

--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

--%%%%%%%%%%%%%%%%%%%% Q2 %%%%%%%%%%%%%%%%%%%%
SELECT case GROUPING(sst.Name)
WHEN 0 THEN sst.Name
WHEN 1 THEN 'All Territories'
end as TerritoryName,

case GROUPING(sst.[Group])
WHEN 0 THEN sst.[Group]
WHEN 1 THEN 'All Regions'
end as Region,

sum(ssh.SubTotal) SalesTotal,

count(*) SalesCount

FROM Sales.SalesOrderHeader ssh INNER JOIN Sales.SalesTerritory sst
on (ssh.TerritoryID = sst.TerritoryID)

GROUP BY rollup(sst.[Group],sst.Name)
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

--%%%%%%%%%%%%%%%%%%%% Q3 %%%%%%%%%%%%%%%%%%%%
SELECT ppc.[Name] CatName, pps.[Name] SubCatName, count(*) cnt, sum(ssd.LineTotal) total_value
from Sales.SalesOrderDetail as ssd INNER JOIN Production.Product as pp ON (pp.ProductID = ssd.ProductID) INNER JOIN
Production.ProductSubcategory as pps ON (pps.ProductSubcategoryID = pp.ProductSubcategoryID) INNER JOIN
Production.ProductCategory as ppc ON (ppc.ProductCategoryID = pps.ProductCategoryID)
group by rollup (ppc.[Name], pps.[Name])
--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

--%%%%%%%%%%%%%%%%%%%% Q4 %%%%%%%%%%%%%%%%%%%%
USE AdventureWorks2012
GO
with temp_table as (
select
pp.FirstName + ' ' + ISNULL(pp.MiddleName, '') + ' ' + pp.LastName as Full_Name,
hr.NationalIDNumber,
hr.Gender,
case hr.MaritalStatus
when 'S' then 'single'
when 'M' then 'married'
end as marital_status,
hr.JobTitle,
COUNT(*) over (partition by hr.JobTitle) as Jobcounter

from HumanResources.Employee as hr
INNER JOIN Person.Person as pp on hr.BusinessEntityID = pp.BusinessEntityID
)

select*
from temp_table
where Jobcounter>3
--%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%
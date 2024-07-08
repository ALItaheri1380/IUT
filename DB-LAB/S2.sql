--############# Query 1 #############--
select soh.*
from [Sales].[SalesTerritory] as sst INNER JOIN [Sales].[SalesOrderHeader] as soh on (sst.TerritoryID = soh.TerritoryID)
where TotalDue between 100000 and 500000 and (sst.[Name] = 'France' or sst.[Group] = 'North America')
--############# Query 2 #############--
SELECT SalesOrderID, CustomerID, TotalDue, OrderDate,sst.[Name]
from [Sales].[SalesOrderHeader] soh INNER JOIN [Sales].[SalesTerritory] sst on (sst.TerritoryID = soh.TerritoryID)
--############# Query 3 #############--
select soh.*
into NAmerica_Sales
from [Sales].[SalesTerritory] as sst INNER JOIN [Sales].[SalesOrderHeader] as soh on (sst.TerritoryID = soh.TerritoryID)
where TotalDue between 100000 and 500000 and (sst.[Group] = 'North America')

alter table NAmerica_Sales
add OrderWeight char(4) check (OrderWeight in ('High', 'Mid', 'Low'))

update NAmerica_Sales
set OrderWeight=case
when TotalDue > (select avg(TotalDue) from NAmerica_Sales) then 'high'
when TotalDue < (select avg(TotalDue) from NAmerica_Sales) then 'low'
else 'mid'
end

select * from NAmerica_Sales
--############# Query 4 #############--
select BusinessEntityID,
case
when max(Rate) <= (select max(Rate) FROM HumanResources.EmployeePayHistory)/4 then max(Rate)*1.20
when max(Rate) > (select max(Rate) from HumanResources.EmployeePayHistory) / 4 and max(Rate) <= (SELECT max(Rate) FROM HumanResources.EmployeePayHistory)/2 then max(Rate)*1.15
when max(Rate) > (select max(Rate) from HumanResources.EmployeePayHistory) / 2 and max(Rate) <= (SELECT max(Rate) FROM HumanResources.EmployeePayHistory)*3/4 then max(Rate)*1.10
else max(rate) * 1.05
end newsalary,
case
when max(Rate) <= 29 then 3
when max(Rate) > 29 and max(Rate)<=50 then 2
else 1
end [LEVEL]
from HumanResources.EmployeePayHistory
GROUP BY BusinessEntityID
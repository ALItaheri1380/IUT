--##### 1.a #####--
--import data through: tasks > import data > next > 
--Change data source on xlsx > browse xlsx file > next>
--Change destination on microsoft ole db driver for sql server >
--set properties> next > next > finish

--######### 1.b #########--
DROP TABLE IF EXISTS [Sales_details2]
GO
--Method One

/*WITH Sales_details2_temp AS (
  SELECT
    [Sales details].*,
    COUNT(*) OVER (PARTITION BY [Sales details].Invoicenum,[Sales details].BranchId,
								[Sales details].Productid, [Sales details].[Jalali-D],
								[Sales details].[Jalali-M], [Sales details].[Jalali-Y])
				   AS cntr
  FROM
    [Sales details]
)
select*
into [Sales_details2]
from Sales_details2_temp
where cntr=1*/

--Method two

WITH Sales_details2_temp AS (
  SELECT
    [Sales details].*,
    COUNT(*) OVER (PARTITION BY [Sales details].Invoicenum,
								[Sales details].BranchId,
								[Sales details].Productid)
				   AS cntr
  FROM
    [Sales details]
),
Sales_details2_temp2 AS(
	SELECT  Sales_details2_temp.[BranchId],
		    Sales_details2_temp.[Productid],
			Sales_details2_temp.[Invoicenum],
			Sales_details2_temp.[Unitssold],
		    Sales_details2_temp.[Jalali-D],
		    Sales_details2_temp.[Jalali-M],
		    Sales_details2_temp.[Jalali-Y]
	FROM Sales_details2_temp
	WHERE Sales_details2_temp.cntr = 1
),
temp AS(
	select [Sales_details2_temp2].*,
		   COUNT(*) OVER (PARTITION BY Sales_details2_temp2.[BranchId], Sales_details2_temp2.[Invoicenum], 
									   Sales_details2_temp2.[Jalali-D], Sales_details2_temp2.[Jalali-M],
									   Sales_details2_temp2.[Jalali-Y]) AS cntr1,
		   COUNT(*) OVER (PARTITION BY Sales_details2_temp2.[BranchId], Sales_details2_temp2.[Invoicenum])
		                 AS cntr2
	FROM Sales_details2_temp2
)
SELECT temp.BranchId , temp.Productid , temp.Invoicenum , temp.Unitssold,
	   temp.[Jalali-D] , temp.[Jalali-M] ,temp.[Jalali-Y]

into [Sales_details2]
from temp
where [temp].cntr1 = [temp].cntr2
--######### 1.c #########--
GO
CREATE OR ALTER PROCEDURE DB_Q_ONE AS
BEGIN
	DROP TABLE IF EXISTS [Sales_details_with_Quarters];
	DROP TABLE IF EXISTS [Sales_details3];

	WITH total_sales AS(
		select [Sales_details2].BranchId, [Sales_details2].Productid,
			   SUM(Unitssold) as total_sales_per_day,
			   [Sales_details2].[Jalali-D], [Sales_details2].[Jalali-M],
			   [Sales_details2].[Jalali-Y]

		FROM   [Sales_details2]

		GROUP BY [Sales_details2].BranchId, [Sales_details2].Productid,
				 [Sales_details2].[Jalali-D], [Sales_details2].[Jalali-M],
				 [Sales_details2].[Jalali-Y]
	),
	Quarters AS (
		SELECT BranchId, Productid, total_sales_per_day,
		   NTILE(4) OVER (PARTITION BY BranchId, Productid ORDER BY total_sales_per_day) AS quarters
		FROM total_sales
	),
	Quart1_temp AS (
		SELECT *,
		   ROW_NUMBER() OVER (PARTITION BY BranchId, Productid ORDER BY total_sales_per_day DESC) AS rn
		FROM Quarters
		WHERE quarters = 1
	),
	Quart1 AS (
		SELECT BranchId, Productid, total_sales_per_day as Q1
		FROM Quart1_temp
		WHERE rn = 1
	),
	Quart3_temp AS (
		SELECT *,
		   ROW_NUMBER() OVER (PARTITION BY BranchId, Productid ORDER BY total_sales_per_day DESC) AS rn
		FROM Quarters
		WHERE quarters = 3
	),
	Quart3 AS (
		SELECT BranchId, Productid, total_sales_per_day as Q3
		FROM Quart3_temp
		WHERE rn = 1
	)

	SELECT ts.*,
			   q1.Q1,
			   q3.Q3
	INTO Sales_details_with_Quarters
	FROM (
		  select [Sales_details2].BranchId, [Sales_details2].Productid,
				 SUM(Unitssold) as total_sales_per_day,
				 [Sales_details2].[Jalali-D], [Sales_details2].[Jalali-M],
				 [Sales_details2].[Jalali-Y]

		  FROM   [Sales_details2]

		  GROUP BY [Sales_details2].BranchId, [Sales_details2].Productid,
				   [Sales_details2].[Jalali-D], [Sales_details2].[Jalali-M],
				   [Sales_details2].[Jalali-Y]
	) as ts
	INNER JOIN Quart1 as q1 ON q1.BranchId = ts.BranchId AND q1.Productid = ts.Productid
	INNER JOIN Quart3 as q3 ON q3.BranchId = ts.BranchId AND q3.Productid = ts.Productid

	UPDATE Sales_details_with_Quarters 
	SET total_sales_per_day = (SELECT avg_Unitssold 
							   FROM
								 (
								   SELECT sd.[BranchId] , sd.[Productid] , AVG(Unitssold) as avg_Unitssold
								   FROM Sales_details2 as sd
								   GROUP BY sd.[BranchId] , sd.[Productid]
								 ) AS au
							   WHERE au.[BranchId]  = Sales_details_with_Quarters.[BranchId] 
							   AND   au.[Productid] = Sales_details_with_Quarters.[Productid]
							   )

							   WHERE total_sales_per_day > (1.5 * (Q3 - Q1)) + Q3
							   OR    total_sales_per_day < Q1 - (1.5 * (Q3 - Q1));
	DROP TABLE IF EXISTS [Sales_details3];

	SELECT sdwq.[BranchId],
		   sdwq.[Productid],
		   sdwq.[total_sales_per_day],
		   sdwq.[Jalali-Y],
		   sdwq.[Jalali-M],
		   sdwq.[Jalali-D]
	INTO [Sales_details3]
	FROM Sales_details_with_Quarters as sdwq

	DROP TABLE [Sales_details_with_Quarters];

END;

GO
EXEC DB_Q_ONE;

select*
from Sales_details3



-- if all([edges(ax,ay)==1, edges(bx,by)==1, edges(cx,cy)==0, edges(dx,dy)==0])
--                      Image(i,j,:) = (ca*a + 0.6*cb*b + 1.3*cc*c + cd*d) /(ca+0.6*cb+1.3*cc+cd);
--                 else
--                      Image(i,j,:) = (1.2*ca*a + cb*b + .9*cc*c + cd*d) /(1.2*ca+cb+.9*cc+cd);
--                 end
            
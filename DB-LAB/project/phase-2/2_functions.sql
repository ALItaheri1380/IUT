USE HotelBooking


--####################### FUNCTIONS #######################

--########################## 1 ############################

DROP FUNCTION IF EXISTS dbo.GetHotelsInCity;
Go

CREATE FUNCTION GetHotelsInCity
(
    @cityName VARCHAR(50)
)
RETURNS TABLE
AS
RETURN
(
    SELECT H.ID, H.Hotel_name, P.Province_Name, H.[Address], H.Phone_Number, H.Web_address, H.Floor_count, H.Room_count
    FROM Hotel H
    INNER JOIN City C ON H.City_ID = C.ID
    INNER JOIN Province P ON H.province_ID = P.ID
    WHERE C.City_Name = @cityName
)
--########################## 2 ############################
Go

IF OBJECT_ID('Total_revenue_within_period_hotel', 'FN') IS NOT NULL
    DROP FUNCTION Total_revenue_within_period_hotel;

GO
CREATE FUNCTION Total_revenue_within_period_hotel
(
    @hotel_id INT,
    @StartDate DATETIME,
    @EndDate DATETIME
)
RETURNS FLOAT
AS
BEGIN
    DECLARE @TotalRevenue FLOAT;

    SELECT @TotalRevenue = SUM(P.amount)
    FROM Payment P
    INNER JOIN Booking_header BH ON P.Booking_header_ID = BH.ID
    WHERE BH.Hotel_ID = @hotel_id
    AND P.Pay_Date >= @StartDate 
    AND P.Pay_Date <= @EndDate;

    RETURN ISNULL(@TotalRevenue, 0);
END;
--########################## 3 ############################

GO
IF OBJECT_ID('CalculatePaymentAmount', 'FN') IS NOT NULL
    DROP FUNCTION CalculatePaymentAmount;
GO
CREATE FUNCTION CalculatePaymentAmount
(
    @BookingID INT
)
RETURNS FLOAT
AS
BEGIN
    DECLARE @PaymentAmount FLOAT;

    SELECT @PaymentAmount = DATEDIFF(DAY, BH.Start_Date, BH.End_Date) * R.Price
    FROM Booking_header BH
    INNER JOIN Booking_room BR ON BH.ID = BR.Booking_header_ID
    INNER JOIN Room R ON BR.Room_ID = R.ID
    WHERE BH.ID = @BookingID;

    RETURN ISNULL(@PaymentAmount, 0);
END


--########################## 4 ############################
IF OBJECT_ID('fn_CalculateAverageRoomPriceByHotel', 'FN') IS NOT NULL
    DROP FUNCTION fn_CalculateAverageRoomPriceByHotel;

GO
CREATE FUNCTION fn_CalculateAverageRoomPriceByHotel()
RETURNS TABLE
AS
RETURN (
    SELECT 
        Hotel_ID,
        AVG(Price) OVER (PARTITION BY Hotel_ID) AS AverageRoomPrice
    FROM Room
)
GO


--########################## 5 ############################
CREATE OR ALTER FUNCTION fn_GetRoomCountAndTypeByHotelAndState()
RETURNS TABLE
AS
RETURN (
    SELECT Hotel_ID, [busy] AS Busy_Count, [free] AS Free_Count
    FROM (
        SELECT Hotel_ID, Room_state, Delineation
        FROM Room
    ) AS SourceTable
    PIVOT (
        COUNT(Room_state)
        FOR Room_state IN ([busy], [free])
    ) AS PivotTable
)
go

--#################### END FUNCTION #######################

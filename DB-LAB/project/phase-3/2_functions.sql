USE HotelBooking

--======================= FUNCTIONS =======================

--=========================== 1 ============================

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
    SELECT 
        H.ID, 
        H.Hotel_name, 
        P.Province_Name, 
        H.[Address],
        PhoneNumbers = STRING_AGG(hp.Phone_Number, '  |  ') WITHIN GROUP (ORDER BY hp.Phone_Number)
    FROM Hotel H
    INNER JOIN City C ON H.City_ID = C.ID
    INNER JOIN Province P ON H.province_ID = P.ID
    INNER JOIN HotelPhoneLink hpl ON H.ID = hpl.HotelID
    INNER JOIN HotelPhone hp ON hpl.PhoneID = hp.ID
    WHERE C.City_Name = @cityName
    GROUP BY H.ID, H.Hotel_name, P.Province_Name, H.[Address]
)
Go
--============================ 2 ============================

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
--============================ 3 ============================

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

GO
CREATE OR ALTER FUNCTION fn_CalculateAverageRoomPriceByHotel()
RETURNS TABLE
AS
RETURN (
    SELECT 
        distinct(Hotel.ID),
        ISNULL(AVG(Price) OVER (PARTITION BY Hotel_ID), 0) AS AverageRoomPrice
    FROM Room full outer join Hotel on Hotel.ID = Room.Hotel_ID
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

--============================ END FUNCTION ============================
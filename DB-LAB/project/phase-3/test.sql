USE HotelBooking
GO

--#################### function test:

----- function 1 -----
select * from GetHotelsInCity('Isfahan')

----- function 2 -----
DECLARE @HotelID INT = 5;
DECLARE @StartDate DATETIME = '2022-01-01';
DECLARE @EndDate DATETIME = '2022-12-31';

SELECT dbo.Total_revenue_within_period_hotel(@HotelID, @StartDate, @EndDate) AS TotalRevenue;

----- function 3 -----
DECLARE @BookingID INT = 1
SELECT dbo.CalculatePaymentAmount(@BookingID)

----- function 4 -----
SELECT *
FROM fn_CalculateAverageRoomPriceByHotel();

----- function 5 -----

SELECT *
FROM dbo.fn_GetRoomCountAndTypeByHotelAndState();
--#################### Procedure test:

----- procedure 1 -----
select * from Booking_header

EXEC Insert_Book_header
	@HotelID = 5,
	@PersonID = 1,
	@StartDate = '2022-04-22',
	@EndDate = '2022-04-29';

select * from Booking_header

----- procedure 2 -----
select * from Booking_room

EXEC Insert_Book_room
	@Booking_Header_ID = 6,
	@Room_ID = 1;
	-- returns ROOM IS BUSY
select * from Booking_room

----- procedure 3 && trigger 1 -----
select * from Payment
select * from Booking_header
-- befor executing this procedure the Reserve_state field in Booking_header is 0

EXEC Insert_Payment
	@Booking_header_ID = 26,
	@Pay_Date = '2022-08-20',
	@amount = 1800;

select * from Payment
select * from Booking_header
-- after executing this procedure th Reserve_state field in Booking_header is 1

----- procedure 4 && Trigger 3-----
select * from Payment
select * from Booking_header
select * from Booking_room

EXEC InsertBookingData
	@HotelID = 4,
	@PersonID = 2,
	@StartDate = '2024-04-22',
	@EndDate = '2024-04-29',
	@RoomID = 61,
	@PayDate = '2024-04-22';

select * from Payment
select * from Booking_header
select * from Booking_room

----- procedure 5 -----
EXEC Total_Income



----- procedure 6 -----
EXEC Update_User_Info
	@Person_ID = 1,
	@Password = 'password123',
	@F_Name = 'Ali',
	@L_Name = 'Rezayi',
	@Address = 'Isfahan, Valiasr St.'
	
select * from Person

--#################### View test:

-- there are tests for each view after them

--#################### Trigger test:

----- Trigger 1 -----

-- go to procedure 3

----- Trigger 2 -----

UPDATE [Person]
SET F_Name = 'Mary'
Where ID='2';

----- Trigger 3 -----

-- go to procedure 4
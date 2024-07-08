CREATE DATABASE HotelBooking;
USE HotelBooking
GO


--################# CREATE TABLES AND INSERT #################

CREATE TABLE Province
(
    ID               INT PRIMARY KEY,
    Province_Name    VARCHAR(30) NOT NULL
)
Go

CREATE TABLE City
(
    ID           INT PRIMARY KEY,
    City_Name    VARCHAR(50) NOT NULL,
    province_ID  INT REFERENCES Province
)
Go

CREATE TABLE [Person]
(
    ID            INT PRIMARY KEY,
    F_Name        VARCHAR(50) NOT NULL,
    L_Name        VARCHAR(50) NOT NULL,
    [Address]       VARCHAR(100) NOT NULL,
    Phone_Number  VARCHAR(11) NOT NULL,
    [Password]      VARCHAR(40) NOT NULL,
    Gender        VARCHAR(7)  NOT NULL,
    BirthDay      DATETIME,
    province_ID   INT REFERENCES Province,
    City_ID       INT REFERENCES City
)
Go

CREATE TABLE Hotel
(
    ID              INT PRIMARY KEY,
    Hotel_name      VARCHAR(50)  NOT NULL,
    province_ID     INT REFERENCES Province,
    City_ID         INT REFERENCES City,
    [Address]       VARCHAR(100) NOT NULL,
    Phone_Number    VARCHAR(15)  NOT NULL,
    Web_address     VARCHAR(255),
    Floor_count     INT NOT NULL,
    Room_count      INT NOT NULL
)
Go

CREATE TABLE Room 
(
    ID               INT PRIMARY KEY,
    Hotel_ID         INT REFERENCES Hotel,
    Price            FLOAT NOT NULL,        -- per night
    Room_number      INT NOT NULL,
    Floor_number     INT NOT NULL,
    Delineation      VARCHAR(1000) NOT NULL,
    Capacity         INT NOT NULL,
    Room_state       VARCHAR(4) check(Room_state like 'busy' or Room_state like 'free') DEFAULT 'free'
)
Go

CREATE TABLE Booking_header 
(
    ID               INT PRIMARY KEY,
    Hotel_ID         INT REFERENCES Hotel,
    Person_ID        INT REFERENCES [Person],
    Start_Date       DATETIME,
    End_Date         DATETIME,
    Reserve_state    INT DEFAULT 0
)
Go

CREATE TABLE Booking_room
(
    ID                     INT PRIMARY KEY,
    Booking_header_ID      INT REFERENCES Booking_header,
    Room_ID                INT REFERENCES Room
)
Go


CREATE TABLE Payment
(
    ID   INT PRIMARY KEY,
    Booking_header_ID   INT REFERENCES Booking_header,
    Pay_Date      DATETIME NOT NULL,
    amount          FLOAT NOT NULL
)
Go

CREATE TABLE [Rank]
(
    ID                INT PRIMARY KEY,
    Hotel_ID          INT REFERENCES Hotel,
    Ranking_Rate      INT CHECK (Ranking_Rate BETWEEN 0 AND 10),
    Delineation       VARCHAR(255)
)
Go

INSERT INTO Province (ID, Province_Name)
VALUES
(1, 'Tehran'),
(2, 'Isfahan'),
(3, 'Fars'),
(4, 'Khorasan Razavi'),
(5, 'Gilan')

Go

INSERT INTO City (ID, City_Name, province_ID)
VALUES
(1, 'Tehran', 1),
(2, 'Shiraz', 3),
(3, 'Isfahan', 2),
(4, 'Mashhad', 4),
(5, 'Rasht', 5)

Go

INSERT INTO Person (ID, F_Name, L_Name, Address, Phone_Number, Password, Gender, BirthDay, province_ID, City_ID)
VALUES
(1, 'Ali', 'Rezayi', 'Tehran, Valiasr St.', '09121234567', 'password123', 'Male', '1990-05-15', 1, 1),
(2, 'Sara', 'Ahmadi', 'Shiraz, Azadi St.', '09132345678', 'securepass', 'Female', '1995-03-10', 3, 2),
(3, 'Mohammad', 'Mohammadi', 'Isfahan, Chahar Bagh St.', '09143456789', 'strongpass123', 'Male', '1988-07-22', 2, 3),
(4, 'Fatemeh', 'Karimi', 'Mashhad, Imam Reza St.', '09154567890', 'mypass123', 'Female', '1992-01-01', 4, 4),
(5, 'Reza', 'Seyed', 'Rasht, Shariati St.', '09165678901', 'anotherpass', 'Male', '1985-12-25', 5, 5)

Go

INSERT INTO Hotel (ID, Hotel_name, province_ID, City_ID, Address, Phone_Number, Web_address, Floor_count, Room_count)
VALUES
(1, 'Espinas Palace Hotel', 1, 1, 'Tehran, Saadat Abad St.', '+982122222222', 'www.espinashotels.com', 20, 400),
(2, 'Abbasi Hotel', 2, 3, 'Isfahan, Amadegah St.', '+983133333333', 'www.abbasihotel.com', 5, 150),
(3, 'Chamran Grand Hotel', 3, 2, 'Shiraz, Chamran Blvd.', '+987144444444', 'www.chamranhotel.com', 10, 250),
(4, 'Darvishi Hotel', 4, 4, 'Mashhad, Imam Reza St.', '+985155555555', 'www.darvishihotel.com', 8, 200),
(5, 'Kadoos Grand Hotel', 5, 5, 'Rasht, Golsar St.', '+981366666666', 'www.kadooshotel.com', 12, 300)

Go

INSERT INTO Room (ID, Hotel_ID, Price, Room_number, Floor_number, Delineation, Capacity)
VALUES
(1, 1, 500, 101, 10, 'Single Room with City View', 1),
(2, 2, 300, 205, 2, 'Double Room with Garden View', 2),
(3, 3, 400, 315, 3, 'Deluxe Suite with Balcony', 4),
(4, 4, 250, 408, 4, 'Twin Room with Mountain View', 2),
(5, 5, 350, 512, 5, 'Family Room with Sea View', 4)

Go

INSERT INTO Booking_header (ID, Hotel_ID, Person_ID, Start_Date, End_Date) 
VALUES
(1, 1, 1, '2024-01-10', '2024-01-15'),
(2, 2, 2, '2024-02-20', '2024-02-23'),
(3, 3, 3, '2024-03-15', '2024-03-20'),
(4, 4, 4, '2024-04-05', '2024-04-10'),
(5, 5, 5, '2024-05-25', '2024-05-30')

Go

INSERT INTO Booking_room (ID, Booking_header_ID, Room_ID)
VALUES 
(1, 1, 1),
(2, 2, 2),
(3, 3, 3),
(4, 4, 4),
(5, 5, 5)

Go
 
INSERT INTO Payment (ID, Booking_header_ID, Pay_Date, amount)
VALUES
(1, 1, '2024-01-05', 2000), 
(2, 3, '2024-03-10', 1600),
(3, 5, '2024-05-20', 1400)

Go

INSERT INTO [Rank] (ID, Hotel_ID, Ranking_Rate, Delineation)
VALUES
(1, 1, 9, 'Excellent service and amenities'), 
(2, 2, 7, 'Good value for money'), 
(3, 3, 5, 'Average experience'),
(4, 4, 8, 'Great location and friendly staff'),
(5, 5, 6, 'Comfortable rooms but needs renovation')


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
--#################### END FUNCTION #######################

Go
--#################### Procedure ##########################

--####################### 1 #############################
CREATE OR ALTER PROCEDURE Insert_Book_header 
  @ID           INT,
  @HotelID      INT,
  @PersonID     INT,
  @StartDate    DATETIME,
  @EndDate      DATETIME
AS
BEGIN
  INSERT INTO Booking_header (ID, Hotel_ID, Person_ID, Start_Date, End_Date)
  VALUES (@ID, @HotelID, @PersonID, @StartDate, @EndDate);
END

/*select * from Booking_header

EXEC Insert_Book_header
	@ID = 6,
	@HotelID = 5,
	@PersonID = 1,
	@StartDate = '2024-04-22',
	@EndDate = '2024-04-29';
*/
--########################## 2 ############################  
GO
CREATE OR ALTER PROCEDURE Insert_Book_room
  @ID             INT,
  @Booking_Header_ID INT,
  @Room_ID       INT
AS
BEGIN
  DECLARE @is_free varchar(4)
  select @is_free = CASE 
                        WHEN (select Room_state from Room where Room.ID =@Room_ID) = 'free' then 1
                        ELSE 0
                    End
  IF @is_free = 1
  BEGIN
    INSERT INTO Booking_room (ID, Booking_header_ID, Room_ID)
    VALUES (@ID, @Booking_Header_ID, @Room_ID);
  END
  ELSE
  BEGIN
    SELECT 'ROOM IS BUSY' AS Message
  END
END

--########################## 3 ############################
Go
CREATE OR ALTER PROCEDURE Insert_Payment
  @ID                 INT,
  @Booking_header_ID  INT,
  @Pay_Date           DATETIME,
  @amount             FLOAT
AS
BEGIN
  INSERT INTO Payment (ID, Booking_header_ID, Pay_Date, amount)
  VALUES (@ID, @Booking_header_ID, @Pay_Date, @amount);
END

--########################## 4 ############################

Go
CREATE OR ALTER PROCEDURE InsertBookingData
    @HotelID INT,
    @PersonID INT,
    @StartDate DATETIME,
    @EndDate DATETIME,
    @RoomID INT,
    @PayDate DATETIME,
    @ReserveState INT
AS
BEGIN

  DECLARE @Header_ID_COUNT INT;
  DECLARE @Book_ID_COUNT INT;
  DECLARE @Payment_Count INT;
  DECLARE @Amount FLOAT;

  SET @Header_ID_COUNT = (SELECT COUNT(*)
						  FROM Booking_header) + 1;

  SET @Book_ID_COUNT = (SELECT COUNT(*)
						FROM Booking_room) + 1;

  SET @Payment_Count = (SELECT COUNT(*)
					    FROM Payment) + 1;

  EXEC Insert_Book_header
     @Header_ID_COUNT,
     @HotelID,
     @PersonID,
     @StartDate,
     @EndDate;

  EXEC Insert_Book_room
    @Book_ID_COUNT,
    @Header_ID_COUNT,
    @RoomID;

  SET @Amount = (SELECT dbo.CalculatePaymentAmount(@Header_ID_COUNT));

  EXEC Insert_Payment
     @Payment_Count,
     @Header_ID_COUNT,
     @PayDate,
     @Amount;
END
--########################## 5 ############################
Go
CREATE OR ALTER PROCEDURE Total_Income
AS
BEGIN
    SELECT H.ID, H.Hotel_name, SUM(amount) as Total_Income_For_Each_Hotel
    FROM Booking_header BH
    INNER JOIN Payment P ON BH.ID = P.Booking_header_ID
    INNER JOIN Hotel H ON BH.Hotel_ID = H.ID
    GROUP BY H.ID, H.Hotel_name;  
END;
--####################### 6 #############################
Go
CREATE OR ALTER PROCEDURE Update_User_Info
    @Person_ID INT,
    @Password VARCHAR(40),
    @F_Name VARCHAR(50),
    @L_Name VARCHAR(50),
    @Address VARCHAR(100),
    @Phone_Number VARCHAR(11)
AS
BEGIN
    DECLARE @Valid_Password BIT

    SELECT @Valid_Password = CASE 
                                WHEN EXISTS (SELECT 1 FROM [Person] WHERE ID = @Person_ID AND [Password] = @Password) THEN 1
                                ELSE 0
                             END

    IF @Valid_Password = 1
    BEGIN
        UPDATE [Person]
        SET F_Name = @F_Name,
            L_Name = @L_Name,
            [Address] = @Address,
            Phone_Number = @Phone_Number
        WHERE ID = @Person_ID

        SELECT 'User information updated successfully.' AS Message
    END
    ELSE
    BEGIN
        SELECT 'Invalid password. Please try again.' AS Message
    END
END;
--################## End of Procedure ######################

--######################### View ###########################

--########################   1   ###########################
Go
CREATE OR ALTER View View_HotelDetails AS
SELECT h.ID AS Hotel_ID, h.Hotel_name, p.Province_Name,
	   c.City_Name, h.Address, h.Phone_Number, h.Web_address,
	   h.Floor_count, h.Room_count
FROM Hotel h
JOIN Province p ON h.province_ID = p.ID
JOIN City c ON h.City_ID = c.ID;
-------------
Go
SELECT * 
FROM View_HotelDetails;

--########################   2   ###########################
Go
CREATE OR ALTER VIEW View_BookingSummary AS
SELECT bh.ID AS BookingID, p.F_Name + ' ' + p.L_Name AS GuestName,
       h.Hotel_name, r.Room_number, bh.Start_Date, bh.End_Date, pay.amount
FROM Booking_header bh
JOIN Person p ON bh.Person_ID = p.ID
JOIN Hotel h ON bh.Hotel_ID = h.ID
JOIN Booking_room br ON bh.ID = br.Booking_header_ID
JOIN Room r ON br.Room_ID = r.ID
JOIN Payment pay ON bh.ID = pay.Booking_header_ID;

--------------
Go
SELECT * 
FROM View_BookingSummary;
--#######################  3   #############################
Go
CREATE OR ALTER View View_PaymentDetails AS
SELECT p.ID AS Payment_ID, bh.ID AS Booking_ID, p.Pay_Date, p.amount, h.Hotel_name
FROM Payment p
JOIN Booking_header bh ON p.Booking_header_ID = bh.ID
JOIN Hotel h ON bh.Hotel_ID = h.ID;
-------------
Go
SELECT *
FROM View_PaymentDetails

--#######################  4   #############################
Go
CREATE OR ALTER VIEW View_HotelRanking AS
SELECT h.Hotel_name, r.Ranking_Rate, r.Delineation AS Comment
FROM Rank r
JOIN Hotel h ON r.Hotel_ID = h.ID;
-------------
Go
SELECT*
FROM View_HotelRanking
--################## End of View ######################

--#################### Triggers #######################

--#####################   1   ######################### 
GO
CREATE OR ALTER TRIGGER dbo.TriggerUpdateBookingState
    ON Payment
    AFTER INSERT
    AS
BEGIN
    UPDATE Booking_header
    SET Reserve_state = 1
    WHERE ID IN (
        SELECT Booking_header_ID
        FROM Payment
    )
END
GO
--#####################   2   #########################
Go
CREATE OR ALTER TRIGGER MoveToArchive
ON [Person]
AFTER DELETE
AS
BEGIN
    SELECT *
    FROM deleted
END;
-------------------
Go
delete from [Person]
Where ID='6';
--#####################   3   ######################### 
GO
CREATE OR ALTER TRIGGER dbo.TriggerChangeRoomState
    ON Booking_room
    AFTER INSERT
    AS
BEGIN
    UPDATE Room
    SET Room_state = 'busy'
    WHERE ID IN (
        SELECT Room_ID
        FROM inserted)
END
GO
--################# End of Triggers ####################

/*EXEC InsertBookingData
    @HotelID = 5,
    @PersonID = 1,
    @StartDate = '2023-05-06',
    @EndDate = '2023-07-06',
    @RoomID = 1,
    @PayDate = '2024-05-06',
    @ReserveState = 1;
-------------------------------------
DECLARE @HotelID INT = 5;
DECLARE @StartDate DATETIME = '2023-01-01';
DECLARE @EndDate DATETIME = '2024-12-31';

SELECT dbo.Total_revenue_within_period_hotel(@HotelID, @StartDate, @EndDate) AS TotalRevenue;
--------------------------------------------------------------------------
/*
USE HotelBooking

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
    @PayDate DATETIME
AS
BEGIN
  DECLARE @is_free BIT
  select @is_free = CASE 
                        WHEN (select Room_state from Room where Room.ID = @RoomID) = 'free' then 1
                        ELSE 0
                    End
  IF @is_free = 1
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
  end
  ELSE 
  BEGIN
	SELECT 'ROOM IS BUSY' AS Message
  END
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

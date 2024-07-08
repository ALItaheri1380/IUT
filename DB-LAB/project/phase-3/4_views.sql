USE HotelBooking
Go
--============================ View ============================

--============================   1   ============================
GO
CREATE OR ALTER VIEW View_HotelDetails AS
SELECT 
    H.ID AS Hotel_ID,H.Hotel_name,P.Province_Name,C.City_Name,H.[Address],
    H.Web_address,H.Floor_count,H.Room_count
    
FROM Hotel H
JOIN Province P ON H.province_ID = P.ID
JOIN City C ON H.City_ID = C.ID
INNER JOIN HotelPhoneLink hpl ON H.ID = hpl.HotelID
INNER JOIN HotelPhone hp ON hpl.PhoneID = hp.ID
GROUP BY H.ID, H.Hotel_name, P.Province_Name, C.City_Name, H.[Address], H.Web_address, H.Floor_count, H.Room_count;
-------------
Go
SELECT * 
FROM View_HotelDetails;

--============================   2   ============================
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
--============================  3   ============================
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

--============================  4   ============================
Go
CREATE OR ALTER VIEW View_HotelRanking AS
SELECT h.Hotel_name, r.Ranking_Rate, r.Delineation AS Comment
FROM Rank r
JOIN Hotel h ON r.Hotel_ID = h.ID;
-------------
Go


SELECT*
FROM View_HotelRanking
order by Ranking_Rate desc
--============================ End of View ============================
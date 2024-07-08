USE HotelBooking
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
(3, 4, 4),
(4, 5, 5)

Go
 
INSERT INTO Payment (ID, Booking_header_ID, Pay_Date, amount)
VALUES
(1, 1, '2024-01-05', 2000), 
(2, 4, '2024-03-10', 1600),
(3, 5, '2024-05-20', 1400)

Go

INSERT INTO [Rank] (ID, Hotel_ID, Ranking_Rate, Delineation)
VALUES
(1, 1, 9, 'Excellent service and amenities'), 
(2, 2, 7, 'Good value for money'), 
(3, 3, 5, 'Average experience'),
(4, 4, 8, 'Great location and friendly staff'),
(5, 5, 6, 'Comfortable rooms but needs renovation')


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

CREATE TABLE [phoneUser]
(
    ID            INT PRIMARY KEY,
    Phone_Number  VARCHAR(11)
)
Go

CREATE TABLE [Person]
(
    ID            INT PRIMARY KEY,
    F_Name        VARCHAR(50) NOT NULL,
    L_Name        VARCHAR(50) NOT NULL,
    [Address]     VARCHAR(100) NOT NULL,
    [Password]    VARCHAR(40) NOT NULL,
    Gender        VARCHAR(7)  NOT NULL,
    BirthDay      DATETIME,
    province_ID   INT REFERENCES Province,
    City_ID       INT REFERENCES City
)
Go

CREATE TABLE PersonPhone 
(
    PersonID INT REFERENCES Person(ID),
    PhoneID INT REFERENCES phoneUser(ID),
    PRIMARY KEY (PersonID, PhoneID)
)
Go

CREATE TABLE [HotelPhone]
(
    ID            INT PRIMARY KEY,
    Phone_Number  VARCHAR(11)
)
Go

CREATE TABLE Hotel
(
    ID              INT PRIMARY KEY,
    Hotel_name      VARCHAR(50)  NOT NULL,
    province_ID     INT REFERENCES Province,
    City_ID         INT REFERENCES City,
    [Address]       VARCHAR(100) NOT NULL,
    Web_address     VARCHAR(255),
    Floor_count     INT NOT NULL,
    Room_count      INT NOT NULL
)
Go

CREATE TABLE HotelPhoneLink
(
    HotelID INT REFERENCES Hotel(ID),
    PhoneID INT REFERENCES HotelPhone(ID),
    PRIMARY KEY (HotelID, PhoneID)
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

--===================== INSERT =====================--
USE HotelBooking
GO


-- Inserting Data into Province Table
INSERT INTO Province (ID, Province_Name) VALUES
    (1, 'Tehran'),
    (2, 'Isfahan'),
    (3, 'Mazandaran'),
    (4, 'Gilan'),
    (5, 'Khorasan Razavi'),
    (6, 'Fars'),
    (7, 'Kerman'),
    (8, 'Khuzestan'),
    (9, 'Ardabil'),
    (10, 'Azarbaijan Gharbi');

-- Inserting Data into City Table
INSERT INTO City (ID, City_Name, province_ID) VALUES
    (1, 'Tehran', 1),
    (2, 'Isfahan', 2),
    (3, 'Shiraz', 6),
    (4, 'Mashhad', 5),
    (5, 'Rasht', 4),
    (6, 'Sari', 3),
    (7, 'Kerman', 7),
    (8, 'Ahvaz', 8),
    (9, 'Ardabil', 9),
    (10, 'Urmia', 10);

	-- Inserting data into phoneUser table
INSERT INTO phoneUser (ID, Phone_Number) VALUES
    (1, '09123456789'), (2, '09367890123'), (3, '09198765432'), (4, '09301234567'), (5, '09112223333'), 
    (6, '09384445555'), (7, '09156667777'), (8, '09321112222'), (9, '09101112222'), (10, '09332223333'),
    (11, '09143334444'), (12, '09354445555'), (13, '09165556666'), (14, '09376667777'), (15, '09187778888'),
    (16, '09398889999'), (17, '09110001111'), (18, '09321112222'), (19, '09132223333'), (20, '09343334444'),
    (21, '09154445555'), (22, '09365556666'), (23, '09176667777'), (24, '09387778888'), (25, '09198889999'),
    (26, '09300001111'), (27, '09111112222'), (28, '09322223333'), (29, '09133334444'), (30, '09344445555'),
    (31, '09155556666'), (32, '09366667777'), (33, '09177778888'), (34, '09388889999'), (35, '09199990000'),
    (36, '09300001111'), (37, '09111112222'), (38, '09322223333'), (39, '09133334444'), (40, '09344445555'),
    (41, '09155556666'), (42, '09366667777'), (43, '09177778888'), (44, '09388889999'), (45, '09199990000'),
    (46, '09300001111'), (47, '09111112222'), (48, '09322223333'), (49, '09133334444'), (50, '09344445555');

-- Inserting data into Person table
INSERT INTO Person (ID, F_Name, L_Name, Address, Password, Gender, BirthDay, province_ID, City_ID) VALUES
    (1, 'Ali', 'Rezaei', 'Tehran, Valiasr Ave.', 'password123', 'Male', '1985-07-15', 1, 1),
    (2, 'Maryam', 'Jafari', 'Isfahan, Chahar Bagh Ave.', 'maryam123', 'Female', '1992-01-28', 2, 2),
    (3, 'Mohammad', 'Hashemi', 'Shiraz, Zand Ave.', 'mh123', 'Male', '1978-10-03', 6, 3),
    (4, 'Sara', 'Mohammadi', 'Mashhad, Ferdowsi Ave.', 'sara123', 'Female', '2001-05-12', 5, 4),
    (5, 'Amir', 'Hosseini', 'Rasht, Shahid Beheshti Ave.', 'amir123', 'Male', '1998-08-22', 4, 5),
    (6, 'Neda', 'Ghasemi', 'Sari, Keshavarz Ave.', 'neda123', 'Female', '1995-02-10', 3, 6),
    (7, 'Reza', 'Akbari', 'Karaj, Golshahr', 'reza123', 'Male', '1982-09-01', 1, 1),
    (8, 'Fatemeh', 'Farahani', 'Kerman, Azadi Ave.', 'fatemeh123', 'Female', '1988-12-25', 7, 7),
    (9, 'Saeed', 'Zarei', 'Ahvaz, Naderi Ave.', 'saeed123', 'Male', '1991-03-18', 8, 8),
    (10, 'Zahra', 'Tavakkoli', 'Ardabil, Azadi Ave.', 'zahra123', 'Female', '1997-06-08', 9, 9),
    (11, 'Ali', 'Rezaei', 'Tehran, Valiasr Ave.', 'password123', 'Male', '1985-07-15', 1, 1),
    (12, 'Maryam', 'Jafari', 'Isfahan, Chahar Bagh Ave.', 'maryam123', 'Female', '1992-01-28', 2, 2),
    (13, 'Mohammad', 'Hashemi', 'Shiraz, Zand Ave.', 'mh123', 'Male', '1978-10-03', 6, 3),
    (14, 'Sara', 'Mohammadi', 'Mashhad, Ferdowsi Ave.', 'sara123', 'Female', '2001-05-12', 5, 4),
    (15, 'Amir', 'Hosseini', 'Rasht, Shahid Beheshti Ave.', 'amir123', 'Male', '1998-08-22', 4, 5),
    (16, 'Neda', 'Ghasemi', 'Sari, Keshavarz Ave.', 'neda123', 'Female', '1995-02-10', 3, 6),
    (17, 'Reza', 'Akbari', 'Karaj, Golshahr', 'reza123', 'Male', '1982-09-01', 1, 1),
    (18, 'Fatemeh', 'Farahani', 'Kerman, Azadi Ave.', 'fatemeh123', 'Female', '1988-12-25', 7, 7),
    (19, 'Saeed', 'Zarei', 'Ahvaz, Naderi Ave.', 'saeed123', 'Male', '1991-03-18', 8, 8),
    (20, 'Zahra', 'Tavakkoli', 'Ardabil, Azadi Ave.', 'zahra123', 'Female', '1997-06-08', 9, 9),
    (21, 'Ali', 'Rezaei', 'Tehran, Valiasr Ave.', 'password123', 'Male', '1985-07-15', 1, 1),
    (22, 'Maryam', 'Jafari', 'Isfahan, Chahar Bagh Ave.', 'maryam123', 'Female', '1992-01-28', 2, 2),
    (23, 'Mohammad', 'Hashemi', 'Shiraz, Zand Ave.', 'mh123', 'Male', '1978-10-03', 6, 3),
    (24, 'Sara', 'Mohammadi', 'Mashhad, Ferdowsi Ave.', 'sara123', 'Female', '2001-05-12', 5, 4),
    (25, 'Amir', 'Hosseini', 'Rasht, Shahid Beheshti Ave.', 'amir123', 'Male', '1998-08-22', 4, 5),
    (26, 'Neda', 'Ghasemi', 'Sari, Keshavarz Ave.', 'neda123', 'Female', '1995-02-10', 3, 6),
    (27, 'Reza', 'Akbari', 'Karaj, Golshahr', 'reza123', 'Male', '1982-09-01', 1, 1),
    (28, 'Fatemeh', 'Farahani', 'Kerman, Azadi Ave.', 'fatemeh123', 'Female', '1988-12-25', 7, 7),
    (29, 'Saeed', 'Zarei', 'Ahvaz, Naderi Ave.', 'saeed123', 'Male', '1991-03-18', 8, 8),
    (30, 'Zahra', 'Tavakkoli', 'Ardabil, Azadi Ave.', 'zahra123', 'Female', '1997-06-08', 9, 9),
    (31, 'Ali', 'Rezaei', 'Tehran, Valiasr Ave.', 'password123', 'Male', '1985-07-15', 1, 1),
    (32, 'Maryam', 'Jafari', 'Isfahan, Chahar Bagh Ave.', 'maryam123', 'Female', '1992-01-28', 2, 2),
    (33, 'Mohammad', 'Hashemi', 'Shiraz, Zand Ave.', 'mh123', 'Male', '1978-10-03', 6, 3),
    (34, 'Sara', 'Mohammadi', 'Mashhad, Ferdowsi Ave.', 'sara123', 'Female', '2001-05-12', 5, 4),
    (35, 'Amir', 'Hosseini', 'Rasht, Shahid Beheshti Ave.', 'amir123', 'Male', '1998-08-22', 4, 5),
    (36, 'Neda', 'Ghasemi', 'Sari, Keshavarz Ave.', 'neda123', 'Female', '1995-02-10', 3, 6),
    (37, 'Reza', 'Akbari', 'Karaj, Golshahr', 'reza123', 'Male', '1982-09-01', 1, 1),
    (38, 'Fatemeh', 'Farahani', 'Kerman, Azadi Ave.', 'fatemeh123', 'Female', '1988-12-25', 7, 7),
    (39, 'Saeed', 'Zarei', 'Ahvaz, Naderi Ave.', 'saeed123', 'Male', '1991-03-18', 8, 8),
    (40, 'Zahra', 'Tavakkoli', 'Ardabil, Azadi Ave.', 'zahra123', 'Female', '1997-06-08', 9, 9),
    (41, 'Ali', 'Rezaei', 'Tehran, Valiasr Ave.', 'password123', 'Male', '1985-07-15', 1, 1),
    (42, 'Maryam', 'Jafari', 'Isfahan, Chahar Bagh Ave.', 'maryam123', 'Female', '1992-01-28', 2, 2),
    (43, 'Mohammad', 'Hashemi', 'Shiraz, Zand Ave.', 'mh123', 'Male', '1978-10-03', 6, 3),
    (44, 'Sara', 'Mohammadi', 'Mashhad, Ferdowsi Ave.', 'sara123', 'Female', '2001-05-12', 5, 4),
    (45, 'Amir', 'Hosseini', 'Rasht, Shahid Beheshti Ave.', 'amir123', 'Male', '1998-08-22', 4, 5),
    (46, 'Neda', 'Ghasemi', 'Sari, Keshavarz Ave.', 'neda123', 'Female', '1995-02-10', 3, 6),
    (47, 'Reza', 'Akbari', 'Karaj, Golshahr', 'reza123', 'Male', '1982-09-01', 1, 1),
    (48, 'Fatemeh', 'Farahani', 'Kerman, Azadi Ave.', 'fatemeh123', 'Female', '1988-12-25', 7, 7),
    (49, 'Saeed', 'Zarei', 'Ahvaz, Naderi Ave.', 'saeed123', 'Male', '1991-03-18', 8, 8),
    (50, 'Zahra', 'Tavakkoli', 'Ardabil, Azadi Ave.', 'zahra123', 'Female', '1997-06-08', 9, 9);

-- Inserting data into PersonPhone table
INSERT INTO PersonPhone (PersonID, PhoneID) VALUES
    (1, 1), (2, 2), (3, 3), (4, 4), (5, 5), 
    (6, 6), (7, 7), (8, 8), (9, 9), (10, 10),
    (11, 11), (12, 12), (13, 13), (14, 14), (15, 15),
    (16, 16), (17, 17), (18, 18), (19, 19), (20, 20),
    (21, 21), (22, 22), (23, 23), (24, 24), (25, 25),
    (26, 26), (27, 27), (28, 28), (29, 29), (30, 30),
    (31, 31), (32, 32), (33, 33), (34, 34), (35, 35),
    (36, 36), (37, 37), (38, 38), (39, 39), (40, 40),
    (41, 41), (42, 42), (43, 43), (44, 44), (45, 45),
    (46, 46), (47, 47), (48, 48), (49, 49), (50, 50);


-- Inserting data into HotelPhone table
INSERT INTO HotelPhone (ID, Phone_Number) VALUES
    (1, '02166778899'), (2, '03133445566'), (3, '07632109876'), (4, '05138007766'), (5, '01335678901'),
    (6, '02188889999'), (7, '01122233333'), (8, '04433344455'), (9, '09123456789'), (10, '09367890123'),
    (11, '09198765432'), (12, '09301234567'), (13, '09112223333'), (14, '09384445555'), (15, '09156667777'),
    (16, '09321112222'), (17, '09101112222'), (18, '09332223333'), (19, '09143334444'), (20, '09354445555'),
    (21, '09165556666'), (22, '09376667777'), (23, '09187778888'), (24, '09398889999'), (25, '09110001111'),
    (26, '09321112222'), (27, '09132223333'), (28, '09343334444'), (29, '09154445555'), (30, '09365556666');

-- Inserting data into Hotel table
INSERT INTO Hotel (ID, Hotel_name, province_ID, City_ID, Address, Web_address, Floor_count, Room_count) VALUES
    (1, 'Grand Hotel Tehran', 1, 1, 'Tehran, Azadi Ave.', 'www.grandhoteltehran.com', 15, 250),
    (2, 'Espinas Palace Hotel', 2, 2, 'Isfahan, Chahar Bagh Ave.', 'www.espinaspalacehotel.com', 12, 180),
    (3, 'Parsian Hotel Shiraz', 6, 3, 'Shiraz, Zand Ave.', 'www.parsianhotels.com', 10, 150),
    (4, 'Homa Hotel Mashhad', 5, 4, 'Mashhad, Ferdowsi Ave.', 'www.homahotels.com', 8, 120),
    (5, 'Radisson Blu Hotel Rasht', 4, 5, 'Rasht, Shahid Beheshti Ave.', 'www.radissonhotels.com', 7, 100),
    (6, 'Laleh Hotel Tehran', 1, 1, 'Tehran, Valiasr Ave.', 'www.lalehhotel.com', 10, 150),
    (7, 'Hilton Hotel Isfahan', 2, 2, 'Isfahan, Chahar Bagh Ave.', 'www.hiltonhotels.com', 14, 200),
    (8, 'Sheraton Hotel Shiraz', 6, 3, 'Shiraz, Zand Ave.', 'www.sheratonhotels.com', 9, 130),
    (9, 'Hyatt Regency Hotel Mashhad', 5, 4, 'Mashhad, Ferdowsi Ave.', 'www.hyatt.com', 12, 180),
    (10, 'InterContinental Hotel Rasht', 4, 5, 'Rasht, Shahid Beheshti Ave.', 'www.intercontinental.com', 8, 120);

-- Inserting data into HotelPhoneLink table
INSERT INTO HotelPhoneLink (HotelID, PhoneID) VALUES
    (1, 1), (2, 2), (3, 3), (4, 4), (5, 5),
    (6, 6), (7, 7), (8, 8), (9, 9), (10, 10),
    (1, 11), (2, 12), (3, 13), (4, 14), (5, 15),
    (6, 16), (7, 17), (8, 18), (9, 19), (10, 20),
    (1, 21), (2, 22), (3, 23), (4, 24), (5, 25),
    (6, 26), (7, 27), (8, 28), (9, 29), (10, 30);



-- Inserting data into Room table
INSERT INTO Room (ID, Hotel_ID, Price, Room_number, Floor_number, Delineation, Capacity, Room_state) VALUES
    (1, 1, 150.00, 101, 1, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (2, 1, 200.00, 102, 1, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (3, 1, 250.00, 103, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (4, 1, 180.00, 104, 1, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (5, 1, 220.00, 105, 1, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (6, 1, 300.00, 106, 1, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (7, 1, 160.00, 107, 1, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (8, 1, 210.00, 108, 1, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (9, 1, 260.00, 109, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (10, 1, 190.00, 110, 1, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (11, 1, 150.00, 201, 2, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (12, 1, 200.00, 202, 2, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (13, 1, 250.00, 203, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (14, 1, 180.00, 204, 2, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (15, 1, 220.00, 205, 2, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (16, 1, 300.00, 206, 2, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (17, 1, 160.00, 207, 2, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (18, 1, 210.00, 208, 2, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (19, 1, 260.00, 209, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (20, 1, 190.00, 210, 2, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (21, 2, 120.00, 101, 1, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (22, 2, 160.00, 102, 1, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (23, 2, 200.00, 103, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (24, 2, 140.00, 104, 1, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (25, 2, 180.00, 105, 1, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (26, 2, 240.00, 106, 1, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (27, 2, 130.00, 107, 1, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (28, 2, 170.00, 108, 1, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (29, 2, 220.00, 109, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (30, 2, 150.00, 110, 1, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (31, 2, 120.00, 201, 2, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (32, 2, 160.00, 202, 2, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (33, 2, 200.00, 203, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (34, 2, 140.00, 204, 2, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (35, 2, 180.00, 205, 2, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (36, 2, 240.00, 206, 2, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (37, 2, 130.00, 207, 2, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (38, 2, 170.00, 208, 2, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (39, 2, 220.00, 209, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (40, 2, 150.00, 210, 2, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (41, 3, 100.00, 101, 1, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (42, 3, 140.00, 102, 1, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (43, 3, 180.00, 103, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (44, 3, 120.00, 104, 1, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (45, 3, 160.00, 105, 1, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (46, 3, 220.00, 106, 1, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (47, 3, 110.00, 107, 1, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (48, 3, 150.00, 108, 1, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (49, 3, 200.00, 109, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (50, 3, 130.00, 110, 1, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (51, 3, 100.00, 201, 2, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (52, 3, 140.00, 202, 2, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (53, 3, 180.00, 203, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (54, 3, 120.00, 204, 2, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (55, 3, 160.00, 205, 2, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (56, 3, 220.00, 206, 2, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (57, 3, 110.00, 207, 2, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (58, 3, 150.00, 208, 2, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (59, 3, 200.00, 209, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (60, 3, 130.00, 210, 2, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (61, 4, 80.00, 101, 1, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (62, 4, 120.00, 102, 1, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (63, 4, 160.00, 103, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (64, 4, 100.00, 104, 1, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (65, 4, 140.00, 105, 1, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (66, 4, 200.00, 106, 1, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (67, 4, 90.00, 107, 1, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (68, 4, 130.00, 108, 1, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (69, 4, 180.00, 109, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (70, 4, 110.00, 110, 1, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (71, 4, 80.00, 201, 2, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (72, 4, 120.00, 202, 2, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (73, 4, 160.00, 203, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (74, 4, 100.00, 204, 2, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (75, 4, 140.00, 205, 2, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (76, 4, 200.00, 206, 2, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (77, 4, 90.00, 207, 2, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (78, 4, 130.00, 208, 2, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (79, 4, 180.00, 209, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (80, 4, 110.00, 210, 2, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (81, 5, 70.00, 101, 1, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (82, 5, 110.00, 102, 1, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (83, 5, 150.00, 103, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (84, 5, 90.00, 104, 1, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (85, 5, 130.00, 105, 1, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (86, 5, 190.00, 106, 1, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (87, 5, 80.00, 107, 1, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (88, 5, 120.00, 108, 1, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (89, 5, 170.00, 109, 1, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (90, 5, 100.00, 110, 1, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free'),
    (91, 5, 70.00, 201, 2, 'Single room with a king-size bed, private bathroom, and balcony', 1, 'free'),
    (92, 5, 110.00, 202, 2, 'Double room with two queen-size beds, private bathroom, and city view', 2, 'free'),
    (93, 5, 150.00, 203, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (94, 5, 90.00, 204, 2, 'Single room with a queen-size bed, private bathroom, and garden view', 1, 'free'),
    (95, 5, 130.00, 205, 2, 'Double room with two queen-size beds, private bathroom, and balcony', 2, 'free'),
    (96, 5, 190.00, 206, 2, 'Deluxe suite with a spacious living area, king-size bed, private bathroom, and panoramic city view', 3, 'free'),
    (97, 5, 80.00, 207, 2, 'Single room with a queen-size bed, private bathroom, and street view', 1, 'free'),
    (98, 5, 120.00, 208, 2, 'Double room with two queen-size beds, private bathroom, and garden view', 2, 'free'),
    (99, 5, 170.00, 209, 2, 'Suite with a living area, king-size bed, private bathroom, and balcony', 2, 'free'),
    (100, 5, 100.00, 210, 2, 'Single room with a queen-size bed, private bathroom, and city view', 1, 'free');



-- Inserting data into Booking_header table
INSERT INTO Booking_header (ID, Hotel_ID, Person_ID, Start_Date, End_Date, Reserve_state)
values
(1,1,1,'2022-09-01 00:00:00.000','2022-09-05 00:00:00.000',0),
(2,1,2,'2022-09-08 00:00:00.000','2022-09-15 00:00:00.000',0),
(3,1,3,'2022-09-01 00:00:00.000','2022-09-02 00:00:00.000',0),
(4,1,4,'2022-09-10 00:00:00.000','2022-09-11 00:00:00.000',0),
(5,2,5,'2022-09-02 00:00:00.000','2022-09-03 00:00:00.000',0),
(6,2,6,'2022-09-06 00:00:00.000','2022-09-08 00:00:00.000',0),
(7,2,8,'2022-09-09 00:00:00.000','2022-09-10 00:00:00.000',0),
(8,3,9,'2022-09-01 00:00:00.000','2022-09-02 00:00:00.000',0),
(9,3,15,'2022-09-09 00:00:00.000','2022-09-10 00:00:00.000',0),
(10,3,16,'2022-09-02 00:00:00.000','2022-09-03 00:00:00.000',0),
(11,4,10,'2022-09-10 00:00:00.000','2022-09-11 00:00:00.000',0),
(12,4,11,'2022-09-07 00:00:00.000','2022-09-08 00:00:00.000',0),
(13,4,13,'2022-09-02 00:00:00.000','2022-09-03 00:00:00.000',0),
(14,5,1,'2022-09-10 00:00:00.000','2022-09-11 00:00:00.000',0),
(15,5,18,'2022-09-08 00:00:00.000','2022-09-09 00:00:00.000',0),
(16,5,19,'2022-09-03 00:00:00.000','2022-09-09 00:00:00.000',0),
(17,6,20,'2022-09-07 00:00:00.000','2022-09-08 00:00:00.000',0),
(18,6,21,'2022-09-08 00:00:00.000','2022-09-09 00:00:00.000',0),
(19,6,22,'2022-09-07 00:00:00.000','2022-09-08 00:00:00.000',0),
(20,7,23,'2022-09-05 00:00:00.000','2022-09-06 00:00:00.000',0),
(21,8,24,'2022-09-10 00:00:00.000','2022-09-11 00:00:00.000',0),
(22,8,28,'2022-09-06 00:00:00.000','2022-09-07 00:00:00.000',0),
(23,8,31,'2022-09-10 00:00:00.000','2022-09-11 00:00:00.000',0),
(24,9,40,'2022-09-01 00:00:00.000','2022-09-02 00:00:00.000',0),
(25,10,36,'2022-09-06 00:00:00.000','2022-09-07 00:00:00.000',0);



-- Inserting data into Booking_room table
INSERT INTO Booking_room (ID, Booking_header_ID, Room_ID) VALUES
(1, 1, 1),
(2, 2, 2),
(3, 3, 3),
(4, 4, 4),
(5, 5, 5),
(6, 6, 6),
(7, 7, 7),
(8, 8, 8),
(9, 9, 9),
(10, 10, 10),
(11, 11, 11),
(12, 12, 12),
(13, 13, 13),
(14, 14, 14),
(15, 15, 15),
(16, 16, 16),
(17, 17, 17),
(18, 18, 18),
(19, 19, 19),
(20, 20, 20),
(21, 21, 21),
(22, 22, 22),
(23, 23, 23),
(24, 24, 24),
(25, 25, 25),
(26, 1, 26),
(27, 2, 27),
(28, 3, 28),
(29, 4, 29),
(30, 5, 30),
(31, 6, 31),
(32, 7, 32),
(33, 8, 33),
(34, 9, 34),
(35, 10, 35),
(36, 11, 36),
(37, 12, 37),
(38, 13, 38),
(39, 14, 39),
(40, 15, 40);



-- Inserting data into Payment table
INSERT INTO Payment (ID, Booking_header_ID, Pay_Date, amount) VALUES
(1, 1, '2022-08-30 12:00:00', 600.00),
(2, 2, '2022-09-07 12:00:00', 1400.00),
(3, 3, '2022-08-31 12:00:00', 150.00),
(4, 4, '2022-09-09 12:00:00', 180.00),
(5, 5, '2022-09-01 12:00:00', 120.00),
(6, 6, '2022-09-05 12:00:00', 320.00),
(7, 7, '2022-09-08 12:00:00', 160.00),
(8, 8, '2022-08-31 12:00:00', 100.00),
(9, 9, '2022-09-08 12:00:00', 90.00),
(10, 10, '2022-09-01 12:00:00', 180.00),
(11, 11, '2022-09-09 12:00:00', 110.00),
(12, 12, '2022-09-06 12:00:00', 120.00),
(13, 13, '2022-09-01 12:00:00', 140.00),
(14, 14, '2022-09-09 12:00:00', 90.00),
(15, 15, '2022-09-07 12:00:00', 130.00),
(16, 16, '2022-09-02 12:00:00', 120.00),
(17, 17, '2022-09-06 12:00:00', 190.00),
(18, 18, '2022-09-07 12:00:00', 110.00),
(19, 19, '2022-09-06 12:00:00', 90.00),
(20, 20, '2022-09-04 12:00:00', 170.00),
(21, 21, '2022-09-09 12:00:00', 110.00),
(22, 22, '2022-09-05 12:00:00', 130.00),
(23, 23, '2022-09-09 12:00:00', 70.00),
(24, 24, '2022-08-31 12:00:00', 80.00),
(25, 25, '2022-09-05 12:00:00', 150.00);



-- Inserting data into [Rank] table
INSERT INTO [Rank] (ID, Hotel_ID, Ranking_Rate, Delineation) VALUES
    (1, 1, 8, 'Very Good'),
    (2, 2, 9, 'Excellent'),
    (3, 3, 7, 'Good'),
    (4, 4, 6, 'Fair'),
    (5, 5, 8, 'Very Good'),
    (6, 6, 9, 'Excellent'),
    (7, 7, 7, 'Good'),
    (8, 8, 6, 'Fair'),
    (9, 9, 8, 'Very Good'),
    (10, 10, 9, 'Excellent');

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
Go

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
--============================ Procedure ============================


--============================ 1 ============================
Go
CREATE OR ALTER PROCEDURE Insert_Book_header 
  @HotelID      INT,
  @PersonID     INT,
  @StartDate    DATETIME,
  @EndDate      DATETIME
AS
BEGIN
  declare @ID INT;
  SET @ID = (select Max(ID) from Booking_header) + 1
  INSERT INTO Booking_header (ID, Hotel_ID, Person_ID, Start_Date, End_Date)
  VALUES (@ID, @HotelID, @PersonID, @StartDate, @EndDate);
END

--============================ 2 ============================  
GO
	CREATE OR ALTER PROCEDURE Insert_Book_room
	  @Booking_Header_ID INT,
	  @Room_ID       INT
	AS
	BEGIN
	  DECLARE @ID      INT
	  DECLARE @is_free varchar(4)
	  SET @ID = (select Max(ID) from Booking_room) + 1
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

--============================ 3 ============================
Go
CREATE OR ALTER PROCEDURE Insert_Payment
  @Booking_header_ID  INT,
  @Pay_Date           DATETIME,
  @amount             FLOAT
AS
BEGIN
  DECLARE @ID INT
  SET @ID = (select Max(ID) from Payment) + 1
  INSERT INTO Payment (ID, Booking_header_ID, Pay_Date, amount)
  VALUES (@ID, @Booking_header_ID, @Pay_Date, @amount);
END


--============================ 4 ============================

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

  DECLARE @Header_ID_COUNT INT;
  DECLARE @Amount FLOAT;

  SET @Header_ID_COUNT = (SELECT COUNT(*)
						  FROM Booking_header) + 1;

  EXEC Insert_Book_header
     @HotelID,
     @PersonID,
     @StartDate,
     @EndDate;

  EXEC Insert_Book_room
    @Header_ID_COUNT,
    @RoomID;

  SET @Amount = (SELECT dbo.CalculatePaymentAmount(@Header_ID_COUNT));

  EXEC Insert_Payment
     @Header_ID_COUNT,
     @PayDate,
     @Amount;
END
--============================ 5 ============================
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
--============================ 6 ============================
Go
CREATE OR ALTER PROCEDURE Update_User_Info
    @Person_ID INT,
    @Password VARCHAR(40),
    @F_Name VARCHAR(50),
    @L_Name VARCHAR(50),
    @Address VARCHAR(100)
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
        SET    F_Name = @F_Name,
               L_Name = @L_Name,
               [Address] = @Address

        WHERE ID = @Person_ID

        SELECT 'User information updated successfully.' AS Message
    END
    ELSE
    BEGIN
        SELECT 'Invalid password. Please try again.' AS Message
    END
END;
--============================ End of Procedure ============================

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

--============================ Triggers ============================

--============================   1   ============================ 
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
--============================   2   ============================
Go
CREATE OR ALTER TRIGGER MoveToArchive
ON [Person]
AFTER UPDATE
AS
BEGIN
    SELECT *
    FROM deleted
END;
-------------------
Go


--============================   3   ============================ 
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
--============================ End of Triggers ============================
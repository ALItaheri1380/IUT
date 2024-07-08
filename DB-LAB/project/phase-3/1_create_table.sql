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
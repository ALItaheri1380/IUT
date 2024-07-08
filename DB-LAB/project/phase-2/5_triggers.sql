USE HotelBooking
GO
--#################### Triggers #######################

--#####################   1   ######################### 

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
AFTER Update
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
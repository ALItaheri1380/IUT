DECLARE @i INT = 0;
DECLARE @date DATE = GETDATE(); 

WHILE @i <= 366
BEGIN
    INSERT INTO dimTime (
        FullDate, 
        FullDateAlternateKey, 
        DayNumberOfWeek, 
        EnglishDayNameOfWeek, 
        DayNumberOfMonth, 
        DayNumberOfYear, 
        WeekNumberOfYear, 
        EnglishMonthName, 
        MonthNumberOfYear, 
        CalendarQuarter, 
        CalendarYear, 
        CalendarSemester
    )
    VALUES (
        CAST(FORMAT(@date, 'yyyyMMdd') AS INT), 
        @date, 
        DATEPART(WEEKDAY, @date), 
        DATENAME(WEEKDAY, @date), 
        DATEPART(DAY, @date), 
        DATEPART(DAYOFYEAR, @date), 
        DATEPART(WEEK, @date), 
        DATENAME(MONTH, @date), 
        DATEPART(MONTH, @date), 
        DATEPART(QUARTER, @date), 
        DATEPART(YEAR, @date),
        CASE 
            WHEN DATEPART(MONTH, @date) IN (1, 2, 3, 4, 5, 6) THEN 1 
            ELSE 2 
        END
    );

    SET @date = DATEADD(DAY, 1, @date);
    SET @i = @i + 1;
END;
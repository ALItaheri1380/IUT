USE Library_DW
GO

-- افزودن فایل‌گروپ‌ها و فایل‌ها
DECLARE @i INT = 1;
DECLARE @date NVARCHAR(8);
WHILE @i <= 366
BEGIN
    SET @date = REPLACE(CONVERT(NVARCHAR(10), DATEADD(DAY, @i-1, '2024-06-18'), 112), '-', '');
    EXEC('ALTER DATABASE Library_DW ADD FILEGROUP [FG_' + @date + ']');
    EXEC('ALTER DATABASE Library_DW ADD FILE (
        NAME = ''DB_2_partition_' + @date + ''',
        FILENAME = ''C:\Program Files\Microsoft SQL Server\MSSQL16.TEST\MSSQL\DATA\' + @date + ''',
        SIZE = 3072KB,
        FILEGROWTH = 65536KB
    ) TO FILEGROUP [FG_' + @date + ']');
    SET @i = @i + 1;
END;
GO

BEGIN TRANSACTION;

-- ایجاد پارتیشن فانکشن
DECLARE @cmd NVARCHAR(MAX);
SET @cmd = 'CREATE PARTITION FUNCTION [pfn_FactDaily_KeyDate](int) AS RANGE LEFT FOR VALUES (';
DECLARE @i INT = 1;
WHILE @i <= 366
BEGIN
    SET @cmd = @cmd + REPLACE(CONVERT(NVARCHAR(8), DATEADD(DAY, @i-1, '2024-06-18'), 112), '-', '');
    IF @i < 366 SET @cmd = @cmd + ', ';
    SET @i = @i + 1;
END;
SET @cmd = @cmd + ')';
EXEC(@cmd);

-- ایجاد پارتیشن اسکیم
SET @cmd = 'CREATE PARTITION SCHEME [ps_FactDaily_KeyDate] AS PARTITION [pfn_FactDaily_KeyDate] TO (';
SET @i = 1;
WHILE @i <= 366
BEGIN
    SET @cmd = @cmd + '[FG_' + REPLACE(CONVERT(NVARCHAR(8), DATEADD(DAY, @i-1, '2024-06-18'), 112), '-', '') + ']';
    IF @i < 366 SET @cmd = @cmd + ', ';
    SET @i = @i + 1;
END;
SET @cmd = @cmd + ', [PRIMARY])';
EXEC(@cmd);

COMMIT TRANSACTION;
GO

CREATE CLUSTERED INDEX CI_FactDaily_TimeID
ON [LendingsDataMart].FactDaily (TimeID)
ON ps_FactDaily_KeyDate (TimeID);
GO

-- نمایش اطلاعات پارتیشن‌ها
SELECT DISTINCT
    p.partition_number as [Partition],
    s.name,
    o.name,
    fg.name AS [Filegroup],
    p.rows
FROM sys.partitions p
    INNER JOIN sys.allocation_units au ON au.container_id = p.hobt_id
    INNER JOIN sys.filegroups fg ON fg.data_space_id = au.data_space_id
    INNER JOIN sys.objects o ON o.object_id = p.object_id
    INNER JOIN sys.schemas s ON s.schema_id = o.schema_id
WHERE o.type = 'U'
AND o.name = 'FactDaily'
ORDER BY
    o.name,
    fg.name,
    s.name;
GO
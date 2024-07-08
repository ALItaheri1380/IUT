--### 1 ###--
create login db_test
with password = '123003';
--### 1.2 ###--
create server role role1;
alter server role dbcreator add member role1;
--### 1.3 ###--
alter server role role1 add member db_test;
--### 1.4 ###--
USE AdventureWorks2012
GO
create user ali_user for login db_test

alter role db_datareader ADD MEMBER ali_user
alter role db_datawriter ADD MEMBER ali_user
alter role db_ddladmin ADD MEMBER ali_user
alter role db_owner ADD MEMBER ali_user

create table new_table_game_4(
ID int primary key,
Name varchar(50)
);

insert into new_table_game_4
values (1 , 'ali') , (2 , 'mmd') , (3 , 'hasan');

select* from new_table_game_4

--##### END OF Q1 #####--

--### 2 ###--
USE AdventureWorks2012
GO
create login final_test2 
with password='123003';


create user final_user2
for login final_test2;

create role final_Role2;

alter role db_securityadmin  add member final_Role2;
alter role db_denydatareader  add member final_Role2;

alter role final_Role2 add member final_user2;

grant select on database::AdventureWorks2012
to final_Role2;
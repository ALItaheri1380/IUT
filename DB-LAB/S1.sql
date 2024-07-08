create table departments (
 name varchar(20) not null,
 id char(5) primary key,
 budget numeric(12, 2),
 category varchar(15) check (category in ('Engineering', 'Science'))
);

create table teachers (
 firstname varchar(20) not null,
 lastname varchar(30) not null,
 id char(7),
 birthyear int,
 departmentid char(5),
 salary numeric(7,2) default 10000.00,
 primary key (id),
 foreign key (departmentid) references departments(id)
);

create table students (
 firstname varchar(20) not null,
 lastname varchar(30) not null,
 studentnumber char(7) primary key,
 birthyear int,
 departmentid char(5),
 advisorid char(7),
 foreign key (departmentid) references departments(id),
 foreign key (advisorid) references teachers(id)
);

create table courses (
 id char(7) primary key,
 title varchar(50) not null,
 credits tinyint,
 departmentid char(5),
 foreign key (departmentid) references departments(id)
);

create table available_courses(
 courseid char(7) not null,
 semester varchar(6) check (semester in ('fall', 'spring')) not null,
 year numeric(4,0) not null,
 id char(7),
 teacherid char(7),
 foreign key (id) references courses(id),
 foreign key (teacherid) references teachers(id),
 primary key (courseid, semester, year)
);

create table taken_courses(
 studentid char(7),
 courseid char(7),
 semester varchar(6) check (semester in ('fall', 'spring')),
 year numeric(4,0) not null,
 grade numeric(4, 2) check (grade between 0 and 20),
 primary key (studentid, courseid, semester, year),
 foreign key (courseid, semester, year) references available_courses(courseid, semester, year)
);


create table prerequisites(
 courseid char(7),
 prereqid char(7),
 primary key (courseid, prereqid),
 foreign key (courseid) references courses(id),
 foreign key (prereqid) references courses(id)
);



alter table students
add pass_credit int;

-- ********************INSERT************************--

insert into departments values ('Computer', '1', 2000000, 'Science'), ('Electrical', '2', 3000000, 'Science');

insert into teachers values ('maziar', 'palhang', '1', 1250, '1', 100.23),('abdolreza', 'mirzaei', '2', 1360, '1', 2000.09),('nader', 'karimi', '3', 1345, '1', 2500.12);

insert into students values ('ali', 'taheri', '123', 1382, '1', '2' , 84),('ali', 'sadeghi', '124', 1381, '1', '3' , 50),('amir', 'hadian', '125', 1381, '1', '1' , 82);

insert into courses values ('1', 'ai', 3, '1'),('2', 'ds', 3, '1'),('3', 'dg', 3, '1'),('4', 'db', 3, '1');

insert into available_courses values ('1_01', 'fall', 1401, '1', '1'),('1_02', 'fall', 1401, '1', '2'),('2_01', 'fall', 1401, '2', '2'),('3_01', 'spring', 1401, '3', '3'),('4_01' ,'fall', 1402 , '4' , '3');

insert into taken_courses values ('123', '1_01', 'fall', 1401, 18),('123', '2_01', 'fall', 1401, 19),('124' , '3_01' , 'spring' , 1401 , 12),('125' , '1_02' , 'fall' , 1401 , 20),('123' , '4_01' , 'fall' , 1402 , 17);

insert into prerequisites values ('1', '2');

--**********************QUERY*************************--
select dpt.*
from departments as dpt INNER JOIN students as st on(dpt.id = st.departmentid)
where st.studentnumber = '123';
--*****************************************************--

update taken_courses
set grade = (case when grade <=19 then grade +1 else 20 end);

select * from taken_courses;
--*****************************************************--
select st.studentnumber , st.firstname , st.lastname
from students as st
where st.studentnumber NOT IN
(
select tk.studentid
from courses as crs INNER JOIN available_courses as avb on(crs.id = avb.id)
INNER JOIN taken_courses as tk on(tk.courseid = avb.courseid and tk.semester = avb.semester and tk.year = avb.year)
where crs.title = 'db'
);
--**********************END****************************--

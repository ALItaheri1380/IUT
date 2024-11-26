--3a
SELECT *
FROM student
where name LIKE '%x%'

--3b
SELECT T1.id, T1.course_id
FROM takes T1
WHERE NOT EXISTS (
    SELECT T1.id, T1.course_id
    FROM takes T1
    GROUP BY T1.id, T1.course_id
    EXCEPT
    SELECT T2.id, T2.course_id
    FROM takes T2
    GROUP BY T2.id, T2.course_id
    HAVING COUNT(*) = 2
);


--3c

SELECT DISTINCT(ss.id), ss.name, ss.dept_name, ss.tot_cred
FROM
  (SELECT s.id, s.name, s.dept_name, s.tot_cred
   FROM student s
   WHERE s.dept_name = 'Comp. Sci.') AS ss
WHERE EXISTS
  (SELECT *
   FROM course c
   WHERE c.dept_name = 'Comp. Sci.'
     AND c.course_id NOT IN (SELECT t.course_id
                              FROM takes t
                              WHERE t.id = ss.id))
 
--3d

SELECT t.course_id, c.title, COUNT(s.id) AS num_students
FROM takes t JOIN course c ON t.course_id = c.course_id
             JOIN student s ON t.id = s.id  
WHERE t.semester = 'Fall' AND t.year = 2003
GROUP BY t.course_id
HAVING COUNT(s.id) > 300
ORDER BY num_students DESC;

--3e
SELECT s.* ,c.title,t.grade ,CASE WHEN t.grade IN ('A ','B ','A+','A-','B-','B+') THEN 'PASS'
            ELSE 'FAIL'
       END AS pass_fail
from takes t JOIN student s ON t.ID=s.ID
   JOIN course c on t.course_id=c.course_id 
WHERE t.semester='Spring' AND t.year = 2004

--3f
SELECT c.*
FROM section s JOIN course c on s.course_id=c.course_id
GROUP by s.course_id 
HAVING COUNT(*)<3

--3g
WITH avg_units AS 
  (SELECT AVG(num) AS avg_courses
   FROM
     (SELECT s.id, s.name, COUNT(t.course_id) AS num
      FROM student s JOIN takes t ON s.id = t.id
      WHERE t.semester = 'Spring' AND t.year = 2005
      GROUP BY s.id)
   )
SELECT s.*, COUNT(t.course_id)
FROM student s JOIN takes t ON s.id = t.id
                 JOIN avg_units ON 1=1
WHERE t.semester = 'Spring' AND t.year = 2005 AND 
      s.dept_name = 'Comp. Sci.'
GROUP BY s.id, s.name  
HAVING COUNT(t.course_id) > avg_units.avg_courses;

--3h
SELECT c1.course_id, SUM(c3.credits) AS sum
FROM course c1 Join prereq c2 ON c1.course_id = c2.course_id Join course c3 ON c2.prereq_id=c3.course_id 
GROUP by c1.course_id
ORDER BY sum;
-----------------------------------------------------------------------------------------------------------------
--4a
UPDATE instructor
SET salary = salary*1.1
WHERE dept_name = 'Comp. Sci.';

SELECT * 
FROM instructor
where dept_name = 'Comp. Sci.'

--4b
SELECT COUNT(*)
from instructor

INSERT INTO instructor (id, name, dept_name, salary)
SELECT id, name, dept_name, 10000000
FROM student
WHERE tot_cred > 100;

SELECT COUNT(*)
from instructor

--4c


SELECT  t.course_id,t.sec_id,t.semester,t.year
  from instructor i JOIN teaches t on i.ID = t.ID JOIN section s on t.course_id=s.course_id and t.sec_id=s.sec_id AND t.semester =s.semester and t.year = s.year JOIN time_slot tt on s.time_slot_id = tt.time_slot_id
  where i.name = 'Romero' and tt.day in ('S','M') and tt.start_hr<12
  
UPDATE section  
SET building = 'Kharazmi', room_number = '202'
where (course_id , sec_id , semester , year) in (
  SELECT  t.course_id,t.sec_id,t.semester,t.year
  from instructor i JOIN teaches t on i.ID = t.ID JOIN section s on t.course_id=s.course_id and t.sec_id=s.sec_id AND t.semester =s.semester and t.year = s.year JOIN time_slot tt on s.time_slot_id = tt.time_slot_id
  where i.name = 'Romero' and tt.day in ('S','M') and tt.start_hr<12)

SELECT  i.* , s.*
  from instructor i JOIN teaches t on i.ID = t.ID JOIN section s on t.course_id=s.course_id and t.sec_id=s.sec_id AND t.semester =s.semester and t.year = s.year JOIN time_slot tt on s.time_slot_id = tt.time_slot_id
  where i.name = 'Romero' and tt.day in ('S','M') and tt.start_hr<12
--4d
SELECT c.* , s.*
FROM course c JOIN section s on s.course_id = c.course_id

DELETE FROM course 
WHERE course_id NOT IN
     (SELECT DISTINCT course_id 
      FROM section  
      WHERE year >= 2019);
      
SELECT c.* , s.*
FROM course c JOIN section s on s.course_id = c.course_id




------------------------------------------------------
--5a

CREATE VIEW v_students_avg_grade AS
SELECT s.ID, s.name, a.i_ID, i.name,  
       AVG(CASE WHEN t.grade ='A+' THEN 100
                WHEN t.grade ='A' THEN 95
           		WHEN t.grade ='A-' THEN 90
           		WHEN t.grade ='B+' THEN 85
           		WHEN t.grade ='B' THEN 80
           		WHEN t.grade ='B-' THEN 75
           		WHEN t.grade ='C+' THEN 85
           		WHEN t.grade ='C' THEN 80
           		WHEN t.grade ='C-' THEN 75
                ELSE 0 END) AS avg_grade
FROM student s LEFT JOIN advisor a ON s.ID = a.s_ID
             LEFT JOIN takes t ON s.ID = t.ID 
             LEFT JOIN instructor i ON i.ID = a.i_ID
GROUP BY s.ID, s.name, a.i_ID, i.name;


SELECT * from v_students_avg_grade

--5b
--1
CREATE VIEW v_top_students_by_dept AS
WITH top_students AS (
  SELECT s.dept_name, s.ID, s.name, 
         AVG(CASE WHEN t.grade ='A+' THEN 100
                WHEN t.grade ='A' THEN 95
           		WHEN t.grade ='A-' THEN 90
           		WHEN t.grade ='B+' THEN 85
           		WHEN t.grade ='B' THEN 80
           		WHEN t.grade ='B-' THEN 75
           		WHEN t.grade ='C+' THEN 85
           		WHEN t.grade ='C' THEN 80
           		WHEN t.grade ='C-' THEN 75
                ELSE 0 END) AS gpa
    FROM student s JOIN takes t ON s.ID = t.ID
   GROUP BY s.ID, s.dept_name
   HAVING SUM(CASE WHEN t.grade in('A%','B%','C%') THEN 1 ELSE 0 END) = 0
   ORDER BY s.dept_name, gpa DESC
)
SELECT *
  FROM (SELECT dept_name, ID, name, gpa, 
               ROW_NUMBER() OVER (PARTITION BY dept_name 
                                  ORDER BY gpa DESC) AS rnum
          FROM top_students) x
 WHERE rnum <= 3;

---way2
CREATE VIEW top_students_dense_rank AS  
SELECT dept_name, admission_year, name, gpa, dense_rank
FROM
  (SELECT dept_name, tot_cred AS admission_year, name, AVG(grade) AS gpa,
          DENSE_RANK() OVER (PARTITION BY dept_name, tot_cred
                                 ORDER BY AVG(CASE WHEN grade ='A+' THEN 100
                                                    WHEN grade ='A' THEN 95
                                                    WHEN grade ='A-' THEN 90
                                                    WHEN grade ='B+' THEN 85
                                                    WHEN grade ='B' THEN 80
                                                    WHEN grade ='B-' THEN 75
                                                    WHEN grade ='C+' THEN 85
                                                    WHEN grade ='C' THEN 80
                                                    WHEN grade ='C-' THEN 75
                                                    ELSE 0 END) DESC) AS dense_rank
   FROM student JOIN takes ON student.id = takes.id
   GROUP BY dept_name, tot_cred, name) derived_table
WHERE dense_rank <= 3;


SELECT *
from v_top_students_by_dept

SELECT *
FROM top_students_dense_rank
--c
CREATE VIEW v_dept_courses AS 
SELECT d.dept_name, sec.year, sec.semester, 
       SUM(c.credits) AS total_units
FROM department d JOIN course c ON d.dept_name = c.dept_name
                JOIN section sec ON c.course_id = sec.course_id
GROUP BY d.dept_name, sec.year, sec.semester
ORDER BY d.dept_name, sec.year, sec.semester;

SELECT * from v_dept_courses

--d
CREATE VIEW v_student_prof_avg AS
SELECT s.name AS student, i.name AS professor, 
       AVG(CASE WHEN t.grade ='A+' THEN 100
                WHEN t.grade ='A' THEN 95
           		WHEN t.grade ='A-' THEN 90
           		WHEN t.grade ='B+' THEN 85
           		WHEN t.grade ='B' THEN 80
           		WHEN t.grade ='B-' THEN 75
           		WHEN t.grade ='C+' THEN 85
           		WHEN t.grade ='C' THEN 80
           		WHEN t.grade ='C-' THEN 75
                ELSE 0 END) AS avg_grade
FROM student s JOIN takes t ON s.ID = t.ID
              JOIN teaches te ON t.course_id = te.course_id AND t.sec_id = te.sec_id AND  
                                t.semester = te.semester AND t.year = te.year
              JOIN instructor i ON i.ID = te.ID
GROUP BY s.name, i.name;

SELECT *
from v_student_prof_avg


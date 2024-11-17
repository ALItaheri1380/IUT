--1a
select * from rental

ALTER TABLE rental ADD COLUMN Customer_Rate integer DEFAULT 50 CHECK (Customer_Rate >= 0 AND Customer_Rate <= 100);
select * from rental

SELECT * from film 
ALTER TABLE Film ADD COLUMN Score numeric(8,2);
SELECT * from film 

---------------------------------------1b

CREATE OR REPLACE FUNCTION update_film_score()
RETURNS trigger AS $$
BEGIN
  UPDATE Film 
  SET score = (
    SELECT AVG(r.customer_rate)
    FROM rental r 
    JOIN inventory i ON r.inventory_id = i.inventory_id
    WHERE i.film_id in(
            SELECT film_id
            FROM inventory 
            WHERE inventory_id = new.inventory_id
            )  
  )
  WHERE film_id in(
          SELECT film_id
          FROM inventory 
          WHERE inventory_id = new.inventory_id
          ) ;
  
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER update_score
AFTER UPDATE OF Customer_Rate ON Rental
FOR EACH ROW
EXECUTE PROCEDURE update_film_score();


--1c

select f.Score
from rental as r,film as f,inventory as i
where r.inventory_id = i.inventory_id and i.film_id = f.film_id and r.rental_id=2; 

UPDATE Rental 
SET Customer_Rate = 100
where rental_id = 2;

select f.Score
from rental as r,film as f,inventory as i
where r.inventory_id = i.inventory_id and i.film_id = f.film_id and r.rental_id=2;


--2 
CREATE OR REPLACE FUNCTION get_actor_films(p_actor_id integer)
RETURNS TABLE(film_id integer, rental_count bigint, customer_satisfaction numeric)
AS $$
BEGIN
    RETURN QUERY
    SELECT f.film_id, COUNT(r.rental_id), CASE when AVG(r.customer_rate) is NULL then 0 else AVG(r.customer_rate) end
    FROM film f
    JOIN film_actor fa ON f.film_id = fa.film_id
    left JOIN inventory i ON f.film_id = i.film_id
    left JOIN rental r ON i.inventory_id = r.inventory_id
    WHERE fa.actor_id = p_actor_id
    GROUP BY f.film_id;
END;
$$ LANGUAGE plpgsql;

select * from get_actor_films(42)

--3
select title, rating,
	row_number() over (order by sum_amount DESC) AS rank_in_all,
	dense_rank() over (PARTITION BY rating order by sum_amount DESC) as rank_in_rating,
	sum_amount,
	CASE WHEN quartile = 4 THEN 1 ELSE 0 END AS is_in_fourth_quartile
FROM (
	SELECT f.title, f.rating,
			SUM(p.amount) AS sum_amount,
			NTILE(4) OVER (ORDER BY SUM(p.amount) DESC) AS quartile
	FROM payment p
	LEFT JOIN rental r ON p.rental_id = r.rental_id
	LEFT JOIN inventory i ON r.inventory_id = i.inventory_id
	LEFT JOIN film f ON i.film_id = f.film_id
	GROUP BY f.film_id, f.title, f.rating
) AS subquery
ORDER BY title;

--4
select 
	EXTRACT(MONTH FROM rental_date) AS month_number,
	rating, 
	SUM(amount) AS sum_amount,
	LAG(SUM(amount)) over (PARTITION by rating order BY EXTRACT(MONTH FROM rental_date)) AS prev_month_sales,
	LEAD(SUM(amount)) over (PARTITION by rating order BY EXTRACT(MONTH FROM rental_date)) AS next_month_sales
FROM payment
JOIN rental ON payment.rental_id = rental.rental_id
JOIN inventory ON rental.inventory_id = inventory.inventory_id
JOIN film ON inventory.film_id = film.film_id
GROUP BY EXTRACT(MONTH FROM rental_date) , rating
ORDER BY month_number

--5

create table S(id1 integer not null, id2 integer, date_time date);
insert into S values(1, 2, '2023-12-24');
insert into S values(1, null, '2023-12-23');
insert into S values(1, 2, '2023-12-22');
insert into S values(1, 1, '2023-12-21');
insert into S values(1, 1, '2023-12-20');
insert into S values(2, 2, '2023-12-24');
insert into S values(2, 2, '2023-12-23');
insert into S values(2, null, '2023-12-22');
insert into S values(2, 1, '2023-12-21');
insert into S values(2, 1, '2023-12-20');

create table sc(
	id INTEGER,
	transaction_count INTEGER,
    last_updated DATE
)


CREATE OR REPLACE PROCEDURE update_table()
AS $$
DECLARE
  current_date DATE := CURRENT_DATE;
BEGIN
    TRUNCATE sc;
    INSERT INTO sc
    (
        SELECT id1 as id, COUNT(id1) as transaction_count, MAX(date_time) as last_updated
        FROM (
            SELECT s.id1, s.date_time
            FROM S
            WHERE current_date > date_time
            UNION ALL
            SELECT id2, date_time
            FROM s
            WHERE id1 <> id2 AND current_date > date_time
        ) AS subquery
        GROUP BY id
    );
END;
$$ LANGUAGE plpgsql;

CALL update_table();

select *
from Sc

--6

create table Y(age INTEGER, weight NUMERIC(8,2));
INSERT INTO Y
    (
        WITH RECURSIVE test AS
		(
		 SELECT 1 AS day, cast(2 as numeric) as wieght
		 UNION ALL
		 SELECT day + 1, cast(wieght + random()/10 as numeric(8,2))
		 FROM test
		 WHERE day < 70
		)
		select * from test
    );
select * from y


WITH Y_duplicate AS (
	SELECT age, row_age, weight, LAG(weight, 6) OVER (ORDER BY age) AS prev_weight
	FROM (
		SELECT weight, age, ROW_NUMBER() OVER (ORDER BY age) AS row_age
		FROM Y
	) AS subquery
)
SELECT row_age / 7 as week, age, weight, (weight / prev_weight) * 100 AS percent_weight
FROM Y_duplicate
WHERE MOD(row_age, 7) = 0
ORDER BY percent_weight DESC
limit 1






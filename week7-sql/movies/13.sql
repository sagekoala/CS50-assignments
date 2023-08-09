
-- Kevin Bacon id FROM people
-- movie_id from stars where person_id is kevin bacon's

   SELECT name FROM movies
   INNER JOIN stars ON stars.movie_id = movies.id
   INNER JOIN people ON people.id = stars.person_id
   WHERE movie_id
   IN (SELECT movie_id FROM stars WHERE person_id
   IN (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958))
   AND person_id != (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958);





SELECT title, rating FROM ratings, movies WHERE ratings.movie_id = movies.id AND year = 2010 AND rating is not NULL ORDER BY rating DESC, title ASC;
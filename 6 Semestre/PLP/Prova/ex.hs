maxtres :: Int -> Int -> Int -> Int 

maxtres x y z = if x > y && x > z then x
		else if y > x && y > z then y
		else z 

multiplica :: Int -> Int -> Int -> Int 
multiplica x y z = x*y*z

fat :: Int -> Int 

fat n = product [1..n]
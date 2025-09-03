soma x y = x + y
inc x = x + 1
dist (x1,y1) (x2,y2) = sqrt((x2 - x1)^2 + (y2 - y1)^2) 
maxTres x y z
	| x >= y && x >= z = x
	| y >= z 	   = y
	| otherwise 	   = z
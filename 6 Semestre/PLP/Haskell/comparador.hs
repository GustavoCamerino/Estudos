menorTres :: Int -> Int -> Int -> Int
menorTres x y z = if x <=  y && x <= z then x 
                else if y <= x && y <= z then y
                else  z
faz :: Int -> [Int]
faz n = [i | i <- [1..n], n `mod` i == 0]

cal :: Int -> Int
cal x = sum (faz x)
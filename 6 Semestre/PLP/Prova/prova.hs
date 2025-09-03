faz :: Int -> [Int]
faz n = [i | i <- [1..n], n `mod` i == 0]

cal :: Int -> Int
cal x = sum (faz x)

a = [0,3..24]

-- Os múltiplos de  2 e 3 entre 0 e 20

b = [x | x <- [0..20], x `mod` 2 == 0, x `mod` 3 == 0]

c = [(x, y) | x <- [1..3], y <- [1..3]]

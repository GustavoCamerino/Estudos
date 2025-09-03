type Data = (Int, Int, Int)
bissexto :: Int -> Bool
bissexto x
    | x `mod` 400 == 0 = True
    | x `mod` 4 == 0 && x `mod` 100 /= 0 = True
    | otherwise = False

valida :: Data -> Bool
valida (d, m, a)
    | d >= 1 && d <= 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) = True
    | d >= 1 && d <= 30 && (m == 4 || m == 6 || m == 9 || m == 11) = True
    | d >= 1 && d <= 28 && m == 2 && not (bissexto a) = True
    | d >= 1 && d <= 29 && m == 2 && bissexto a = True
    | otherwise = False

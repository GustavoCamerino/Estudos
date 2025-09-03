somaP :: Int -> Int
somaP n = somaPaux n 0
  where
    somaPaux 0 acc = acc
    somaPaux x acc
      | odd x = somaPaux (x - 1) (acc + x)
      | otherwise = somaPaux (x - 1) acc

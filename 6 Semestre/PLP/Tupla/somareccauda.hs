serie :: (Float, Int) -> Float
serie (x, n) = serieAux x n 1 0.0
  where
    serieAux _ 0 _ acc = acc
    serieAux x n i acc
      | even i = serieAux x (n - 1) (i + 1) (acc + (x / fromIntegral i))
      | otherwise = serieAux x (n - 1) (i + 1) (acc + (fromIntegral i / x))

idadeMedia :: Int -> Float
idadeMedia n = fromIntegral (somaIdades n) / fromIntegral n

somaIdades :: Int -> Int
somaIdades 0 = 0
somaIdades n = let (_, idade, _, _) = pess n in idade + somaIdades (n - 1)

maiorIdade :: Int -> Int
maiorIdade n = maiorIdadeAux 1 n 0 0
  where
    maiorIdadeAux i n maxIdade idx
      | i > n = idx
      | otherwise =
          let (_, idade, _, _) = pess i
          in if idade > maxIdade
             then maiorIdadeAux (i + 1) n idade i
             else maiorIdadeAux (i + 1) n maxIdade idx

mascSup25 :: Int -> Int
mascSup25 n = mascSup25Aux 1 n 0
  where
    mascSup25Aux i n acc
      | i > n = acc
      | otherwise =
          let (_, idade, _, sexo) = pess i
          in if sexo == 'M' && idade > 25
             then mascSup25Aux (i + 1) n (acc + 1)
             else mascSup25Aux (i + 1) n acc

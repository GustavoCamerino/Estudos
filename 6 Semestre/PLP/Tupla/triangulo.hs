triangulo :: (Float, Float, Float) -> (String, Float)
triangulo (a, b, c)
  | a + b > c && a + c > b && b + c > a = (tipo, a + b + c)
  | otherwise = ("Não é um triângulo", 0.0)
  where
    tipo
      | a == b && b == c = "Equilatero"
      | a == b || a == c || b == c = "Isosceles"
      | otherwise = "Escaleno"

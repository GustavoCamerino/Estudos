type Livro = (String, String, String, String, Int)
type Pessoa = (String, String, String, String)
type Emprestimo = (String, String, Data, Data, String)
type Data = (Int, Int, Int)
type Livros = [Livro]

l1,l2::Livro
l1 = ("H123C9", "Haskell", "Thompson", "Pearson", 1999)
l2 = ("M134C3", "Calculo", "James", "Stuart", 2019) 

p1,p2::Pessoa
p1 = ("BSI945", "Ana Silva", "Ana@example.com", "3333-9643")
p2 = ("BSK997", "Roberto Gomes", "Robgomes@example.com", "1345-7574")
e1,e2::Emprestimo
e1 = ("H123C9", "BSI945", (12,9,2009), (20,9,2009), "aberto")
e2 = ("M134C3", "BSK997", (14,6,2009), (22,6,2009), "fechado")

bdLivros::Livros
bdLivros[Livro]

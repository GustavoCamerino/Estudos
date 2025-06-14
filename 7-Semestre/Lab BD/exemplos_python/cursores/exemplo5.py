import mysql.connector

if __name__ == '__main__':

    #cria uma conexao
    con = mysql.connector.connect(option_files = 'config.cnf')

    #cria um cursor
    cur = con.cursor()

    #executa uma consulta
    sql = """select editora_nome, count(*) as numero_livros
             from livro natural join editora
             group by editora_nome
             having numero_livros > %(qtd)s"""
    
    params = {'qtd': 10}
    cur.execute(sql, params=params) #usando dicionário

    if cur.with_rows:
        tuplas = cur.fetchall()
        for tup in tuplas:
            print("Editora = {0}, Numero_livros = {1}".format(tup[0], tup[1]))

    cur.close()
    con.close()    
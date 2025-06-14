import mysql.connector

if __name__ == '__main__':

    #cria uma conexao
    con = mysql.connector.connect(option_files = 'config.cnf')

    #cria um cursor
    cur = con.cursor(dictionary=True)

    #executa uma consulta
    sql = """select editora_nome, count(*) as numero_livros
             from livro natural join editora
             group by editora_nome
             having numero_livros > 10"""
    
    cur.execute(sql)

    if cur.with_rows:
        tupla = cur.fetchone()
        while(tupla):
            print("Editora = {0}, Numero_livros = {1}".format(tupla["editora_nome"], tupla["numero_livros"]))
            tupla = cur.fetchone()

    cur.close()
    con.close()    
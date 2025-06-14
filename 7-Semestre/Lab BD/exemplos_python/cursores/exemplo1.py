import mysql.connector

if __name__ == '__main__':

    #cria uma conexao
    con = mysql.connector.connect(option_files = 'config.cnf')

    #cria um cursor default
    cur = con.cursor()

    #executa uma consulta
    sql = """selecte editora_nome, count(*) as numero_livros
             from livro natural join editora
             group by editora_nome
             having numero_livros > 10"""
    try:
        cur.execute(sql)
        if(cur.with_rows):
            tuplas = cur.fetchall()
            for tupla in tuplas:
                print("Editora = {0}, Numero_livros = {1}".format(tupla[0], tupla[1]))
    except mysql.connector.ProgrammingError as e:
        print("Houve um erro durante a execucao da consulta")
        print(e)
        

    cur.close()
    con.close()    
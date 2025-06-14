import mysql.connector
from mysql.connector import Error

try:
    # Cria uma conexão
    conn = mysql.connector.connect(option_files='config.cnf')
    if conn.is_connected():
        cur = conn.cursor()  # Cria um cursor padrão

        # SQL para realizar a consulta
        sql = """
        SELECT * from livro natural join editora
        """

        cur.execute(sql)  # Realiza a consulta estática
        tuplas = cur.fetchall()  # Busca as tuplas do servidor

        for tup in tuplas:
            print(f'{tup[0]}, ed.|Número de Livros = {tup[1]}')

        cur.close()
    else:
        print("A conexão não foi estabelecida.")
except Error as e:
    print(f"Erro ao conectar ao MySQL: {e}")
finally:
    if conn.is_connected():
        conn.close()
        print("Conexão encerrada.")

import mysql.connector

if __name__ == "__main__":

    # cria um dicionario com os parametros da conexao e faz a conexao com o servidor
    params = {
        "host":"localhost",
        "port":"3306",
        "user":"root",
        "password":"Ronca100.",
        "database":"lab1" 
    }

    con = mysql.connector.connect(**params)

    print(f"ID da conexão: {con.connection_id}")

    # fecha a conexao
    con.close()


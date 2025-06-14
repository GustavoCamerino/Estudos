import mysql.connector


if __name__ == "__main__":
    
    # cria um dicionario com os parametros da conexao e faz a conexao com o servidor
    connect_args={
        "host":"localhost",
        "port":"3306",
        "user":"root",
        "password":"Ronca100.",
        "database":"lab1" 
    }

    conn = mysql.connector.connect(**connect_args)

    print(f"ID da conexão: {conn.connection_id}")
    conn.close()
import mysql.connector
if __name__ == "__main__":
    conn = mysql.connector.connect(option_files="Con.cnf")

    print(f'ID da conexão: {conn.connection_id}')
    conn.close()
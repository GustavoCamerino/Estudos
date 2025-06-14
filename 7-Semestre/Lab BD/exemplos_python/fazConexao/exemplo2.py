import mysql.connector

if __name__ == "__main__":
    # Estabelece conexao com o servidor MySQL
    con = mysql.connector.connect(option_files = "config.cnf")

    print('Conexão estabelecida! \n Id da conexao = {0}'.format(con.connection_id))    

    # fecha a conexao
    con.close()


#Sempre c

import mysql.connector

conn = mysql.connector.connect(
    host = "localhost",user = "root",password = "Ronca100.",database="lab1"
    )

print(f"ID da conexão: {conn.connection_id}")
conn.close()
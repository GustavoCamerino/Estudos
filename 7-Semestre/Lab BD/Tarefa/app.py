import mysql.connector
from mysql.connector import Error

# Consultas SQL
todos_query = "SELECT L.isbn13, L.titulo, L.num_paginas FROM livro as L"

editora_query = """
    SELECT L.isbn13, L.titulo, L.num_paginas 
    FROM livro as L, editora as E
    WHERE L.editora_id = E.editora_id AND E.editora_nome = %s
"""

autor_query = """
    SELECT L.isbn13, L.titulo, L.num_paginas 
    FROM livro as L, livro_autor LA, autor as A
    WHERE A.autor_id = LA.autor_id 
    AND LA.livro_id = L.livro_id
    AND A.autor_nome = %s
"""

update_pages_query = """
    UPDATE livro AS L
    JOIN editora AS E ON L.editora_id = E.editora_id
    SET L.num_paginas = %s
    WHERE E.editora_nome = %s
"""

def busca_editoras(connection):
    """ Obtém todas as editoras do BD """
    editoras = ["Any"]
    
    try:
        cursor = connection.cursor()
        cursor.execute("SELECT editora_nome FROM editora")
        editoras.extend([row[0] for row in cursor.fetchall()])

    except Error as e:
        print("Erro ao buscar editoras", e)

    return editoras

def busca_autores(connection):
    """ Obtém todos os autores do BD """
    autores = ["Any"]
    
    try:
        cursor = connection.cursor()
        cursor.execute("SELECT autor_nome FROM autor")
        autores.extend([row[0] for row in cursor.fetchall()])
        
    except Error as e:
        print("Erro ao buscar autores", e)
    
    return autores

def select_option(prompt, options):
    """ Permite ao usuário selecionar uma opção """
    while True:
        print(prompt)
        for i, option in enumerate(options, 1):
            print(f"{i}) {option}")
        choice = int(input("Selecione uma opção: "))
        if 1 <= choice <= len(options):
            return options[choice - 1]

def execute_query(connection, query, params):
    """ Executa uma consulta com parâmetros e exibe os resultados """
    try:
        cursor = connection.cursor()
        cursor.execute(query, params)
        for row in cursor.fetchall():
            print(row)
    except Error as e:
        print("Erro ao executar consulta", e)

def update_pages(connection, publisher, pages):
    """ Atualiza o número de páginas dos livros de uma editora """
    try:
        cursor = connection.cursor()
        cursor.execute(update_pages_query, (pages, publisher))
        connection.commit()
        print(f"Número de páginas atualizado para {pages} para todos os livros da editora {publisher}.")
    except Error as e:
        print("Erro ao atualizar número de páginas", e)

def main():
    connection = mysql.connector.connect(option_files='config.cnf')
    if connection:
        editoras = busca_editoras(connection)
        autores = busca_autores(connection)

        while True:
            choice = input("(A) Alterar páginas\n(B) Consultar por Editora\n(C) Consultar por Autor\n(S) Sair\n").upper()
            if choice == "A":
                publisher = select_option("Editoras:", editoras[1:])
                pages = int(input("Mudar o número de páginas para: "))
                update_pages(connection, publisher, pages)
            elif choice == "B":
                publisher = select_option("Editoras:", editoras)
                if publisher != "Any":
                    execute_query(connection, editora_query, (publisher,))
                else:
                    execute_query(connection, todos_query, ())
            elif choice == "C":
                author = select_option("Autores:", autores)
                if author != "Any":
                    execute_query(connection, autor_query, (author,))
                else:
                    execute_query(connection, todos_query, ())
            elif choice == "S":
                break

        connection.close()

if __name__ == "__main__":
    main()

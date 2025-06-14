import java.io.*;
import java.nio.charset.*;
import java.nio.file.*;
import java.sql.*;
import java.util.*;

/**
 * Este programa demonstra varias consultas no banco de dados catalogo_livros.
 * Adptado do exemplo 5.3, capitulo 5, do livro Core Java, volume 2, edicao 12.
 */
public class TestaConsulta
{
   private static final String todosQuery = "SELECT L.isbn13, L.titulo, L.num_paginas FROM livro as L";

   //selecionar livros, dados o nome do autor e da editora
   private static final String autorEditoraQuery = """
      SELECT L.isbn13, L.titulo, L.num_paginas
      FROM livro as L, livro_autor as LA, autor as A, editora as E
      WHERE A.autor_id = LA.autor_id
            AND LA.livro_id = L.livro_id
            AND L.editora_id = E.editora_id
            AND A.autor_nome = ? AND E.editora_nome = ?""";
  
   //selecionar os livros, dado o nome do autor
   private static final String autorQuery = """
      SELECT L.isbn13, L.titulo, L.num_paginas 
      FROM livro as L, livro_autor LA, autor as A
      WHERE  A.autor_id = LA.autor_id 
             AND LA.livro_id = L.livro_id
             AND A.autor_nome = ?""";

   //seleciona os livros, dado o nome da editora
   private static final String editoraQuery = """
      SELECT L.isbn13, L.titulo, L.num_paginas 
      FROM livro as L, editora as E
      WHERE L.editora_id = E.editora_id AND E.editora_nome = ?""";
   
   //atualiza o numero de paginas dos livros de uma editora (sem sentido, mas ok!)
   private static final String paginasUpdate = """
      UPDATE livro SET num_paginas = num_paginas + ? 
      WHERE livro._id = (SELECT editora_id FROM editora WHERE editora_nome = ?)""";

   private static Scanner in;
   private static ArrayList<String> autores = new ArrayList<>();
   private static ArrayList<String> editoras = new ArrayList<>();
   
   public static void main(String[] args) throws IOException
   {
      // Preenche as listas de autores e editoras
      try (Connection conn = getConnection()) 
      {
         autores.add("Any");
         editoras.add("Any");
         try (Statement stat = conn.createStatement())
         {
            // Preenche a lista de autores
            String query = "SELECT autor_nome FROM autor";
            try (ResultSet rs = stat.executeQuery(query))
            {
               while (rs.next())
                  autores.add(rs.getString("autor_nome"));
            }
               
            // Preenche a lista de editoras
            query = "SELECT editora_nome FROM editora";
            try (ResultSet rs = stat.executeQuery(query))
            {
               while (rs.next())
                  editoras.add(rs.getString("editora_nome"));
            }
         }
         
         // Menu
         boolean done = false;
         in = new Scanner(System.in);
         while (!done)
         {
            System.out.print("(C) Consulta (A) Altera paginas (S) Sair: ");
            String input = in.next().toUpperCase();
            if (input.equalsIgnoreCase("C"))
               executaConsulta(conn);
            else if (input.equalsIgnoreCase("A"))
               alteraPaginas(conn);
            else 
               done = true;
         }
      }catch (SQLException e)
      {
         for (Throwable t : e)
            System.out.println(t.getMessage());
      }
   }

   /**
    * Executa a consulta selecionada.
    * @param conn a conexão com o banco de dados
    */
   private static void executaConsulta(Connection conn) throws SQLException
   {
      // Solicita que o usuario escolha um autor e uma editora
      String autor = select("Autores:", autores);
      String editora = select("Editoras:", editoras);
      
      PreparedStatement stat;
      if (!autor.equals("Any") && !editora.equals("Any"))
      {
         stat = conn.prepareStatement(autorEditoraQuery);
         stat.setString(1, autor);
         stat.setString(2, editora);
      }
      else if (!autor.equals("Any") && editora.equals("Any"))
      {
          stat = conn.prepareStatement(autorQuery);
          stat.setString(1, autor);
      }
      else if (autor.equals("Any") && !editora.equals("Any"))
      {
          stat = conn.prepareStatement(editoraQuery);
          stat.setString(1, editora);
      }
      else
         stat = conn.prepareStatement(todosQuery);
      
      try (ResultSet rs = stat.executeQuery())
      {
         while (rs.next())
            System.out.println(rs.getString(1) + ", " + rs.getString(2) + ", " + rs.getString(3));
      }
   }

   /**
    * Pede o usuario para selecionar uma string.
    * @param prompt o texto apresentado para incitar o usuario 
    * @param options as opcoes que o usuario pode escolher 
    * @return a opcao que o usuario escolheu
    */
    public static String select(String prompt, List<String> options)
    {
       while (true)
       {
          System.out.println(prompt);     
          for (int i = 0; i < options.size(); i++)
             System.out.printf("%2d) %s%n", i + 1, options.get(i));
          int sel = in.nextInt();
          if (sel > 0 && sel <= options.size())
             return options.get(sel - 1);
       }      
    }

   /**
    * Executa uma atualizacao do numero de paginas.
    * @param conn the database connection
    */
   public static void alteraPaginas(Connection conn) throws SQLException
   {
      String editora = select("Editoras:", editoras.subList(1, editoras.size()));
      System.out.print("Mudar o numero de paginas por: ");
      int numero = in.nextInt();
      PreparedStatement stat = conn.prepareStatement(paginasUpdate);
      stat.setDouble(1, numero);
      stat.setString(2, editora);
      int r = stat.executeUpdate();
      System.out.println(r + " tuplas atualizadas.");
   }
   

   /**
    * Obtem uma conexao dos parametros especificados no arquivo database.properties.
    * @return o objeto de conexao com o banco de dados
    */
   public static Connection getConnection() throws SQLException, IOException
   {

      String url = "jdbc:mysql://localhost:3306/Catalogo_Livros";
      String username = "linder";
      String password = "labbd2024";

      return DriverManager.getConnection(url, username, password);
   }
}

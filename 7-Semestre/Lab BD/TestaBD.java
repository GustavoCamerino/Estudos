import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class GerenciadorBiblioteca {

    private static final String URL = "jdbc:mysql://localhost:3306/teste?autoReconnect=true&useSSL=false&allowPublicKeyRetrieval=true";
    private static final String USUARIO = " ;
    private static final String SENHA = "";

    public static void main(String[] args) {
        System.out.println("Iniciando Gerenciador de Biblioteca...");

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            System.out.println("Driver JDBC do MySQL carregado.");

            try (Connection conexao = DriverManager.getConnection(URL, USUARIO,
            // SENHA);
                 Scanner scanner = new Scanner(System.in)) {
                    
                System.out.println("Conexão com o MySQL estabelecida com sucesso!");

                if (!conexao.isValid(5)) {
                    System.err.println("A conexão não é válida ou expirou. Abortando operações.");
                    return;
                }

                int opcao = -1;
                while (opcao != 0) {
                    exibirMenu();
                    System.out.print("Escolha uma opção: ");
                    try {
                        opcao = Integer.parseInt(scanner.nextLine());

                        switch (opcao) {
                            case 1:
                                criarTabelas(conexao);
                                break;
                            case 2:
                                inserirLivroEAutor(conexao, scanner);
                                break;
                            case 3:
                                System.out.print("Digite o título do livro para consultar: ");
                                String tituloConsulta = scanner.nextLine();
                                consultarLivroPorTitulo(conexao, tituloConsulta);
                                break;
                            case 4:
                                System.out.print("Digite o título do livro para deletar: ");
                                String tituloDelecao = scanner.nextLine();
                                deletarLivroPorTitulo(conexao, tituloDelecao);
                                break;
                            case 5:
                                listarTodosLivrosComAutores(conexao);
                                break;
                            case 6:
                                inserirCapaLivro(conexao, scanner);
                                break;
                            case 7:
                                consultarCapaLivro(conexao, scanner);
                                break;
                            case 0:
                                System.out.println("Saindo da aplicação. Até mais!");
                                break;
                            default:
                                System.out.println("Opção inválida. Por favor, tente novamente.");
                        }
                    } catch (NumberFormatException e) {
                        System.out.println("Entrada inválida. Por favor, digite um número.");
                    }
                    System.out.println("\nPressione Enter para continuar...");
                    scanner.nextLine();
                }

            }
            System.out.println("\nRecursos do banco de dados e scanner foram fechados automaticamente.");

        } catch (ClassNotFoundException e) {
            System.err.println("Erro: Driver JDBC do MySQL não encontrado. Verifique o CLASSPATH.");
            e.printStackTrace();
        } catch (SQLException e) {
            System.err.println("Erro de SQL: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void exibirMenu() {
        System.out.println("\n--- MENU DE GERENCIAMENTO DE BIBLIOTECA ---");
        System.out.println("1. Criar Tabelas (autores, livros, publica, capa_livro)");
        System.out.println("2. Inserir Livro, Autor e Publicação");
        System.out.println("3. Consultar Livro por Título");
       
     *  System.out.println("4. Deletar Livro por Título");
        System.out.println("5. Listar Todos os Livros com Autores e Edições");
        System.out.println("6. Inserir/Atualizar Capa de Livro");
        System.out.println("7. Consultar Capa de Livro por ID");
        System.out.println("0. Sair");
        System.out.println("-------------------------------------------");
    }

    private static void criarTabelas(Connection conexao) throws SQLException {
        try (Statement stmt = conexao.createStatement()) {
            String sqlAutores = "CREATE TABLE IF NOT EXISTS autores (" +
                                "id_autor INT AUTO_INCREMENT PRIMARY KEY," +
                                "nome VARCHAR(100) NOT NULL," +
       
     *                           "sobrenome VARCHAR(100) NOT NULL" +
                                ") ENGINE=InnoDB;";
            stmt.executeUpdate(sqlAutores);
            System.out.println("Tabela 'autores' criada ou já existente.");

            String sqlLivros = "CREATE TABLE IF NOT EXISTS livros (" +
                               "id_publicacao INT AUTO_INCREMENT PRIMARY KEY," +
                               "titulo VARCHAR(255) NOT NULL," +
                               "ISBN VARCHAR(20) UNIQUE NOT NULL," +
                               "preco DECIMAL(10, 2) NOT NULL" +
                               ") ENGINE=InnoDB;";
            stmt.executeUpdate(sqlLivros);
            System.out.println("Tabela 'livros' criada ou já existente.");

            String sqlPublica = "CREATE TABLE IF NOT EXISTS publica (" +
                                "autor_id INT NOT NULL," +
                                "livro_id INT NOT NULL," +
       
     *                          "edicao INT NOT NULL," +
                                "PRIMARY KEY (autor_id, livro_id, edicao)," +
                                "FOREIGN KEY (autor_id) REFERENCES autores(id_autor) ON DELETE CASCADE," +
                                "FOREIGN KEY (livro_id) REFERENCES livros(id_publicacao) ON DELETE CASCADE" +
                                ") ENGINE=InnoDB;";
                tmt.executeUpdate(sqlPublica);
            System.out.println("Tabela 'publica' criada ou já existente.");

            String sqlCapaLivro = "CREATE TABLE IF NOT EXISTS capa_livro (" +
                                  "livro_id INT PRIMARY KEY," +
                                  "capa LONGBLOB," +
                                  "FOREIGN KEY (livro_id) REFERENCES livros(id_publicacao) ON DELETE CASCADE" +
                                  ") ENGINE=InnoDB;";
            stmt.executeUpdate(sqlCapaLivro);
            System.out.println("Tabela 'capa_livro' criada ou já existente.");
        }
    }

    private static void inserirLivroEAutor(Connection conexao, Scanner scanner) throws SQLException {
        conexao.setAutoCommit(false);
 
     * 
        try {
            System.out.println("\n--- Inserir Novo Livro e Autor ---");
            System.out.print("Nome do Autor: ");
            String nomeAutor = scanner.nextLine();
            System.out.print("Sobrenome do Autor: ");
            String sobrenomeAutor = scanner.nextLine();

            int autorId = obterOuCriarAutor(conexao, nomeAutor, sobrenomeAutor);
            if (autorId == -1) {
                System.err.println("Falha ao obter ou criar o autor.");
                conexao.rollback();
                return;
            }

            System.out.print("Título do Livro: ");
            String tituloLivro = scanner.nextLine();
            System.out.print("ISBN do Livro: ");
            String isbnLivro = scanner.nextLine();

            double precoLivro = 0.0;
            boolean precoValido = false;
            while (!precoValido) {
                System.out.print("Preço do Livro (ex: 49.99): ");
                try {
                    precoLivro = Double.parseDouble(scanner.nextLine());
                    if (precoLivro < 0) {
                        System.out.println("Preço não pode ser negativo.");
                    } else {
                        precoValido = true;
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Entrada inválida para o preço. Digite um número decimal.");
                }
            }

            String sqlInsertLivro = "INSERT INTO livros (titulo, ISBN, preco) VALUES (?, ?, ?)";
            int livroId;
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlInsertLivro, Statement.RETURN_GENERATED_KEYS)) {
                pstmt.setString(1, tituloLivro);
                pstmt.setString(2, isbnLivro);
                pstmt.setDouble(3, precoLivro);
                pstmt.executeUpdate();

                try (ResultSet rs = pstmt.getGeneratedKeys()) {
                    if (rs.next()) {
                        livroId = rs.getInt(1);
                    } else {
                        throw new SQLException("Falha ao obter ID do livro inserido.");
                    }
                }
            }

            int edicao = 0;
            boolean edicaoValida = false;
            while(!edicaoValida){
                System.out.print("Edição do Livro: ");
                try {
                    edicao = Integer.parseInt(scanner.nextLine());
                    if (edicao <= 0) {
                        System.out.println("Edição deve ser um número positivo.");
                    } else {
                        edicaoValida = true;
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Entrada inválida para a edição. Digite um número inteiro.");
                }
            }

            String sqlInsertPublica = "INSERT INTO publica (autor_id, livro_id, edicao) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlInsertPublica)) {
                pstmt.setInt(1, autorId);
                pstmt.setInt(2, livroId);
                pstmt.setInt(3, edicao);
                pstmt.executeUpdate();
            }

            conexao.commit();
            System.out.println("Livro, autor e publicação inseridos com sucesso!");

        } catch (SQLException e) {
            conexao.rollback();
            System.err.println("Erro ao inserir livro e autor. Transação desfeita.");
            throw e;
        } finally {
            conexao.setAutoCommit(true);
        }
    }

    private static int obterOuCriarAutor(Connection conexao, String nome, String sobrenome) throws SQLException {
        String sqlSelect = "SELECT id_autor FROM autores WHERE nome = ? AND sobrenome = ?";
        try (PreparedStatement pstmt = conexao.prepareStatement(sqlSelect)) {
            pstmt.setString(1, nome);
            pstmt.setString(2, sobrenome);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("id_autor");
                }
            }
        }

        String sqlInsert = "INSERT INTO autores (nome, sobrenome) VALUES (?, ?)";
        try (PreparedStatement pstmt = conexao.prepareStatement(sqlInsert, Statement.RETURN_GENERATED_KEYS)) {
            pstmt.setString(1, nome);
            pstmt.setString(2, sobrenome);
            pstmt.executeUpdate();

            try (ResultSet rs = pstmt.getGeneratedKeys()) {
                if (rs.next()) {
                    return rs.getInt(1);
                } else {
                    System.err.println("Falha ao obter ID do autor recém-inserido.");
                    return -1;
                }
            }
        }
    }

    private static void consultarLivroPorTitulo(Connection conexao, String titulo) throws SQLException {
        String sql = "SELECT l.id_publicacao, l.titulo, l.ISBN, l.preco, a.nome, a.sobrenome, p.edicao " +
                     "FROM livros l " +
                     "JOIN publica p ON l.id_publicacao = p.livro_id " +
                     "JOIN autores a ON p.autor_id = a.id_autor " +
                     "WHERE LOWER(l.titulo) LIKE ?";

        System.out.println("\n--- Consulta de Livro por Título ---");
        try (PreparedStatement pstmt = conexao.prepareStatement(sql)) {
            pstmt.setString(1, "%" + titulo.toLowerCase() + "%");

            try (ResultSet rs = pstmt.executeQuery()) {
                if (!rs.isBeforeFirst()) {
                    System.out.println("Nenhum livro encontrado com o título '" + titulo + "'.");
                } else {
                    while (rs.next()) {
                        System.out.println("ID Livro: " + rs.getInt("id_publicacao"));
                        System.out.println("Título: " + rs.getString("titulo"));
                        System.out.println("ISBN: " + rs.getString("ISBN"));
                        System.out.println("Preço: " + String.format("%.2f", rs.getDouble("preco")));
                        System.out.println("Autor: " + rs.getString("nome") + " " + rs.getString("sobrenome"));
                        System.out.println("Edição: " + rs.getInt("edicao"));
                        System.out.println("--------------------");
                    }
                }
            }
        }
    }

    private static void deletarLivroPorTitulo(Connection conexao, String titulo) throws SQLException {
        conexao.setAutoCommit(false);

        try {
            String sqlSelectId = "SELECT id_publicacao FROM livros WHERE LOWER(titulo) = ?";
            int livroId = -1;
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlSelectId)) {
                pstmt.setString(1, titulo.toLowerCase());
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        livroId = rs.getInt("id_publicacao");
                    }
                }
            }

            if (livroId == -1) {
                System.out.println("Livro com título '" + titulo + "' não encontrado.");
                conexao.rollback();
                return;
            }

            String sqlDeleteLivro = "DELETE FROM livros WHERE id_publicacao = ?";
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlDeleteLivro)) {
                pstmt.setInt(1, livroId);
                int linhasAfetadas = pstmt.executeUpdate();
                if (linhasAfetadas > 0) {
                    System.out.println("Livro '" + titulo + "' deletado com sucesso (e referências em 'publica' e 'capa_livro').");
                } else {
                    System.out.println("Erro ao deletar livro '" + titulo + "'.");
                }
            }
            conexao.commit();

        } catch (SQLException e) {
            conexao.rollback();
            System.err.println("Erro ao deletar livro. Transação desfeita.");
            throw e;
        } finally {
            conexao.setAutoCommit(true);
        }
    }

    private static void listarTodosLivrosComAutores(Connection conexao) throws SQLException {
        String sql = "SELECT l.id_publicacao, l.titulo, l.ISBN, l.preco, a.nome, a.sobrenome, p.edicao " +
                     "FROM livros l " +
                     "JOIN publica p ON l.id_publicacao = p.livro_id " +
                     "JOIN autores a ON p.autor_id = a.id_autor " +
                     "ORDER BY l.titulo, a.nome, a.sobrenome, p.edicao";

        System.out.println("\n--- Todos os Livros Cadastrados ---");
        try (Statement stmt = conexao.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            if (!rs.isBeforeFirst()) {
                System.out.println("Nenhum livro cadastrado.");
            } else {
                while (rs.next()) {
                    System.out.println("ID Livro: " + rs.getInt("id_publicacao"));
                    System.out.println("Título: " + rs.getString("titulo"));
                    System.out.println("ISBN: " + rs.getString("ISBN"));
                    System.out.println("Preço: " + String.format("%.2f", rs.getDouble("preco")));
                    System.out.println("Autor: " + rs.getString("nome") + " " + rs.getString("sobrenome"));
                    System.out.println("Edição: " + rs.getInt("edicao"));
                    System.out.println("--------------------");
                }
            }
        }
    }

    private static void inserirCapaLivro(Connection conexao, Scanner scanner) throws SQLException {
        System.out.println("\n--- Inserir/Atualizar Capa de Livro ---");
        System.out.print("Digite o ID do livro para adicionar/atualizar a capa: ");
        int livroId = -1;
        try {
            livroId = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("ID de livro inválido. Por favor, digite um número.");
            return;
        }

        String sqlCheckLivro = "SELECT COUNT(*) FROM livros WHERE id_publicacao = ?";
        try (PreparedStatement pstmt = conexao.prepareStatement(sqlCheckLivro)) {
            pstmt.setInt(1, livroId);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next() && rs.getInt(1) == 0) {
                    System.out.println("Livro com ID " + livroId + " não encontrado.");
                    return;
                }
            }
        }

        System.out.print("Digite o caminho completo da imagem da capa (ex: C:/imagens/capa.jpg): ");
        String caminhoImagem = scanner.nextLine();

        File imagemFile = new File(caminhoImagem);
        if (!imagemFile.exists() || !imagemFile.isFile()) {
            System.out.println("Arquivo de imagem não encontrado ou inválido: " + caminhoImagem);
            return;
        }

        try (FileInputStream fis = new FileInputStream(imagemFile)) {
            String sqlInsertUpdateCapa = "INSERT INTO capa_livro (livro_id, capa) VALUES (?, ?) " +
                                         "ON DUPLICATE KEY UPDATE capa = VALUES(capa)";
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlInsertUpdateCapa)) {
                pstmt.setInt(1, livroId);
                pstmt.setBinaryStream(2, fis, (int) imagemFile.length());
                pstmt.executeUpdate();
                System.out.println("Capa para o livro ID " + livroId + " inserida/atualizada com sucesso!");
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo de imagem: " + e.getMessage());
        }
    }

    private static void consultarCapaLivro(Connection conexao, Scanner scanner) throws SQLException {
        System.out.println("\n--- Consultar Capa de Livro ---");
        System.out.print("Digite o ID do livro para consultar a capa: ");
        int livroId = -1;
        try {
            livroId = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("ID de livro inválido. Por favor, digite um número.");
            return;
        }

        String sql = "SELECT capa FROM capa_livro WHERE livro_id = ?";
        try (PreparedStatement pstmt = conexao.prepareStatement(sql)) {
            pstmt.setInt(1, livroId);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    byte[] capaBytes = rs.getBytes("capa");
                    if (capaBytes != null) {
                        System.out.println("Capa encontrada para o livro ID " + livroId + ".");
                        System.out.println("Tamanho da capa (bytes): " + capaBytes.length);
                        System.out.println("Para exibir a imagem, você precisaria de uma interface gráfica.");
                    } else {
                        System.out.println("Nenhuma capa encontrada para o livro ID " + livroId + ".");
                    }
                } else {
                    System.out.println("Nenhuma capa encontrada para o livro ID " + livroId + ".");
                }
            }
        }
    }
}
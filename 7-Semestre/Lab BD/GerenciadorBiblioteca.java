import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class GerenciadorBiblioteca {

    // Detalhes da conexão com o banco de dados
    private static final String URL = "jdbc:mysql://localhost:3306/teste?autoReconnect=true&useSSL=false&allowPublicKeyRetrieval=true";
    private static final String USUARIO = "root"; // Substitua pelo seu usuário do MySQL
    private static final String SENHA = "";     // Substitua pela sua senha do MySQL

    public static void main(String[] args) {
        System.out.println("Iniciando Gerenciador de Biblioteca...");

        try {
            // Carregar o driver JDBC para MySQL
            Class.forName("com.mysql.jdbc.Driver");
            System.out.println("Driver JDBC do MySQL carregado.");

            // Usar try-with-resources para garantir que a conexão e o scanner sejam fechados automaticamente
            try (Connection conexao = DriverManager.getConnection(URL, USUARIO, SENHA);
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
                    scanner.nextLine(); // Consome o Enter após a seleção da opção
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

    /**
     * Exibe o menu de opções para o usuário.
     */
    private static void exibirMenu() {
        System.out.println("\n--- MENU DE GERENCIAMENTO DE BIBLIOTECA ---");
        System.out.println("1. Criar Tabelas (autores, livros, publica)");
        System.out.println("2. Inserir Livro, Autor e Publicação");
        System.out.println("3. Consultar Livro por Título");
        System.out.println("4. Deletar Livro por Título");
        System.out.println("5. Listar Todos os Livros com Autores e Edições");
        System.out.println("0. Sair");
        System.out.println("-------------------------------------------");
    }

    /**
     * Cria as tabelas 'autores', 'livros' e 'publica' se não existirem.
     * @param conexao A conexão JDBC com o banco de dados.
     * @throws SQLException Se ocorrer um erro SQL.
     */
    private static void criarTabelas(Connection conexao) throws SQLException {
        try (Statement stmt = conexao.createStatement()) {
            // Tabela autores
            String sqlAutores = "CREATE TABLE IF NOT EXISTS autores (" +
                                "id_autor INT AUTO_INCREMENT PRIMARY KEY," +
                                "nome VARCHAR(100) NOT NULL," +
                                "sobrenome VARCHAR(100) NOT NULL" +
                                ") ENGINE=InnoDB;"; // InnoDB para suportar chaves estrangeiras
            stmt.executeUpdate(sqlAutores);
            System.out.println("Tabela 'autores' criada ou já existente.");

            // Tabela livros
            String sqlLivros = "CREATE TABLE IF NOT EXISTS livros (" +
                               "id_publicacao INT AUTO_INCREMENT PRIMARY KEY," +
                               "titulo VARCHAR(255) NOT NULL," +
                               "ISBN VARCHAR(20) UNIQUE NOT NULL," +
                               "preco DECIMAL(10, 2) NOT NULL" +
                               ") ENGINE=InnoDB;";
            stmt.executeUpdate(sqlLivros);
            System.out.println("Tabela 'livros' criada ou já existente.");

            // Tabela Publica (tabela de junção)
            String sqlPublica = "CREATE TABLE IF NOT EXISTS publica (" +
                                "autor_id INT NOT NULL," +
                                "livro_id INT NOT NULL," +
                                "edicao INT NOT NULL," +
                                "PRIMARY KEY (autor_id, livro_id, edicao)," + // Chave primária composta
                                "FOREIGN KEY (autor_id) REFERENCES autores(id_autor) ON DELETE CASCADE," +
                                "FOREIGN KEY (livro_id) REFERENCES livros(id_publicacao) ON DELETE CASCADE" +
                                ") ENGINE=InnoDB;";
            stmt.executeUpdate(sqlPublica);
            System.out.println("Tabela 'publica' criada ou já existente.");
        }
    }

    /**
     * Insere um autor (se não existir), um livro e a relação de publicação.
     * @param conexao A conexão JDBC com o banco de dados.
     * @param scanner O objeto Scanner para ler a entrada do usuário.
     * @throws SQLException Se ocorrer um erro SQL.
     */
    private static void inserirLivroEAutor(Connection conexao, Scanner scanner) throws SQLException {
        conexao.setAutoCommit(false); // Inicia transação

        try {
            System.out.println("\n--- Inserir Novo Livro e Autor ---");
            System.out.print("Nome do Autor: ");
            String nomeAutor = scanner.nextLine();
            System.out.print("Sobrenome do Autor: ");
            String sobrenomeAutor = scanner.nextLine();

            // Verificar se o autor já existe
            int autorId = obterOuCriarAutor(conexao, nomeAutor, sobrenomeAutor);
            if (autorId == -1) { // Caso ocorra algum problema na criação/obtenção
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

            // Inserir o livro
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


            // Inserir na tabela Publica
            String sqlInsertPublica = "INSERT INTO publica (autor_id, livro_id, edicao) VALUES (?, ?, ?)";
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlInsertPublica)) {
                pstmt.setInt(1, autorId);
                pstmt.setInt(2, livroId);
                pstmt.setInt(3, edicao);
                pstmt.executeUpdate();
            }

            conexao.commit(); // Confirma a transação
            System.out.println("Livro, autor e publicação inseridos com sucesso!");

        } catch (SQLException e) {
            conexao.rollback(); // Desfaz a transação em caso de erro
            System.err.println("Erro ao inserir livro e autor. Transação desfeita.");
            throw e; // Relança a exceção
        } finally {
            conexao.setAutoCommit(true); // Reativa o auto-commit
        }
    }

    /**
     * Obtém o ID de um autor existente ou cria um novo.
     * @param conexao A conexão JDBC.
     * @param nome Nome do autor.
     * @param sobrenome Sobrenome do autor.
     * @return O ID do autor. Retorna -1 em caso de erro.
     * @throws SQLException Se ocorrer um erro SQL.
     */
    private static int obterOuCriarAutor(Connection conexao, String nome, String sobrenome) throws SQLException {
        // Tenta encontrar o autor existente
        String sqlSelect = "SELECT id_autor FROM autores WHERE nome = ? AND sobrenome = ?";
        try (PreparedStatement pstmt = conexao.prepareStatement(sqlSelect)) {
            pstmt.setString(1, nome);
            pstmt.setString(2, sobrenome);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("id_autor"); // Autor encontrado
                }
            }
        }

        // Se não encontrou, insere um novo autor
        String sqlInsert = "INSERT INTO autores (nome, sobrenome) VALUES (?, ?)";
        try (PreparedStatement pstmt = conexao.prepareStatement(sqlInsert, Statement.RETURN_GENERATED_KEYS)) {
            pstmt.setString(1, nome);
            pstmt.setString(2, sobrenome);
            pstmt.executeUpdate();

            try (ResultSet rs = pstmt.getGeneratedKeys()) {
                if (rs.next()) {
                    return rs.getInt(1); // Retorna o ID do novo autor
                } else {
                    System.err.println("Falha ao obter ID do autor recém-inserido.");
                    return -1;
                }
            }
        }
    }

    /**
     * Consulta um livro por título e exibe todas as informações relacionadas.
     * @param conexao A conexão JDBC com o banco de dados.
     * @param titulo O título (ou parte dele) a ser pesquisado.
     * @throws SQLException Se ocorrer um erro SQL.
     */
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

    /**
     * Deleta um livro e suas referências na tabela 'publica' dado o título.
     * @param conexao A conexão JDBC com o banco de dados.
     * @param titulo O título do livro a ser deletado.
     * @throws SQLException Se ocorrer um erro SQL.
     */
    private static void deletarLivroPorTitulo(Connection conexao, String titulo) throws SQLException {
        conexao.setAutoCommit(false); // Inicia transação

        try {
            // Primeiro, obtenha o ID do livro
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

            // As chaves estrangeiras com ON DELETE CASCADE na tabela 'publica'
            // garantirão que as entradas relacionadas em 'publica' serão deletadas automaticamente
            // quando o livro for deletado da tabela 'livros'.

            String sqlDeleteLivro = "DELETE FROM livros WHERE id_publicacao = ?";
            try (PreparedStatement pstmt = conexao.prepareStatement(sqlDeleteLivro)) {
                pstmt.setInt(1, livroId);
                int linhasAfetadas = pstmt.executeUpdate();
                if (linhasAfetadas > 0) {
                    System.out.println("Livro '" + titulo + "' deletado com sucesso (e referências em 'publica').");
                } else {
                    System.out.println("Erro ao deletar livro '" + titulo + "'.");
                }
            }
            conexao.commit(); // Confirma a transação

        } catch (SQLException e) {
            conexao.rollback(); // Desfaz a transação em caso de erro
            System.err.println("Erro ao deletar livro. Transação desfeita.");
            throw e; // Relança a exceção
        } finally {
            conexao.setAutoCommit(true); // Reativa o auto-commit
        }
    }

    /**
     * Lista todos os livros cadastrados, com seus autores e edições.
     * @param conexao A conexão JDBC com o banco de dados.
     * @throws SQLException Se ocorrer um erro SQL.
     */
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
}
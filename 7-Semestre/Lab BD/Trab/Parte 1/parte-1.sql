-- Criar o banco de dados
CREATE DATABASE Empresa;
USE Empresa;

-- Tabela de Clientes
CREATE TABLE Clientes( 
	id INT PRIMARY KEY,
    email VARCHAR(50),
	nome VARCHAR(100),
    telefone CHAR(20),
    cpf CHAR(15),
    historico TEXT
);

-- Tabela de Endereços (endereços múltiplos por cliente)
CREATE TABLE EnderecosClientes (
    endereco_id INT PRIMARY KEY,
    cliente_id INT,
    endereco VARCHAR(100),
    FOREIGN KEY (cliente_id) REFERENCES Clientes(id)
);

-- Tabela de Restaurantes
CREATE TABLE Restaurantes(
	id INT PRIMARY KEY,
	nome VARCHAR(100),
    endereco VARCHAR(100),
    telefone CHAR(20),
	tipoculinaria VARCHAR(50)
);

-- Tabela de Horários de Funcionamento dos Restaurantes
CREATE TABLE HorariosFuncionamentoRestaurantes(
	horariofuncionamento_id INT PRIMARY KEY, 
	restaurante_id INT, 
	dia_semana CHAR(15),
	horarioabertura TIME,
	horariofechamento TIME,
	FOREIGN KEY (restaurante_id) REFERENCES Restaurantes(id),
	UNIQUE (restaurante_id, dia_semana)
);

-- Tabela de Categorias de Pratos
CREATE TABLE CategoriasPratos(
	categoria_id INT PRIMARY KEY, 
	nome_categoria VARCHAR(50) NOT NULL UNIQUE,
	estoque INT CHECK(estoque >= 0)
);

-- Tabela de Pratos
CREATE TABLE Pratos (
    prato_id INT PRIMARY KEY,
    restaurante_id INT,
    categoria_id INT,
    nome VARCHAR(100),
    descricao TEXT,
    preco DECIMAL(10,2),
    status_disponibilidade BOOLEAN,
    estoque INT CHECK (estoque >= 0),
    FOREIGN KEY (restaurante_id) REFERENCES Restaurantes(id),
    FOREIGN KEY (categoria_id) REFERENCES CategoriasPratos(categoria_id)
);

-- Tabela de Pedidos
CREATE TABLE Pedidos(
	id INT PRIMARY KEY,
    cliente_id INT,
    restaurante_pedido_id INT,
    data_hora TIMESTAMP,
    statusatual VARCHAR(30),
    formapagamento VARCHAR(30),
    valortotal DECIMAL(10,2),
    FOREIGN KEY (cliente_id) REFERENCES Clientes(id),
    FOREIGN KEY (restaurante_pedido_id) REFERENCES Restaurantes(id)
);

-- Tabela de Itens do Pedido
CREATE TABLE ItensPedido (
    item_id INT PRIMARY KEY,
    pedido_id INT,
    prato_id INT,
    quantidade INT,
    preco_item DECIMAL(10,2),
    observacao TEXT,
    FOREIGN KEY (pedido_id) REFERENCES Pedidos(id),
    FOREIGN KEY (prato_id) REFERENCES Pratos(prato_id)
);

-- Tabela de Avaliações de Restaurantes
CREATE TABLE AvaliacoesRestaurantes (
    avaliacao_id INT PRIMARY KEY,
    restaurante_id INT,
    cliente_id INT,
    nota INT CHECK (nota BETWEEN 0 AND 5),
    feedback TEXT,
    data_hora TIMESTAMP,
    FOREIGN KEY (restaurante_id) REFERENCES Restaurantes(id),
    FOREIGN KEY (cliente_id) REFERENCES Clientes(id)
);

-- (Opcional) Registro de Comissão de 3%
CREATE TABLE PagamentosComissao (
    pagamento_id INT PRIMARY KEY,
    pedido_id INT,
    restaurante_id INT,
    valor_total DECIMAL(10,2),
    valor_comissao DECIMAL(10,2),
    data_pagamento TIMESTAMP,
    FOREIGN KEY (pedido_id) REFERENCES Pedidos(id),
    FOREIGN KEY (restaurante_id) REFERENCES Restaurantes(id)
);

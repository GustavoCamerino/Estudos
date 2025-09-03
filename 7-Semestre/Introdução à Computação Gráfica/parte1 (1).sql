CREATE DATABASE Empresa;
USE Empresa;

CREATE TABLE Clientes( 
	id int,
    email varchar(30),
	nome varchar(30),
    telefone char(20),
    lista_endereco varchar(30),
    cpf char(15),
    historico varchar(20)
);

CREATE TABLE Restaurantes(
	id int,
	nome varchar(50),
    endereco varchar(20),
    telefone char(20),
	tipoculinaria varchar(20),
    listapratos varchar(100),
    horariofuncionamento int,
    avaliacoes varchar(100)
);

CREATE TABLE HorariosFuncionamentoRestaurantes(
	horariofuncionamento_id int, 
	restaurante_id int, 
	dia_semana char(15),
	horarioabertura int,
	horariofechamento int,
	constraint regra1 primary key(horario_funcionamento_id),
	constraint regra2 foreign key(restaurante_id) references Restaurantes(id),
	constraint regra3 unique (restaurante_id, dia_semana)
);

CREATE TABLE CategoriasPratos(
	categoria_id int, 
	nome_categoria varchar(20) not null unique,
	estoque int check(estoque >= 0),
	constraint regra4 primary key(categoria_id)
);

CREATE TABLE Pedidos(
	id int,
    cliente_id int,
    restaurante_pedido_id int,
    data_hora TIMESTAMP,
    statusatual varchar(15),
    formapagamento varchar(15),
    valortotal int,
    constraint regra5 foreign key(cliente_id) references Clientes(id),
    constraint regra6 foreign key(restaurante_pedido_id) references Restaurantes(id)
);
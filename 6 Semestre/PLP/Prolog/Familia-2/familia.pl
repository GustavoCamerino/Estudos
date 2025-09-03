% Base de conhecimento

familia( 
    pessoa(pedro, silva, data(1, abril, 1930), empregado(cnn, 1000)),
    pessoa(maria, silva, data(1, maio, 1945), empregado(bnpp, 1230)),
    [
        pessoa(manoel, silva, data(10, setembro, 1975), desempregado),
        pessoa(ana, silva, data(12, novembro, 1981), empregado(bcc, 800))
    ]
).

familia(
    pessoa(paulo, santos, data(1, janeiro, 1955), empregado(abb, 1200)),
    pessoa(ana, santos, data(1, maio, 1955), desempregado),
    [
        pessoa(manoela, santos, data(10, setembro, 1981), desempregado),
        pessoa(andre, santos, data(18, novembro, 1978), empregado(bb, 1100)),
        pessoa(carlos, santos, data(02, fevereiro, 1981), empregado(cc, 3200))
    ]
).

familia(
    pessoa(eddard, stark, data(31, 03, 1948), morto),
    pessoa(catelyn, stark, data(11, 08, 1953), morto),
    [
        pessoa(robb, stark, data(09, 12, 1977), morto),
        pessoa(sansa, stark, data(01, 06, 1979), empregado(conselheira, 11000)),
        pessoa(arya, stark, data(06, 01, 1991), empregado(assassina, 8800)),
        pessoa(bran, stark, data(23, 10, 1993), empregado(vidente, 1)),
        pessoa(rickon, stark, data(29, 04, 1999), morto)
    ]
).

% Regras

marido(NomeCompleto) :- 
    familia(pessoa(Nome, Sobrenome, _, _), _, _),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

esposa(NomeCompleto) :- 
    familia(_, pessoa(Nome, Sobrenome, _, _), _),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

filhos(NomeCompleto) :- 
    familia(_, _, Filhos),
    member(pessoa(Nome, Sobrenome, _, _), Filhos),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

existe(NomeCompleto) :- 
    marido(NomeCompleto); esposa(NomeCompleto); filhos(NomeCompleto).

dataDeNasc(pessoa(Nome, Sobrenome, Data, _), NomeCompleto, Data) :-
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

dt(Data) :- 
    existe(NomeCompleto),
    dataDeNasc(pessoa(_, _, Data, _), NomeCompleto, Data).

% Definição única de salario/2 para evitar conflitos
salario(pessoa(_, _, _, empregado(_, S)), S).
salario(pessoa(_, _, _, desempregado), 0).
salario(pessoa(_, _, _, morto), 0).

% Indica que salario/2 pode ser definido em locais diferentes, se necessário
:- discontiguous salario/2.

nomes(NomeCompleto) :-
    ( familia(pessoa(Nome, Sobrenome, _, _), _, _) ;
      familia(_, pessoa(Nome, Sobrenome, _, _), _) ;
      familia(_, _, Filhos), member(pessoa(Nome, Sobrenome, _, _), Filhos) ),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

filhosBydt(NomeCompleto, Ano) :-
    familia(_, _, Filhos),
    member(pessoa(Nome, Sobrenome, data(_, _, Ano), _), Filhos),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

esposaEmpregada(NomeCompleto) :-
    familia(_, pessoa(Nome, Sobrenome, _, empregado(_, _)), _),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

pessoasDesempregada(NomeCompleto, AnoLimite) :-
    ( familia(pessoa(Nome, Sobrenome, data(_, _, Ano), desempregado), _, _) ;
      familia(_, pessoa(Nome, Sobrenome, data(_, _, Ano), desempregado), _) ;
      familia(_, _, Filhos), member(pessoa(Nome, Sobrenome, data(_, _, Ano), desempregado), Filhos) ),
    Ano < AnoLimite,
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

nascidoAntesSalario(NomeCompleto, AnoLimite, SalarioLimite) :-
    ( familia(pessoa(Nome, Sobrenome, data(_, _, Ano), empregado(_, Salario)), _, _) ;
      familia(_, pessoa(Nome, Sobrenome, data(_, _, Ano), empregado(_, Salario)), _) ;
      familia(_, _, Filhos), member(pessoa(Nome, Sobrenome, data(_, _, Ano), empregado(_, Salario)), Filhos) ),
    Ano < AnoLimite,
    Salario < SalarioLimite,
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

familiaMinimFilhos(Sobrenome, N) :-
    number(N),
    familia(pessoa(_, Sobrenome, _, _), _, Filhos),
    length(Filhos, Qtd),
    Qtd >= N.

rendaFamilia(Sobrenome, RendaTotal) :-
    familia(pessoa(_, Sobrenome, _, EmpregoPai), pessoa(_, Sobrenome, _, EmpregoMae), Filhos),
    salario(pessoa(_, _, _, EmpregoPai), SalarioPai),
    salario(pessoa(_, _, _, EmpregoMae), SalarioMae),
    somaSalarios(Filhos, SalarioFilhos),
    RendaTotal is SalarioPai + SalarioMae + SalarioFilhos.

familiaSemFilhos(Sobrenome) :-
    familia(pessoa(_, Sobrenome, _, _), _, []).

filhosDesempregados(NomeCompleto) :-
    familia(_, _, Filhos),
    member(pessoa(Nome, Sobrenome, _, desempregado), Filhos),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

paisIdade(NomeCompleto, DiferencaMinima) :-
    familia(pessoa(_, _, data(_, _, AnoPai), _), pessoa(_, _, data(_, _, AnoMae), _), Filhos),
    Diferenca is abs(AnoPai - AnoMae),
    Diferenca >= DiferencaMinima,
    member(pessoa(Nome, Sobrenome, _, _), Filhos),
    atomic_list_concat([Nome, Sobrenome], ' ', NomeCompleto).

somaSalarios([], 0).
somaSalarios([pessoa(_, _, _, Emprego) | Filhos], Total) :-
    salario(pessoa(_, _, _, Emprego), Salario),
    somaSalarios(Filhos, SalarioRestante),
    Total is Salario + SalarioRestante.
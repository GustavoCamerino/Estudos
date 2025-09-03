% Fatos basicos sobre os individuos
homem(manuel).
homem(jose).
homem(fernando).
homem(paulo).
homem(samuel).
homem(carlos).
homem(ricardo).
homem(daniel).
homem(anibal).
homem(francisco).
homem(alvaro).
mulher(maria).
mulher(marta).
mulher(delfina).
mulher(zulmira).
mulher(alzira).
mulher(diana).
mulher(fatima).
mulher(adriana).
mulher(celia).
mulher(sara).

% Relacoes de casamento
casados(manuel,maria).
casados(anibal,alzira).
casados(jose,marta).
casados(fernando,diana).
casados(alvaro,celia).
casados(carlos,zulmira).
casados(paulo,fatima).

% Relacoes de descendencia
% filho ou filha(X) de pai e mae
% X e descendente direto de P (pai) e M (mae)
descendente_direto(marta,manuel,maria).
descendente_direto(fernando,manuel,maria).
descendente_direto(diana,anibal,alzira).
descendente_direto(francisco,anibal,alzira).
descendente_direto(alvaro,anibal,alzira).
descendente_direto(delfina,jose,marta).
descendente_direto(carlos,fernando,diana).
descendente_direto(paulo,fernando,diana).
descendente_direto(sara,alvaro,celia).
descendente_direto(ricardo,carlos,zulmira).
descendente_direto(daniel,carlos,zulmira).
descendente_direto(adriana,paulo,fatima).
descendente_direto(samuel,paulo,fatima).

% Definindo quem e pai e mae
pai(P,F) :- descendente_direto(F,P,_). % P e pai de F se F for descendente de P
mae(M,F) :- descendente_direto(F,_,M). % M e mae de F se F for descendente de M

% Definindo avos e avos
avo(A,N) :- pai(P,N), pai(A,P). % Avo paterno
avo(A,N) :- pai(P,N), mae(A,P). % Avo materno paterno
avo(A,N) :- mae(M,N), pai(A,M). % Avo paterno materno
avo(A,N) :- mae(M,N), mae(A,M). % Avo materno

% Definindo filho e filha
filho(F,P) :- descendente_direto(F,P,_), homem(F). % F e filho de P se for descendente e homem
filho(F,M) :- descendente_direto(F,_,M), homem(F). % F e filho de M se for descendente e homem
filha(F,P) :- descendente_direto(F,P,_), mulher(F). % F e filha de P se for descendente e mulher
filha(F,M) :- descendente_direto(F,_,M), mulher(F). % F e filha de M se for descendente e mulher

% Neto e neta
neto_avo(N,V) :- 
    avo(V,N), 
    homem(N). % N e neto de V se for homem

neta_avo(N,V) :- 
    avo(V,N), 
    mulher(N). % N e neta de V se for mulher

% Relacao de irmaos e irmas
irmao_irma(X, Y) :- descendente_direto(X, P, M), descendente_direto(Y, P, M), X \= Y. % X e Y sao irmaos se compartilham pai e mae, e sao diferentes
irmao(X, Y) :- 
    irmao_irma(X,Y), 
    homem(X). % X e irmao de Y se for homem

irma(K,J) :- 
    irmao_irma(K,J), 
    mulher(K). % K e irma de J se for mulher

% Tio e tia
% X e tio de Y se for irmao do pai ou da mae de Y
tio(X, Y) :- 
    (pai(P, Y); mae(P, Y)), 
    irmao(X, P).

% X e tia de Y se for irma do pai ou da mae de Y
tia(X, Y) :- 
    (pai(P, Y); mae(P, Y)), 
    irma(X, P).

% Sobrinho e sobrinha
% X e sobrinho de Y se Y for irmao do pai ou da mae de X e X for homem
sobrinho(X, Y) :- 
    (pai(P, X); mae(P, X)), 
    irmao(Y, P), homem(X).

% X e sobrinha de Y se Y for irmao do pai ou da mae de X e X for mulher
sobrinha(X, Y) :- 
    (pai(P, X); mae(P, X)), 
    irmao(Y, P), 
    mulher(X).

% Primos e primas
% X e primo de Y se os pais de X e Y forem irmaos e X for homem
primo(X,Y) :- 
    (pai(P1,X); mae(P1,X)), 
    (pai(P2,Y); mae(P2,Y)), 
    irmao(P1,P2), 
    homem(X).

% X e prima de Y se os pais de X e Y forem irmaos e X for mulher
prima(X,Y) :- 
    (pai(P1,X); mae(P1,X)), 
    (pai(P2,Y); mae(P2,Y)), 
    irmao(P1,P2), 
    mulher(X).

% X é cunhado de Y se Y for irmao da mulher de X
cunhado(X,Y) :-
    casados(X,Z),
    irmao(Y,Z).

% X é cunhada de Y se Y for irmao da mulher de X
cunhado(X,Y) :-
    casados(X,Z),
    irma(Y,Z).

ascendente(X,Y) :-
    pai(X,Y). % X é pai de Y

ascendente(X,Y) :-
    mae(X,Y). % X é mae de Y

ascendente(X,Y) :-
    pai(Z,Y),
    ascendente(X,Z). % Recursivamente encontra os ascendentes de Z

ascendente(X,Y) :-
    mae(Z,Y),
    ascendente(X,Z). % Recursivamente encontra os ascendentes de Z

descendente(X,Y) :- 
    filho(X,Y).  % X é filho de Y

descendente(X,Y) :- 
    filha(X,Y).  % X é filha dY

descendente(X,Y) :- 
    filho(Z,Y),  % Encontra o filho Z de Y
    descendente(X,Z).  % Recursivamente encontra os descendentes de Z

descendente(X,Y) :- 
    filha(Z,Y),  % Encontra a filha Z de Y
    descendente(X,Z).  % Recursivamente encontra os descendentes de Z

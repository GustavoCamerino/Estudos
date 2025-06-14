#!/bin/bash
while true; do
    clear
    printf "O Fabuloso Gesto de Contatos - powered by Camerino\n"
    printf ".................................\n"
    ncontatos=$(wc -l < contatos.txt)
    printf "Você possui %d contatos\n" $ncontatos
    printf "1 - Novo contato\n"
    printf "2 - Pesquisar contato\n"
    printf "3 - Listar contatos\n"
    printf "4 - Sair\n"

    read opcao
    case $opcao in 
        1) ./novo.sh ;;
        2) ./pesquisa.sh ;;
        3) cat contatos.txt ;;
        4) exit ;;
        *) echo "Opção inválida" ;;
    esac 
    read -p "Pressione enter para continuar."
done
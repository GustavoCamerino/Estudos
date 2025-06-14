#!/bin/bash

# Inicializa a variável nome como uma string vazia
nome=""

# Loop que continua até que o usuário forneça um nome não vazio
while [[ -z "$nome" ]]; do
    # Solicita ao usuário para digitar o nome desejado
    printf "Digite o nome desejado: "
    read nome

    # Se a variável 'nome' ainda estiver vazia, exibe uma mensagem
    if [[ -z "$nome" ]]; then
        echo "Você não digitou um nome. Tente novamente."
    fi
done

# Procura o nome no arquivo 'contatos.txt' ignorando maiúsculas e minúsculas
grep -i "$nome" contatos.txt

#!/bin/bash

set=0
printf "Nome: "
read nome # variável que guarda o nome

printf "Telefone: "
read fone
printf "%s | %s\n" "$nome" "$fone" >> contatos.txt

    
sort contatos.txt > tmp.txt
mv tmp.txt contatos.txt
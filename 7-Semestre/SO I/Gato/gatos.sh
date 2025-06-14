# Definicao de um array chamado 'cats' contendo codigos Unicode para emojis de gatos
cats=("1F63a" "1F638" "1F639" "1f63b" "1f63c")

# Inicio de um loop que irah iterar sobre cada elemento do array 'cats'
for emoji in "${cats[@]}"
do 
    # Impressao do emoji correspondente ao codigo Unicode
    # A sequencia \U eh usada para representar um codigo Unicode em printf
    printf "\U$emoji\n"
done

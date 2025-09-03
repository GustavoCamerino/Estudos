int valor;

begin
    write "Calculando 1 - 1 = 0 -> falso";
    
    if (1 - 1)
    begin
        write "O valor do teste eh VERDADEIRO!\n";
    end
    else
    begin
        write "O valor eh teste eh FALSO!\n";
    end

    write "Informe um valor menor ou igual a dez:";
    read valor;

    write "";
    write "Escrevendo de 'valor' ateh 10";
    while (valor <= 10)
    begin
        write valor;
        valor = valor + 1;
    end
end
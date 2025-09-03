int test(int a, float b, char c);
int countdown(int n);
int dummy = 2;

begin
    write "Inicio da 'main'";
    
    write "Escreva um valor:";
    read dummy;
    write "Chamando funcao 'int test(int a, float b, char c)'";
    test(dummy, 2.213, 'e');

    write "Voltamos para a 'main'. Contando de 5 ateh 0:";
    countdown(5);
    write "Voltamos para a 'main'.";
end

int test(int a, float b, char c)
begin
    write "Entramos na funcao 'test'. Valor dos parametros passados:";
    write a;
    write b;
    write c;
    write "";

    write "Testando se a > 0 (print 1), a == 0 (print 0) ou a < 0 (print -1):";
    if (a > 0)
    begin
        write "'a' MAIOR QUE ZERO -> 1";

        write "Contando de 'a' ateh zero";
        countdown(a);
        write "Voltamos para a funcao 'test'";
        
    end
    else
    begin
        if (a == 0)
        begin
            write "'a' IGUAL A ZERO -> 0";
            
            write "Contando de 'a' ateh zero";
            countdown(a);
            write "Voltamos para a funcao 'test'";
        end
        else
        begin
            write "'a' MENOR QUE ZERO -> -1";

            write "Contando de 'a' ateh zero (nao vai contar, pois 'a' eh negativo)";
            countdown(a);
            write "Voltamos para a funcao 'test'";
        end
    end
end

int countdown(int n)
begin
    write "Chegamos na funcao 'countdown'";
    while (n >= 0)
    begin
        write n;
        n = n - 1;
    end
    write "FIM DA CONTAGEM!";
end

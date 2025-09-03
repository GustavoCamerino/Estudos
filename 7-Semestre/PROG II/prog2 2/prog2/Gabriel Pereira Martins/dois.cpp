/* Nesse exercício, você deve implementar o clássico jogo da velha 
bidimensional. Use um Array C++ 3x3 (matriz) para armazenar as jogadas. Cada jogador 
deve indicar suas jogadas inserindo um par de números inteiros representando os 
índices de linha e coluna do quadrado no qual deseja colocar sua marca, um 'X' ou um 
'O'. Cada jogada deve ser para um quadrado vazio. Se a jogada for para um quadrado 
ocupado, o jogo deve solicitar outra posição para o jogador da vez, até que ele insira 
uma posição desocupada. Após cada movimento válido, o jogo deve verificar se alguém 
ganhou ou se houve empate. */


int main(){

    int matrix [[000],[000],[000]]; //linder: errado! alem disso pedi com array c++
    bool valor = true;
    int linha = 0;
    int coluna = 0;
    contador = 0;


        while(contador < 9 ){ 

            std::cout << "digite a linha : ";
            std::cin >> linha;
            std::cout << "digita a coluna : ";
            std::cin >> coluna;

            if(contador + 1 % 2 == 0){ 

                for(int i = 0 ; i < 3 ; i++){
                matrix[e]; //linder: matriz tem duas dimensoes

                    for(int e = 0 ; e < 3; e++){

                        if( matrix[e]!= 0){
                            std::cout << "ja foi escolhido ! " << std::endl;
                            contador--
                            return contador;

                        }
                        else{
                            matrix[e] = x;
                            contador++
                            return contador;

                        }
                    
                    }

                }

            }

            else { 

                for(int i = 0 ; i < 3 ; i++){
                matrix[e];

                    for(int e = 0 ; e < 3; e++){

                        if( matrix[e]!= 0){
                            std::cout << "ja foi escolhido ! " << std::endl;
                            contador--
                            return contador;

                        }
                        else{
                            matrix[e] = 0;
                            contador++
                            return cotador;

                        }
                    
                    }

                }

            }

        }

    }

}
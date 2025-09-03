import numpy as np

def main():
    arr = np.zeros(10, dtype=int)  # Cria um array de 10 elementos com valores iniciais zero
    
    # Preenche o array com valores de 1 a 10
    for i in range(len(arr)):  # Use range() para iterar pelos índices
        arr[i] = i + 1
        
    # Imprime os valores do array
    print("|")
    for i in range(len(arr)):  # Novamente, use range() para acessar índices
        print(arr[i], end= "|")
    print()
if __name__ == "__main__":
    main()

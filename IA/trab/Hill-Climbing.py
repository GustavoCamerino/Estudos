import random
import time

def calcular_conflitos(tabuleiro):
    conflitos = 0
    n = len(tabuleiro)
    for i in range(n):
        for j in range(i + 1, n):
            if tabuleiro[i] == tabuleiro[j] or abs(tabuleiro[i] - tabuleiro[j]) == j - i:
                conflitos += 1
    return conflitos

def hill_climbing(n):
    tabuleiro = list(range(n))
    random.shuffle(tabuleiro)
    conflitos = calcular_conflitos(tabuleiro)

    while True:
        vizinhos = []
        for i in range(n):
            for j in range(i + 1, n):
                novo_tabuleiro = tabuleiro[:]
                novo_tabuleiro[i], novo_tabuleiro[j] = novo_tabuleiro[j], novo_tabuleiro[i]
                vizinhos.append((novo_tabuleiro, calcular_conflitos(novo_tabuleiro)))

        vizinhos.sort(key=lambda x: x[1])
        melhor_vizinho, melhor_conflito = vizinhos[0]

        if melhor_conflito < conflitos:
            tabuleiro, conflitos = melhor_vizinho, melhor_conflito
        else:
            break

    return tabuleiro, conflitos

# Testando o Hill-Climbing
n = 32
start_time = time.time()
solucao, conflitos = hill_climbing(n)
end_time = time.time()

print(f"Solucao para n={n} usando Hill-Climbing:\n")
print(f"Tabuleiro: {solucao}\n")
print(f"Conflitos: {conflitos}\n")
print(f"Tempo de execução: {end_time - start_time:.2f} segundos")

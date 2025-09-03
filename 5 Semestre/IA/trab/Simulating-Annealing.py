import random
import math
import time


def calcular_conflitos(tabuleiro):
    conflitos = 0
    n = len(tabuleiro)
    for i in range(n):
        for j in range(i + 1, n):
            if tabuleiro[i] == tabuleiro[j] or abs(tabuleiro[i] - tabuleiro[j]) == j - i:
                conflitos += 1
    return conflitos

def simulated_annealing(n, temperatura_inicial=1000, resfriamento=0.99, temperatura_final=1):
    tabuleiro = list(range(n))
    random.shuffle(tabuleiro)
    conflitos = calcular_conflitos(tabuleiro)

    temperatura = temperatura_inicial

    while temperatura > temperatura_final:
        i, j = random.sample(range(n), 2)
        novo_tabuleiro = tabuleiro[:]
        novo_tabuleiro[i], novo_tabuleiro[j] = novo_tabuleiro[j], novo_tabuleiro[i]
        novo_conflito = calcular_conflitos(novo_tabuleiro)

        delta_e = novo_conflito - conflitos
        if delta_e < 0 or random.uniform(0, 1) < math.exp(-delta_e / temperatura):
            tabuleiro, conflitos = novo_tabuleiro, novo_conflito

        temperatura *= resfriamento

    return tabuleiro, conflitos

# Testando o Simulated Annealing
n = 32
start_time = time.time()
solucao, conflitos = simulated_annealing(n)
end_time = time.time()

print(f"\nSolucao para n={n} usando Simulated Annealing:\n")
print(f"Tabuleiro: {solucao}\n")
print(f"Conflitos: {conflitos}\n")
print(f"Tempo de execução: {end_time - start_time:.2f} segundos\n")

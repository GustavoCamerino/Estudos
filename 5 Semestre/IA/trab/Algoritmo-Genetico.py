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

def gerar_populacao_inicial(n, tamanho_populacao):
    return [random.sample(range(n), n) for _ in range(tamanho_populacao)]

def calcular_fitness(tabuleiro):
    return 1 / (1 + calcular_conflitos(tabuleiro))

def selecao_roleta(populacao, fitnesses):
    soma_fitness = sum(fitnesses)
    pick = random.uniform(0, soma_fitness)
    atual = 0
    for individuo, fitness in zip(populacao, fitnesses):
        atual += fitness
        if atual > pick:
            return individuo

def crossover(pai1, pai2):
    n = len(pai1)
    ponto = random.randint(1, n - 1)
    filho1 = pai1[:ponto] + [gene for gene in pai2 if gene not in pai1[:ponto]]
    filho2 = pai2[:ponto] + [gene for gene in pai1 if gene not in pai2[:ponto]]
    return filho1, filho2

def mutacao(individuo, taxa_mutacao):
    if random.random() < taxa_mutacao:
        i, j = random.sample(range(len(individuo)), 2)
        individuo[i], individuo[j] = individuo[j], individuo[i]
    return individuo

def algoritmo_genetico(n, tamanho_populacao=100, taxa_mutacao=0.01, num_geracoes=1000):
    populacao = gerar_populacao_inicial(n, tamanho_populacao)

    for _ in range(num_geracoes):
        fitnesses = [calcular_fitness(individuo) for individuo in populacao]
        nova_populacao = []

        while len(nova_populacao) < tamanho_populacao:
            pai1 = selecao_roleta(populacao, fitnesses)
            pai2 = selecao_roleta(populacao, fitnesses)
            filho1, filho2 = crossover(pai1, pai2)
            nova_populacao.append(mutacao(filho1, taxa_mutacao))
            nova_populacao.append(mutacao(filho2, taxa_mutacao))

        populacao = nova_populacao

    fitnesses = [calcular_fitness(individuo) for individuo in populacao]
    melhor_individuo = populacao[fitnesses.index(max(fitnesses))]
    melhor_conflito = calcular_conflitos(melhor_individuo)
    
    return melhor_individuo, melhor_conflito

# Testando o Algoritmo Genético
n = 32
start_time = time.time()
solucao, conflitos = algoritmo_genetico(n)
end_time = time.time()

print(f"\nSolucao para n={n} usando Algoritmo Genético:\n")
print(f"Tabuleiro: {solucao}\n")
print(f"Conflitos: {conflitos}\n")
print(f"Tempo de execução: {end_time - start_time:.2f} segundos\n")

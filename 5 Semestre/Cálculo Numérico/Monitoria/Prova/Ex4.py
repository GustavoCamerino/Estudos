import numpy as np

def exercicio4():
    # Como a imagem do sistema não está disponível, vou assumir um sistema típico de treliça
    # com 13 membros e criar uma matriz de exemplo
    # Na prática, a matriz deve ser montada com base nas equações de equilíbrio dos nós
    
    # Exemplo genérico (valores hipotéticos)
    # Matriz 13x13 representando os coeficientes das forças
    A = np.zeros((13, 13))
    
    # Preenchendo com valores de exemplo (em um caso real, isso viria da análise da treliça)
    for i in range(13):
        A[i, i] = 2 + i*0.1  # Diagonal principal
        if i > 0:
            A[i, i-1] = -1   # Subdiagonal
        if i < 12:
            A[i, i+1] = -1    # Superdiagonal
    
    # Vetor de cargas (exemplo)
    b = np.array([10, 20, 15, 25, 30, 10, 5, 15, 20, 10, 5, 10, 15])
    
    # Resolvendo o sistema
    try:
        F = np.linalg.solve(A, b)
        print("Forças axiais nos membros da treliça:")
        for i in range(13):
            print(f"Membro {i+1}: {F[i]:.2f} N ({'Tração' if F[i] > 0 else 'Compressão'})")
    except np.linalg.LinAlgError:
        print("O sistema não tem solução única. Verifique a matriz de coeficientes.")
        # Alternativa com mínimos quadrados
        F, residuals, rank, s = np.linalg.lstsq(A, b, rcond=None)
        print("\nSolução aproximada (mínimos quadrados):")
        for i in range(13):
            print(f"Membro {i+1}: {F[i]:.2f} N ({'Tração' if F[i] > 0 else 'Compressão'})")

exercicio4()
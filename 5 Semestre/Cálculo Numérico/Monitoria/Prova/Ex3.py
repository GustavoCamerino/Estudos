import numpy as np

def exercicio3():
    # Matriz de composição das minas
    A = np.array([
        [0.52, 0.20, 0.25],  # Mina 1: areia, cascalho fino, cascalho grosso
        [0.30, 0.50, 0.20],  # Mina 2
        [0.18, 0.30, 0.55]   # Mina 3
    ]).T  # Transposta para ficar no formato Ax = b
    
    # Vetor de demandas
    b = np.array([4800, 5800, 5700])
    
    # Resolvendo o sistema
    try:
        x = np.linalg.solve(A, b)
        print("Quantidade a ser minerada em cada mina:")
        print(f"Mina 1: {x[0]:.2f} m³")
        print(f"Mina 2: {x[1]:.2f} m³")
        print(f"Mina 3: {x[2]:.2f} m³")
    except np.linalg.LinAlgError:
        print("O sistema não tem solução única. Pode ser necessário usar mínimos quadrados.")
        # Alternativa com mínimos quadrados
        x, residuals, rank, s = np.linalg.lstsq(A, b, rcond=None)
        print("\nSolução aproximada (mínimos quadrados):")
        print(f"Mina 1: {x[0]:.2f} m³")
        print(f"Mina 2: {x[1]:.2f} m³")
        print(f"Mina 3: {x[2]:.2f} m³")
        print(f"Resíduos: {residuals}")

exercicio3()
import numpy as np

def exercicio2():
    # Matriz dos coeficientes
    A = np.array([
        [13.422, 0, 0, 0],
        [-13.422, 12.252, 0, 0],
        [0, -12.252, 12.377, 0],
        [0, 0, -12.377, 11.797]
    ])
    
    # Vetor de termos independentes
    b = np.array([750.5, 300, 102, 30])
    
    # Resolvendo o sistema
    c = np.linalg.solve(A, b)
    
    print("Concentrações nos lagos:")
    print(f"Powell (c1): {c[0]:.2f}")
    print(f"Mead (c2): {c[1]:.2f}")
    print(f"Mohave (c3): {c[2]:.2f}")
    print(f"Havasu (c4): {c[3]:.2f}")
    
    # Parte 2: Reduzir carga no Powell para c4 = 75
    # Vamos isolar a primeira equação: 13.422*c1 = b1
    # Queremos c4 = 75, então precisamos resolver o sistema com c4 fixo
    
    # Novo sistema considerando c4 = 75
    # Podemos resolver de trás para frente
    c4_new = 75
    c3_new = (11.797 * c4_new) / 12.377
    c2_new = (12.377 * c3_new) / 12.252
    c1_new = (12.252 * c2_new) / 13.422
    
    # Nova carga no Powell
    b1_new = 13.422 * c1_new
    
    reducao = 750.5 - b1_new
    print(f"\nRedução necessária na carga do Lago Powell: {reducao:.2f}")

exercicio2()
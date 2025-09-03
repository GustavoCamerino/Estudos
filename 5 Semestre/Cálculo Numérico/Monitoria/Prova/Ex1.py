import math

def exercicio1():
    def f(t):
        k = 0.7
        w = 4
        return 9 * math.exp(-k * t) * math.cos(w * t) - 3.5
    
    def df(t):
        k = 0.7
        w = 4
        return 9 * (-k * math.exp(-k * t) * math.cos(w * t) - w * math.exp(-k * t) * math.sin(w * t))
    
    # Método de Newton
    def newton(f, df, x0, epsilon, max_iter=100):
        x = x0
        for i in range(max_iter):
            fx = f(x)
            if abs(fx) < epsilon:
                return x
            dfx = df(x)
            if dfx == 0:
                raise ValueError("Derivada zero. O método não converge.")
            x = x - fx / dfx
        return x
    
    # Método das Secantes
    def secantes(f, x0, x1, epsilon, max_iter=100):
        for i in range(max_iter):
            fx0 = f(x0)
            fx1 = f(x1)
            if abs(fx1) < epsilon:
                return x1
            if fx1 - fx0 == 0:
                raise ValueError("Diferença zero. O método não converge.")
            x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0)
            x0, x1 = x1, x2
        return x1
    
    epsilon = 1e-8
    # Chute inicial baseado no gráfico da função (precisa ser próximo da raiz)
    t0_newton = 0.5
    t0_secantes1 = 0.4
    t0_secantes2 = 0.6
    
    try:
        raiz_newton = newton(f, df, t0_newton, epsilon)
        print(f"Método de Newton: t = {raiz_newton:.8f} segundos")
    except ValueError as e:
        print(f"Erro no Método de Newton: {e}")
    
    try:
        raiz_secantes = secantes(f, t0_secantes1, t0_secantes2, epsilon)
        print(f"Método das Secantes: t = {raiz_secantes:.8f} segundos")
    except ValueError as e:
        print(f"Erro no Método das Secantes: {e}")

exercicio1()
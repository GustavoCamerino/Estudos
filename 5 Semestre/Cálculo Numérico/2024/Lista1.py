def main():
    r1, r2 = teste_de_erro()
    re = fun()

    print("Resultados da 1:")
    for i in range(9):
        print(f"{r1[i]:.6f}")


    print("Resultados da 2")
    for i in range(9):
        print(f"{r1[i]:.6f}")

    print("\nResultados de fun():")
    for i in range(10):
        print(f"{re[i]:.6f}")

def fun():
    k = 1.0
    iterations = 10
    results = [0] * iterations
    for i in range(iterations):
        x = 0.5 * (k + 2/k)
        k = x
        results[i] = k
    return results

def teste_de_erro():
    results = fun()
    r1 = [0] * 9
    r2 = [0] * 9
    for i in range(9):
        e1 = abs(results[i] - results[i + 1])
        e2 = abs(results[i] - results[i + 1]) / abs(results[i + 1])
        r1[i] = e1
        r2[i] = e2
    return r1, r2

if __name__ == '__main__':
    main()

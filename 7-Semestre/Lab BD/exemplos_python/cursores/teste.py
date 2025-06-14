def execute(a=10, params=None):
    return a + params

if __name__=='__main__':
    a = 50
    um_nome_diferente = 70
    ret = execute(a=a, params=um_nome_diferente)
    print(ret)
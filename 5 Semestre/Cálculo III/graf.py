import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Definindo os limites para x e y
x = np.linspace(0, 1, 100)
y = np.linspace(0, 1, 100)
X, Y = np.meshgrid(x, y)

# Calculando os valores de Z dentro das restrições
Z = np.minimum(1 - X**2, 1 - X - Y)

# Criando o gráfico 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plotando a superfície
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, alpha=0.7, edgecolor='none')

# Adicionando rótulos aos eixos
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Ajustando os limites dos eixos
ax.set_xlim([0, 1])
ax.set_ylim([0, 1])
ax.set_zlim([0, 1])

plt.show()

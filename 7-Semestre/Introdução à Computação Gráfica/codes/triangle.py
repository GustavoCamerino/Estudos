# Importa todas as funções e constantes da biblioteca OpenGL para gráficos
from OpenGL.GL import *
# Importa todas as funções e constantes do GLUT (utilitário para criar janelas e interações com OpenGL)
from OpenGL.GLUT import *


# Função de callback responsável por desenhar na tela
def display():
    glClear(GL_COLOR_BUFFER_BIT)  # Limpa o buffer de cor, preparando a tela para um novo desenho

    glColor3f(1.0, 0.0, 0.0)      # Define a cor atual para vermelho (RGB: 1, 0, 0)

    glBegin(GL_POLYGON)          # Inicia o desenho de um polígono
    glVertex3f(0.0, 0.0, 0.0)     # Primeiro vértice (canto inferior esquerdo)
    glVertex3f(1.0, 0.0, 0.0)     # Segundo vértice (canto inferior direito)
    glVertex3f(0.0, 1.0, 0.0)     # Terceiro vértice (canto superior esquerdo)
    glVertex3f(0.0,0.0,0.0)
    glVertex3f(-1.0,0.0,0.0)
    glVertex3f(0.0,1.0,0.0)
    glVertex3f(0.0,0.0,0.0)
    glVertex3f(1.0, 0.0, 0.0)
    glVertex3f(0.0, -1.0, 0.0)
    glVertex3f(0.0,0.0,0.0)
    glVertex3f(-1.0, 0.0, 0.0)
    glVertex3f(0.0, -1.0, 0.0)
    
    glEnd()                      # Finaliza o desenho do polígono

    glFlush()                    # Força a execução imediata de todos os comandos OpenGL pendentes


# Inicializa o GLUT (biblioteca de janelas e eventos para OpenGL)
glutInit()

# Define o modo de exibição da janela:
# GLUT_SINGLE: usa um único buffer de exibição
# GLUT_RGB: usa o sistema de cores RGB
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)

# Define o tamanho da janela em pixels (largura x altura)
glutInitWindowSize(350, 350)

# Define a posição inicial da janela na tela (em pixels a partir do canto superior esquerdo)
glutInitWindowPosition(500, 150)

# Cria a janela com o título "hello" e salva o identificador da janela na variável `wind`
wind = glutCreateWindow("hello")

# Define a cor de fundo da janela (preto com opacidade 0)
glClearColor(0.0, 0.0, 0.0, 0.0)

# Registra a função de exibição (display) como a responsável por renderizar o conteúdo da janela
glutDisplayFunc(display)

# Inicia o loop principal do GLUT — mantém a janela aberta e responde a eventos (como renderizar e interações)
glutMainLoop()

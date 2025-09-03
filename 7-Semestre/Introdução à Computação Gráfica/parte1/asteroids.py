## UFMT - Ciencia da Computacao
## Materia: Introducao a Computacao Grafica
## Professor: Rafael Teixeira Sousa
## Aluno: Gabriel Neves Silveira
##
## Implementacao do Codigo do Trabalho Asteroids - Parte 1

######################################################################

# Bibliotecas
import sys
import random
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import pywavefront
from pywavefront import visualization
from math import pi, cos, sin

# Variaveis globais para estado da nave
ship_x = 0.0 # Posicao X da nave no plano XZ
ship_z = 0.0 # Posicao Z da nave no plano XZ
ship_angle = 0.0 # Angulo de rotacao da nave em graus

# Parametro de altura para a visao top-down
camera_height = 15.0 # Altura da camera no eixo Y

# Modelos 3D e lista de asteroides
spaceship = None # Objeto 3D da nave
asteroid = None # Objeto 3D do asteroide
asteroids = [] # Lista de dicionarios com informacoes dos asteroides


## Funcao que realiza configuracoes iniciais do OpenGL
def init():
    glClearColor(0.0, 0.0, 0.0, 1.0)  # Cor de fundo preta
    glEnable(GL_DEPTH_TEST) # Habilita teste de profundidade

    # Configura a matriz de projecao
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    # Projecao perspectiva (campo de visao 60°, aspect ratio 1:1, planes: near=1, far=100)
    gluPerspective(60.0, 1.0, 1.0, 100.0)

    glMatrixMode(GL_MODELVIEW) # Volta para modo modelview


## Funcao de desenho da cena (chamada pelo GLUT)
def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)  # Limpa buffers
    glLoadIdentity() # Reseta matriz modelview

    # Configura camera em top-down:
    # Olho em (0, altura, 0), centro na origem (0,0,0), vetor up (0,0,-1)
    gluLookAt(0.0, camera_height, 0.0,      # Posicao da camera (eye)
              0.0, 0.0, 0.0,                # Ponto da camera (aim)
              0.0, 0.0, -1.0)               # Vetor UP
    

    # Desenha a nave no plano XZ
    glPushMatrix() # Salva estado atual da matriz

    # Aplica transformacoes geometricas:
    glTranslatef(ship_x, 0.0, ship_z) # Posiciona a nave no centro
    glRotatef(ship_angle, 0.0, 1.0, 0.0) # Rotaciona no eixo Y
    glScalef(0.7, 0.7, 0.7)  # Ajusta o tamanho da nave (escala)
    visualization.draw(spaceship) # Renderiza modelo
    glPopMatrix() # Restaura matriz

    # Desenha todos os asteroides:
    for ast in asteroids:
        pos = ast['position'] # Pega posicao (x,y,z)
        angle = ast['rotation'] # Pega angulo de rotacao

        glPushMatrix() # Salva matriz

        # Aplica transformacoes para cada asteroide:
        glTranslatef(pos[0], pos[1], pos[2]) # Posiciona o asteroide
        glRotatef(angle, 0.0, 1.0, 0.0) # Rotaciona o asteroide
        glScalef(0.2, 0.2, 0.2)  # Ajusta o tamanho dos asteroide (escala)
        visualization.draw(asteroid) # Renderiza o asteroide
        glPopMatrix() # Restaura matriz

    
    glutSwapBuffers() # Troca buffers


## Tratamento de teclado: move ou gira a nave (teclas especiais)
def Keys(key, x, y):
    global ship_x, ship_z, ship_angle
    step = 0.5 # Passo de translacao da nave
    rot_step = 5.0 # Passo de rotacao (em graus) da nave

    
    if key == GLUT_KEY_UP:
        # Move para frente (calculada usando seno e cosseno)
        rad = ship_angle * pi / 180.0 # Converte angulo para radianos (para calculos trigonometricos)
        ship_x += step * -sin(rad)
        ship_z += step * -cos(rad)
    elif key == GLUT_KEY_DOWN:
        # Move para tras (calculada usando seno e cosseno)
        rad = ship_angle * pi / 180.0 # Converte angulo para radianos (para calculos trigonometricos)
        ship_x -= step * -sin(rad)
        ship_z -= step * -cos(rad)
    elif key == GLUT_KEY_LEFT:
        # Gira nave para esquerda (sentido anti-horario)
        ship_angle += rot_step
    elif key == GLUT_KEY_RIGHT:
        # Gira nave para direita (sentido horario)
        ship_angle -= rot_step

    glutPostRedisplay() # Forca redesenho da tela


## Ajusta viewport e projecao quando janela e redimensionada
def resize(w, h):
    if h == 0: h = 1 # Evita divisao por zero
    glViewport(0, 0, w, h) # Define area de desenho

    # Atualiza matriz de projecao:
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    # Mantem perspectiva com novo aspect ratio (w/h)
    gluPerspective(60.0, float(w) / float(h), 1.0, 100.0)

    glMatrixMode(GL_MODELVIEW) # Volta para modelview


## Funcao de animacao (chamada periodicamente pelo timer)
## Atualiza a posicao dos asteroides e remove os que estao fora de limites da visao do jogo
def animacao(value):
    global asteroids
    new_list = [] # Nova lista para asteroides validos


    for ast in asteroids:
        # Atualiza posicao (movimento linear)
        ast['position'][0] += ast['velocity'][0]
        ast['position'][2] += ast['velocity'][2]

        # Atualiza rotacao (movimento angular)
        ast['rotation'] += ast['rot_velocity']


        # Verifica se asteroide esta dentro dos limites:
        x, z = ast['position'][0], ast['position'][2]
        if abs(x) <= 20.0 and abs(z) <= 20.0: # Se estah dentro da area de 40x40
            new_list.append(ast) # Mantem na lista

    asteroids = new_list # Atualiza lista global


    glutPostRedisplay() # Solicita atualizacao de tela
    glutTimerFunc(30, animacao, 1)  # Reprograma timer a cada 30 ms


## Funcao principal: inicializa sistema e inicia o loop do jogo
def main():
    global spaceship, asteroid, asteroids
    
    # Carrega modelos 3D (em obj)
    spaceship = pywavefront.Wavefront('objects/spaceship.obj')
    asteroid = pywavefront.Wavefront('objects/asteroide.obj')

    # Cria asteroides iniciais com posicao e velocidade aleatorias
    for i in range(15): # 15 asteroides
        # Posicao inicial aleatoria (-10 a 10 em X e Z)
        x = random.uniform(-10, 10)
        z = random.uniform(-10, 10)

        # Velocidade linear aleatoria
        vx = random.uniform(-0.2, 0.2)
        vz = random.uniform(-0.2, 0.2)

        # Estado inicial de rotacao aleatoria
        angle = random.uniform(0, 360) # Angulo inicial
        rot_vel = random.uniform(-2.0, 2.0) # Velocidade angular

        # Adiciona dicionario com dados do asteroide
        asteroids.append({
            'position': [x, 0.0, z],    # Pos (Y fixo em 0)
            'velocity': [vx, 0.0, vz],  # Velocidade (Y fixo em 0)
            'rotation': angle,          # Rotacao atual
            'rot_velocity': rot_vel     # Velocidade rotacao
        })

    # Inicializa GLUT:
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) 
    glutInitWindowSize(800, 600) # Tamanho inicial janela
    glutCreateWindow("Asteroids 3D") # Cria janela

    init() # Chama configuracao inicial do OpenGL

    # Registra funcoes callback:
    glutDisplayFunc(display) # Redesenhar a tela
    glutSpecialFunc(Keys) # Teclas especiais (quando sao pressionadas)
    glutReshapeFunc(resize) # Redimensionamento (quando a tela eh redimensionada)
    glutTimerFunc(30, animacao, 1) # Timer para animacao (a cada 30ms)


    glutMainLoop() # Inicia loop principal do GLUT

## Chama a funcao principal como sendo a "main()"
if __name__ == '__main__':
    main()

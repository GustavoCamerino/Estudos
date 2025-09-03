import numpy as np
import matplotlib.pyplot as plt

# funcao para redimensionar a imagem
def resizeImg(img, sch, scw):
    '''
      img: imagem de entrada
      sch: fator de escala na altura
      scw: fator de escala na largura
    '''
    h, w, c = img.shape # dimensoes de img (linhas, colunas, canais)
    print(h)
    print(w)
    # aloca a nova imagem
    nh = int(round(h * sch))
    nw = int(round(w * scw))
    newImg = np.zeros((nh, nw, c), dtype=np.uint8)

    # indices dos pixels da nova imagem
    Ro = np.arange(nh)
    Co = np.arange(nw)
   

    # calcula os fatores de escala
    Sr = float(h) / float(nh) # h = numero de linhas da imagem original; nh= nova
    Sc = float(w) / float(nw) # w = numero de colunas da imagem original; nw = nova

    #calcula o mapeamento dos indices
    Rm = Ro * Sr
    Cm = Co * Sc

    R = np.round(Rm).astype(int)
    C = np.round(Cm).astype(int)
    C[C>= w] = w - 1
    R[R >= h] = h - 1


    coord_new = [(x,y) for x in Ro for y in Co] # coodenadas de pixel da imagem nova
    coord_ori = [(x,y) for x in R for y in C] # coordendas novas mapeadas
    for cn, co in zip(coord_new, coord_ori):
        newImg[cn] = img[co]

    return newImg

# funcao principal
def main():
    img = plt.imread("cat_puppy.jpg")
    
    factor = 3.0
    newImg = resizeImg(img, factor, factor)
    
    #Concatena as imagens para apresentação
    img_aux = None
    images = None
    if factor > 1.0:
        img_aux = np.ones(newImg.shape, dtype=np.uint8)
        img_aux[0:(img.shape[0]), 0:(img.shape[1])] = img
        images = np.hstack((img_aux, newImg))
    else:
        img_aux = np.ones(img.shape, dtype=np.uint8)
        img_aux[0:(newImg.shape[0]), 0:(newImg.shape[1])] = newImg
        images = np.hstack((img, img_aux))
    
    
    # mostra as imagens com opencv
    fig, axs = plt.subplots()
    axs.set_title("Original vs Resized")
    axs.set_axis_off()
    axs.imshow(images)
    plt.show()

# Chama a funcao principal
if __name__ == '__main__':
    main()

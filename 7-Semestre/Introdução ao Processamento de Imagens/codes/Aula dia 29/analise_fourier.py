import numpy as np
import cv2
import matplotlib.pyplot as plt
from numpy.fft import fft2 ,ifft2,fftshift, ifftshift # Importa as funções das transformadas de Fourrier

# Tira frequencia baixa transições sobra as mais altas que são transições
# Tira frequencia Alta Continuidade sobre

# Carrega imagem
img = cv2.imread("imagem_teste.jpeg",cv2.IMREAD_GRAYSCALE)
print(type(img))
print(img.dtype)
print(img.shape)

# Implementaçõesh

# --- FFT ---
F = fft2(img)
F_shiffted = fftshift(F)

linhas,colunas = F_shiffted.shape
cl = linhas // 2
cc = colunas // 2

mascara = np.zeros(F_shiffted.shape)
mascara[cl -10:cl +10, cc -10: cc +10] = 1
F_shiffted = F_shiffted * mascara
img_hp = np.real(ifft2(ifftshift(F_shiffted)))


print(type(F))
print(F.dtype)
print(F.shape)

# Plotar o specrun
fig, axs = plt.subplots(1, 3, figsize=(15,5))
axs[0].imshow(img,cmap="gray")
axs[0].set_title("Imagem Original")
axs[1].imshow(np.log10(np.abs(F_shiffted + 1)),cmap="gray")
axs[1].set_title("Imagem 2")
axs[2].imshow(img_hp,cmap="gray")
axs[2].set_title("Imagem 3")
plt.show()






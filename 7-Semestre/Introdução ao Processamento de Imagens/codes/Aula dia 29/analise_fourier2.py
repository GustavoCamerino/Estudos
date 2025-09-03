import numpy as np
import cv2
import matplotlib.pyplot as plt
from numpy.fft import fft2 ,ifft2,fftshift, ifftshift # Importa funções de transformadas de Fourier
                                                     # fft2 -> Transformada rápida 2D
                                                     # ifft2 -> Inversa da FFT
                                                     # fftshift -> Centraliza espectro no meio da matriz
                                                     # ifftshift -> Desfaz centralização

# -------------------- PARÂMETROS --------------------
N = 512                       # Dimensão do espectro (matriz NxN)
u0 = 10                        # Frequência espacial na horizontal (não usado ainda neste trecho)
v0 = 10                        # Frequência espacial na vertical  (não usado ainda neste trecho)
amplitude = 1.0               # Amplitude da senoide
fase = np.deg2rad(30.0)       # Converte 30 graus para radianos (fase da senoide)

# -------------------- CRIA COMPONENTE COMPLEXA --------------------
# Representa amplitude + fase em forma complexa:
# A = amplitude * (cos(fase) + j·sen(fase))
A = amplitude * np.exp(1j * fase)

# -------------------- CRIA ESPECTRO --------------------
# Matriz do espectro inicializada com zeros (tipo complexo)
S = np.zeros((N, N), dtype=np.complex128)

# Coordenadas do centro da matriz (frequência zero no meio)
cl = N // 2   # linha central
cc = N // 2   # coluna central

# -------------------- INSERE FREQUÊNCIAS --------------------
# Coloca duas componentes simétricas no espectro:
#   - Uma em (cl, cc+5) com amplitude+fase A
#   - Outra em (cl, cc-5) com o conjugado de A
# Isso garante simetria hermitiana → resultado da IFFT será real

S[cl, cc+u0] = A
S[cl, cc-v0] = np.conj(A)
S[cl+u0, cc] = A
S[cl-v0, cc] = np.conj(A)


# FFT - Inversa
img = np.real(ifft2(ifftshift(S)))


fig, axs = plt.subplots(1, 2)
axs[0].imshow(img, cmap="gray")
axs[0].set_title("Imagem Original")
axs[1].imshow(np.log(np.abs(S) + 1),cmap="gray")
axs[1].set_title("Spectrum")
plt.show()
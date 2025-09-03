import numpy as np
import cv2
from sklearn.datasets import fetch_lfw_people

# Baixar o dataset com imagens coloridas e pessoas com pelo menos 100 imagens
lfw = fetch_lfw_people(min_faces_per_person=100, resize=1.0, color=True)

# Mostrar as pessoas disponíveis
print("Pessoas disponíveis:", lfw.target_names)

# Escolher a pessoa desejada
person_name = "George W Bush"
person_index = list(lfw.target_names).index(person_name)

# Filtrar imagens dessa pessoa
images = lfw.images[lfw.target == person_index]

# Redimensionar para 250x250 se necessário
images_resized = [cv2.resize(img, (250, 250)) for img in images]

# Inicializar acumulador
accumulator = np.zeros((250, 250, 3), dtype=np.float64)

# Acumular as imagens convertidas para float64
for img in images_resized:
    accumulator += img.astype(np.float64)

# Calcular a média
average_img = accumulator / len(images_resized)

# Converter para uint8 e salvar
average_img_uint8 = np.clip(average_img, 0, 255).astype(np.uint8)
cv2.imwrite("media_bush.jpg", cv2.cvtColor(average_img_uint8, cv2.COLOR_RGB2BGR))

print("Imagem média salva como media_bush.jpg")

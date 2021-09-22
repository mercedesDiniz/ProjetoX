import cv2
import os
from imutils import paths                    # BIBLIOTECAS
import shutil

def listNegImagem():
    imagemPath = list(paths.list_images('Fotos/NArmas'))    # CAMINHO PARA O DATASET
    numero = 1
    if not os.path.exists('Neg'):
        os.makedirs('Neg')

    for i in imagemPath:
        i.replace(i, "neg/" + str(numero) + ".png")
        shutil.copy(i, i.replace(i, "neg/" + str(numero) + ".png"))
        img = cv2.imread("neg/" + str(numero) + ".png", cv2.IMREAD_GRAYSCALE)  # CRIAÇÃO DAS NOVAS IMAGENS
        resized_image = cv2.resize(img, (100, 100))
        cv2.imwrite("neg/" + str(numero) + ".png", resized_image)

        print(i.replace(i, "neg/" + str(numero) + ".png"))

        numero += 1


listNegImagem()

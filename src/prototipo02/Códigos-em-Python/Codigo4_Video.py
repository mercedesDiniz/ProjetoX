import cv2

webCamera = cv2.VideoCapture(0)      # DEFININDO A WEBCAM
classificadorVideoFace = cv2.CascadeClassifier('cascade.xml')  # DEFININDO O NOSSO HAAR CASCADE

while True:
    camera, frame = webCamera.read()

    cinza = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) # TRANSFORMA CAPTURA DA WEBCAM EM ESCALA DE CINZA
    detectar = classificadorVideoFace.detectMultiScale(cinza, minSize=(275,275)) # DETECTAR O OBJETO ALVO
    for(x ,y ,l , a) in detectar:
             cv2.rectangle(frame, (x,y),(x+l , y+a), (50,50,255) , 10)        # CRIAÇÃO DO RETÂNGULO

    cv2.imshow("Video WebCamera", frame)    # MOSTRA A WEBCAM NO PC
    if cv2.waitKey(1) == ord('f'):          # ENCERRA O PROGRAMA COM A TECLA 'F'
        break

webCamera.release()                          #
cv2.destroyAllWindows()                      # LIMPA MEMÓRIA

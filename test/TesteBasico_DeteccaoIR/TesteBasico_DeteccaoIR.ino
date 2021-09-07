/* Link: https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-led-emissor-ir-e-fototransistor-ir  */
const int pinoFototransistor = A2; //PINO ANALÓGICO UTILIZADO PELO FOTOTRANSISTOR
               
void setup(){
  Serial.begin(9600); //INICIALIZAÇÃO DA SERIAL
   pinMode(pinoFototransistor, INPUT); //DEFINE O PINO COMO ENTRADA
}

void loop(){
  if(analogRead(pinoFototransistor) < 800){ //SE A LEITURA DO PINO FOR MENOR QUE 800 BITS, FAZ
    Serial.println("Recebendo sinal infravermelho"); //IMPRIME O TEXTO NA SERIAL
  }else{ //SENÃO, FAZ
    Serial.println("Sinal infravermelho interrompido"); //IMPRIME O TEXTO NA SERIAL
  }
 }

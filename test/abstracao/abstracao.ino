//Declaração das constantes
const int ledVerde = 11;   //constante led refere-se ao pino digital 11.
const int ledYellow = 12; //constante led refere-se ao pino digital 12.
const int botao1 = 9; //constante botão refere-se ao pino digital 9.
const int botao2 = 4; //constante botão refere-se ao pino digital 4.
int pinoPir = 2; //constante sensor refere-se ao pino digital 2.
int pinBuzzer = 3; //constante buzzer refere-se ao pino digital 3.

String numeroUsuario = "982094131";

//Variável que conterá os estados do botão e sensor
int estadoBotao1 = 0;
int estadoBotao2 = 0;
int valorSensorPir = 0;
 
//Método setup, executado uma vez ao ligar o Arduino.
void setup() {
  pinMode(pinoPir, INPUT);	 //Definindo sensor 2 como de entrada.
  pinMode(ledVerde,OUTPUT);  //Definindo pino 11 como de saída.
  pinMode(ledYellow,OUTPUT); //Definindo pino 12 como de saída.
  pinMode(botao1,INPUT);	 //Definindo botão 9 como de entrada.
  pinMode(pinBuzzer,OUTPUT); //Definindo buzzer 8 como de saída.
  pinMode(botao2,INPUT); //Definindo botão 2 como de entrada. 
  Serial.begin(9600); //comunicação serial
}
 
//Método loop, executado enquanto o Arduino estiver ligado.
void loop() {  
  //Lendo os estados dos pinos, do botao, e atribuindo 
  //o resultado a variável estadoBotao.
  estadoBotao1 = digitalRead(botao1); 
  estadoBotao2 = digitalRead(botao2);
  valorSensorPir = digitalRead(pinoPir);
   
  //Verificando o estado do botão para definir se acenderá ou
  //apagará o led. 
  if(valorSensorPir == HIGH)
  {
    Serial.println("ALERTA! ");
    Serial.println("Para ignorar aperte 1 || Para escutar aperte 2");
    tone(pinBuzzer,1500);//Ligando o buzzer com uma frequencia de 1500 hz.
    delay(2000);
  }
      if (estadoBotao1 == HIGH) {
        digitalWrite(ledVerde,HIGH); //Botão pressionado, acende o led.
      	Serial.println(" OK. Descartando Avisso ... Ignorado com Sucesso! " );
      } 
  		else if (estadoBotao2 == HIGH) {
          digitalWrite(ledYellow,HIGH); //Botão pressionado, acende o led.
          Serial.println(" OK. Estou ligando para vc ... " );

      } else {
        digitalWrite(ledYellow,LOW);  //Botão não pressionado, apaga o led.    
        digitalWrite(ledVerde,LOW);  //Botão não pressionado, apaga o led.    
      }
    noTone(pinBuzzer);//Desligando o buzzer
  
}

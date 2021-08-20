/*  PROTOTIPO - MAIN DO MODULO PRINCIPAL (NAO TESTADO - SERA ALTERADO EM BREVE)

Descriçao: Aqui desenvolveremos o codigo que integrara as funcionalidade basicas do modulo principal, com a programaçao do sensor
PIR (Detecçao) e do modulo GSM(Comunicaçao).

Codigo base para as funçoes do modulo GSM foi o "Q0161-Sketch" disponibilizado pelo canal Brincando com Ideias.
Link do video: https://www.youtube.com/watch?v=GbVXixOUUPM&t=428s
Link do codigo Original: https://drive.google.com/file/d/0B91L9po09u35T0x5RGJKamNXUDA/view?resourcekey=0-2_TNdrAr0S6vTDiInLa6xA
*/

#include <SoftwareSerial.h>
SoftwareSerial serialGSM(10, 11); // RX, TX

bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";

#define senhaGsm "1234"
#define numeroCall "982094131" 

#define pinoPIR 13; // Pino do sensor PIR

bool callStatus = false;

void leGSM();
void enviaSMS(String telefone, String mensagem);
void fazLigacao(String telefone);
void configuraGSM();

void setup() {

  Serial.begin(9600);
  serialGSM.begin(9600); 

  pinMode(pinoPIR, INPUT); // Pino de Entrada
  Serial.println("Sketch Iniciado!");
  configuraGSM();
}

void loop() {
  leGSM();

  if (comandoGSM != "") {
      Serial.println(comandoGSM);
      ultimoGSM = comandoGSM;
      comandoGSM = "";
  }
  
  if(digitalRead(pinoPIR) == HIGH){ // SE A LEITURA DO pinoPIR FOR IGUAL A HIGH -> ALGO FOI DETECTADO! 
    // bloco de instruções: 
    

 }else{  // SE A LEITURA DO pinoPIR FOR IGUAL A LOW -> NADA DETECTADO! 
    // bloco de instruções:
 }
  
}


// FUNÇOES:

void leGSM()
{
  static String textoRec = "";
  static unsigned long delay1 = 0;
  static int count=0;  
  static unsigned char buffer[64];

  if (serialGSM.available()) {            
 
     while(serialGSM.available()) {         
   
        buffer[count++] = serialGSM.read();     
        if(count == 64)break;
     }

     textoRec += (char*)buffer;
     delay1   = millis();
     
     for (int i=0; i<count; i++) {
         buffer[i]=NULL;
     } 
     count = 0;                       
  }


  if ( ((millis() - delay1) > 100) && textoRec != "" ) {

     if ( textoRec.substring(2,7) == "+CMT:" ) {
        temSMS = true;
     }

     if (temSMS) {
            
        telefoneSMS = "";
        dataHoraSMS = "";
        mensagemSMS = "";

        byte linha = 0;  
        byte aspas = 0;
        for (int nL=1; nL < textoRec.length(); nL++) {

            if (textoRec.charAt(nL) == '"') {
               aspas++;
               continue;
            }                        
          
            if ( (linha == 1) && (aspas == 1) ) {
               telefoneSMS += textoRec.charAt(nL);
            }

            if ( (linha == 1) && (aspas == 5) ) {
               dataHoraSMS += textoRec.charAt(nL);
            }

            if ( linha == 2 ) {
               mensagemSMS += textoRec.charAt(nL);
            }

            if (textoRec.substring(nL - 1, nL + 1) == "\r\n") {
               linha++;
            }
        }
     } else {
       comandoGSM = textoRec;
     }
     
     textoRec = "";  
  }     
}

//
void enviaSMS(String telefone, String mensagem) {
  serialGSM.print("AT+CMGS=\"" + telefone + "\"\n");
  serialGSM.print(mensagem + "\n");
  serialGSM.print((char)26); 
}

//
void fazLigacao(String telefone) {
  serialGSM.println("ATH0\n");
  serialGSM.print((char)26); 
  serialGSM.println("ATD " + telefone + ";\n");
  serialGSM.print((char)26); 
}

//
void configuraGSM() {
   serialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}



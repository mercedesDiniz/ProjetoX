  /* PROTOTIPO - MAIN DO MODULO PRINCIPAL (NAO TESTADO - SERA ALTERADO EM BREVE)
  
  Descriçao: Aqui desenvolveremos o codigo que integrara as funcionalidade basicas do modulo principal, com a programaçao do sensor
  PIR (Detecçao) e do modulo GSM(Comunicaçao).
  
  Codigo base para as funçoes do modulo GSM foi o "Q0161-Sketch" disponibilizado pelo canal Brincando com Ideias, o mesmo esta do 
  diretorio assets. Link do video: https://www.youtube.com/watch?v=GbVXixOUUPM&t=428s
  */
  
  #include <SoftwareSerial.h>
  SoftwareSerial serialGSM(10, 11); // RX, TX
  
  bool temSMS = false;
  String telefoneSMS;
  String dataHoraSMS;
  String mensagemSMS;
  String comandoGSM = "";
  String ultimoGSM = "";
  String mensagemAviso = "Algo foi detectado!Envei um SMS de resposta!Deseja: 1)Ignorar ou 2)Escutar ?";
  
  //#define senhaGsm "1234"
  #define numeroUsuario "982094131" 
  int pinoPIR = 13; // Pino do sensor PIR
  
  bool callStatus = false;
  
  void leGSM();
  void enviaSMS(String telefone, String mensagem);
  void fazLigacao(String telefone);
  void configuraGSM();
  
  void setup() {
    // Iniciando comunicaçao Serial:
    Serial.begin(9600);     // Configurando o Monitor serial e os Pinos RX e  
    serialGSM.begin(9600);  // TX do Modulo GSM, na mesma frequencia.
  
    pinMode(pinoPIR, INPUT); // Pino de Entrada
    Serial.println("Sketch Iniciado!");
    configuraGSM();        // Funçao para configurar o GSM para receber SMS, usando comandos AT.
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
      
      enviaSMS(numeroUsuario, mensagemAviso);
      
      if(temSMS)
      {
        if(mensagemSMS == "1" || mensagemSMS == "Ignorar"){
          enviaSMS(numeroUsuario, "OK. Descartando Avisso...Ignorado com Sucesso!");
        }
        
        if(mensagemSMS == "2" || mensagemSMS == "Escutar" && !callStatus){
          enviaSMS(numeroUsuario, "OK. Estou ligando para vc...");
          fazLigacao(numeroUsuario);
          callStatus = true;
          
          // 
          if (ultimoGSM.indexOf("+COLP:") > -1) {
             enviaSMS(numeroUsuario, "Ligacao em Andamento ...");
             ultimoGSM = "";                
          }
           
          if (ultimoGSM.indexOf("NO CARRIER") > -1) {
             enviaSMS(numeroUsuario, "Ligacao Concluida com Sucesso!");
             ultimoGSM = "";
             callStatus = false;
          }
               
          if (ultimoGSM.indexOf("BUSY") > -1) {
             enviaSMS(numeroUsuario, "Linha/Numero Ocupado!");
             ultimoGSM = "";
             callStatus = false;
          }
        
          if (ultimoGSM.indexOf("NO DIALTONE") > -1) {
             enviaSMS(numeroUsuario, "SEM LINHA!");
             ultimoGSM = "";
             callStatus = false;
          }
               
          if (ultimoGSM.indexOf("NO ANSWER") > -1) {
             enviaSMS(numeroUsuario, "NAO ATENDE!");
             ultimoGSM = "";
             callStatus = false;
          }
          
        }
        temSMS = false; // Apos os comandos serem tratados, "zeramos" essa variavel.
      }
  
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
  


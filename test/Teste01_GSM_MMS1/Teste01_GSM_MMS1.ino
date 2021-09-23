#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

  SoftwareSerial serialGSM(10, 11); // RX, TX
  String mensagemSMS;
  String SerialGSM = "";
  
  #define numeroUsuario "982094131"
  const int chipSelect = 4;
  int dados;
  int i;

  // Ler GSM
  void leGSM();
  // talvez tenha q ter mais parametros
  void enviaMMS(String telefone, String mensagem);   
  // para o GSM trabalhar com MMS (enviar Imagens)
  void configGSMmms(); 
            
void setup() {
  // Configurando o Monitor serial e os Pinos RX e
  Serial.begin(9600);
  //TX do Modulo GSM, na mesma frequencia.
  serialGSM.begin(9600);

  //verificando se o cartão está presente e pode ser inicializado
  if (!SD.begin(chipSelect)) {
    Serial.println("O cartão falhou ou não está presente");
    // não faça mais nada
    while (1);
  }
  Serial.println("cartão inicializado!");
  // Funçao para configurar o GSM para enviar MMS, usando comandos AT.
  configGSMmms();
}

void loop(){}
//configurando o GSM para enviar imagem com texto em MMS
void configGSMmms(){
  //incialização
  serialGSM.print("AT + CMMSINIT \n");//Inicializar função MMS
  if (serialGSM.available ())
  {
    //available:retorna o número de bytes na porta serial||read:ler dados recebidos na porta serial
    //Escreve dados binários na porta serial
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  // configuração de parametros 
  serialGSM.print("AT + CMMSCURL = \" https://ibb.co/6wSrbMj \"\n"); //Definindo URL central do MMS
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  //ID de contexto do portador
  serialGSM.print("AT + CMMSCID = 1 \n"); //parâmetros de rede para MMS
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  serialGSM.print("AT + CMMSPROTO = \" 10.0.0.172 \", 80 \n");//parâmetro de protocolo e proxy MMS
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  serialGSM.print("AT + CMMSSENDCFG = 6,3,0,0,2,4,1,0 \n");//parâmetros para enviar MMS
  if (serialGSM.available ())
  {
    while (serialGSM.available()) Serial.write (serialGSM.read ());
  }
  serialGSM.print ("AT + SAPBR = 3,1, \" CONTYPE \", \" GPRS \"\n");//Definir parâmetro portador
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  serialGSM.print("AT + SAPBR = 3,1, \" APN \", \" CMWAP \"\n");//Definir o contexto do portador
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  serialGSM.print("AT + SAPBR = 1,1 \n");//Contexto do portador ativo

  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  serialGSM.print("AT + SAPBR = 2,1 \n");//Ler parâmetro do portador
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }

  //Enviar MMS
  serialGSM.print("AT + CMMSEDIT = 1 \n");//Entrar ou sair do modo de edição
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
  serialGSM.print("AT + CMMSDOWN = \" PIC \", 12963,20000, \" produto-teste.jpg \"\n");//Baixe os dados do arquivo ou título do UART
  if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }

  File dataFile = SD.open("produto-teste.jpg");// abrir o arquivo
  i = 0;
  // se o arquivo estiver aberto
  if (dataFile)
  {
    while (dataFile.available ())// enquanto aparecer na porta serial
    {
      dados = dataFile.read ();
      if (dados <0x10) // tamanho
      Serial.print("0");
      Serial.print(dados, HEX);
      i ++;
      if ((i% 40) == 0) 
      Serial.println ();
      serialGSM.write(dados);
    }
    dataFile.close ();
  }  
  else
  {
    Serial.println ("erro ao abrir produto-teste.jpg");//
  }
    serialGSM.print("AT + CMMSRECP = \"13918181818 \"\n");//Adicionar destinatários
    if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
    serialGSM.print("AT + CMMSVIEW \n");//Colocando o MMS no buffer e mostrando as informações
    if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
    serialGSM.print("AT + CMMSSEND \n");//Começar a enviar MMS
    if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read());
  }
    serialGSM.print("AT + CMMSEDIT = 0 \n");//Entrar ou sair do modo de edição
    if (serialGSM.available ())
  {
    while (serialGSM.available ()) Serial.write (serialGSM.read ());
  }
    serialGSM.print("AT + CMMSTERM \n");//Sair da função MMS
     if (serialGSM.available())
  {
    while (serialGSM.available()) Serial.write (serialGSM.read ());
  }
}

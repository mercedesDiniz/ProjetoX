/* Teste 01 - Sistema Auxiliar de Detecção Infravermelho (usando Led Emissor IR e Fototransistor IR)  (NÃO TESTADO E PUCO PROVAVEL Q DE CERTO)
- Proposta: Utilizar o Led Emissor IR e Fototransistor IR em conjunto com o Arduino e enviar o sinal IR do emissor para o receptor, e sempre que o sinal for interrompido significa que algum obstaculo/pessoa passou pelo perimetro. Com um comjunto formado por dois pares desse sistema podemos determida o sentido da locomoção (se a pessoa esta entrando ou saindo) se instalado em uma abertura (como porta ou janela). 

*OBS.01: Quanto maior for a distância do emissor em relação ao receptor, maior será a leitura feita pelo pino analógico.

*OBS.02: O Fototransistor funciona de forma similar que um transistor NPN, ou seja, é constituído de Base, Coletor e Emissor. Coletor é o terminal mais curto (C) eo Emissor é o terminal mais comprido (E). Conecte o terminal maior (E - emissor) no GND e o terminal menor ou o lado com chanfro (C - coletor) em um pino analógico do Arduino.

*/

const int pinoFotot01 = A2; // Pino Analogico 
const int pinoFotot02 = A3; // Pino Analogico

int controle_pessoas = 1;  // Ao ligar o dispositivo e sair, esse valor será ZERO! (consederando que apenas uma pessoa saiu apos o dispositivo ser ligado). Essa condição pode ter que ser adaptada dependendo da situação ou local de instalação (se for instalado em uma janela, pode ser iniciado ja como ZERO).
int cont_F01, cont_F02 = 0; // Variaveis de controle para auxiliar na determinação da ordem de disparo do sistema.

  void setup() {   
    Serial.begin(9600); // Iniciando comunicaçao Serial   
    pinMode(pinoFotot01, INPUT); // Pino de Entrada
    pinMode(pinoFotot02, INPUT); // Pino de Entrada
  }
  
  void loop() {
// ANALIZANDO O PRIMEIRO PAR(LedIR01 e F01 que devem está mais para a parte de FORA, logo se ele for acionado primeiro é pq a pesoa está ENTRANDO.)
// ANALIZANDO O SEGUNDO PAR(LedIR02 e F02 que devem está mais para a parte de DENTRO, logo se ele for acionado primeiro é pq a pesoa está SAINDO.)	
    
    if(cont_F01 == 0 && cont_F02 == 0){	
	    if(analogRead(pinoFotot01) > 800){   // Sinal infravermelho do F01 interrompido! (valor varia de acordo com a distancia do Led01 e F01,e pode ter que ser calibrado).
	    	Serial.println("Sinal infravermelho interrompido no F01");
	    	cont_F01 = 1; // o F1 foi o Primeiro à disparar
	    	if(analogRead(pinoFotot02) > 800){  // Sinal infravermelho do F02 interrompido! (valor varia de acordo com a distancia do Led02 e F02,e pode ter que ser calibrado).
	    	Serial.println("Sinal infravermelho interrompido no F02");   
	    	cont_F02 = 2; //  o F2 foi o Sugundo à disparar
		}  		
	    }
    }
    
// OBS.: Não tenho certeza se o bloco de instruções de baixo não vai sobreescrever o de cima! A logica pode ter que ser modificada.

    if(cont_F01 == 0 && cont_F02 == 0){
	    if(analogRead(pinoFotot02) > 800){   // Sinal infravermelho do F02 interrompido! (valor varia de acordo com a distancia do Led01 e F01,e pode ter que ser calibrado).
	    	Serial.println("Sinal infravermelho interrompido no F02");
	    	cont_F02 = 1; //  o F2 foi o Primeiro à disparar
	    	if(analogRead(pinoFotot02) > 800){  // Sinal infravermelho do F01 interrompido! (valor varia de acordo com a distancia do Led02 e F02,e pode ter que ser calibrado).
	    	Serial.println("Sinal infravermelho interrompido no F01");   
	    	cont_F01 = 2; //  o F1 foi o Sugundo à disparar
		}  		
	    }
    }
    
// Analizando a ordem para determinar se o movimento foi de ENTRADA ou SAIDA:
   if (cont_F01 == 1 && cont_F02 == 2){
  	Serial.println("ALGUEM ENTROU"); // ALGUEM ENTROU!
   } 
   if (cont_F01 == 2 && cont_F02 == 1){
  	Serial.println("ALGUEM SAIU"); // ALGUEM SAIU!
   } 
   Serial.print("NÚMERO DE PESSOAS VERIFICADO = ");
   Serial.println(controle_pessoas);	
// Reiniciando os parametros de controle:
   cont_F01 = 0;
   cont_F02 = 0;
  
 }
        
  
  


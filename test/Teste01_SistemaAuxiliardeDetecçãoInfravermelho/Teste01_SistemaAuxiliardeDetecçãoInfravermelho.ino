/* Teste 01 - Sistema Auxiliar de Detecção Infravermelho (usando Led Emissor IR e Fototransistor IR)  (NÃO TESTADO)

- Proposta: Utilizar o Led Emissor IR e Fototransistor IR em conjunto com o Arduino e enviar o sinal IR do emissor para o receptor, e sempre que o sinal for interrompido significa que algum obstaculo/pessoa passou pelo perimetro. Com um comjunto formado por dois pares desse sistema podemos determida o sentido da locomoção (se a pessoa esta entrando ou saindo) se instalado em uma abertura (como porta ou janela). 

*OBS.01: Quanto maior for a distância do emissor em relação ao receptor, maior será a leitura feita pelo pino analógico.

*OBS.02: O Fototransistor funciona de forma similar que um transistor NPN, ou seja, é constituído de Base, Coletor e Emissor. Coletor é o terminal mais curto (C) eo Emissor é o terminal mais comprido (E). Conecte o terminal maior (E - emissor) no GND e o terminal menor ou o lado com chanfro (C - coletor) em um pino analógico do Arduino.

*/

const int pinoFotot01 = A2; // Pino Analogico 
const int pinoFotot02 = A3; // Pino Analogico

int controle_pessoas = 1;  // Ao ligar o dispositivo e sair, esse valor será ZERO! (consederando que apenas uma pessoa saiu apos o dispositivo ser ligado). Essa condição pode ter que ser adaptada dependendo da situação ou local de instalação (se for instalado em uma janela, pode ser iniciado ja como ZERO).


  void setup() {   
    Serial.begin(9600); // Iniciando comunicaçao Serial   
    pinMode(pinoFotot01, INPUT); // Pino de Entrada
    pinMode(pinoFotot02, INPUT); // Pino de Entrada
  }
  
  void loop() {
    // ANALIZANDO O PRIMEIRO PAR(LedIR01 e F01 que devem está mais para a parte de fora, logo se ele for acionado primeiro é pq a pesoa está ENTRANDO.)	
    if(analogRead(pinoFotot01) < 800){  // Recebendo sinal infravermelho do F01! (valor varia de acordo com a distancia do Led01 e F01,e pode ter que ser calibrado).
    	Serial.println("Recebendo sinal infravermelho no F01"); // TUDO OK! 	
    }
    else{  // Sinal infravermelho do F01 interrompido
        controle_pessoas = controle_pessoas + 1;
	Serial.println("Sinal infravermelho interrompido no F01 = ALGUEM ENTROU"); // ALGUEM ENTROU!
    }
    
    // ANALIZANDO O SEGUNDO PAR(LedIR02 e F02 que devem está mais para a parte de dentro, logo se ele for acionado primeiro é pq a pesoa está SAINDO.)	
    if(analogRead(pinoFotot01) < 800){  // Recebendo sinal infravermelho do F02! (valor varia de acordo com a distancia do Led02 e F02,e pode ter que ser calibrado).
    	Serial.println("Recebendo sinal infravermelho no F02"); // TUDO OK! 	
    }
    else{  // Sinal infravermelho do F01 interrompido
        controle_pessoas = controle_pessoas - 1;
	Serial.println("Sinal infravermelho interrompido no F02 = ALGUEM SAIU"); // ALGUEM SAIU!
    }
    
    Serial.print("NÚMERO DE PESSOAS VERIFICADO = ");
    Serial.println(controle_pessoas);
  }
  


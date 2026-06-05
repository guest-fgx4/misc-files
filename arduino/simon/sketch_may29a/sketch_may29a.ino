#include <TimerOne.h>
#include <MultiFuncShield.h>


//para minha solução, estou utilizando a variável ultimaDistancia para filtrar valores espúrios do sensor
int ultimaDistancia = 0;
//estaAtivo tem dois valores, sistema ligado ou não, de acordo com o pressionar do botão 1.
bool estaAtivo = false;


// Pinos do sensor ultrassônico, escolhidos porque o Shield disponibiliza poucos para utilização do programador.
const int pinoTrigger = 5;
const int pinoEcho = 6;

//Filtro
const int tamanhoFiltro = 10;
int filtro[tamanhoFiltro];
int indexAtual = 0;


//jogo
typedef struct dadosJogo {
  int faseAtual   = 0;
  int faseMaxima  = 10;
  int dados[faseMaxima];
} dadosJogo; 

short jogoLoop = 1;

enum class ESTADOJOGO
{
  INICIO = 0,
  SIMON,
  JOGADOR,
  VITORIA,
  PERDA
};

ESTADOJOGO operator++ (ESTADOJOGO& estadoJogo, int)
{
  switch(estadoJogo)
  {
    case ESTADOJOGO::INCIO:
      estadoJogo = ESTADOJOGO::SIMON;
      break;
    case ESTADOJOGO::SIMON:
      estadoJogo = ESTADOJOGO::JOGADOR;
      break;
    case ESTADOJOGO::JOGADOR:
      estadoJogo = ESTADOJOGO::VITORIA
      break;
    case ESTADOJOGO::VITORIA:
      estadoJogo = ESTADOJOGO::PERDA;
      break;
    case ESTADOJOGO::PERDA:
      estadoJogo = ESTADOJOGO::INICIO;
      break;
  }
  return estadoJogo;
}

ESTADOJOGO estadoJogo = ESTADOJOGO::INICIO;

dadosJogo jogoAtual;

void definirSequencia(dadosJogo jogoAtual)
{
  for(int i = 0; i <= jogoAtual.faseAtual; i++)
  {
    jogoAtual.dados[i] = (rand() % 4);
  }
}

void inicializarJogo()
{
  jogoAtual.faseAtual = 0;
  jogoAtual.faseMaxima = 10;
  jogoAtual.dados[jogoAtual.faseMaxima];

  definirSequencia(jogoAtual);
}


int fazerMedia()
{
  int res;
  for(int i = 0; i < tamanhoFiltro; i++)
  {
    res += filtro[i];
  }
  return res;
}

void adicionarValorMedia(int valor)
{
  filtro[indexAtual] = valor;
  indexAtual = (indexAtual + 1) % tamahoFiltro;
}

// Esta função mede a distância usando o sensor
int converterDistancia(int distancia) {
    // Mapeamento dos níveis
  if (distancia >= 0 && distancia < 10) {
    MFS.write("1");
    return 1; // Nível 1
   
  }
  else if (distancia >= 10 && distancia < 20) {
    MFS.write("2");
    return 2; // Nível 2
  }
  else if (distancia >= 20 && distancia < 30) {
    MFS.write("3");
    return 3; // Nível 3
  }
  else if (distancia >= 30 && distancia < 40) {
    MFS.write("4");
    return 4; // Nível 4
  }
  else {
    MFS.write("0");
    return 0; // Fora da faixa
  }
}

int medirDistancia()
{

  pinMode(pinoTrigger, OUTPUT);
  digitalWrite(pinoTrigger, LOW);
  delayMicroseconds(2);

  digitalWrite(pinoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrigger, LOW);

  pinMode(pinoEcho, INPUT);
  long tempo = pulseIn(pinoEcho, HIGH);

  // Converte tempo em centímetros
  int distancia = tempo * 0.01723;

  if (distancia > 100)
  {
    distancia = fazerMedia();
  }
  else
  {
    adicionarValorMedia(distancia);
  }

  return distancia; 
}



// Esta função faz o buzzer apitar
void mostrarEstado(int distancia) {
     if (distancia >= 0 && distancia < 10) {
    MFS.write("1");
    //MFS.beep();
    tone(3, 420, 500);
  }
  else if (distancia >= 10 && distancia < 20) {
    MFS.write("2");
   // MFS.beep();
    tone(3, 420, 500);
    
  }
  else if (distancia >= 20 && distancia < 30) {
    MFS.write("3");
    //MFS.beep();
    tone(3, 800, 500);
    
  }
   else if (distancia >= 30 && distancia < 40) {
    MFS.write("4");
    //MFS.beep();
    tone(3, 800, 500);
    
  }
   else {
    MFS.write("0");
    MFS.beep(0); 
  }
}


// Acende os LEDs conforme a distância
void mostrarAlertaComLeds(int distancia) {
  MFS.writeLeds(LED_ALL, OFF);


  if (distancia == 1) {
    MFS.writeLeds(LED_1, ON);
  } else if (distancia == 2){
    MFS.writeLeds(LED_1, ON);
    
    MFS.writeLeds(LED_2, ON);
  } else if (distancia == 3) {
    MFS.writeLeds(LED_1, ON);
    MFS.writeLeds(LED_2, ON);
    MFS.writeLeds(LED_3, ON);
  }
  else if (distancia == 4) {
     MFS.writeLeds(LED_1, ON);
    MFS.writeLeds(LED_2, ON);
    MFS.writeLeds(LED_3, ON);
    MFS.writeLeds(LED_4, ON);
  }
}


// Lê o botão e ativa/desativa o sistema
void checarBotao() {
  byte botao = MFS.getButton();


  if (botao) {
    byte numero = botao & B00111111;
    byte acao = botao & B11000000;


    if (numero == 1 && acao == BUTTON_PRESSED_IND) {
      estaAtivo = !estaAtivo;//se o botão for pressionado um número ímpar de vezes, liga o sistema; senão, desliga.
      delay(50);  // Evita o efeito de debounce do botão
    }
  }
}


// Parte que roda uma vez no início
void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  Serial.begin(9600);

  inicializarJogo();
}

void mostrarDados()
{
  for(int i = 0; i <= jogoAtual.faseAtual; i++)
  {
    MFS.write(jogoAtual.dados[i]); 
    tone(3, 120, 500);
    delay(500);
  }
}

void executarEstadoJogo()
{
  switch(estadoJogo)
  {
    case ESTADOJOGO::INCIO:

      MFS.write("LOAD");
      delay(1000);
      estadoJogo++;
      break;
    case ESTADOJOGO::SIMON:
      mostarDados();
      estadoJogo++;
      break;
    case ESTADOJOGO::JOGADOR:
      int estado = converterDistancia(medirDistancia());
      mostrarEstado(estado);
      mostrarAlertaComLeds(estado);
      break;
    case ESTADOJOGO::VITORIA:
      break;
    case ESTADOJOGO::PERDA:
      break;
  }
}


// Parte que fica repetindo
void loop() {

  executarEstadoJogo();


  if (jogoLoop & 0x1)
  {
  }
  else
  {

  }






  if (true) {
        Serial.println(ultimaDistancia);        // Mostra a distância no monitor serial

  } else {
    MFS.write("");                // Apaga display
    MFS.writeLeds(LED_ALL, OFF);  // Apaga LEDs
  }
  delay(100);  // Pequena pausa
}


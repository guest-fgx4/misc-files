#include <TimerOne.h>                     // Biblioteca para controlar o Timer1
#include <MultiFuncShield.h>              // Biblioteca específica para o Shield Multifuncional

// Variáveis para guardar o estado dos botões (LED ligado ou desligado)
bool state_bt1 = 0;
bool state_bt2 = 0;
bool state_bt3 = 0;

bool PANIC = 0;

// Variaveis para o timer
unsigned long previousMillis = 0;
int countdown = 0;
bool timerRunning = false;

// Variáveis para senha
String keyword = "";
String passwordEntered = "";
int keywordSize = 8;
int passwordIndex = 0;

int potentiometer = 0;

void setup()
{
  Serial.begin(9600);                     // Inicia comunicação com o monitor serial (9600 bps)
  Timer1.initialize();                    // Inicializa o Timer1
  MFS.initialize(&Timer1);                // Inicializa o Shield Multifuncional com o Timer1

  keyword = generateRandomKeyword();
  Serial.println(keyword);
}

void loop()
{
  potentiometer = getSecurityTime(analogRead(A0));
  
  if(timerRunning == 0) {
    MFS.write(potentiometer); // 45 até 90  
  }

  byte btn = MFS.getButton();             // Lê o botão pressionado (se houver)

  if (btn)                                // Se algum botão foi pressionado
  {
    byte buttonNumber = btn & B00111111;  // Isola os bits que representam o número do botão (0 a 3)
    byte buttonAction = btn & B11000000;  // Isola os bits que indicam a ação (pressionado / long press)

    // Ação: botão pressionado normalmente (toque curto)
    if (buttonAction == BUTTON_PRESSED_IND)
    {
        Serial.println(buttonNumber);
        if (buttonNumber == 1) {
          if(!timerRunning) {
            countdown = potentiometer;
            timerRunning = true;
            previousMillis = millis();
          }
          else {
            Buzzer(1);
            validarSenha(buttonNumber);
          }
        }
        if (buttonNumber == 2) {
          Buzzer(1);
          validarSenha(buttonNumber);
        }
          
        if (buttonNumber == 3) {
          Buzzer(1);
          validarSenha(buttonNumber);
        } 
      Serial.println(passwordEntered);

    }

    // Ação: botão pressionado por tempo longo (long press)
    else if (buttonAction == BUTTON_LONG_PRESSED_IND)
    {
        MFS.write(buttonNumber);          // Mostra o número do botão no display de 7 segmentos
        Buzzer(buttonNumber);             // Toca o buzzer com repetições equivalentes ao número do botão
    }

    // Atualiza o estado dos LEDs conforme os botões
    MFS.writeLeds(LED_1, state_bt1);
    MFS.writeLeds(LED_2, state_bt2);
    MFS.writeLeds(LED_3, state_bt3);
  }

  updateTimer();
}

void validarSenha(int butao)
{

  if((butao + 48) == (int)keyword[passwordIndex])
  {
    passwordIndex++;

    if (password == 9)
    {
      Serial.println("Ganhou!");
    }
  }
  else
  {
    countdown = countdown - 2;
  }
}

int getSecurityTime(int potentiometerValue) {
  potentiometerValue += 45;
  if(potentiometerValue > 90) {
    potentiometerValue = 90;
  }
  return potentiometerValue;
}

String generateRandomKeyword() {
  randomSeed(4);

  String keyword = "";

  for (int i = 0; i < 8; i++) {
    int digito = random(1, 4);
    keyword += String(digito);
  }

  return keyword;
}

void updateTimer() {

  if (timerRunning) {

    unsigned long currentMillis = millis();

    // passou 1 segundo?
    if (currentMillis - previousMillis >= 1000) {

      previousMillis = currentMillis;

      countdown--;

      if (PANIC)
      {
        MFS.write(countdown);
      }
      else
      {
        MFS.write("");
        delay(50)
        MFS.write(countdown);
      }



      Serial.println(countdown);

      // acabou o tempo
      if (countdown <= 20 && countdown > 0)
      {
        PANIC = true;
        
      } else  if (countdown <= 0 ) {

        countdown = 0;

        timerRunning = false;

        MFS.write("ICE");

        Serial.println("GAME OVER");
      }
    }
  }
}



// Função para tocar o buzzer
void Buzzer (int number_repetition)
{
  // Lê o valor do potenciômetro e mapeia para um intervalo de tempo entre 100 e 1000 ms
  long inter_loop_time = map(analogRead(POT_PIN), 0, 1023, 10, 100);
  Serial.println(inter_loop_time);        // Mostra o tempo de intervalo no monitor serial

  // Toca o buzzer:
  // 5 bipes com 50ms de som e 50ms de silêncio, repetidos "number_repetition" vezes
  // Intervalo entre cada sequência definido pelo potenciômetro
  MFS.beep(5,      // Tempo do bip: 50ms (5 * 10ms)
           5,      // Tempo de silêncio: 50ms (5 * 10ms)
           5,      // Número de bipes por sequência
           number_repetition,  // Número de repetições da sequência
           inter_loop_time);   // Intervalo entre as repetições (ajustado pelo potenciômetro)
}
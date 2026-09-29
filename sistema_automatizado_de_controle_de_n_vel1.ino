// ===== PINOS =====

// Sensor ultrassônico
const int TRIG = 9;
const int ECHO = 10;

// 74HC595
const int DATA = 11;
const int CLOCK = 12;
const int LATCH = 8;

// Buzzer
const int BUZZER = 6;

// Motor / bomba
const int MOTOR = 7;


void setup() {

  // Configura os pinos do sensor
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Configura os pinos do 74HC595
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  // Configura buzzer e bomba
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR, OUTPUT);

  // Inicia o Monitor Serial
  Serial.begin(9600);
}


void loop() {

  // ===== TESTE =====
  // A distância está sendo fixada em 20 cm
  // para testar o funcionamento do sistema.
  float distancia = 28;


  // ===== CONVERSÃO PARA NÍVEL =====

  // Converte a distância em porcentagem.
  // Reservatório vazio = 30 cm
  // Reservatório cheio = 5 cm
  float nivel = ((30 - distancia) / (30 - 5)) * 100;

  // Garante que o nível fique entre 0% e 100%
  if (nivel < 0) {
    nivel = 0;
  }

  if (nivel > 100) {
    nivel = 100;
  }


  // ===== CONTROLE DO SISTEMA =====

  if (nivel < 15) {

    // Nível crítico
    digitalWrite(MOTOR, HIGH);
    digitalWrite(BUZZER, HIGH);

    // LED vermelho
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, B00010000);
    digitalWrite(LATCH, HIGH);

  }

  else if (nivel < 30) {

    // Nível de atenção
    digitalWrite(MOTOR, HIGH);
    digitalWrite(BUZZER, LOW);

    // LED amarelo
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, B00001000);
    digitalWrite(LATCH, HIGH);

  }

  else {

    // Nível normal
    digitalWrite(MOTOR, LOW);
    digitalWrite(BUZZER, LOW);

    // LED verde
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, B00000100);
    digitalWrite(LATCH, HIGH);
  }


  // ===== MONITOR SERIAL =====

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm | Nivel: ");
  Serial.print(nivel);
  Serial.print("% | Bomba: ");

  if (digitalRead(MOTOR) == HIGH) {
    Serial.println("Ligada");
  }
  else {
    Serial.println("Desligada");
  }

  // Aguarda meio segundo antes da próxima leitura
  delay(500);
}
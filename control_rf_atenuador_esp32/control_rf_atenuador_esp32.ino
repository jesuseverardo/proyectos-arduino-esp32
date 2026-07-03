#include <Arduino.h>

// Pines de control de los 4 switches RF
const int U1 = 16;
const int U2 = 17;
const int U3 = 18;
const int U4 = 19;

// Pines del atenuador, si lo estás usando
const int pinV1 = 21; // 16 dB
const int pinV2 = 22; // 8 dB
const int pinV3 = 23; // 4 dB
const int pinV4 = 25; // 2 dB
const int pinV5 = 26; // 1 dB
const int pinV6 = 27; // 0.5 dB

const int ledPin = 2;

// Botón físico opcional para alternar DIRECTO/INVERSO.
// Conecta el botón entre GPIO4 y GND.
const int buttonPin = 4;
bool lastButtonState = HIGH;
unsigned long lastButtonMs = 0;
const unsigned long debounceMs = 180;

// pinMap[0] = 0.5 dB, pinMap[5] = 16 dB
const int pinMap[6] = {pinV6, pinV5, pinV4, pinV3, pinV2, pinV1};

String modo = "DIRECTO";

// Prototipos para evitar problemas de compilación en algunos IDE.
void aplicarDirecto();
void aplicarInverso();
void aplicarMascara(int m);
void imprimirStatus();
void toggleModo();
void setAtenuacion(int pasos);
void pruebaOsciloscopio();
bool esNumero(String s);
void procesarComando(String cmd);

void aplicarDirecto() {
  digitalWrite(U1, LOW);
  digitalWrite(U2, HIGH);
  digitalWrite(U3, LOW);
  digitalWrite(U4, HIGH);

  modo = "DIRECTO";
  digitalWrite(ledPin, LOW);
  delay(200);
}

void aplicarInverso() {
  digitalWrite(U1, HIGH);
  digitalWrite(U2, LOW);
  digitalWrite(U3, HIGH);
  digitalWrite(U4, LOW);

  modo = "INVERSO";
  digitalWrite(ledPin, HIGH);
  delay(200);
}

void aplicarMascara(int m) {
  digitalWrite(U1, (m & 1) ? HIGH : LOW);
  digitalWrite(U2, (m & 2) ? HIGH : LOW);
  digitalWrite(U3, (m & 4) ? HIGH : LOW);
  digitalWrite(U4, (m & 8) ? HIGH : LOW);
  modo = "MANUAL";
  delay(150);
}

void toggleModo() {
  if (modo == "DIRECTO") {
    aplicarInverso();
    Serial.println("OK TOGGLE INVERSO");
  } else {
    aplicarDirecto();
    Serial.println("OK TOGGLE DIRECTO");
  }
  imprimirStatus();
}

void setAtenuacion(int pasos) {
  if (pasos < 0) pasos = 0;
  if (pasos > 63) pasos = 63;

  for (int i = 0; i < 6; i++) {
    bool bitSet = (pasos >> i) & 1;
    digitalWrite(pinMap[i], bitSet ? LOW : HIGH);
  }

  Serial.print("OK ATT=");
  Serial.print(pasos);
  Serial.print(" (");
  Serial.print(pasos * 0.5, 1);
  Serial.println(" dB)");
}

void imprimirStatus() {
  Serial.print("STATUS | MODO=");
  Serial.print(modo);

  Serial.print(" | U1=");
  Serial.print(digitalRead(U1) ? "HIGH" : "LOW");

  Serial.print(" | U2=");
  Serial.print(digitalRead(U2) ? "HIGH" : "LOW");

  Serial.print(" | U3=");
  Serial.print(digitalRead(U3) ? "HIGH" : "LOW");

  Serial.print(" | U4=");
  Serial.println(digitalRead(U4) ? "HIGH" : "LOW");
}

void pruebaOsciloscopio() {
  Serial.println("TEST INICIO");

  aplicarDirecto();
  Serial.println("TEST DIRECTO  U1=LOW U2=HIGH U3=LOW U4=HIGH");
  imprimirStatus();
  delay(1000);

  aplicarInverso();
  Serial.println("TEST INVERSO  U1=HIGH U2=LOW U3=HIGH U4=LOW");
  imprimirStatus();
  delay(1000);

  aplicarDirecto();
  Serial.println("TEST FIN");
  imprimirStatus();
}

bool esNumero(String s) {
  if (s.length() == 0) return false;
  for (size_t i = 0; i < s.length(); i++) {
    if (!isDigit(s.charAt(i))) return false;
  }
  return true;
}

void procesarComando(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd == "") return;

  if (cmd == "PING") {
    Serial.println("PONG");
    return;
  }

  if (cmd == "STATUS" || cmd == "?") {
    imprimirStatus();
    return;
  }

  if (cmd == "SW0" || cmd == "DIRECTO" || cmd == "DIRECT") {
    aplicarDirecto();
    Serial.println("OK SW0 DIRECTO");
    imprimirStatus();
    return;
  }

  if (cmd == "SW1" || cmd == "INVERSO" || cmd == "INVERSE") {
    aplicarInverso();
    Serial.println("OK SW1 INVERSO");
    imprimirStatus();
    return;
  }

  if (cmd == "TOGGLE" || cmd == "T") {
    toggleModo();
    return;
  }

  if (cmd == "TEST") {
    pruebaOsciloscopio();
    return;
  }

  if (cmd.startsWith("M ")) {
    int m = cmd.substring(2).toInt();
    if (m >= 0 && m <= 15) {
      aplicarMascara(m);
      Serial.print("OK MASK=");
      Serial.println(m);
      imprimirStatus();
    } else {
      Serial.println("ERR MASK 0-15");
    }
    return;
  }

  if (cmd.startsWith("U1 ")) {
    digitalWrite(U1, cmd.substring(3).toInt() ? HIGH : LOW);
    modo = "MANUAL";
    Serial.println("OK U1");
    imprimirStatus();
    return;
  }

  if (cmd.startsWith("U2 ")) {
    digitalWrite(U2, cmd.substring(3).toInt() ? HIGH : LOW);
    modo = "MANUAL";
    Serial.println("OK U2");
    imprimirStatus();
    return;
  }

  if (cmd.startsWith("U3 ")) {
    digitalWrite(U3, cmd.substring(3).toInt() ? HIGH : LOW);
    modo = "MANUAL";
    Serial.println("OK U3");
    imprimirStatus();
    return;
  }

  if (cmd.startsWith("U4 ")) {
    digitalWrite(U4, cmd.substring(3).toInt() ? HIGH : LOW);
    modo = "MANUAL";
    Serial.println("OK U4");
    imprimirStatus();
    return;
  }

  if (cmd.startsWith("ATT ")) {
    int pasos = cmd.substring(4).toInt();
    setAtenuacion(pasos);
    return;
  }

  // Compatibilidad con versiones del programa que mandan sólo número.
  if (esNumero(cmd)) {
    int pasos = cmd.toInt();
    setAtenuacion(pasos);
    return;
  }

  if (cmd == "H") {
    digitalWrite(ledPin, HIGH);
    Serial.println("OK LED HIGH");
    return;
  }

  if (cmd == "L") {
    digitalWrite(ledPin, LOW);
    Serial.println("OK LED LOW");
    return;
  }

  Serial.print("ERR COMANDO NO RECONOCIDO: ");
  Serial.println(cmd);
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(U1, OUTPUT);
  pinMode(U2, OUTPUT);
  pinMode(U3, OUTPUT);
  pinMode(U4, OUTPUT);

  pinMode(pinV1, OUTPUT);
  pinMode(pinV2, OUTPUT);
  pinMode(pinV3, OUTPUT);
  pinMode(pinV4, OUTPUT);
  pinMode(pinV5, OUTPUT);
  pinMode(pinV6, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  lastButtonState = digitalRead(buttonPin);

  // Atenuador en 0 dB al iniciar.
  digitalWrite(pinV1, HIGH);
  digitalWrite(pinV2, HIGH);
  digitalWrite(pinV3, HIGH);
  digitalWrite(pinV4, HIGH);
  digitalWrite(pinV5, HIGH);
  digitalWrite(pinV6, HIGH);

  aplicarDirecto();

  Serial.println("ESP32_RF_CONTROLLER_READY");
  imprimirStatus();
}

void loop() {
  // Botón físico con antirrebote.
  bool currentButtonState = digitalRead(buttonPin);
  unsigned long now = millis();

  if (lastButtonState == HIGH && currentButtonState == LOW && (now - lastButtonMs) > debounceMs) {
    lastButtonMs = now;
    toggleModo();
  }
  lastButtonState = currentButtonState;

  // Comandos por USB/Serial.
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    procesarComando(cmd);
  }
}

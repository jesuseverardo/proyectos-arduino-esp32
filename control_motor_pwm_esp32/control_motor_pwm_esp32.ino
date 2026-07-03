// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Potenciómetro
int potPin = 34;   // Pin ADC del ESP32

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;

int potValue = 0;
int dutyCycle = 0;

void setup() {
  // Pines del motor
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // Configurar PWM
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);

  // Comunicación serial
  Serial.begin(115200);
  Serial.println("Control de velocidad con potenciometro");
  
  // Dirección fija del motor: adelante
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
}

void loop() {
  // Leer el potenciómetro (ADC ESP32: 0 - 4095)
  potValue = analogRead(potPin);

  // Convertir lectura a PWM de 8 bits (0 - 255)
  dutyCycle = map(potValue, 0, 4095, 0, 255);

  // Aplicar velocidad al motor
  ledcWrite(enable1Pin, dutyCycle);

  // Mostrar datos en monitor serial
  Serial.print("Potenciometro: ");
  Serial.print(potValue);
  Serial.print(" | Duty Cycle: ");
  Serial.println(dutyCycle);

  delay(100);
}
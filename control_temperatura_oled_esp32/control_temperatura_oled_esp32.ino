#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C   

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pines
const int sensorPin = 34;      
const int botonUP = 12;
const int botonDOWN = 13;
const int ledPin = 2;          

float setpoint = 35.0;

void setup() {
  Serial.begin(9600);

  pinMode(botonUP, INPUT_PULLUP);
  pinMode(botonDOWN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Error al iniciar OLED");
    for (;;);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  if (digitalRead(botonUP) == LOW) {
    setpoint++;
    delay(200);
  }

  if (digitalRead(botonDOWN) == LOW) {
    setpoint--;
    delay(200);
  }

  int adcValor = analogRead(sensorPin);
  float voltaje = (adcValor / 4095.0) * 3.3;
  float temperaturaC = voltaje * 100.0;

  if (temperaturaC >= setpoint) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  Serial.print("Temp: ");
  Serial.print(temperaturaC);
  Serial.print(" C | Setpoint: ");
  Serial.println(setpoint);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperatura:");
  display.setCursor(0, 12);
  display.print(temperaturaC, 1);
  display.print(" C");

  display.setCursor(0, 30);
  display.print("Setpoint:");

  display.setCursor(0, 42);
  display.print(setpoint);
  display.print(" C");

  display.setCursor(0, 55);
  if (temperaturaC >= setpoint) {
    display.print("LED: ON");
  } else {
    display.print("LED: OFF");
  }

  display.display();

  delay(500);
}

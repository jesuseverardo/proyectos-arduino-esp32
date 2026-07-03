# Prácticas y proyectos Arduino y ESP32

Este repositorio contiene una colección de prácticas desarrolladas con Arduino y ESP32, enfocadas en control electrónico, comunicación WiFi, sensores, pantallas OLED, PWM, Blynk IoT y sistemas de RF.

Los nombres de las carpetas y de los archivos `.ino` coinciden para que puedan abrirse directamente desde Arduino IDE.

## Proyectos incluidos

| Proyecto | Archivo `.ino` | Descripción |
|---|---|---|
| `control_rf_atenuador_esp32` | `control_rf_atenuador_esp32.ino` | Control de switches RF, atenuador programable de 0 a 31.5 dB, comandos seriales y botón físico. |
| `control_motor_pwm_esp32` | `control_motor_pwm_esp32.ino` | Control de velocidad de un motor mediante PWM, lectura ADC, potenciómetro y puente H. |
| `control_temperatura_oled_esp32` | `control_temperatura_oled_esp32.ino` | Lectura de temperatura, visualización en pantalla OLED, botones, setpoint y salida de control. |
| `portal_wifi_esp32` | `portal_wifi_esp32.ino` | Configuración WiFi mediante WiFiManager y servidor web básico con ESP32. |
| `control_led_blynk_esp32` | `control_led_blynk_esp32.ino` | Control remoto de un LED mediante la plataforma Blynk IoT. |
| `control_rf_atenuador_nano` | `control_rf_atenuador_nano.ino` | Variante del proyecto de control RF desarrollada para Arduino Nano. |

## Estructura del repositorio

```text
practicas-arduino-esp32/
│
├── README.md
├── .gitignore
│
├── control_led_blynk_esp32/
├── control_motor_pwm_esp32/
├── control_rf_atenuador_esp32/
├── control_rf_atenuador_nano/
├── control_temperatura_oled_esp32/
└── portal_wifi_esp32/
```

## Tecnologías utilizadas

- Arduino IDE
- ESP32
- Arduino Nano
- Lenguaje C/C++
- Blynk IoT
- WiFiManager
- Pantalla OLED SSD1306
- Sensores analógicos
- PWM
- Control de RF

## Dependencias

Para compilar algunos proyectos es necesario instalar las siguientes bibliotecas desde el gestor de librerías de Arduino IDE:

- ESP32 Arduino Core
- Adafruit GFX Library
- Adafruit SSD1306
- WiFiManager
- Blynk

No se incluyó la carpeta `libraries` del proyecto original porque contiene copias de bibliotecas externas y aumenta innecesariamente el tamaño del repositorio.

## Cómo usar los proyectos

1. Descarga o clona este repositorio.

```bash
git clone https://github.com/jesuseverardo/practicas-arduino-esp32.git
```

2. Abre Arduino IDE.

3. Entra a la carpeta del proyecto que deseas probar.

4. Abre el archivo `.ino` correspondiente.

5. Selecciona la tarjeta adecuada en Arduino IDE.

Para proyectos con ESP32:

```text
Herramientas > Placa > ESP32 Dev Module
```

Para proyectos con Arduino Nano:

```text
Herramientas > Placa > Arduino Nano
```

6. Selecciona el puerto COM correspondiente.

7. Compila y carga el programa en la placa.

## Preparación del proyecto Blynk

El proyecto `control_led_blynk_esp32` utiliza credenciales privadas, por lo que estas no se incluyen directamente en el código.

Para usarlo:

1. Copia el archivo:

```text
control_led_blynk_esp32/config.example.h
```

2. Renómbralo como:

```text
control_led_blynk_esp32/config.h
```

3. Coloca tus propios datos:

```cpp
#define BLYNK_TEMPLATE_ID "TU_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "TU_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "TU_AUTH_TOKEN"

char ssid[] = "TU_WIFI";
char pass[] = "TU_PASSWORD";
```

4. No subas `config.h` al repositorio. Este archivo ya está excluido en `.gitignore`.

## Descripción de las prácticas

### Control RF con ESP32

El proyecto `control_rf_atenuador_esp32` permite controlar switches de RF y un atenuador programable. Está orientado a aplicaciones de medición, automatización y pruebas relacionadas con sistemas de radiofrecuencia.

Incluye:

- Control de cuatro switches RF.
- Ajuste de atenuación de 0 a 31.5 dB.
- Comandos por monitor serial.
- Botón físico para control manual.
- Aplicación relacionada con sistemas de medición RF.

### Control de motor PWM con ESP32

El proyecto `control_motor_pwm_esp32` permite controlar la velocidad de un motor mediante una señal PWM. La velocidad puede ajustarse mediante un potenciómetro leído por el ADC del ESP32.

Incluye:

- Lectura analógica mediante ADC.
- Generación de señal PWM.
- Control de motor con puente H.
- Regulación de velocidad.

### Control de temperatura con OLED

El proyecto `control_temperatura_oled_esp32` permite leer una señal analógica de temperatura y mostrar información en una pantalla OLED.

Incluye:

- Lectura de sensor analógico.
- Visualización en pantalla OLED.
- Botones físicos.
- Ajuste de setpoint.
- Salida de control.

### Portal WiFi con ESP32

El proyecto `portal_wifi_esp32` utiliza WiFiManager para configurar la conexión WiFi del ESP32 sin escribir directamente el SSID y la contraseña en el código.

Incluye:

- Portal de configuración WiFi.
- Conexión automática a red guardada.
- Servidor web básico.
- Configuración desde navegador.

### Control LED con Blynk

El proyecto `control_led_blynk_esp32` permite controlar un LED de manera remota usando la plataforma Blynk IoT.

Incluye:

- Conexión a Blynk IoT.
- Control remoto desde aplicación o dashboard.
- Separación de credenciales privadas en archivo externo.
- Ejemplo básico de Internet de las Cosas.

### Control RF con Arduino Nano

El proyecto `control_rf_atenuador_nano` es una variante del sistema de control RF implementada con Arduino Nano. Se conserva como alternativa para documentar el uso de otra plataforma de hardware.

## Privacidad y seguridad

Las credenciales personales, tokens de Blynk, nombres de red WiFi y contraseñas fueron retirados del código antes de publicar el repositorio.

Si alguna credencial real fue utilizada durante las pruebas, se recomienda cambiarla antes de compartir el proyecto públicamente.

También se recomienda revisar que no existan datos sensibles escritos directamente en los archivos `.ino`, como:

```cpp
char ssid[] = "NOMBRE_REAL_DE_WIFI";
char pass[] = "CONTRASEÑA_REAL";
#define BLYNK_AUTH_TOKEN "TOKEN_REAL"
```

En su lugar, deben usarse valores de ejemplo o archivos de configuración excluidos mediante `.gitignore`.

## Objetivo

El objetivo de este repositorio es documentar diferentes prácticas de electrónica y programación embebida, mostrando ejemplos aplicados con Arduino y ESP32 para proyectos académicos y de aprendizaje.

## Autor

Jesús Everardo Díaz Alvarado

## Licencia

Este proyecto se publica bajo la licencia MIT. Puedes consultar el archivo `LICENSE` para más información.
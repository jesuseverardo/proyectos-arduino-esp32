#include <WiFi.h>
#include <WebServer.h>
#include <WiFiManager.h>

WebServer server(80);

const char* CONFIG_PORTAL_NAME = "ESP32_Config_AP";
const char* CONFIG_PORTAL_PASSWORD = "cambiar-clave";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFiManager wm;

  Serial.println("\n--- Iniciando WiFi Manager ---");

  wm.setConfigPortalTimeout(180);

  bool exito = wm.autoConnect(CONFIG_PORTAL_NAME, CONFIG_PORTAL_PASSWORD);

  if (!exito) {
    Serial.println("Fallo en la conexion, tiempo de espera del portal agotado.");
    ESP.restart();
  } else {
    Serial.println("Mini Sistema conectado exitosamente.");
    Serial.print("SSID Actual: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Asignada: ");
    Serial.println(WiFi.localIP());
  }

  server.on("/", []() {
    server.send(200, "text/html", "<h1>ESP32 conectado correctamente</h1>");
  });

  server.begin();
  Serial.println("Servidor web iniciado.");
}

void loop() {
  server.handleClient();
}

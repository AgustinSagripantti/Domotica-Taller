#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Personal-C9B-2.4GHz";
const char* password = "01122F2C9B";

WebServer server(80); // Puerto HTTP

int led = 4; // Pin del LED

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ESP32 está vivo!");
}

void handleLedOn() {
  digitalWrite(led, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "LED encendido");
}

void handleLedOff() {
  digitalWrite(led, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "LED apagado");
}

void handleCriptos() {

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Método no permitido");
    return;
  }

  String body = server.arg("plain"); 
  Serial.println(body);

  server.send(200, "text/plain", "Precios recibidos correctamente");
}


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);
  server.on("/criptos", HTTP_POST, handleCriptos);

 server.on("/criptos", HTTP_OPTIONS, []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.send(204); // Sin contenido, pero válida
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}

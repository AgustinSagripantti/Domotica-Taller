#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Personal-C9B-2.4GHz";
const char* password = "01122F2C9B";

WebServer server(80); // Puerto HTTP

int led = 2; // Pin del LED

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

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}

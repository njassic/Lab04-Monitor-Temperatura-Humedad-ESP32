
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* WIFI_SSID = "TU_RED_WIFI";
const char* WIFI_PASSWORD = "TU_CONTRASENA";
const char* WRITE_API_KEY = "TU_WRITE_API_KEY";

const char* THINGSPEAK_URL =
  "http://api.thingspeak.com/update";

// 3. CONFIGURACION DEL SENSOR Y LED
#define DHTPIN 18
#define DHTTYPE DHT11
#define LED_PIN 4

const float UMBRAL = 30.0;

DHT dht(DHTPIN, DHTTYPE);

// Intervalo entre publicaciones: 20 segundos
const unsigned long INTERVALO = 20000;
unsigned long ultimaPublicacion = 0;

void conectarWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.print("Conectando a WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long inicio = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - inicio < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado");
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nSin conexion WiFi");
  }
}

void publicarDatos(float temperatura,
                   float humedad,
                   int alarma) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No se publica: sin WiFi");
    return;
  }

  HTTPClient http;

  http.begin(THINGSPEAK_URL);
  http.addHeader(
    "Content-Type",
    "application/x-www-form-urlencoded"
  );

  String datos =
    "api_key=" + String(WRITE_API_KEY) +
    "&field1=" + String(temperatura, 1) +
    "&field2=" + String(humedad, 1) +
    "&field3=" + String(alarma);

  int codigoHTTP = http.POST(datos);

  if (codigoHTTP == 200) {
    String respuesta = http.getString();

    if (respuesta != "0") {
      Serial.println("Datos publicados correctamente");
      Serial.print("Entry ID: ");
      Serial.println(respuesta);
    } else {
      Serial.println("ThingSpeak rechazo la actualizacion");
    }
  } else {
    Serial.print("Error HTTP: ");
    Serial.println(codigoHTTP);
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  conectarWiFi();

  Serial.println("Monitor IoT iniciado");

  // Permite la primera lectura inmediata
  ultimaPublicacion = millis() - INTERVALO;
}

void loop() {

  if (millis() - ultimaPublicacion >= INTERVALO) {
    ultimaPublicacion = millis();

    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();

    if (isnan(temperatura) || isnan(humedad)) {
      Serial.println("Error al leer el DHT11");
      return;
    }

    int alarma = (temperatura > UMBRAL) ? 1 : 0;

    digitalWrite(LED_PIN, alarma ? HIGH : LOW);

    Serial.println("----------------------");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" C");

    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");

    Serial.print("Estado alarma: ");
    Serial.println(alarma);

    conectarWiFi();
    publicarDatos(temperatura, humedad, alarma);
  }
}

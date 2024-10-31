#include <WiFi.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>

#define WIFI_AP "Vodafone_VDSL"
#define WIFI_PASS "Aa01030898172"

#define TB_SERVER "thingsboard.cloud"
#define TOKEN "NbSp694lfQ5DjSuy1IHc"

constexpr uint16_t MAX_MESSAGE_SIZE = 128U;

WiFiClient espClient;
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

const int GSR_PIN = 34; // Set to the GPIO pin you’re using for the GSR sensor
int gsr_average = 0;

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  int attempts = 0;
  
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    WiFi.begin(WIFI_AP, WIFI_PASS);
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi.");
  } else {
    Serial.println("\nConnected to WiFi");
  }
}

void connectToThingsBoard() {
  if (!tb.connected()) {
    Serial.println("Connecting to ThingsBoard server");
    
    if (!tb.connect(TB_SERVER, TOKEN)) {
      Serial.println("Failed to connect to ThingsBoard");
    } else {
      Serial.println("Connected to ThingsBoard");
    }
  }
}

// Send GSR data to ThingsBoard
void sendDataToThingsBoard(int gsr) {
  String jsonData = "{\"gsr_value\":" + String(gsr) + "}";
  tb.sendTelemetryJson(jsonData.c_str());
  Serial.println("Data sent: " + jsonData);
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToThingsBoard();
}

void loop() {
  connectToWiFi();

  // Calculate GSR average from 10 readings
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    int sensorValue = analogRead(GSR_PIN);
    sum += sensorValue;
    delay(100); // Stabilize readings
  }
  gsr_average = sum / 10; // Average GSR reading

  Serial.println("GSR Value: " + String(gsr_average));

  connectToThingsBoard();
  
  // Send GSR data to ThingsBoard
  sendDataToThingsBoard(gsr_average);

  delay(1000);
  tb.loop(); // Keep the ThingsBoard connection alive
}

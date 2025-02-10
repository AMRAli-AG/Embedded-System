#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>

// WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// MQTT broker details
const char* mqtt_server = "your_mqtt_server";
const int mqtt_port = 1883;
const char* mqtt_user = "your_mqtt_username";
const char* mqtt_password = "your_mqtt_password";
const char* mqtt_topic_pub = "sms/received";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// SIM808 constants
const int RX_PIN = 16; // GPIO 16 (RX2)
const int TX_PIN = 17; // GPIO 17 (TX2)
const int BAUD_RATE = 9600; // Baud rate for SIM808

HardwareSerial mySerial(2); // UART2 for communication with SIM808

// Function to send AT command and wait for a response
String sendAT(String command, const int timeout = 2000) {
  mySerial.println(command);
  long int time = millis();
  String response = "";

  while ((time + timeout) > millis()) {
    while (mySerial.available()) {
      char c = mySerial.read();
      response += c;
    }
  }
  return response;
}

// Function to connect to WiFi
void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to reconnect to MQTT broker
void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect with MQTT credentials
    if (mqttClient.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Function to initialize SIM808 for receiving SMS
void setupSIM808() {
  sendAT("AT+CMGF=1"); // Set SMS mode to text
  sendAT("AT+CNMI=1,2,0,0,0"); // Configure to receive SMS automatically
}

// Function to handle incoming SMS
void handleIncomingSMS() {
  if (mySerial.available()) {
    String response = "";
    while (mySerial.available()) {
      char c = mySerial.read();
      response += c;
      delay(10); // Small delay to allow all characters to be received
    }

    Serial.println("Received SMS: " + response);

    // Parse the response to get the sender number and message
    int senderStart = response.indexOf("+CMT: \"") + 7;
    int senderEnd = response.indexOf("\",\"", senderStart);
    String senderNumber = response.substring(senderStart, senderEnd);

    int messageStart = response.indexOf("\r\n", senderEnd) + 2;
    int messageEnd = response.indexOf("\r\n", messageStart);
    String message = response.substring(messageStart, messageEnd);

    Serial.println("Sender: " + senderNumber);
    Serial.println("Message: " + message);

    // Create JSON object
    StaticJsonDocument<200> doc;
    doc["number"] = senderNumber;
    doc["message"] = message;
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    // Publish to MQTT
    mqttClient.publish(mqtt_topic_pub, jsonBuffer);
  }
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  // Initialize UART2 for SIM808
  mySerial.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);

  delay(500); // Wait for SIM808 to initialize

  // Send AT command to check communication
  Serial.println("Sending AT command to check communication...");
  String response = sendAT("AT");
  Serial.println("Response: " + response);

  if (response.indexOf("OK") < 0) {
    Serial.println("SIM808 communication failed");
    while (1); // Halt if communication failed
  }

  // Set up SIM808 for receiving SMS
  setupSIM808();

  // Set up WiFi connection
  setupWiFi();

  // Set up MQTT connection
  mqttClient.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  handleIncomingSMS();
}

/*
 * Author:  Alexan Mardigian
 * 
 * This sketch will switch a Powerswitch Tail 2 either on or off, via MQTT
 * publication, using a simple push button switch.
 * 
 * 
 * This sketch was created for the Wemos D1 Mini, but it can be modified
 * to run on other ESP8266 boards.  After uploading the code to the Wemos D1 Mini,
 * wire the D3 pin to one pin of your push button switch.  Then wire GND on the Wemos 
 * D1 mini to the other pin of your push button switch.
 * 
 * NOTE:  You will need to enter the details of your MQTT server in
 *        secrets.h, before you compile and upload to your board.
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include "secrets.h"

#define ENABLE_SSL

const int BUTTON_PIN = D3;
const int BAUD_SPEED = 115200;
const char* OFF = "0";
const char* ON = "1";

#ifdef ENABLE_SSL
  const int MQTT_PORT = 8883;

  X509List caCertX509(caCert);
  WiFiClientSecure espClient;
#else
  const int MQTT_PORT = 1883;
  WiFiClient espClient;
#endif

int button_state = 0;
int lampState = LOW;
int prevButtonState = 0;   // The previous state of the button.

const long DEBOUNCE = 200;   // The debounce time, in milliseconds.
long toggleTime = 0;   // The last time the output pin was toggled.

PubSubClient client(espClient);

void connect_to_mqtt_server();
void callback(char* topic, byte* payload, unsigned int length);

void setup()
{
  Serial.begin(BAUD_SPEED);
  delay(10);
  
  pinMode(BUTTON_PIN, INPUT);

  WiFiManager wifiManager;
  wifiManager.autoConnect("Light-switch-remote-AP");

#ifdef ENABLE_SSL
  // Configure secure client connection.
  espClient.setTrustAnchors(&caCertX509);         // Load CA cert into trust store.
  espClient.allowSelfSignedCerts();               // Enable self-signed cert support.
  espClient.setFingerprint(mqttCertFingerprint);  // Load SHA1 mqtt broker cert fingerprint for connection validation.
#endif

  // Connect to the MQTT server.
  client.setServer(MQTT_SERVER_IP, MQTT_PORT);
  client.setCallback(callback);

  connect_to_mqtt_server();
}

void loop()
{
  if (!client.connected()) {
    connect_to_mqtt_server();
  }

  client.loop();

  button_state = digitalRead(BUTTON_PIN);

  if (button_state != prevButtonState && millis() - toggleTime > DEBOUNCE) {
    if (lampState == LOW) {
      client.publish(MQTT_TOPIC, ON);
    } else {
      client.publish(MQTT_TOPIC, OFF);
    }

    toggleTime = millis();
  }

  prevButtonState = button_state;
}

void connect_to_mqtt_server()
{
  Serial.print("Connecting to MQTT server ");
  Serial.print(MQTT_SERVER_IP);
  Serial.print("..");
  
  while (!client.connected()) {
    Serial.print(".");
 
    if (client.connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected.");  
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  client.publish(MQTT_TOPIC, "Hello from Wemos D1 Mini Powerswitch Tail Button1");
  client.subscribe(MQTT_TOPIC);
}

void callback(char* topic, byte* payload, unsigned int length)
{
  lampState = *payload - 48;  // Convert ASCII data to an integer (either 1 or 0).

  if (strcmp(topic, MQTT_TOPIC) == LOW) {  
    if (lampState == HIGH) {
      Serial.println("Powerswitch tail ON");
    } else {
      Serial.println("Powerswitch tail OFF");
    }
  }
}
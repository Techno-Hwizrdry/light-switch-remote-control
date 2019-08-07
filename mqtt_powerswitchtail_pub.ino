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
 * NOTE:  You will need to enter the details of your wifi network and MQTT server in
 *        secrets.h, before you compile and upload to your board.
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"

const int BUTTON_PIN = D3;
const int BAUD_SPEED = 115200;
const char* OFF = "0";
const char* ON = "1";

const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "wemosD1MiniPowerswitchTailButton1";

int button_state = 0;
int lampState = LOW;
int prevButtonState = 0;   // The previous state of the button.

long toggleTime = 0;   // The last time the output pin was toggled.
long debounce = 200;   // The debounce time, in milliseconds.

WiFiClient espClient;
PubSubClient client(espClient);

void connect_to_mqtt_server();
void callback(char* topic, byte* payload, unsigned int length);

void setup()
{
  Serial.begin(BAUD_SPEED);
  delay(10);
  
  pinMode(BUTTON_PIN, INPUT);

  //  Connect to the wifi network.
  Serial.println();
  Serial.print("Connecting to WiFi network ");
  Serial.print(NETWORK_SSID);
  Serial.print("..");
  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("connected.");

  // Connect to the MQTT server.
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  connect_to_mqtt_server();
}

void loop()
{
  if (! client.connected()) {
    connect_to_mqtt_server();
  }

  client.loop();

  button_state = digitalRead(BUTTON_PIN);

  if (button_state != prevButtonState && millis() - toggleTime > debounce){
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
  Serial.print(MQTT_SERVER);
  Serial.print("..");
  
  while (! client.connected()) {
    Serial.print(".");
 
    if (client.connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD )) {
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

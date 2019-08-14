/*
 * Enter your wifi network and MQTT server settings in this file.
 */

const char* NETWORK_SSID = "";
const char* NETWORK_PASSWORD = "";

const char* MQTT_SERVER_IP = "";  // IP address of your MQTT server.
const char* MQTT_USER = "";
const char* MQTT_PASSWORD = "";
const char* MQTT_TOPIC = "";

/*
 * If you want to use SSL over MQTT, enter your CA cert
 * and MQTT broker cert fingerprint here.
 */

const char caCert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
    ... Your CA cert here ...
-----END CERTIFICATE-----
)EOF";

const uint8_t mqttCertFingerprint[] = {Your, MQTT, brokero cert, fingerprint, here};

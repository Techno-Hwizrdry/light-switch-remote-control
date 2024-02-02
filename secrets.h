/*
 * Enter your MQTT server settings in this file.
 */

const char* MQTT_SERVER_IP = "192.168.1.195";  // IP address of your MQTT server.
const char* MQTT_USER = "alexanmqtt";
const char* MQTT_PASSWORD = "T)(R9o7Y2j1O";
const char* MQTT_TOPIC = "bedroomlamp";

// This should be unique if you plan to have more than one on your network.
// Otherwise, the subsequent device(s) that join will be in an infinite
// loop of connecting and getting disconnected by your MQTT server.
const char* MQTT_CLIENT_NAME = "WemosD1MiniPowerswitchTailClient_test";

/*
 * If you want to use SSL over MQTT, enter your CA cert
 * and MQTT broker cert fingerprint here.
 */

const char caCert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIICjzCCAfCgAwIBAgIJAMeJn5s1gppjMAoGCCqGSM49BAMCMGoxCzAJBgNVBAYT
AlVTMQswCQYDVQQIDAJNQTETMBEGA1UEBwwKU29tZXJ2aWxsZTEhMB8GA1UECwwY
RG9tYWluIENvbnRyb2wgVmFsaWRhdGVkMRYwFAYDVQQDDA0xOTIuMTY4LjEuMTk1
MB4XDTE5MDgxNDAxNTIyM1oXDTI5MDgxMTAxNTIyM1owajELMAkGA1UEBhMCVVMx
CzAJBgNVBAgMAk1BMRMwEQYDVQQHDApTb21lcnZpbGxlMSEwHwYDVQQLDBhEb21h
aW4gQ29udHJvbCBWYWxpZGF0ZWQxFjAUBgNVBAMMDTE5Mi4xNjguMS4xOTUwgZsw
EAYHKoZIzj0CAQYFK4EEACMDgYYABABp/Rs2Q+XSgMwoXZR+Vdh9SR3GGclxQV5w
AD+vdeMpVVn8jiSSn20oGA8qtQcRsZ2nxL5VdTSSfB9qrHF7oywTQQGhMp70LzRK
F9kfB7p5EIs1U8MbfO0rm1ERRG5jC3IZR9RgUC20xeIyNkbfEfgL5J5ILpRQiCYt
MWkB9L/uQyDL5aM8MDowCQYDVR0TBAIwADALBgNVHQ8EBAMCBeAwIAYDVR0RBBkw
F4IJbG9jYWxob3N0hwR/AAABhwTAqAHDMAoGCCqGSM49BAMCA4GMADCBiAJCAZnd
TqX5g8jvcCYUZSQwKdjCHIQsn80GLHJrTCSGxKMcpstsgsVVNNdwCgTf5SXusx20
oA7qXuHeIPupx54h3eAgAkIAnIesPOjA1ipCmXJtmcVwAuFUYRjsarJKsiJzvjHG
eiV1C8gd1aTZ49Ti9TYSqe3rIYfpN76j2RMQtFUnQeM1mXg=
-----END CERTIFICATE-----
)EOF";

const uint8_t mqttCertFingerprint[] = {0xDA,0xDF,0xF0,0x37,0xE0,0x93,0x3E,0x5C,0x83,0xEC,0x3F,0x01,0xD6,0x35,0x00,0x7A,0x31,0xFE,0xBE,0x88};
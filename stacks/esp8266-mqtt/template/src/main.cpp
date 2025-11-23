#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"

// Les variables sont définies via build_flags dans platformio.ini
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqtt_server = SECRET_MQTT_SERVER;
const char* mqtt_user = SECRET_MQTT_USER;
const char* mqtt_pass = SECRET_MQTT_PASS;


WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("✅ WiFi connected !");
  WiFiClient test;
if (test.connect(mqtt_server, 1883)) {
  Serial.println("✅ TCP connection to MQTT broker successful !");
  test.stop();
} else {
  Serial.println("❌ ESP cannot reach MQTT broker");
}
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("MQTT reconnection attempt...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("✅ MQTT Connected");
    } else {
      Serial.print("❌ Failed, state=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
    return;
  }
  client.loop();

  float fakeTemp = 22.0 + random(0, 400) / 100.0;
  char tempString[6];
  dtostrf(fakeTemp, 4, 2, tempString);

  client.publish("diagbox/temp", tempString);
  Serial.print("Temp sent : ");
  Serial.println(tempString);

  delay(5000);
}

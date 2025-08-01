#include <WiFiS3.h>

#include "SCPI_RP.h"
#include "arduino_secrets.h"  // defines SECRET_SSID & SECRET_PASS

scpi_rp::SCPIRedPitaya rp;
WiFiClient client;
IPAddress server(192, 168, 0, 17);
const uint16_t serverPort = 5000;

bool isInit = false;
float value = 0;

void setup() {
  Serial.begin(115200);
  delay(100);

  // ————— STATIC IP (or DHCP if it fails silently) —————
  {
    IPAddress local(192, 168, 0, 50);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress dns(8, 8, 8, 8);
    WiFi.config(local, gateway, subnet, dns);
    Serial.println("⚙️  Static IP configuration applied (no return code)");
  }

  // ————— CONNECT TO WIFI —————
  Serial.print("Connecting to WiFi \"");
  Serial.print(SECRET_SSID);
  Serial.println("\" ...");
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  Serial.print("Waiting for connection");
  unsigned long wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 30000) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ WiFi connection failed");
    while (true) delay(1000);
  }
  Serial.print("✅ WiFi connected — IP = ");
  Serial.println(WiFi.localIP());

  // ————— CONNECT TCP TO RED PITAYA —————
  Serial.print("Connecting to Red Pitaya at ");
  Serial.print(server);
  Serial.print(":");
  Serial.println(serverPort);

  if (!client.connect(server, serverPort)) {
    Serial.println("❌ TCP connection failed");
    while (true) delay(1000);
  }
  Serial.println("✅ TCP connected!");

  rp.initSocket(&client);
  isInit = true;
}

void loop() {
  if (isInit) {
    float in_value = 0;
    if ((value * 10) > 18) value = 0;
    if (!rp.aio.state(scpi_rp::AOUT_0, value)) {
      Serial.println("Error set value");
    }
    if (!rp.aio.stateQ(scpi_rp::AOUT_0, &in_value)) {
      Serial.println("Error get value");
    }
    Serial.print("AOUT_0 value = ");
    Serial.println(in_value);
    if (!rp.aio.stateQ(scpi_rp::AIN_0, &in_value)) {
      Serial.println("Error get value");
    }
    Serial.print("AIN_0 value = ");
    Serial.println(in_value);
    delay(1000);
    value += 0.1;
  }
}

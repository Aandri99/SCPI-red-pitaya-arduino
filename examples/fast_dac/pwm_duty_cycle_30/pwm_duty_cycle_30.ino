// Example of PWM generator with 30% duty cycle

// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

#include <Arduino.h>
#include <WiFi.h>

#include "SCPI_RP.h"

const char *SSID = "YOUR_SSID";
const char *PASSWORD = "YOUR_PASSWORD";
IPAddress server(192, 168, 0, 17);
const uint16_t serverPort = 5000;

scpi_rp::SCPIRedPitaya rp;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if (!client.connect(server, serverPort)) {
    while (true) {
      delay(1000);
    }
  }

  rp.initSocket(&client);
  rp.gen.reset();
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::PWM);
  rp.gen.dutyCycle(scpi_rp::GEN_CH_1, 0.3);
  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);
  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
  rp.gen.sync(scpi_rp::GEN_CH_1);
}

void loop() { delay(1000); }

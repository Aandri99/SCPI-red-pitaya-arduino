// The example generates a signal when a button is pressed.
// The button should close contacts DIO0_N and DIO0_P

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

  rp.dio.reset();
  rp.dio.dir(scpi_rp::DIO_0_P, scpi_rp::IN);
  rp.dio.dir(scpi_rp::DIO_0_N, scpi_rp::OUT);
  rp.dio.state(scpi_rp::DIO_0_N, true);

  rp.gen.reset();

  // Set internal trigger
  rp.gen.trigSource(scpi_rp::GEN_CH_1, scpi_rp::GEN_EXT_NE);

  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);

  // Set burst mode
  rp.gen.genMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_BURST);
  rp.gen.burstInitValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstLastValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstNCycles(scpi_rp::GEN_CH_1, 3);
  rp.gen.burstNRepetitions(scpi_rp::GEN_CH_1, 1);

  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
}

void loop() { delay(100); }

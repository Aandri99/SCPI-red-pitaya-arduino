// The example shows how you can switch the signal frequency without resetting
// the settings and stopping the generator.

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

float freq = 10000;

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

  if (!rp.gen.reset()) {
    Serial.println("Error reset");
  }

  if (!rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SQUARE)) {
    Serial.println("Error set waveform to ch1");
  }

  if (!rp.gen.freq(scpi_rp::GEN_CH_1, freq)) {
    Serial.println("Error set freq to ch1");
  }

  if (!rp.gen.amp(scpi_rp::GEN_CH_1, 0.6)) {
    Serial.println("Error set amplitude to ch1");
  }

  if (!rp.gen.enable(scpi_rp::GEN_CH_1, true)) {  // Power on CH1
    Serial.println("Error enable ch1");
  }

  if (!rp.gen.sync()) {
    Serial.println("Error start generator");
  }
}

void loop() {
  delay(100);

  if (!rp.gen.freqDirect(scpi_rp::GEN_CH_1, freq)) {
    Serial.println("Error set freq to ch1");
  }

  if (!rp.gen.sync()) {
    Serial.println("Error sync generator");
  }

  if (!rp.gen.freqQ(scpi_rp::GEN_CH_1, &freq)) {
    Serial.println("Error get freq from ch1");
  } else {
    Serial.print("Freq CH1: ");
    Serial.println(freq);
  }
  freq += 1000;
  if (freq > 100000) {
    freq = 10000;
  }
}

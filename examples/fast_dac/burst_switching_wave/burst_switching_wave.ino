// The example runs a pulse signal of a different shape every second.

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
uint8_t waveform = 0;

void setup() {
  // Initializing console output
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

  scpi_rp::EGENTrigger trig = scpi_rp::GEN_INT;

  rp.gen.reset();

  // Set internal trigger
  rp.gen.trigSource(scpi_rp::GEN_CH_1, scpi_rp::GEN_INT);
  rp.gen.trigSourceQ(scpi_rp::GEN_CH_1, &trig);
  Serial.print("Gen trigger mode = ");
  Serial.println(trig);

  int deb = 0;
  rp.gen.trigExtDebouncer(213);
  rp.gen.trigExtDebouncerQ(&deb);
  Serial.print("Debouncer = ");
  Serial.println(deb);

  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);

  // Set burst mode
  rp.gen.genMode(scpi_rp::GEN_CH_1, scpi_rp::GEN_BURST);
  rp.gen.burstInitValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstLastValue(scpi_rp::GEN_CH_1, 0);
  rp.gen.burstNCycles(scpi_rp::GEN_CH_1, 3);
  rp.gen.burstNRepetitions(scpi_rp::GEN_CH_1, 2);
  rp.gen.burstPeriod(scpi_rp::GEN_CH_1, 400);

  // Check burst settings
  scpi_rp::EGENBurst mode = scpi_rp::GEN_CONTINUOUS;
  if (!rp.gen.genModeQ(scpi_rp::GEN_CH_1, &mode)) {
    Serial.println("Error get gen mode");
  } else {
    Serial.print("Gen mode = ");
    Serial.println(mode);
  }

  float initV = 0;
  if (!rp.gen.burstInitValueQ(scpi_rp::GEN_CH_1, &initV)) {
    Serial.println("Error get init value");
  } else {
    Serial.print("Init value = ");
    Serial.println(initV);
  }

  float lastV = 0;
  if (!rp.gen.burstLastValueQ(scpi_rp::GEN_CH_1, &lastV)) {
    Serial.println("Error get last value");
  } else {
    Serial.print("Last value = ");
    Serial.println(lastV);
  }

  uint16_t cyc = 0;
  if (!rp.gen.burstNCyclesQ(scpi_rp::GEN_CH_1, &cyc)) {
    Serial.println("Error get n-cyc value");
  } else {
    Serial.print("Number of cycles = ");
    Serial.println(cyc);
  }

  uint16_t rep = 0;
  if (!rp.gen.burstNRepetitionsQ(scpi_rp::GEN_CH_1, &rep)) {
    Serial.println("Error get rep value");
  } else {
    Serial.print("Number of repetitions = ");
    Serial.println(rep);
  }

  uint32_t per = 0;
  if (!rp.gen.burstPeriodQ(scpi_rp::GEN_CH_1, &per)) {
    Serial.println("Error get rep interval value");
  } else {
    Serial.print("Repetition interval = ");
    Serial.println(per);
  }

  rp.gen.enable(scpi_rp::GEN_CH_1, true);  // Power on CH1
}

void loop() {
  delay(1000);
  rp.gen.wave(scpi_rp::GEN_CH_1, (scpi_rp::EGENWave)waveform);
  rp.gen.sync(scpi_rp::GEN_CH_1);
  waveform++;
  if (waveform >= scpi_rp::EGENWave::ARBITRARY) {
    waveform = 0;
  }
}

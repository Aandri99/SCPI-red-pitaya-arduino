#include <WiFiS3.h>

#include "SCPI_RP.h"
#include "arduino_secrets.h"  // defines SECRET_SSID & SECRET_PASS

scpi_rp::SCPIRedPitaya rp;
WiFiClient client;
IPAddress server(192, 168, 0, 17);
const uint16_t serverPort = 5000;

void acquire();

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
  acquire();
  client.stop();
}

void loop() { delay(1000); }

void acquire() {
  rp.gen.reset();
  rp.gen.wave(scpi_rp::GEN_CH_1, scpi_rp::SINE);
  rp.gen.freq(scpi_rp::GEN_CH_1, 10000);
  rp.gen.amp(scpi_rp::GEN_CH_1, 0.9);
  rp.gen.enable(scpi_rp::GEN_CH_1, true);
  rp.gen.sync(scpi_rp::GEN_CH_1);

  if (!rp.acq.control.reset()) {
    Serial.println("Error reset acq");
  }

  float hysteresis = 0.05;
  if (!rp.acq.trigger.hysteresis(hysteresis)) {
    Serial.println("Error set hysteresis");
  }

  if (!rp.acq.trigger.hysteresisQ(&hysteresis)) {
    Serial.println("Error get hysteresis");
  } else {
    Serial.print("Hysteresis = ");
    Serial.println(hysteresis);
  }

  scpi_rp::EACQDecimation decimation = scpi_rp::ACQ_DEC_1;
  if (!rp.acq.settings.decimation(decimation)) {
    Serial.println("Error set decimation");
  }

  if (!rp.acq.settings.decimationQ(&decimation)) {
    Serial.println("Error get decimation");
  } else {
    Serial.print("Decimation = ");
    Serial.println((uint32_t)decimation);
  }

  if (!rp.acq.control.start()) {
    Serial.println("Error start ADC");
  }

  if (!rp.acq.trigger.trigger(scpi_rp::ACQ_CH1_PE)) {
    Serial.println("Error set trigger");
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.stateQ(&state);
    if (state) break;
  }

  while (1) {
    bool state = false;
    rp.acq.trigger.fillQ(&state);
    if (state) break;
  }

  if (!rp.acq.control.stop()) {
    Serial.println("Error stop ADC");
  }

  uint32_t wp = 0;
  if (!rp.acq.data.writePositionQ(&wp)) {
    Serial.println("Error get write pointer");
  } else {
    Serial.print("Write pointer = ");
    Serial.println(wp);
  }

  uint32_t tp = 0;
  if (!rp.acq.data.triggerPositionQ(&tp)) {
    Serial.println("Error get trigger pointer");
  } else {
    Serial.print("Trigger pointer = ");
    Serial.println(tp);
  }

  bool last = false;
  float sample = 0;
  int idx = 0;
  while (!last) {
    rp.acq.data.dataStartEndQ(scpi_rp::ACQ_CH_1, tp, wp, &sample, &last);
    Serial.print(idx++);
    Serial.print(" - ");
    Serial.print(sample, 6);
    Serial.println("");
  }
}

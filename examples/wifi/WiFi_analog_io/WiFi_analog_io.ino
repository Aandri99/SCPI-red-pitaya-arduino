// Example demonstrating analog input/output control over WiFi
// using the SCPIRPWiFi helper. Connect AO0 to AI0 on the Red Pitaya
// before running.
//
// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library
// - WiFiS3, WiFiNINA or WiFi

#include <SCPI_RP_WiFi.h>

const char ssid[] = "YOUR_WIFI";        // change me
const char pass[] = "YOUR_PASS";        // change me
const char host[] = "rp-f0ada4.local";  // or IP address
const uint16_t port = 5000;

scpi_rp::SCPIRPWiFi rp;

bool isInit = false;
float value = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  if (!rp.begin(ssid, pass, host, port)) {
    Serial.println("Connection failed");
    while (true) {
      delay(1000);
    }
  }
  Serial.println("Connected to SCPI server");
  isInit = true;
}

void loop() {
  if (!isInit) {
    return;
  }
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

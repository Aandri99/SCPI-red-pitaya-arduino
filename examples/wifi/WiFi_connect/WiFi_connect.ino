// Minimal example showing how to connect to a Red Pitaya over Wi-Fi
// using the built-in helper class.
//
// Provide your Wi-Fi credentials and the Red Pitaya hostname or IP.

#include <SCPI_RP_WiFi.h>

const char ssid[] = "YOUR_WIFI";        // change me
const char pass[] = "YOUR_PASS";        // change me
const char host[] = "rp-f0ada4.local";  // or IP address
const uint16_t port = 5000;

scpi_rp::SCPIRPWiFi rp;

void setup() {
  Serial.begin(9600);
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
}

void loop() {
  // Add your SCPI calls here
}

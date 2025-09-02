#include "wifiSCPI.h"
#include "arduino_secrets.h"   // WiFi + Red Pitaya settings

WifiSCPI rp;

void setup() {
  // Connect to WiFi and Red Pitaya
  rp.begin(SECRET_SSID, SECRET_PASS, SECRET_RP_IP, SECRET_RP_PORT);

  // Set all LEDs as outputs
  for (int i = 0; i < 8; i++) {
    rp.scpi(String("DIG:PIN:DIR LED") + String(i) + ",OUT");
  }
}

void loop() {
  // Run through LEDs 0 → 7
  for (int i = 0; i < 8; i++) {
    // Turn ON LED i
    rp.scpi(String("DIG:PIN LED") + String(i) + ",1");
    delay(200);

    // Turn OFF LED i
    rp.scpi(String("DIG:PIN LED") + String(i) + ",0");
  }

  // (Optional) run backwards 7 → 0 for a "ping-pong" effect
  for (int i = 6; i > 0; i--) {
    rp.scpi(String("DIG:PIN LED") + String(i) + ",1");
    delay(200);
    rp.scpi(String("DIG:PIN LED") + String(i) + ",0");
  }
}

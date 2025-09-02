#include "wifiSCPI.h"
#include "arduino_secrets.h"   // WiFi + Red Pitaya settings

WifiSCPI rp;

void setup() {
  // Connect to WiFi and Red Pitaya
  rp.begin(SECRET_SSID, SECRET_PASS, SECRET_RP_IP, SECRET_RP_PORT);

  // Set LED0 as output
  rp.scpi("DIG:PIN:DIR LED0,OUT");
}

void loop() {
  // Turn LED0 ON
  rp.scpi("DIG:PIN LED0,1");
  delay(500);

  // Turn LED0 OFF
  rp.scpi("DIG:PIN LED0,0");
  delay(500);
}

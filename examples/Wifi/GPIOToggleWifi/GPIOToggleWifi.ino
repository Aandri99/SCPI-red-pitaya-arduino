#include "wifiSCPI.h"
#include "arduino_secrets.h"   // WiFi + Red Pitaya settings

WifiSCPI rp;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi and Red Pitaya
  rp.begin(SECRET_SSID, SECRET_PASS, SECRET_RP_IP, SECRET_RP_PORT);

  // Configure DIO0_P as OUTPUT
  rp.scpi("DIG:PIN:DIR DIO0_P,OUT");

  // Configure DIO1_P as INPUT
  rp.scpi("DIG:PIN:DIR DIO1_P,IN");

  Serial.println("Setup done. Toggling DIO0_P and reading DIO1_P...");
}

void loop() {
  // ---- Write HIGH on DIO0_P ----
  rp.scpi("DIG:PIN DIO0_P,1");
  delay(500);

  // ---- Read DIO1_P ----
  String state = rp.scpiQuery("DIG:PIN? DIO1_P");
  Serial.print("DIO1_P reads: ");
  Serial.println(state);

  // ---- Write LOW on DIO0_P ----
  rp.scpi("DIG:PIN DIO0_P,0");
  delay(500);

  // ---- Read again ----
  state = rp.scpiQuery("DIG:PIN? DIO1_P");
  Serial.print("DIO1_P reads: ");
  Serial.println(state);
}

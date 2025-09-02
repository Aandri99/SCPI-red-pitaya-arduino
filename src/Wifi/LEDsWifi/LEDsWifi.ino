#include "wifiSCPI.h"
#include "arduino_secrets.h"   // WiFi + Red Pitaya settings

// ------- User config -------

const float GEN_FREQ_HZ   = 2000.0;
const float GEN_AMPL_V    = 1.0;
const float GEN_OFFSET_V  = 0.0;
// ---------------------------

WifiSCPI rp;

void startGen() {
  rp.scpi("GEN:RST");
  rp.scpi("SOUR1:FUNC SINE");
  rp.scpi(String("SOUR1:FREQ:FIX ") + String(GEN_FREQ_HZ, 6));
  rp.scpi(String("SOUR1:VOLT ")     + String(GEN_AMPL_V, 6));
  rp.scpi(String("SOUR1:VOLT:OFFS ")+ String(GEN_OFFSET_V, 6));
  rp.scpi("OUTPUT1:STATE ON");
  rp.scpi("SOUR1:TRig:SOUR INT");
  rp.scpi("SOUR1:TRig:INT");
}

void setup() {
  Serial.begin(115200);
  delay(150);

  if(!rp.begin(SECRET_SSID, SECRET_PASS, SECRET_RP_IP, SECRET_RP_PORT)){
    Serial.println(F("Failed to connect"));
    while(true){}
  }

  startGen();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) rp.connectWiFi(SECRET_SSID, SECRET_PASS);
  if (!rp.connected()) {
    if (rp.connectRP(SECRET_RP_IP, SECRET_RP_PORT)) startGen();
  }
  delay(500);
}


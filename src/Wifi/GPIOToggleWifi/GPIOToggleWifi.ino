#include "wifiSCPI.h"
#include "arduino_secrets.h"   // WiFi + Red Pitaya settings

// ---------- User config ----------
// ---------------------------------

WifiSCPI rp;

// --- GPIO pins ---
const char* OUT_PIN = "DIO0_P";
const char* IN_PIN  = "DIO1_P";

void setup() {
  Serial.begin(115200);
  delay(150);

  if(!rp.begin(SECRET_SSID, SECRET_PASS, SECRET_RP_IP, SECRET_RP_PORT)){
    Serial.println(F("Failed to connect"));
    while(true){}
  }

  rp.scpi(String("DIG:PIN:DIR OUT,") + OUT_PIN);
  rp.scpi(String("DIG:PIN:DIR IN,")  + IN_PIN);

  Serial.print(OUT_PIN); Serial.print(" dir="); Serial.println(rp.scpiLine(String("DIG:PIN:DIR? ")+OUT_PIN));
  Serial.print(IN_PIN);  Serial.print(" dir="); Serial.println(rp.scpiLine(String("DIG:PIN:DIR? ")+IN_PIN));
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) rp.connectWiFi(SECRET_SSID, SECRET_PASS);
  if (!rp.connected()) {
    if (rp.connectRP(SECRET_RP_IP, SECRET_RP_PORT)) {
      rp.scpi(String("DIG:PIN:DIR OUT,") + OUT_PIN);
      rp.scpi(String("DIG:PIN:DIR IN,")  + IN_PIN);
    }
  }
  if (!rp.connected()) { delay(200); return; }

  static bool level = false;
  rp.scpi(String("DIG:PIN ") + OUT_PIN + "," + (level ? "1" : "0"));
  level = !level;

  String v = rp.scpiLine(String("DIG:PIN? ") + IN_PIN);
  Serial.print(IN_PIN); Serial.print(" = "); Serial.println(v);

  delay(200);
}


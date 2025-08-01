#include "wifi/SCPI_RP_WiFi.h"

#include <Arduino.h>

using namespace scpi_rp;

bool SCPIRPWiFi::begin(const char* ssid, const char* pass, const char* host,
                       uint16_t port) {
  WiFi.begin(ssid, pass);
  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 10000) {
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  IPAddress addr;
  if (WiFi.hostByName(host, addr) != 1) {
    return false;
  }

  if (!m_client.connect(addr, port)) {
    return false;
  }
  initStream(&m_client);
  return true;
}

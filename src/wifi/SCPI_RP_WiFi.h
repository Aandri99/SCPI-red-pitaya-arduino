#ifndef SCPI_RP_WIFI_H
#define SCPI_RP_WIFI_H

#include "SCPI_RP.h"

#if __has_include(<WiFiS3.h>)
#include <WiFiS3.h>
#elif __has_include(<WiFiNINA.h>)
#include <WiFiNINA.h>
#elif __has_include(<WiFi.h>)
#include <WiFi.h>
#else
#error "No compatible WiFi library found"
#endif

namespace scpi_rp {

class SCPIRPWiFi : public SCPIRedPitaya {
 public:
  SCPIRPWiFi() = default;

  bool begin(const char* ssid, const char* pass, const char* host,
             uint16_t port);

 private:
  WiFiClient m_client;
};

}  // namespace scpi_rp

#endif

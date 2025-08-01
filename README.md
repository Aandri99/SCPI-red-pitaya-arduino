#SCPI red pitaya library
[![Build Status](https://github.com/RedPitaya/SCPI-red-pitaya-arduino/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/RedPitaya/SCPI-red-pitaya-arduino/actions)

## Description

Arduino library for controlling Red Pitaya boards via SCPI server.

You can get acquainted with Red Pitaya products [here](https://redpitaya.com).
Information about SCPI server is located [here](https://redpitaya.readthedocs.io/en/latest/appsFeatures/remoteControl/scpi.html).

#Dependencies
 * [Red pitaya boards](https://redpitaya.com/stemlab-125-14/).

#Contributing

Contributions are welcome!  Not only you’ll encourage the development of the library, but you’ll also learn how to best use the library and probably some C++ too

## Documentation and doxygen
Documentation is produced by doxygen. Contributions should include documentation for any new code added.

Some examples of how to use doxygen can be found in these guide pages:

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen-tips

MIT license, check license.txt for more information
All text above must be included in any redistribution

To install, use the Arduino Library Manager and search for "SCPI Red Pitaya" and install the library.

## WiFi helper
Boards using the WiFiS3 library, such as the Arduino UNO R4 WiFi, are supported.
You can now connect to a Red Pitaya over Wi‑Fi using `SCPIRPWiFi`. Provide your Wi‑Fi credentials and the Red Pitaya address:
```cpp
#include <SCPI_RP_WiFi.h>

const char ssid[] = "YOUR_WIFI";
const char pass[] = "YOUR_PASS";
const char host[] = "rp-f0ada4.local"; // or IP address
const uint16_t port = 5000;

scpi_rp::SCPIRPWiFi rp;

void setup() {
  Serial.begin(9600);
  if (!rp.begin(ssid, pass, host, port)) {
    Serial.println("Connection failed");
    while (1) {
    }
  }
  Serial.println("Connected");
}
```

See the sketches in the examples/wifi directory for complete usage, including WiFi_analog_io.


# Scpi

## WifiSCPI helper

`wifiSCPI.h` / `wifiSCPI.cpp` provide a small class that joins a Wi-Fi network, opens a TCP connection to the Red Pitaya SCPI server and exposes helpers for sending commands.

### Using the helper in your sketch

1. Copy `wifiSCPI.h` and `wifiSCPI.cpp` into your sketch folder (or install them as a library).
2. Create an `arduino_secrets.h` with your WiFi credentials and Red Pitaya address:

   ```cpp
   #define SECRET_SSID "NetworkName"
   #define SECRET_PASS "Password"
   #define SECRET_RP_IP IPAddress(x, x, x, x)
   #define SECRET_RP_PORT 5000
   ```
3. Include the headers and call `begin` with your Red Pitaya details:

   ```cpp
   #include "wifiSCPI.h"
   #include "arduino_secrets.h"

   WifiSCPI rp;

   void setup() {
     Serial.begin(115200);
     rp.begin(SECRET_SSID, SECRET_PASS, SECRET_RP_IP, SECRET_RP_PORT);

     rp.scpi("ACQ:RST");
     Serial.println(rp.scpiLine("*IDN?"));
   }

   void loop() {}
   ```

`begin` retries until both Wi-Fi and SCPI connections succeed. Use `scpi` to send a command without reading a response, `scpiLine` for single line replies, and `scpiBlock` for block data between `{}` braces. The underlying `WiFiClient` can be accessed via `client()` for streaming operations.

Each example folder demonstrates a different Red Pitaya feature while leveraging this helper for network setup and SCPI communication.

// Example of a test sketch for reading date and time from Red Pitaya board via
// SCPI server. Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

#include "SCPI_RP.h"

scpi_rp::SCPIRedPitaya rp;
FILE f_out;
int sput(char c, __attribute__((unused)) FILE *f) { return !Serial.write(c); }

void setup() {
  // Initializing console output
  Serial.begin(115200);
  // Replacing standard output for the printf command
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE);
  stdout = &f_out;

  // Initializes line 8 as RX and line 9 as TX for SCPI communication via UART
  rp.initUart(8, 9);

  uint16_t year;
  uint8_t month, day;
  if (!rp.system.dateQ(&year, &month, &day)) { // Request date from RP
    printf("Error getting date from RP\n");
  } else {
    printf("Year: %d Month: %02d Day: %02d\n", year, month, day);
  }

  uint8_t hour, min, sec;
  if (!rp.system.timeQ(&hour, &min, &sec)) { // Request time from RP
    printf("Error getting time from RP\n");
  } else {
    printf("Hour: %02d Minute: %02d Second: %02d\n", hour, min, sec);
  }
}

void loop() {}

// Example of a test sketch for Read Red Pitaya board name and board family ID.
// Written by Nikolay Danilyuk

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

#include "SCPI_RP.h"

#define BUFF_SIZE 30

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

  char name[BUFF_SIZE];
  if (!rp.system.boardNameQ(name, BUFF_SIZE)) { // Request name from RP
    printf("Error getting board name from RP\n");
  } else {
    printf("Board name: %s\n", name);
  }

  uint32_t board_id;
  if (!rp.system.boardIDQ(&board_id)) { // Request id from RP
    printf("Error getting board ID from RP\n");
  } else {
    printf("ID: %d\n", board_id);
  }
}

void loop() {}

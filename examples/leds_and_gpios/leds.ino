// Example of a test sketch for reading DNA code from the Red Pitaya ZING
// processor Written by Nikolay Danilyuk, public domain

// REQUIRES the following Arduino libraries:
// - SCPI Red Pitaya Library:
// https://github.com/RedPitaya/SCPI-red-pitaya-arduino

#include "SCPI_RP.h"

scpi_rp::SCPIRedPitaya rp;
FILE f_out;
int sput(char c, __attribute__((unused)) FILE *f) { return !Serial.write(c); }

void setup() {
  Serial.begin(115200);
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE);
  stdout = &f_out;
  rp.initUart(8, 9);
  auto dna = rp.readDNA();
  printf("DNA %d\n", dna);
}

void loop() {}

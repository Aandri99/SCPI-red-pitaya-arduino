/*!
 *  @file SCPI_RP.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "SCPI_RP.h"
#include "common/base_io.h"
#include "uart/uart.h"
#include <SoftwareSerial.h>

using namespace scpi_rp;

BaseIO *g_base_io = nullptr;
SoftwareSerial *g_serial = nullptr;

SCPIRedPitaya::SCPIRedPitaya() {}

SCPIRedPitaya::~SCPIRedPitaya() {
  delete g_base_io;
  delete g_serial;
}

// software serial #2: RX = digital pin 8, TX = digital pin 9
void SCPIRedPitaya::initUart(uint8_t rx, uint8_t tx) {
  g_serial = new SoftwareSerial(rx, tx);
  g_serial->begin(UART_RATE);
  UART *u = new UART();
  u->init(g_serial);
  g_base_io = u;
  system.setInterface(u);
}

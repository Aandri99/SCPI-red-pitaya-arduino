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

using namespace scpi_rp;

BaseIO *g_base_io = nullptr;

SCPIRedPitaya::SCPIRedPitaya() {}

SCPIRedPitaya::~SCPIRedPitaya() { delete g_base_io; }

void SCPIRedPitaya::initUart(SoftwareSerial *serial) {
  serial->begin(UART_RATE);
  UART *u = new UART();
  u->init(serial);
  g_base_io = u;
  system.setInterface(u);
}

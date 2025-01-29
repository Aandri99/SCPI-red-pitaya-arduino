/*!
 *  @file SCPI_RP.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_H
#define SCPI_RP_H

#include "scpi/scpi_rp_system.h"
#include <SoftwareSerial.h>
#include <stdint.h>

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIRedPitaya {
public:
  SCPIRedPitaya();
  ~SCPIRedPitaya();

  /*!
   *  Initializes uart interface with specified RX,TX lines
   *  @param serial UART interface.
   */
  void initUart(SoftwareSerial *serial);

  SCPISystem system;
};

} // namespace scpi_rp

#endif

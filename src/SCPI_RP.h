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

#include <Stream.h>
#include <stdint.h>

#include "scpi/scpi_rp_system.h"

#define RED_PITAYA_UART_RATE 115200

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIRedPitaya {
 public:
  SCPIRedPitaya();
  ~SCPIRedPitaya();

  /*!
   *  @param serial Stream for UART interface.
   */
  void initUARTStream(Stream *serial);

  SCPISystem system;
};

}  // namespace scpi_rp

#endif

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
   *  @param rx RX line number
   *  @param tx TX line number
   */
  void initUart(uint8_t rx, uint8_t tx);

  SCPISystem system;
};

} // namespace scpi_rp

#endif

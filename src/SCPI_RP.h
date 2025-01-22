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

#include <stdint.h>

/*!
 *  @brief  Class that stores state and functions for DHT
 */
class SCPIRedPitaya {
public:
  SCPIRedPitaya();

  /*!
   *  @brief  Returns the DNA code value from the Zynq processor
   *  @return DNA value
   */
  uint64_t readDNA();

};

#endif
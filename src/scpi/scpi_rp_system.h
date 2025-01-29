/*!
 *  @file scpi_rp_system.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_SYSTEM_H
#define SCPI_RP_SYSTEM_H

#include "common/base_io.h"
#include "system/system_enums.h"
#include <stdint.h>

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPISystem {

public:
  SCPISystem() {};
  ~SCPISystem() {};

  /*!
   *  Enables scpi-server log output mode.
   *  @param mode Log output mode on the server.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool log(ESYSLog mode);

  /*!
   *  Sets the time on the board.
   *  @param hour Hour value. Valid values ​​are from 0 - 23.
   *  @param min Minute value. Valid values ​​are from 0 - 59.
   *  @param sec Second value. Valid values ​​are from 0 - 59
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool time(uint8_t hour, uint8_t min, uint8_t sec);

  /*!
   *  Returns the current time on the board.
   *  @param hour Return hour value.
   *  @param min Return minute value.
   *  @param sec Return second value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool timeQ(uint8_t *hour, uint8_t *min, uint8_t *sec);

  /*!
   *  Sets the date on the board.
   *  @param year Year value. Valid values ​​are from 1900 - 3000.
   *  @param month Month value. Valid values ​​are from 1 - 12.
   *  @param day Day value. Valid values ​​are from 1 - 31
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool date(uint16_t year, uint8_t month, uint8_t day);

  /*!
   *  Returns the current date on the board.
   *  @param year Return year value.
   *  @param month Return month value.
   *  @param day Return day value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool dateQ(uint16_t *year, uint8_t *month, uint8_t *day);

  /*!
   *  Identification number of the board model, described in the Proflie api.
   * Not unique for the same board models. Required to determine the board
   * family.
   *  @param id Return id value.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool boardIDQ(uint32_t *id);

  /*!
   *  Returns the board name.
   *  @param buffer Buffer to fill with board model in string format. Ends with
   * '\0'
   *  @param size The size of the buffer being transferred. If the buffer is not
   * enough, the data will be truncated.
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems
   */
  bool boardNameQ(char *buffer, uint16_t size);

  friend class SCPIRedPitaya;

private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

} // namespace scpi_rp

#endif

/*!
 *  @file scpi_rp_acq_data.h
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef SCPI_RP_ACQ_DATA_H
#define SCPI_RP_ACQ_DATA_H

#include <stdint.h>

#include "acq/acq_enums.h"
#include "common/base_io.h"

namespace scpi_rp {
/*!
 *  Class that stores state and functions for SCPI server
 */
class SCPIAcqData {
 public:
  SCPIAcqData(){};
  ~SCPIAcqData(){};

  /*!
   *  Returns the current position of the write pointer, i.e the index of the
   *  most recent sample in the buffer.
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool writePositionQ(uint32_t *position);

  /*!
   *  Returns the position where the trigger event appeared.
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool triggerPositionQ(uint32_t *position);

  /*!
   *  Returns the current position of the write pointer, i.e the index of the
   *  most recent sample in the buffer. Used only in split trigger mode
   *  (currently only STEMlab 125-14 4-Input)
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool writePositionChQ(EACQChannel channel, uint32_t *position);

  /*!
   *  Returns the position where the trigger event appeared. Used only in split
   *  trigger mode (currently only STEMlab 125-14 4-Input)
   *  @param position Buffer position in samples
   *  @return Returns true if the command was called successfully, returns false
   * for any other problems.
   */
  bool triggerPositionChQ(EACQChannel channel, uint32_t *position);

  friend class SCPIRedPitaya;

 private:
  void setInterface(BaseIO *io);
  BaseIO *m_io = nullptr;
};

}  // namespace scpi_rp

#endif

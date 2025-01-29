/*!
 *  @file scpi_rp_system.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_system.h"
#include "common/base_io.h"
#include "system/system.h"

using namespace scpi_rp;

void SCPISystem::setInterface(BaseIO *io) { m_io = io; }

bool SCPISystem::log(ESYSLog mode) {
  if (m_io == nullptr)
    return false;
  return setSYSLog(m_io, mode);
}

bool SCPISystem::time(uint8_t hour, uint8_t min, uint8_t sec) {
  if (m_io == nullptr)
    return false;
  return setSYSTime(m_io, hour, min, sec);
}

bool SCPISystem::timeQ(uint8_t *hour, uint8_t *min, uint8_t *sec) {
  if (m_io == nullptr)
    return false;
  return getSYSTime(m_io, hour, min, sec);
}

bool SCPISystem::date(uint16_t year, uint8_t month, uint8_t day) {
  if (m_io == nullptr)
    return false;
  return setSYSDate(m_io, year, month, day);
}

bool SCPISystem::dateQ(uint16_t *year, uint8_t *month, uint8_t *day) {
  if (m_io == nullptr)
    return false;
  return getSYSDate(m_io, year, month, day);
}

bool SCPISystem::boardIDQ(uint32_t *id) {
  if (m_io == nullptr)
    return false;
  return getSYSBoardID(m_io, id);
}

bool SCPISystem::boardNameQ(char *buffer, uint16_t size) {
  if (m_io == nullptr)
    return false;
  return getSYSBoardName(m_io, buffer, size);
}

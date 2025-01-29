#include "system.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setSYSLog(BaseIO *io, ESYSLog mode) {
  constexpr char cmd[] = "RP:LOGmode ";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  if (mode == ESYSLog::OFF) {
    constexpr char param[] = "OFF\r\n";
    return io->writeStr(param);
  }
  if (mode == ESYSLog::CONSOLE) {
    constexpr char param[] = "CONSOLE\r\n";
    return io->writeStr(param);
  }
  if (mode == ESYSLog::OFF) {
    constexpr char param[] = "SYS_LOG\r\n";
    return io->writeStr(param);
  }
  return false;
}

bool scpi_rp::setSYSTime(BaseIO *io, uint8_t hour, uint8_t min, uint8_t sec) {
  char buffer[3];
  if (hour > 23)
    return false;
  if (min > 59)
    return false;
  if (sec > 59)
    return false;

  constexpr char cmd[] = "SYSTem:TIME \"";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  itoa(hour, buffer, 10);
  if (!io->writeStr(buffer)) {
    return false;
  }
  io->write(":", 1);
  itoa(min, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->write("\r\n", 2);
    return false;
  }
  io->write(":", 1);
  itoa(sec, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->write("\r\n", 2);
    return false;
  }
  return io->write("\"\r\n", 3);
}

bool scpi_rp::getSYSTime(BaseIO *io, uint8_t *hour, uint8_t *min,
                         uint8_t *sec) {
  constexpr char cmd[] = "SYSTem:TIME?\r\n";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    uint32_t x, y, z;
    int ret = sscanf(value.value, "%u:%u:%u", &x, &y, &z);
    io->flushCommand(value.next_value);
    *hour = x;
    *min = y;
    *sec = z;
    if (ret != 3)
      return false;
    return true;
  }
  return false;
}

bool scpi_rp::setSYSDate(BaseIO *io, uint16_t year, uint8_t month,
                         uint8_t day) {
  char buffer[6];
  constexpr char cmd[] = "SYSTem:DATE \"";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  itoa(year, buffer, 10);
  if (!io->writeStr(buffer)) {
    return false;
  }
  io->write("-", 1);
  itoa(month, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->write("\r\n", 2);
    return false;
  }
  io->write("-", 1);
  itoa(day, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->write("\r\n", 2);
    return false;
  }
  return io->write("\"\r\n", 3);
}

bool scpi_rp::getSYSDate(BaseIO *io, uint16_t *year, uint8_t *month,
                         uint8_t *day) {
  constexpr char cmd[] = "SYSTem:DATE?\r\n";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    uint32_t x, y, z;
    int ret = sscanf(value.value, "%u-%u-%u", &x, &y, &z);
    io->flushCommand(value.next_value);
    *year = x;
    *month = y;
    *day = z;
    if (ret != 3)
      return false;
    return true;
  }
  return false;
}

bool scpi_rp::getSYSBoardID(BaseIO *io, uint32_t *id) {
  constexpr char cmd[] = "SYSTem:BRD:ID?\r\n";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *id = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::getSYSBoardName(BaseIO *io, char *name, scpi_size size) {
  constexpr char cmd[] = "SYSTem:BRD:Name?\r\n";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    memset(name, 0, size);
    strncpy(name, value.value, value.size < size - 1 ? value.size : size - 1);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

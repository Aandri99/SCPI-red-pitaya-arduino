#include "system.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setSYSLog(BaseIO *io, ESYSLog mode) {
  constexpr char cmd[] = "RP:LOGmode ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
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
  if (hour > 23) return false;
  if (min > 59) return false;
  if (sec > 59) return false;

  constexpr char cmd[] = "SYSTem:TIME \"";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  itoa(hour, buffer, 10);
  if (!io->writeStr(buffer)) {
    return false;
  }
  io->write(":", 1);
  itoa(min, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeCommandSeparator();
    return false;
  }
  io->write(":", 1);
  itoa(sec, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->write("\"\r\n", 3);
}

bool scpi_rp::getSYSTime(BaseIO *io, uint8_t *hour, uint8_t *min,
                         uint8_t *sec) {
  constexpr char cmd[] = "SYSTem:TIME?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
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
    if (ret != 3) return false;
    return true;
  }
  return false;
}

bool scpi_rp::setSYSDate(BaseIO *io, uint16_t year, uint8_t month,
                         uint8_t day) {
  char buffer[6];
  constexpr char cmd[] = "SYSTem:DATE \"";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  itoa(year, buffer, 10);
  if (!io->writeStr(buffer)) {
    return false;
  }
  io->write("-", 1);
  itoa(month, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeCommandSeparator();
    return false;
  }
  io->write("-", 1);
  itoa(day, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeCommandSeparator();
    return false;
  }
  return io->write("\"\r\n", 3);
}

bool scpi_rp::getSYSDate(BaseIO *io, uint16_t *year, uint8_t *month,
                         uint8_t *day) {
  constexpr char cmd[] = "SYSTem:DATE?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
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
    if (ret != 3) return false;
    return true;
  }
  return false;
}

bool scpi_rp::getSYSBoardID(BaseIO *io, uint32_t *id) {
  constexpr char cmd[] = "SYSTem:BRD:ID?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
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
    io->writeCommandSeparator();
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

bool scpi_rp::setCls(BaseIO *io) {
  constexpr char cmd[] = "*CLS\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setEse(BaseIO *io, uint8_t _value) {
  char buffer[3];
  constexpr char cmd[] = "*ESE {";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  itoa(_value, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char param[] = "}\r\n";
  return io->writeStr(param);
}

bool scpi_rp::getEse(BaseIO *io, uint8_t *_value) {
  constexpr char cmd[] = "*ESE?\r\n";
  if (!io->writeStr(cmd)) {
    io->write("\r\n", 2);
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *_value = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::getEsr(BaseIO *io, uint8_t *_value) {
  constexpr char cmd[] = "*ESR?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *_value = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setOpc(BaseIO *io) {
  constexpr char cmd[] = "*OPC\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::getOpc(BaseIO *io, uint8_t *_value) {
  constexpr char cmd[] = "*OPC?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *_value = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::setRst(BaseIO *io) {
  constexpr char cmd[] = "*RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setSre(BaseIO *io, uint8_t _value) {
  char buffer[3];
  constexpr char cmd[] = "*SRE {";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  itoa(_value, buffer, 10);
  if (!io->writeStr(buffer)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char param[] = "}\r\n";
  return io->writeStr(param);
}

bool scpi_rp::getSre(BaseIO *io, uint8_t *_value) {
  constexpr char cmd[] = "*SRE?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *_value = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::getStb(BaseIO *io, uint8_t *_value) {
  constexpr char cmd[] = "*STB?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *_value = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::getErr_c(BaseIO *io, uint16_t *_value) {
  constexpr char cmd[] = "SYST:ERR:COUNt?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  auto value = io->read();
  if (value.isValid) {
    *_value = atoi(value.value);
    io->flushCommand(value.next_value);
    return true;
  }
  return false;
}

bool scpi_rp::getErr_n(BaseIO *io, char *name, scpi_size size) {
  constexpr char cmd[] = "SYST:ERR:NEXT?r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
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

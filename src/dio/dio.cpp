#include "dio.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool scpi_rp::setDIORst(BaseIO *io) {
  constexpr char cmd[] = "DIG:RST\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return true;
}

bool scpi_rp::setDIODir(BaseIO *io, EDIOPin pin, EDIODir dir) {
  auto writedir = [&](EDIODir dir) {
    switch (dir) {
      case IN:
        if (!io->writeStr("IN")) {
          io->writeCommandSeparator();
          return false;
        }
        break;
      case OUT:
        if (!io->writeStr("OUT")) {
          io->writeCommandSeparator();
          return false;
        }
        break;
      default:
        io->writeCommandSeparator();
        return false;
        break;
    }
    return true;
  };

  char buffer[3];
  constexpr char cmd[] = "DIG:PIN:DIR ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  writedir(dir);
  if (pin >= LED_0 && pin <= LED_7) {
    if (!io->writeStr(",LED")) {
      io->writeCommandSeparator();
      return false;
    }
    itoa(pin, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr(",DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    itoa(pin - DIO_0_P, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr(",DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    itoa(pin - DIO_0_N, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeCommandSeparator();
      return false;
    }
    return io->writeCommandSeparator();
  }

  io->writeCommandSeparator();
  return false;
}

bool scpi_rp::getDIODir(BaseIO *io, EDIOPin pin, EDIODir *dir) {
  auto readDir = [&]() {
    auto value = io->read();
    if (value.isValid) {
      if (strcmp(value.value, "IN")) {
        *dir = EDIODir::IN;
      } else if (strcmp(value.value, "OUT")) {
        *dir = EDIODir::OUT;
      } else {
        io->flushCommand(value.next_value);
        return false;
      }
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  char buffer[3];
  constexpr char cmd[] = "DIG:PIN:DIR? ";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (pin >= LED_0 && pin <= LED_7) {
    if (!io->writeStr("LED")) {
      io->writeCommandSeparator();
      return false;
    }
    itoa(pin, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    itoa(pin - DIO_0_P, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr("DIO")) {
      io->writeCommandSeparator();
      return false;
    }
    itoa(pin - DIO_0_N, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeCommandSeparator();
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeCommandSeparator();
      return false;
    }
    io->writeCommandSeparator();
    return readDir();
  }
  return false;
}

bool scpi_rp::setDIOState(BaseIO *io, EDIOPin pin, bool state) {
  auto writeState = [&](bool state) {
    if (!io->writeStr(state ? ",1" : ",0")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    return io->writeStr(SCPI_COMMAND_SEPARATOR);
  };
  char buffer[3];
  constexpr char cmd[] = "DIG:PIN ";
  if (!io->writeStr(cmd)) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }
  if (pin >= LED_0 && pin <= LED_7) {
    if (!io->writeStr("LED")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    return writeState(state);
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr("DIO")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin - DIO_0_P, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    return writeState(state);
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr("DIO")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin - DIO_0_N, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    return writeState(state);
  }

  io->writeStr(SCPI_COMMAND_SEPARATOR);
  return false;
}
bool scpi_rp::getDIOState(BaseIO *io, EDIOPin pin, bool *state) {
  auto readDir = [&]() {
    auto value = io->read();
    if (value.isValid) {
      if (!strcmp(value.value, "1")) {
        *state = true;
      } else if (!strcmp(value.value, "0")) {
        *state = false;
      } else {
        io->flushCommand(value.next_value);
        return false;
      }
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };

  char buffer[3];
  constexpr char cmd[] = "DIG:PIN? ";
  if (!io->writeStr(cmd)) {
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return false;
  }
  if (pin >= LED_0 && pin <= LED_7) {
    if (!io->writeStr("LED")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return readDir();
  }

  if (pin >= DIO_0_P && pin <= DIO_10_P) {
    if (!io->writeStr("DIO")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin - DIO_0_P, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    if (!io->writeStr("_P")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return readDir();
  }

  if (pin >= DIO_0_N && pin <= DIO_10_N) {
    if (!io->writeStr("DIO")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    itoa(pin - DIO_0_N, buffer, 10);
    if (!io->writeStr(buffer)) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    if (!io->writeStr("_N")) {
      io->writeStr(SCPI_COMMAND_SEPARATOR);
      return false;
    }
    io->writeStr(SCPI_COMMAND_SEPARATOR);
    return readDir();
  }
  return false;
}

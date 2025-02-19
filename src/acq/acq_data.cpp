#include "acq_data.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace scpi_rp;

bool getAcqWritePointer(BaseIO *io, uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:WPOS?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool getAcqTriggerPointer(BaseIO *io, uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:TPOS?\r\n";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool getAcqWritePointerCh(BaseIO *io, EACQChannel channel, uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:WPOS:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = "?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

bool getAcqTriggerPointerCh(BaseIO *io, EACQChannel channel,
                            uint32_t *position) {
  auto readValue = [&]() {
    auto value = io->read();
    if (value.isValid) {
      *position = atoi(value.value);
      io->flushCommand(value.next_value);
      return true;
    }
    return false;
  };
  constexpr char cmd[] = "ACQ:TPOS:CH";
  if (!io->writeStr(cmd)) {
    io->writeCommandSeparator();
    return false;
  }
  if (!io->writeNumber(channel)) {
    io->writeCommandSeparator();
    return false;
  }
  constexpr char cmd2[] = "?\r\n";
  if (!io->writeStr(cmd2)) {
    io->writeCommandSeparator();
    return false;
  }
  return readValue();
}

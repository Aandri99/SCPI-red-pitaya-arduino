#include "base_io.h"
#include "Arduino.h"
#include <stdio.h>
#include <string.h>

using namespace scpi_rp;

BaseIO::BaseIO() {
  m_bufferSize = 0;
  m_bufferReadPos = 0;
}

BaseIO::~BaseIO() {}

int BaseIO::checkParamSeparator() {
  for (scpi_size i = m_bufferReadPos; i < m_bufferSize; i++) {
    if (m_buffer[i] == SCPI_PARAM_SEPARATOR) {
      return i;
    }
  }
  return -1;
}

int BaseIO::checkCommandSeparator() {
  for (scpi_size i = m_bufferReadPos; i < m_bufferSize - 1 && m_bufferSize > 0;
       i++) {
    if (m_buffer[i] == SCPI_COMMAND_SEPARATOR[0] &&
        m_buffer[i + 1] == SCPI_COMMAND_SEPARATOR[1]) {
      return i;
    }
  }
  return -1;
}

int BaseIO::fillBuffer() {
  int end = -1;
  while (end == -1) {
    end = checkParamSeparator();
    if (end == -1) {
      end = checkCommandSeparator();
    }
    if (end == -1) {
      scpi_size ret = readToBuffer();
      if (ret == 0) {
        return -1;
      }
    }
  }
  return end;
}

const Value BaseIO::readStr() {
  Value value;
  int end = fillBuffer();
  if (end == -1)
    return value;
  if (m_buffer[m_bufferReadPos] == "\"" && m_buffer[end - 1] == "\"") {
    m_buffer[end - 1] = '\0';
    value.value = m_buffer + m_bufferReadPos + 1;
    value.size = end - m_bufferReadPos;
    value.isValid = true;
    value.next_value = m_buffer[end] == "," ? end + 1 : end + 2;
  }
  return value;
}

const Value BaseIO::read() {
  Value value;
  int end = fillBuffer();
  if (end == -1)
    return value;
  m_buffer[end] = '\0';
  value.value = m_buffer + m_bufferReadPos;
  value.size = end - m_bufferReadPos;
  value.isValid = true;
  value.next_value = m_buffer[end] == "," ? end + 1 : end + 2;
  return value;
}

bool BaseIO::writeStr(const char *_data) {
  scpi_size len = strlen((char *)_data);
  if (write(_data, len) != len) {
    return false;
  }
  return true;
}

void BaseIO::flush() {
  m_bufferSize = 0;
  m_bufferReadPos = 0;
}

void BaseIO::flushCommand(scpi_size value) {
  int next_block = value;
  if (m_bufferSize <= next_block) {
    flush();
    return;
  }
  memmove(m_buffer, m_buffer + next_block, m_bufferSize - next_block);
  m_bufferReadPos = 0;
  m_bufferSize = m_bufferSize - next_block;
}

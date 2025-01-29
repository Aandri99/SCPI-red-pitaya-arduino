#include "uart.h"
#include <stdio.h>
#include <string.h>

using namespace scpi_rp;

UART::UART() {}

UART ::~UART() {}

int UART::init(SoftwareSerial *uart) {
  m_uart = uart;
  return 0;
}

scpi_size UART::write(const uint8_t *_data, scpi_size _size) {
  scpi_size pos = 0;
  scpi_size s = _size;
  while (pos < _size) {
    auto send = m_uart->write(_data + pos, s);
    pos += send;
    s -= send;
  }
  return pos;
}

scpi_size UART::readToBuffer() {
  if (BASE_IO_BUFFER_SIZE - m_bufferSize < UART_PROTO_BLOCK_SIZE) {
    DEBUG_UP("Not enough memory in buffer")
    return 0;
  }

  scpi_size rs = m_protocol.readBlock(m_uart, m_buffer + m_bufferSize,
                                      UART_PROTO_BLOCK_SIZE);
  m_bufferSize += rs;
  return rs;
}

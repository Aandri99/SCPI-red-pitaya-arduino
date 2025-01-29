#include "uart_protocol.h"
#include <stdio.h>
#include <string.h>

using namespace scpi_rp;

auto UARTProtocol::crc4(uint8_t *data, uint8_t size) -> uint8_t {
  const uint8_t CRC4_POLY = 0x13;
  uint8_t crc = 0;
  for (uint8_t z = 0; z < size; z++) {
    uint8_t byte = data[z];
    for (int i = 7; i >= 0; --i) {
      bool bit = (byte >> i) & 1;
      bool crc_msb = crc & 0x08;
      crc <<= 1;
      if (crc_msb ^ bit) {
        crc ^= CRC4_POLY;
      }
      crc &= 0x0F;
    }
  }
  return crc;
}

// auto UARTProtocol::read(SoftwareSerial *uart, uint8_t *buffer,
//                         scpi_size size) -> scpi_size {
//   scpi_size pos = 0;
//   uint8_t receiveSize =
//       size < UART_PROTO_BLOCK_SIZE ? size : UART_PROTO_BLOCK_SIZE;
//   while (pos < size) {
//     scpi_size ret = readBlock(uart, buffer + pos, receiveSize);
//     if (ret == 0) {
//       return 0;
//     }
//     pos += ret;
//     receiveSize =
//         size - pos > UART_PROTO_BLOCK_SIZE ? UART_PROTO_BLOCK_SIZE : size -
//         pos;
//   }
//   return pos;
// }

auto UARTProtocol::readBlock(SoftwareSerial *uart, uint8_t *buffer,
                             scpi_size size) -> scpi_size {
  uint8_t header = 0;
  while (uart->available() == 0)
    ;
  uint8_t ret = uart->readBytes(&header, 1);
  if (ret != 1) {
    DEBUG_UP("Error reading header size %d\n", ret);
    return 0;
  }
  uint8_t readSize = (header & 0x0F) + 1;
  if (readSize > size) {
    DEBUG_UP("Block size %d is larger than buffer size %d\n", readSize, size);
    return 0;
  }
  while (uart->available() != readSize)
    ;
  ret = uart->readBytes(buffer, readSize);
  if (ret != readSize) {
    DEBUG_UP("Buffer read error. Read size %d\n", ret);
    return 0;
  }
  uint8_t headerReceive = getHeaderForBlock(buffer, readSize);
  if (headerReceive != header) {
    DEBUG_UP("The receive does not match the packet header 0x%X != 0x%X\n",
             header, headerReceive);
    return 0;
  }
  ret = uart->write(&headerReceive, 1);
  if (ret != 1) {
    return 0;
  }
  return readSize;
}

// auto UARTProtocol::write(SoftwareSerial *uart, const uint8_t *buffer,
//                          size_t size) -> size_t {
//   size_t pos = 0;
//   uint8_t sendSize = size < 8 ? size : 8;
//   bool first = true;
//   while (pos < size) {
//     uint8_t header = getHeaderForBlock(buffer + pos, sendSize, first);
//     uint8_t ret = uart->write(&header, 1); // Send header at first
//     if (ret != 1) {
//       return pos;
//     }
//     first = false;
//     uart->flush();
//     ret = uart->write(buffer + pos, sendSize); // Send data block
//     if (ret != sendSize) {
//       return pos + ret;
//     }
//     uart->flush();
//     uint8_t headerResponse = 0;
//     while (uart->available() == 0)
//       ;
//     ret = uart->readBytes(&headerResponse, 1);
//     if (headerResponse != header) {
//       DEBUG_UP("The response does not match the packet header 0x%X !=
//       0x%X\n",
//                header, headerResponse);
//       return pos;
//     }
//     uart->flush();
//     pos += sendSize;
//     sendSize = pos + sendSize < size ? sendSize : size - pos;
//   }

//   return size;
// }

auto UARTProtocol::getHeaderForBlock(uint8_t *buffer, uint8_t size) -> uint8_t {
  if (size == 0) {
    DEBUG_UP("Buffer size cannot be 0\n");
    return 0;
  }
  if (size > UART_PROTO_BLOCK_SIZE) {
    DEBUG_UP("The size %d is larger than the allowed %d\n", size,
             UART_PROTO_BLOCK_SIZE);
    return 0;
  }
  uint8_t value = crc4(buffer, size);
  value = value << 4;
  value = (value & 0xF0) | ((size - 1) & 0xF);
  return value;
}

#ifndef STRUCTS_SCPI_H
#define STRUCTS_SCPI_H

#include <stdint.h>

namespace scpi_rp {

#define SCPI_COMMAND_SEPARATOR "\r\n"
#define SCPI_PARAM_SEPARATOR ","
#define SCPI_BINARY_HEADER "#"

// #define DEBUG_UART_PROTOCOL

#define UART_RATE 115200

#define BASE_IO_BUFFER_SIZE 128

#define scpi_size uint16_t

/**
 Structure with return values ​​from the server
*/
struct ReadData {
  const uint8_t *data = nullptr;
  scpi_size size = 0;
};

struct ReadData16Bytes {
  uint8_t data[16];
  uint8_t size = 0;
};

// template <typename T> struct Value {
//   bool isValid;
//   T value;
// };

/**
 Structure wrapper for a string.
*/
struct Value {
  bool isValid = false;
  const char *value = nullptr;
  scpi_size size = 0;
  scpi_size next_value = 0;
};

// /**
//  Structure wrapper for a string.
// */
// struct ValueMnemonic {
//   bool isValid = false;
//   const char *value = nullptr;
//   scpi_size size = 0;
// };

#ifdef DEBUG_UART_PROTOCOL
#define DEBUG_UP(...)                                                          \
  { printf(__VA_ARGS__); }
#else
#define DEBUG_UP(...)
#endif

} // namespace scpi_rp

#endif

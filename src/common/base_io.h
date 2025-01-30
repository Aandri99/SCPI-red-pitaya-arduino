#ifndef BASE_IO_H
#define BASE_IO_H

#include <stdint.h>

#include "structs.h"

namespace scpi_rp {
/**
 Base input/output class
*/
class BaseIO {
 public:
  /**
   * Default constructor - setting all variabels to default values
   */
  BaseIO();

  virtual ~BaseIO();

  /**
   * The function reads the value from the server. Excluding the command
   * separator.
   */
  const Value readStr();
  const Value read();

  bool writeStr(const char *_data);

  bool writeCommandSeparator();

  void flush();
  void flushCommand(scpi_size value);

  /**
   * The function sends data to the server.
   *
   * @param _data  Buffer with command. Excluding the command separator.
   * @param _size  Size of data sent
   *
   * If the data was not sent, it returns the value 0
   */
  virtual scpi_size write(const uint8_t *_data, scpi_size _size) = 0;

  scpi_size write(const char *_data, scpi_size _size);

 protected:
  int checkParamSeparator();
  int checkCommandSeparator();
  int fillBuffer();

  virtual scpi_size readToBuffer() = 0;

  uint8_t m_buffer[BASE_IO_BUFFER_SIZE];
  scpi_size m_bufferSize = 0;
  scpi_size m_bufferReadPos = 0;
};

}  // namespace scpi_rp

#endif

#ifndef UART_H
#define UART_H

#include "common/base_io.h"
#include "common/structs.h"
#include "uart_protocol.h"
#include <SoftwareSerial.h>
#include <stdint.h>

namespace scpi_rp {

class UART : public BaseIO {

public:
  UART();
  ~UART();

  /**
   * The function reads the value from the server. Excluding the command
   * separator.
   */
  int init(SoftwareSerial *uart);

  /**
   * The function sends data to the server.
   *
   * @param _data  Buffer with command. Excluding the command separator.
   * @param _size  Size of data sent
   *
   * If the data was not sent, it returns the value 0
   */
  scpi_size write(const uint8_t *_data, scpi_size _size) override;

private:
  scpi_size readToBuffer() override;

  SoftwareSerial *m_uart;
  UARTProtocol m_protocol;
};

} // namespace scpi_rp

#endif

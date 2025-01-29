#ifndef BASE_IO_H
#define BASE_IO_H

#include "structs.h"
#include <stdint.h>

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

  // IEEE Mandated Commands

  // /**
  //  * The Clear Status (CLS) command clears the status byte by emptying the
  //  error
  //  * queue and clearing all the event registers including the Data
  //  Questionable
  //  * Event Register, the Standard Event Status Register, the Standard
  //  Operation
  //  * Status Register and any other registers that are summarized in the
  //  status
  //  * byte.
  //  *
  //  * The SCPI server does not return any data.
  //  *
  //  * @return Returns the status whether the command was sent or not.
  //  *
  //  */
  // bool cls();

  // /**
  //  * Selects the desired bits from the standard event status enable register.
  //  * The variable <_value> represents the sum of the bits that will be
  //  enabled.
  //  * This register monitors I/O errors and synchronization conditions such as
  //  * operation complete, request control, query error, device dependent
  //  error,
  //  * status execution error, command error and power on. The selected bits
  //  are
  //  * OR’d to become a summary bit (bit 5) in the byte register which can be
  //  * queried.
  //  *
  //  * The SCPI server does not return any data.
  //  *
  //  * @param _value  Range: 0-255
  //  * @return Returns the status whether the command was sent or not.
  //  *
  //  */
  // bool ese(int _value);

  // /**
  //  * The Standard Event Status Enable (ESE) query returns the value of
  //  * the Standard Event Status Enable Register.
  //  */
  // const ReadData ese_q();

  // /**
  //  * The Standard Event Status Register (ESR) query returns the value of
  //  * the Standard Event Status Register.
  //  */
  // const ReadData esr_q();

  // /**
  //  * The Identification (IDN) query outputs an identifying string.
  //  * The response will show the following information:
  //  *    <company name>, <model number>, <serial number>, <firmware revision>
  //  */
  // const ReadData idn_q();

  // /**
  //  * The Operation Complete (OPC) command sets bit 0 in the Standard Event
  //  * Status Register when all pending operations have finished.
  //  */
  // bool opc();

  // /**
  //  * The Operation Complete (OPC) query returns the ASCII character 1 in
  //  * the Standard Event Status Register when all pending operations have
  //  * finished. This query stops any new commands from being processed until
  //  the
  //  * current processing is complete.
  //  */
  // const ReadData opc_q();

  // /**
  //  * This reset (RST) command resets most functions to factory-defined
  //  * conditions. Each command shows *RST value if the setting is affected.
  //  */
  // bool rst();

  // /**
  //  * The Service Request Enable (SRE) command sets the value of the Service
  //  * Request Enable Register. The variable <_value> is the decimal sum of the
  //  * bits that will be enabled. Bit 6 (value 64) is ignored and cannot be set
  //  by
  //  * this command.
  //  *
  //  * @param _value  Range: 0–255
  //  *                Entering values from 64 to 127 is equivalent to entering
  //  * values from 0 to 63.
  //  */
  // bool sre(int _value);

  // /**
  //  * The Service Request Enable (SRE) query returns the value of the Service
  //  * Request Enable Register. Range: 0–63 or 128–191
  //  */
  // const ReadData sre_q();

  // /**
  //  * The Read Status Byte (STB) query returns the value of the status byte
  //  * including the master summary status (MSS) bit without erasing its
  //  contents.
  //  * Range: 0–255
  //  */
  // const ReadData stb_q();

  // // :SYSTem

  // /**
  //  * Error count.
  //  */
  // const ReadData err_c();

  // /**
  //  * Error next.
  //  */
  // const ReadData err_n();

protected:
  /**
   * Function implementing delay() function in milliseconds
   * - blocking function
   * - hardware specific

  * @param ms number of milliseconds to wait
  */
  void _delay(unsigned long ms);

  /**
   * Function implementing timestamp getting function in microseconds
   * hardware specific
   */
  unsigned long _micros();

  int checkParamSeparator();
  int checkCommandSeparator();
  int fillBuffer();

  virtual scpi_size readToBuffer() = 0;

  uint8_t m_buffer[BASE_IO_BUFFER_SIZE];
  scpi_size m_bufferSize = 0;
  scpi_size m_bufferReadPos = 0;
};

} // namespace scpi_rp

#endif

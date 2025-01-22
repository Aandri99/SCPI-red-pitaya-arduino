#ifndef BASE_IO_H
#define BASE_IO_H

#include <stdint.h>

#define SCPI_COMMAND_SEPARATOR "\r\n"
#define SCPI_BINARY_HEADER "#"

/**
 Structure with return values ​​from the server
*/
struct ReadData {
  const uint8_t *data = nullptr;
  uint32_t size = 0;
};

/**
 Base input/output class
*/
class BaseIO {
public:
  /**
   * Default constructor - setting all variabels to default values
   */
  BaseIO();

  virtual ~BaseIO(){};

  /**  Initializing connection parameters and connecting */
  virtual int init() = 0;

  /**
   * The function reads the value from the server. Excluding the command
   * separator.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  virtual const ReadData read(uint32_t _timeout_ms) = 0;

  /**
   * The function sends data to the server.
   *
   * @param _data  Buffer with command. Excluding the command separator.
   * @param _size  Size of data sent
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   * If the data was not sent, it returns the value 0
   */
  virtual uint32_t write(const uint8_t *_data, uint32_t _size,
                         uint32_t _timeout_ms) = 0;

  // IEEE Mandated Commands

  /**
   * The Clear Status (CLS) command clears the status byte by emptying the error
   * queue and clearing all the event registers including the Data Questionable
   * Event Register, the Standard Event Status Register, the Standard Operation
   * Status Register and any other registers that are summarized in the status
   * byte.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  bool cls(uint32_t _timeout_ms);

  /**
   * Selects the desired bits from the standard event status enable register.
   * The variable <_value> represents the sum of the bits that will be enabled.
   * This register monitors I/O errors and synchronization conditions such as
   * operation complete, request control, query error, device dependent error,
   * status execution error, command error and power on. The selected bits are
   * OR’d to become a summary bit (bit 5) in the byte register which can be
   * queried.
   *
   * @param _value  Range: 0-255
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  bool ese(int _value, uint32_t _timeout_ms);

  /**
   * The Standard Event Status Enable (ESE) query returns the value of
   * the Standard Event Status Enable Register.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData ese_q(uint32_t _timeout_ms);

  /**
   * The Standard Event Status Register (ESR) query returns the value of
   * the Standard Event Status Register.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData esr_q(uint32_t _timeout_ms);

  /**
   * The Identification (IDN) query outputs an identifying string.
   * The response will show the following information:
   *    <company name>, <model number>, <serial number>, <firmware revision>
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData idn_q(uint32_t _timeout_ms);

  /**
   * The Operation Complete (OPC) command sets bit 0 in the Standard Event
   * Status Register when all pending operations have finished.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  bool opc(uint32_t _timeout_ms);

  /**
   * The Operation Complete (OPC) query returns the ASCII character 1 in
   * the Standard Event Status Register when all pending operations have
   * finished. This query stops any new commands from being processed until the
   * current processing is complete.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData opc_q(uint32_t _timeout_ms);

  /**
   * This reset (RST) command resets most functions to factory-defined
   * conditions. Each command shows *RST value if the setting is affected.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  bool rst(uint32_t _timeout_ms);

  /**
   * The Service Request Enable (SRE) command sets the value of the Service
   * Request Enable Register. The variable <_value> is the decimal sum of the
   * bits that will be enabled. Bit 6 (value 64) is ignored and cannot be set by
   * this command.
   *
   * @param _value  Range: 0–255
   *                Entering values from 64 to 127 is equivalent to entering
   * values from 0 to 63.
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  bool sre(int _value, uint32_t _timeout_ms);

  /**
   * The Service Request Enable (SRE) query returns the value of the Service
   * Request Enable Register. Range: 0–63 or 128–191
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData sre_q(uint32_t _timeout_ms);

  /**
   * The Read Status Byte (STB) query returns the value of the status byte
   * including the master summary status (MSS) bit without erasing its contents.
   * Range: 0–255
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData stb_q(uint32_t _timeout_ms);

  // :SYSTem

  /**
   * Error count.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData err_c(uint32_t _timeout_ms);

  /**
   * Error next.
   *
   * @param _timeout_ms  Timeout in milliseconds. 0 - Timeout disabled
   *
   */
  const ReadData err_n(uint32_t _timeout_ms);

private:
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
};

#endif

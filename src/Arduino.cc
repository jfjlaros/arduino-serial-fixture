#include "Arduino.h"


/**
 * Constructor.
 */
HardwareSerial::HardwareSerial(void) {
  reset();
}

/**
 * Reset the internal counters.
 */
void HardwareSerial::reset(void) {
  int i;

  rx = 0;
  tx = 0;
  _rx = 0;
  _tx = 0;

  for (i = 0; i < _BUFFER_SIZE; i++) {
    rxBuffer[i] = '\0';
    txBuffer[i] = '\0';
  }
}

/**
 * Test for serial availability.
 *
 * @return {bool} - True;
 */
bool HardwareSerial::available(void) {
  return true;
}

/**
 * Read one byte from serial.
 *
 * @return {byte} - One byte;
 */
byte HardwareSerial::read(void) {
  rx++;

  return rxBuffer[rx - 1];
}

/**
 * Read a number of bytes from serial.
 *
 * @arg {char *} buffer - Buffer.
 * @arg {size_t} size - Number of bytes to read.
 */
void HardwareSerial::readBytes(char *buffer, size_t size) {
  memcpy((void *)buffer, (const void *)&rxBuffer[rx], size);
  rx += size;
}

/**
 * Read a string from serial.
 *
 * @arg {char} delimiter - String delimiter.
 *
 * @return {String} - A string.
 */
String HardwareSerial::readStringUntil(char delimiter) {
  size_t size = strchr(&rxBuffer[rx], delimiter) - &rxBuffer[rx] + 1;

  rx += size;

  return ((String)&rxBuffer[rx - size]).substr(0, size - 1);
}

/**
 * Write one byte to serial.
 *
 * @return {size_t} - Number of bytes written.
 */
size_t HardwareSerial::write(char c) {
  txBuffer[tx] = c;
  tx++;

  return 1;
}

/**
 * Write a number of bytes to serial.
 *
 * @arg {byte *} buffer - Buffer.
 * @arg {size_t} size - Number of bytes to read.
 *
 * @return {size_t} - Number of bytes written.
 */
size_t HardwareSerial::write(byte *buffer, size_t size) {
  memcpy((void *)&txBuffer[tx], (const void *)buffer, size);
  tx += size;

  return size;
}

/**
 * Write a string to serial.
 *
 * @arg {String} s - A string.
 *
 * @return {size_t} - Number of bytes written.
 */
size_t HardwareSerial::write(String s) {
  size_t size = s.length();

  strcpy(&txBuffer[tx], s.c_str());
  tx += size;

  return size;
}


HardwareSerial Serial;

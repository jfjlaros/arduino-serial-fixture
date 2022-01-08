#include "Arduino.h"


/**
 * Constructor.
 */
Stream::Stream(void) {
  reset();
}

/**
 * Reset the internal counters.
 */
void Stream::reset(void) {
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
 * Get the number of bytes available for reading.
 *
 * @return Number of bytes.
 */
int Stream::available(void) {
  return _rx - rx;
}

/**
 * Read one byte from serial.
 *
 * @return One byte;
 */
byte Stream::read(void) {
  rx++;

  return rxBuffer[rx - 1];
}

/**
 * Read one byte from serial without removing it from the buffer.
 *
 * @return One byte;
 */
byte Stream::peek(void) {
  return rxBuffer[rx];
}

/**
 * Read a number of bytes from serial.
 *
 * @param buffer Buffer.
 * @param size Number of bytes to read.
 */
size_t Stream::readBytes(char* buffer, size_t size) {
  memcpy((void*)buffer, (const void*)&rxBuffer[rx], size);
  rx += size;

  return size;
}

/**
 * Read a string from serial.
 *
 * @param delimiter String delimiter.
 *
 * @return A string.
 */
String Stream::readStringUntil(char delimiter) {
  size_t size = strchr(&rxBuffer[rx], delimiter) - &rxBuffer[rx] + 1;

  rx += size;

  return ((String)&rxBuffer[rx - size]).substr(0, size - 1);
}

/**
 * Write one byte to serial.
 *
 * @return Number of bytes written.
 */
size_t Stream::write(char c) {
  txBuffer[tx] = c;
  tx++;

  return 1;
}

/**
 * Write a number of bytes to serial.
 *
 * @param buffer Buffer.
 * @param size Number of bytes to read.
 *
 * @return Number of bytes written.
 */
size_t Stream::write(const byte* buffer, size_t size) {
  memcpy((void*)&txBuffer[tx], (const void*)buffer, size);
  tx += size;

  return size;
}

/**
 * Write a string to serial.
 *
 * @param s A string.
 *
 * @return Number of bytes written.
 */
size_t Stream::write(String s) {
  size_t size = s.length();

  strcpy(&txBuffer[tx], s.c_str());
  tx += size;

  return size;
}

size_t Stream::print(String s) {
  return write(s);
}


byte pgm_read_byte(byte*) {
  return '\0';
}


Stream Serial;

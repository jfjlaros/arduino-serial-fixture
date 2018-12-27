#ifndef __ARDUINO_TCC__
#define __ARDUINO_TCC__


/**
 * Read from serial.
 *
 * @return {T} - Value.
 */
template<class T>
T HardwareSerial::autoRead(void) {
  T data;

  readBytes((char *)&data, sizeof(T));

  return data;
}

/**
 * Write to serial.
 *
 * @arg {T} data - Value.
 */
template<class T>
size_t HardwareSerial::autoWrite(T data) {
  return write((byte *)&data, sizeof(T));
}

/**
 * Read a string from the output buffer.
 *
 * @return {String} - A string.
 */
template<>
inline String HardwareSerial::_inspect(void) {
  size_t size = strchr(txBuffer, '\0') - rxBuffer;

  return ((String)txBuffer).substr(0, size);
}

/**
 * Read a value with a basic type from the output buffer.
 *
 * @return {T} - A value of type T.
 */
template<class T>
T HardwareSerial::_inspect(void) {
  T data;

  memcpy((void *)&data, (const void *)txBuffer, sizeof(T));

  return data;
}

/**
 * Read any value from the output buffer.
 *
 * @return {T} - A value of type T.
 */
template<class T>
T HardwareSerial::inspect(void) {
  T data;

  data = _inspect<T>();

  return data;
}

/**
 * Recursion terminator for _prepare().
 */
inline size_t HardwareSerial::_prepare(void) {
  return 0;
}

/**
 * Write a string to the input buffer.
 *
 * @arg {const char *} data - A string.
 * @arg {Args...} args - Other parameters.
 *
 * @return {size_t} - Number of bytes written.
 */
template<class... Args>
size_t HardwareSerial::_prepare(const char *data, Args... args) {
  size_t size = strlen(data);

  strcpy(&rxBuffer[rx], data);
  rx += size + 1;

  return size + _prepare(args...);
}

/**
 * Write a value of basic type to the input buffer.
 *
 * @arg {T} data - A value of type T.
 * @arg {Args...} args - Other parameters.
 *
 * @return {size_t} - Number of bytes written.
 */
template<class T, class... Args>
size_t HardwareSerial::_prepare(T data, Args... args) {
  memcpy((void *)&rxBuffer[rx], (const void *)&data, sizeof(T));
  rx += sizeof(T);

  return sizeof(T) + _prepare(args...);
}

/**
 * Write any value to the input buffer.
 *
 * @arg {Args...} args - Parameters.
 *
 * @return {size_t} - Number of bytes written.
 */
template<class... Args>
size_t HardwareSerial::prepare(Args... args) {
  size_t _rx = rx,
         size;

  size = _prepare(args...);
  rx = _rx;

  return size;
}


#endif

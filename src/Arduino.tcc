#ifndef ARDUINO_SERIAL_FIXTURE_ARDUINO_TCC_
#define ARDUINO_SERIAL_FIXTURE_ARDUINO_TCC_

/**
 * Read from serial.
 *
 * @return Value.
 */
template <class T>
T Stream::autoRead(void) {
  T data;

  readBytes((char*)&data, sizeof(T));

  return data;
}

/**
 * Write to serial.
 *
 * @param data Value.
 */
template <class T>
size_t Stream::autoWrite(T data) {
  return write((byte*)&data, sizeof(T));
}

/**
 * Read a string from the output buffer.
 *
 * @return A string.
 */
template <>
inline String Stream::_inspect(void) {
  String data = (String)&txBuffer[_tx];

  _tx += data.length() + 1;

  return data;
}

/**
 * Read a value with a basic type from the output buffer.
 *
 * @return A value of type @a T.
 */
template <class T>
T Stream::_inspect(void) {
  T data;

  memcpy((void*)&data, (const void*)&txBuffer[_tx], sizeof(T));
  _tx += sizeof(T);

  return data;
}

/**
 * Read any value from the output buffer.
 *
 * @return A value of type @a T.
 */
template <class T>
T Stream::inspect(void) {
  T data;

  data = _inspect<T>();

  return data;
}

/**
 * Recursion terminator for @a _prepare().
 */
inline size_t Stream::_prepare(void) {
  return 0;
}

/**
 * Write a string to the input buffer.
 *
 * @param data A string.
 * @param args Other parameters.
 *
 * @return Number of bytes written.
 */
template <class... Args>
size_t Stream::_prepare(const char* data, Args... args) {
  size_t size = strlen(data);

  strcpy(&rxBuffer[_rx], data);
  _rx += size + 1;

  return size + _prepare(args...);
}

/**
 * Write a value of basic type to the input buffer.
 *
 * @param data A value of type @a T.
 * @param args Other parameters.
 *
 * @return Number of bytes written.
 */
template <class T, class... Args>
size_t Stream::_prepare(T data, Args... args) {
  memcpy((void*)&rxBuffer[_rx], (const void*)&data, sizeof(T));
  _rx += sizeof(T);

  return sizeof(T) + _prepare(args...);
}

/**
 * Write any value to the input buffer.
 *
 * @param args Parameters.
 *
 * @return Number of bytes written.
 */
template <class... Args>
size_t Stream::prepare(Args... args) {
  size_t size;

  size = _prepare(args...);

  return size;
}

#endif

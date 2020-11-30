#ifndef ARDUINO_SERIAL_FIXTURE_ARDUINO_H_
#define ARDUINO_SERIAL_FIXTURE_ARDUINO_H_

#include <string.h>
#include <string>

#define _BUFFER_SIZE 128

using namespace std;

typedef string String;
typedef unsigned char byte;
struct __FlashStringHelper;

class Stream {
  public:
    Stream(void);
    void begin(size_t) {}
    void reset(void);
    bool available(void);
    byte read(void);
    size_t readBytes(char*, size_t);
    String readStringUntil(char);
    size_t write(char),
           write(const byte*, size_t),
           write(String),
           print(String);
    template <class T> T autoRead(void);
    template <class T> size_t autoWrite(T);
    template <class T> T inspect(void);
    template <class... Args> size_t prepare(Args...);
    size_t rx,
           tx;
    char rxBuffer[_BUFFER_SIZE],
         txBuffer[_BUFFER_SIZE];
  private:
    template <class T> T _inspect(void);
    inline size_t _prepare(void);
    template <class... Args> size_t _prepare(const char*, Args...);
    template <class T, class... Args> size_t _prepare(T, Args...);
    size_t _rx,
           _tx;
};

byte pgm_read_byte(char const*);


#include "Arduino.tcc"

extern Stream Serial;

#endif

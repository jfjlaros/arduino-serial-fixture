#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <string.h>
#include <string>

#define _BUFFER_SIZE 128

using namespace std;

typedef string String;
typedef unsigned char byte;


class HardwareSerial {
  public:
    HardwareSerial(void);
    void reset(void);
    bool available(void);
    byte read(void);
    void readBytes(char *buf, size_t size);
    String readStringUntil(char);
    size_t write(char),
           write(byte *, size_t),
           write(String);
    template<class T> T autoRead(void);
    template<class T> size_t autoWrite(T);
    template<class T> T inspect(void);
    template<class... Args> size_t prepare(Args...);
    size_t rx,
           tx;
    char rxBuffer[_BUFFER_SIZE],
         txBuffer[_BUFFER_SIZE];
  private:
    template<class T> T _inspect(void);
    inline size_t _prepare(void);
    template<class... Args> size_t _prepare(const char *, Args...);
    template<class T, class... Args> size_t _prepare(T, Args...);
    size_t _rx,
           _tx;

};


#include "Arduino.tcc"

extern HardwareSerial Serial;

#endif

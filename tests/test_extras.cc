#include <catch.hpp>

#include "../src/Arduino.h"


/*
TEST_CASE("Read different types", "[arduino]") {
  int offset = 0;

  Serial.reset();

  Serial.rxBuffer[offset] = 'x';
  offset += sizeof(char);
  ((int *)&Serial.rxBuffer[offset])[0] = 1234;
  offset += sizeof(int);
  ((float *)&Serial.rxBuffer[offset])[0] = 3.14F;

  // Test the readBytes() funcion.
  REQUIRE(Serial._read<char>() == 'x');
  REQUIRE(Serial._read<int>() == 1234);
  REQUIRE(Serial._read<float>() == 3.14F);
}

TEST_CASE("Write different types", "[arduino]") {
  int offset = 0;

  Serial.reset();

  Serial._write('x');
  Serial._write(1234);
  Serial._write(3.14F);

  // Test the write(byte *, size_t) function.
  REQUIRE(Serial.txBuffer[offset] == 'x');
  offset += sizeof(char);
  REQUIRE(((int *)&Serial.txBuffer[offset])[0] == 1234);
  offset += sizeof(int);
  REQUIRE(((float *)&Serial.txBuffer[offset])[0] == 3.14F);
}
*/

TEST_CASE("Inspect output buffer", "[arduino]") {
  Serial.reset();
  strcpy(Serial.txBuffer, "xxx");

  REQUIRE(Serial.inspect<String>() == "xxx");
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Prepare input buffer", "[arduino]") {
  Serial.reset();
  Serial.prepare('c', "xyz", 10);

  REQUIRE(Serial._read<char>() == 'c');
  REQUIRE(Serial.readStringUntil('\0') == "xyz");
  REQUIRE(Serial._read<int>() == 10);
}

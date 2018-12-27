#include <catch.hpp>

#include "../src/Arduino.h"


TEST_CASE("Read different types", "[extras]") {
  int offset = 0;

  Serial.reset();

  // Test the autoRead() funcion.
  Serial.rxBuffer[offset] = 'x';
  offset += sizeof(char);
  REQUIRE(Serial.autoRead<char>() == 'x');
  REQUIRE(Serial.rx == offset);

  ((int *)&Serial.rxBuffer[offset])[0] = 1234;
  offset += sizeof(int);
  REQUIRE(Serial.autoRead<int>() == 1234);
  REQUIRE(Serial.rx == offset);

  ((float *)&Serial.rxBuffer[offset])[0] = 3.14F;
  offset += sizeof(float);
  REQUIRE(Serial.autoRead<float>() == 3.14F);
  REQUIRE(Serial.rx == offset);
}

TEST_CASE("Write different types", "[extras]") {
  int offset = 0;

  Serial.reset();

  // Test the autoWrite() function.
  Serial.autoWrite('x');
  REQUIRE(Serial.txBuffer[offset] == 'x');
  offset += sizeof(char);
  REQUIRE(Serial.tx == offset);

  Serial.autoWrite(1234);
  REQUIRE(((int *)&Serial.txBuffer[offset])[0] == 1234);
  offset += sizeof(int);
  REQUIRE(Serial.tx == offset);

  Serial.autoWrite(3.14F);
  REQUIRE(((float *)&Serial.txBuffer[offset])[0] == 3.14F);
  offset += sizeof(float);
  REQUIRE(Serial.tx == offset);
}

TEST_CASE("Inspect output buffer", "[extras]") {
  Serial.reset();
  strcpy(Serial.txBuffer, "xxx");

  // Test the inspect() function;
  REQUIRE(Serial.inspect<String>() == "xxx");
  REQUIRE(Serial.tx == 0);

  REQUIRE(Serial.inspect<char>() == 'x');
  REQUIRE(Serial.tx == 0);
}

TEST_CASE("Prepare input buffer", "[extras]") {
  Serial.reset();

  // Test the prepare() function;
  Serial.prepare('c', "xyz", 10);
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.autoRead<char>() == 'c');
  REQUIRE(Serial.readStringUntil('\0') == "xyz");
  REQUIRE(Serial.autoRead<int>() == 10);
}

#include <catch.hpp>

#include "../src/Arduino.h"


TEST_CASE("Reset", "[core]") {
  Serial.rxBuffer[2] = 'x';
  Serial.rx = 1;
  Serial.txBuffer[2] = 'x';
  Serial.tx = 1;
  Serial.reset();

  // Test the reset() function.
  REQUIRE(Serial.rxBuffer[2] == '\0');
  REQUIRE(Serial.rx == 0);

  REQUIRE(Serial.txBuffer[2] == '\0');
  REQUIRE(Serial.tx == 0);
}

TEST_CASE("Available", "[core]") {
  REQUIRE(Serial.available() == true);
}

TEST_CASE("Read one byte", "[core]") {
  Serial.reset();
  strcpy(Serial.rxBuffer, "xy");

  // Test the read() function.
  REQUIRE(Serial.read() == 'x');
  REQUIRE(Serial.rx == 1);

  REQUIRE(Serial.read() == 'y');
  REQUIRE(Serial.rx == 2);
}

TEST_CASE("Read multiple bytes", "[core]") {
  char buffer[8];

  Serial.reset();
  strcpy(Serial.rxBuffer, "xyz");

  // Test the readBytes() function.
  Serial.readBytes(buffer, 1);
  REQUIRE(buffer[0] == 'x');
  REQUIRE(Serial.rx == 1);

  Serial.readBytes(buffer, 2);
  REQUIRE(buffer[0] == 'y');
  REQUIRE(buffer[1] == 'z');
  REQUIRE(Serial.rx == 3);
}

TEST_CASE("Read string", "[core]") {
  Serial.reset();
  strcpy(Serial.rxBuffer, "abc");
  strcpy(&Serial.rxBuffer[4], "xyz");

  // Test the readStringUntil() function.
  REQUIRE(Serial.readStringUntil('\0') == "abc");
  REQUIRE(Serial.rx == 4);

  REQUIRE(Serial.readStringUntil('\0') == "xyz");
  REQUIRE(Serial.rx == 8);
}

TEST_CASE("Write one byte", "[core]") {
  Serial.reset();

  // Test the write(char) function.
  Serial.write('x');
  REQUIRE(Serial.txBuffer[0] == 'x');
  REQUIRE(Serial.tx == 1);

  Serial.write('y');
  REQUIRE(Serial.txBuffer[1] == 'y');
  REQUIRE(Serial.tx == 2);
}

TEST_CASE("Write multiple bytes", "[core]") {
  byte buffer[] = "xyz";
  float f = 1.0F;

  Serial.reset();

  // Test the write(byte *, size_t) function.
  Serial.write(buffer, 1);
  REQUIRE(Serial.txBuffer[0] == 'x');
  REQUIRE(Serial.tx == 1);

  Serial.write(&buffer[1], 2);
  REQUIRE(Serial.txBuffer[1] == 'y');
  REQUIRE(Serial.txBuffer[2] == 'z');
  REQUIRE(Serial.tx == 3);

  // Test for internal NULL characters.
  Serial.write((byte *)&f, sizeof(float));
  REQUIRE(((float *)&Serial.txBuffer[3])[0] == 1.0F);
}

TEST_CASE("Write string", "[core]") {
  Serial.reset();

  // Test the write(String) function.
  Serial.write("abc");
  REQUIRE(Serial.txBuffer[0] == 'a');
  REQUIRE(Serial.txBuffer[1] == 'b');
  REQUIRE(Serial.txBuffer[2] == 'c');
  REQUIRE(Serial.tx == 3);

  Serial.write("xyz");
  REQUIRE(Serial.txBuffer[3] == 'x');
  REQUIRE(Serial.txBuffer[4] == 'y');
  REQUIRE(Serial.txBuffer[5] == 'z');
  REQUIRE(Serial.tx == 6);
}

// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP23008
// This code is designed to work with the MCP23008_I2CR8G5LE_10A I2C relay controller available from ControlEverything.com.
// https://www.controleverything.com/content/Relay-Controller?sku=MCP23008_I2CR8G5LE_10A#tabs-0-product_tabset-2

#include <Wire.h>

// MCP23008_I2CR8G5LE I2C address is 0x20(32)
#define Addr 0x20

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select IODIR register
  Wire.write(0x00);
  // All pins are configured as input
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select GPPU register
  Wire.write(0x06);
  // Pull-up enabled on all pins
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();

  // Output data to serial monitor
  Serial.println("Pull-up enabled on all GPIO pins");
  delay(500);
}

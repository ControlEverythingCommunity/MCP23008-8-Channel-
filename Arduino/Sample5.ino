// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP23008
// This code is designed to work with the MCP23008_I2CR8G5LE_10A I2C relay controller available from ControlEverything.com.
// https://www.controleverything.com/content/Relay-Controller?sku=MCP23008_I2CR8G5LE_10A#tabs-0-product_tabset-2

#include <Wire.h>

// MCP23008_I2CR8G5LE I2C address is 0x20(32)
#define Addr 0x20

int value, status, state;
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
  delay(500);
}

void loop()
{
  unsigned int data[0];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select GPPU register
  Wire.write(0x06);
  // Enable pull-up on all pins of the port
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();
  Serial.println("Pull-up enabled on all GPIO pins of the port");

  // Checking status of all GPIO pins of port
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select GPIO register
  Wire.write(0x09);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read 1 byte of data
  if (Wire.available() == 1)
  {
    data[0] = Wire.read();
  }
  status = data[0];

  value = 0x01;
  for (int i = 0; i < 8; i++)
  {
    state = (status & value);
    if (state == value)
    {
      Serial.print("GPIO Pin ");
      Serial.print(i);
      Serial.println(" of port is High");
    }
    else
    {
      Serial.print("GPIO Pin ");
      Serial.print(i);
      Serial.println(" of port is Low");
    }
    value = value << 1;
    delay(500);
  }
}

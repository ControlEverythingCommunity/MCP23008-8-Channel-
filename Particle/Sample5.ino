// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP23008
// This code is designed to work with the MCP23008_I2CR8G5LE_10A I2C relay controller available from ControlEverything.com.
// https://www.controleverything.com/content/Relay-Controller?sku=MCP23008_I2CR8G5LE_10A#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// MCP23008_I2CR8G5LE I2C address is 0x20(32)
#define Addr 0x20

int value, status, state;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "MCP23008_I2CR8G5LE");

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
  Particle.publish("Pull-up enabled on all GPIO pins");
  delay(1000);

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
      Particle.publish("GPIO Pin ", String(i) + " is High");
    }
    else
    {
      Particle.publish("GPIO Pin ", String(i) + " is Low");
    }
    value = value << 1;
    delay(1000);
  }
}

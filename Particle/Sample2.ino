// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP23008
// This code is designed to work with the MCP23008_I2CR8G5LE_10A I2C relay controller available from ControlEverything.com.
// https://www.controleverything.com/content/Relay-Controller?sku=MCP23008_I2CR8G5LE_10A#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// MCP23008_I2CR8G5LE I2C address is 0x20(32)
#define Addr 0x20

int data;
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
  // All pins are configured as output
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(500);
}

void loop()
{
  // Turning all relays ON, one by one
  data = 0x01;
  for (int i = 0; i < 8; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select GPIO register
    Wire.write(0x09);
    // All pins are set to logic HIGH
    Wire.write(data);
    // Stop I2C transmission
    Wire.endTransmission();

    // Output data to dashboard
    Particle.publish("Turning Relay", String(i) + " of port ON");
    data = data << 1;
    data = data + 1;
    delay(1000);
  }

  // Turning all relays OFF, one by one
  data = 0xFE;
  for (int i = 0; i < 8; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select GPIO register
    Wire.write(0x09);
    // All pins are set to logic LOW
    Wire.write(data);
    // Stop I2C transmission
    Wire.endTransmission();

    // Output data to dashboard
    Particle.publish("Turning Relay", String(i) + " of port OFF");
    data = data << 1;
    delay(1000);
  }
}

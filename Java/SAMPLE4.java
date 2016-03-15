// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP23008
// This code is designed to work with the MCP23008_I2CR8G5LE_10A I2C relay controller available from ControlEverything.com.
// https://www.controleverything.com/content/Relay-Controller?sku=MCP23008_I2CR8G5LE_10A#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class SAMPLE4
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, MCP23008 I2C address is 0x20(32)
		I2CDevice device = bus.getDevice(0x20);
		
		// Configure all pins as input
		device.write(0x00, (byte)0xFF);
		
		// Enable Pull-up on all pins, one bye one
		byte data = 0x01;
		for (int i = 0; i < 8; i++)
		{
			System.out.printf("Enabling pull up on %d pin%n", i);
			device.write(0x06, (byte)data);
			data = (byte)(data << 1);
			data += 1;
			Thread.sleep(1000);
		}
		
		// Disable Pull-up on all pins, one bye one
		data = (byte)0xFE;
		for (int i = 0; i < 8; i++)
		{
			System.out.printf("Disabling pull up on %d pin%n", i);
			device.write(0x06, (byte)data); 
			data = (byte)(data << 1);
			Thread.sleep(1000);
		}
	}
}

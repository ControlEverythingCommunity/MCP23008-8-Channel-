import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class SAMPLE1
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, MCP23008 I2C address is 0x20(32)
		I2CDevice device = bus.getDevice(0x20);
		
		// Configured all pins as OUTPUT
		device.write(0x00, (byte)0x00);
		Thread.sleep(500);
		
		// Output to screen
		System.out.println("Turning all relays ON");
		
		// Turn all relays ON 
		device.write(0x09, (byte)0xFF);
	}
}

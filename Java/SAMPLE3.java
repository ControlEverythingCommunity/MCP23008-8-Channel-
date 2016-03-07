import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class SAMPLE3
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, MCP23008 I2C address is 0x20(32)
		I2CDevice device = bus.getDevice(0x20);
		
		// Configure all pins as input
		device.write(0x00, (byte)0xFF);
		
		// Pull-up all pins
		device.write(0x06, (byte)0xFF);
		
		// Output to screen
		System.out.println("Pull-up enabled on all pins");
	}
}

# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MCP23008
# This code is designed to work with the MCP23008_I2CR8G5LE_10A I2C relay controller available from ControlEverything.com.
# https://www.controleverything.com/content/Relay-Controller?sku=MCP23008_I2CR8G5LE_10A#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# MCP23008 address, 0x20(32)
# Select IODIR register, 0x00(00)
#		0xFF(255)	All pins are configured as input
i2c.writeByte(0x20, 0x00, 0xFF)

# MCP23008 address, 0x20(32)
# Select GPPU register, 0x06(06)
#		0xFF(255)	Pull-up enabled on all pins
i2c.writeByte(0x20, 0x06, 0xFF)

# Output to screen
print "Pull-up enabled on all pins"

# Checking Status of all GPIO pins
status = i2c.readBytes(0x20, 0x09, 1)
data = 0x01
for MyData in range(0,8):
	pin = status[0] & data
	if pin == data:
		print "Status for Pin %d is HIGH" %MyData
	else:
		print "Status for Pin %d is LOW" %MyData
	data = data << 1
	time.sleep(0.5)

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# MCP23008 address, 0x20(32)
# Select IODIR register, 0x00(00)
#		0x00(00)	All pins are configured as outputs
bus.write_byte_data(0x20,0x00,0x00)

data = 0x01
for MyData in range(0,8):
# MCP23008 address, 0x20(32)
# Select GPIO register, 0x09(9)
	bus.write_byte_data(0x20,0x09,data)
	print "GPIO Pin %d State is HIGH" %MyData
	data = data << 1
	data = data + 1
	time.sleep(1)

data = 0xFE
for MyData in range(0,8):
# MCP23008 address, 0x20(32)
# Select GPIO register, 0x09(9)
	bus.write_byte_data(0x20,0x09,data)
	print "GPIO Pin %d State is LOW" %MyData
	data = data << 1
	time.sleep(1)

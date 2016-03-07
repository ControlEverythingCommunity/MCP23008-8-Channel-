import smbus

# Get I2C bus
bus = smbus.SMBus(1)

# MCP23008 address, 0x20(32)
# Select IODIR register, 0x00(00)
#		0xFF(255)	All pins are configured as input
bus.write_byte_data(0x20, 0x00, 0xFF)

# MCP23008 address, 0x20(32)
# Select GPPU register, 0x06(06)
#		0xFF(255)	Pull-up enabled on all pins
bus.write_byte_data(0x20, 0x06, 0xFF)

# Output to screen
print "Pull-up enabled on all pins"

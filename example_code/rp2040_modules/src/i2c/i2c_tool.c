#include "i2c_tool.h"

// Write 1 byte to the specified register
uint8_t reg_write(  i2c_inst_t *i2c_instance, 
                const uint8_t addr, 
                const uint8_t reg, 
                uint8_t *buf,
                const uint8_t nbytes) {

    int num_bytes_read = 0;
    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Append register address to front of data packet
    msg[0] = reg;
    for (int i = 0; i < nbytes; i++) {
        msg[i + 1] = buf[i];
    }

    // Write data to register(s) over I2C
    i2c_write_blocking(i2c_instance, addr, msg, (nbytes + 1), false);

    return num_bytes_read;
}

// Read byte(s) from specified register. If nbytes > 1, read from consecutive
// registers.
uint8_t reg_read(  i2c_inst_t *i2c_instance,
                const uint8_t addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes) {

    int num_bytes_read = 0;

    // Check to make sure caller is asking for 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Read data from register(s) over I2C
    i2c_write_blocking(i2c_instance, addr, &reg, 1, true);
    num_bytes_read = i2c_read_blocking(i2c_instance, addr, buf, nbytes, false);

    return num_bytes_read;
}


//
// Read a 8-bit register
//
uint8_t reg_read_8(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr){
	uint8_t temp[1];
	reg_read(i2c_instance, dev_addr, reg_addr, &temp[0], 1);
	if (DEBUG_OUTPUT_ON_I2C) printf("reg_read_8 got %x.\n",temp[0]);
	return temp[0];
}


//
// Read a pair of registers as a 16-bit value
//
uint16_t reg_read_16(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr){
	uint8_t temp[2];
	reg_read(i2c_instance, dev_addr, reg_addr, &temp[0], 2);
	uint16_t return_val = temp[0];
	return_val <<= 8;
	return_val |= temp[1];
	if (DEBUG_OUTPUT_ON_I2C) printf("reg_read_16 got %x %x combined to %x from reg:%x.\n",temp[0],temp[1],return_val,reg_addr);
	return return_val;
}

//
// Write a 8-bit value to a register
//
uint8_t reg_write_8(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr,
				uint8_t value){
	uint8_t temp[1];
	temp[0] = value;
	reg_write(i2c_instance, dev_addr, reg_addr, &temp[0], 1);
}


//
// Write a 16-bit value to a register
//
uint8_t reg_write_16(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr,
				uint16_t value){
	uint8_t temp[2];
	temp[0] = (unsigned char)(value >> 8); // MSB first
	temp[1] = (unsigned char) value;
	if (DEBUG_OUTPUT_ON_I2C) printf("reg_write_16 got %x split to %x %x.\n",value,temp[0],temp[1]);
	reg_write(i2c_instance, dev_addr, reg_addr, &temp[0], 2);
}


//
// Write a list of register/value pairs to the I2C device
//
uint8_t reg_write_list(i2c_inst_t *i2c_instance,
					uint8_t dev_addr,
					uint8_t *list){
uint8_t count = *list; // count is the first element in the list
list++;

	if(DEBUG_OUTPUT_ON_I2C) printf("start transmitting list of %d elements\n",count);
	while (count)
	{
		if(DEBUG_OUTPUT_ON_I2C) printf("reg_write_list send val:%x to reg:%x\n",list[1],list[0]);
		reg_write(i2c_instance, dev_addr, list[0], (uint8_t*)&list[1], 1);
		list += 2;
		count--;
	}
}

void init_i2c_0() {
    // Pins
    const uint sda_pin = 4;
    const uint scl_pin = 5;

    // Ports
    i2c_0 = i2c0;

    // Initialize chosen serial port
    stdio_init_all();

    //Initialize I2C port at 400 kHz
    i2c_init(i2c_0, 400 * 1000);

    // Initialize I2C pins
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);	
}

void init_i2c_1() {
    // Pins
    const uint sda_pin = 2;
    const uint scl_pin = 3;

    // Ports
    i2c_1 = i2c1;

    // Initialize chosen serial port
    stdio_init_all();

    //Initialize I2C port at 400 kHz
    i2c_init(i2c_1, 400 * 1000);

    // Initialize I2C pins
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);	
}

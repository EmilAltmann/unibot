#ifndef _I2C_TOOL_H_
#define _I2C_TOOL_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// this is a meta module for configuring the two i2c busses

// set to 1 for verbouse debug output
#define DEBUG_OUTPUT_ON_I2C 0

// bad practics :-)
i2c_inst_t* i2c_0 __attribute__((__common__));
i2c_inst_t* i2c_1 __attribute__((__common__));

// init i2c bus 0
void init_i2c_0();

// init i2c bus 1
void init_i2c_1();


// example usecase:
// data[0] == 0x00;
// reg_write(i2c_1, TCS34725_ADDR, 0x8F, &data[0], 1);

// write two a register over i2c
uint8_t reg_write(i2c_inst_t *i2c_instance, 
                const uint8_t addr, 
                const uint8_t reg, 
                uint8_t *buf,
                const uint8_t nbytes);


// example usecase:
// reg_read(i2c_1, TCS34725_ADDR, 0x94, data, 8);

// read from a register over i2c
uint8_t reg_read(i2c_inst_t *i2c_instance,
                const uint8_t addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes);

// read 8 bit over i2c
uint8_t reg_read_8(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr);
				
// write 8 bit over i2c
uint8_t reg_write_8(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr,
				uint8_t value);

// read 16 bit over i2c
uint16_t reg_read_16(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr);
				
// write 16 bit over i2c
uint8_t reg_write_16(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t reg_addr,
				uint16_t value);
				
// write to a list of 8 bit data to i2c addresses
uint8_t reg_write_list(i2c_inst_t *i2c_instance,
				uint8_t dev_addr,
				uint8_t *list);
                

#endif

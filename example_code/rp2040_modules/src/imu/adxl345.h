#ifndef _ADXL345_
#define _ADXL345_

#include <stdio.h>
#include "pico/stdlib.h"
#include "src/i2c/i2c_tool.h"
#include "math.h"

// this module configures the adxl345 acceleration sensor

#define ADXL345_ADDRESS 0x53
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATA_FORMAT 0x31
#define ADXL345_DATAX0 0x32

// init the sensor
void init_adxl345();

// sample acceleration
void get_acceleration(int16_t* xyz_acceleration, double* xyz_rotation);

// contious sample and print
void test_adxl345();

#endif

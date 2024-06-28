#ifndef _QMC5883_h_
#define _QMC5883_h_

#include <stdio.h>
#include "src/i2c/i2c_tool.h"
#include <math.h>

// this module reads the values from a qmc5883 magnectic compass sensor

#define QMC5883_ADDR 0x0D

// controll regiser bits

#define QMC5883_Mode_Standby    0b00000000
#define QMC5883_Mode_Continuous 0b00000001

#define QMC5883_ODR_10Hz        0b00000000
#define QMC5883_ODR_50Hz        0b00000100
#define QMC5883_ODR_100Hz       0b00001000
#define QMC5883_ODR_200Hz       0b00001100

#define QMC5883_RNG_2G          0b00000000
#define QMC5883_RNG_8G          0b00010000

#define QMC5883_OSR_512         0b00000000
#define QMC5883_OSR_256         0b01000000
#define QMC5883_OSR_128         0b10000000
#define QMC5883_OSR_64          0b11000000

// this is serios bad practise :-)
int16_t qmc5883_xMag  __attribute__((__common__));
int16_t qmc5883_yMag  __attribute__((__common__));
int16_t qmc5883_zMag  __attribute__((__common__));
float qmc5883_azimuth  __attribute__((__common__));

// init the sensor
void init_qmc5883();

// reset the sensor
void reset_qmc5883();

// sample and calculate azimuth (compass angle)
float get_qmc5883_azimuth();

// sample once the magnetic field
void test_qmc5883();

#endif

#ifndef _ADS1115_H_
#define _ADS1115_H_
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "src/i2c/i2c_tool.h"

// this module utilizes two ads1115 ADCs for sampleing eight tcrt5000 IR sensors

// I2C addresse, for the ADDR = VDD is =x49
#define ADS1115_ADDR 0x48

// used for avariging the sample
#define SAMPLE_CNT 1

// init this module
void ads1115_init();

// sample one port
uint16_t ads1115_sample(uint8_t port);

// test the eight sensors
void test_ads1115();

#endif

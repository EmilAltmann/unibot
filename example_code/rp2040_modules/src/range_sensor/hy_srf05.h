#ifndef _HY_SRF05_
#define _HY_SRF05_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// simple example to use srf04 or srf05 ultrasonic distnce sensors 

struct ultrasonic_inst {
	uint8_t trig_pin;
	uint8_t echo_pin;
};

struct ultrasonic_inst init_hy_srf05(uint8_t echo_pin, uint8_t trig_pin);

uint16_t sample_hy_srf05(struct ultrasonic_inst instance);

#endif

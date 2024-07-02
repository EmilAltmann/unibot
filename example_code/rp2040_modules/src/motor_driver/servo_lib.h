#ifndef _servo_lib_h_
#define _servo_lib_h_

#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <math.h>

// This is a example for smooth servo controll

struct servo_inst {
	uint8_t pin;
    uint slice;
    uint channel;
    int current_pos;
    int start_pos;
    int new_pos;
    int following_pos;
    float timestamp;
};

void add_servo_at_pin(uint8_t pin,uint16_t init_pos);

void set_servo_to_pos(uint8_t pin,int pos);

#endif

#ifndef _servo_lib_h_
#define _servo_lib_h_

#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <math.h>

// This is a example for smooth servo controll

void init_servo_at_pin();

int servo_test();

#endif

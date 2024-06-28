#ifndef _DUAL_DC_MOTORS_H_
#define _DUAL_DC_MOTORS_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/pwm.h"

// This is a generalized module for a two motor differtial drive

/// IO pins for the stepper drivers
#define LDA 4
#define LDB 5
#define RDA 1
#define RDB 2
#define REN 0
#define LEN 3

/// PWM slices and channels
static uint dual_dc_slice_L;
static uint dual_dc_channel_L;
static uint dual_dc_slice_R;
static uint dual_dc_channel_R;

// set motor speeds
void set_dual_dc_speed(int16_t speed_l, int16_t speed_r);

// init this module
void init_dual_dc_drive();

#endif

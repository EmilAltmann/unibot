#ifndef _DUAL_STEPPER_MOTORS_H_
#define _DUAL_STEPPER_MOTORS_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/pwm.h"

// This module configures two stepper motors for differtial drive

/// IO pins for the stepper drivers
#define LD 0
#define LS 1
#define RD 2
#define RS 3

/// PWM slices and channels
static uint slice_L;
static uint channel_L;
static uint slice_R;
static uint channel_R;

// set motor speeds
void set_dual_stepper_speed(int16_t speed_l, int16_t speed_r);

// init this module
void init_dual_stepper_drive();

#endif

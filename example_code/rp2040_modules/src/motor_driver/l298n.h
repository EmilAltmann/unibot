#ifndef _L298N_H_
#define _L298N_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/pwm.h"

// This module implements a two motor drive usig the L298 H-bridges

/// Enable for pwm speed controll
#define ENL 6
#define ENR 9

/// driection configuration
#define IN1L 7
#define IN2L 8
#define IN1R 10
#define IN2R 11

// speed for use with the discrete motor functions 
#define L298N_HIGHSPEED 0x7FFF

/// PWM slices and channels
static uint slice_ENL;
static uint channel_ENL;
static uint slice_ENR;
static uint channel_ENR;

// set the motor speed
void l298n_set_speed(int16_t speed_l, int16_t speed_r);

// init this module
void init_l298n();

// methods for controllling the motors
void l298n_lMotor();
void l298n_rMotor();

void l298n_driveForeward();
void l298n_driveBackward();
void l298n_rotateLeft();
void l298n_rotateRight();
void l298n_turnLeft();
void l298n_turnRight();
void l298n_stop();


#endif

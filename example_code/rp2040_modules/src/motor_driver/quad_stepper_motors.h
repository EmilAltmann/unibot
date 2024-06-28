#ifndef _QUAD_STEPPER_MOTORS_H_
#define _QUAD_STEPPER_MOTORS_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/pwm.h"

// this module configures four stepper motors for quad wheel drive

/// IO pins for the stepper drivers
#define LFD 7
#define LFS 6
#define LBD 9
#define LBS 8

#define RFD 10
#define RFS 11
#define RBD 12
#define RBS 13

/// Speed levels for driving around
#define HIGHSPEED 1
#define LOWSPEED 10

/// clk div for max speed
#define MAXSPEED 1
#define MINSPEED 256

/// set for the max speed if clk div is set to 1 and NEMA17 motors
#define WRAPVAL 32000

/// PWM slices and channels
static uint slice_LF;
static uint channel_LF;
static uint slice_RF;
static uint channel_RF;
static uint slice_LB;
static uint channel_LB;
static uint slice_RB;
static uint channel_RB;

// set the speed for each servo
void set_speed(int8_t speed_lf, int8_t speed_rf, int8_t speed_lb, int8_t speed_rb);

// init the module
void initDrive();


// methods configured for quad wheel mecanum drive
void lfMotor();
void rfMotor();
void lbMotor();
void rbMotor();

void driveForeward();
void driveBackward();
void rotateLeft();
void rotateRight();
void turnLeft();
void turnRight();
void driveRight();
void driveLeft();
void driveForewardRight();
void driveForewardLeft();
void driveBackwardRight();
void driveBackwardLeft();
void stop();

#endif

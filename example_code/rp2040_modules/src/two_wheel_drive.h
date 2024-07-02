#ifndef _TWO_WHEEL_DRIVE_H_
#define _TWO_WHEEL_DRIVE_H_

#include "pico/stdlib.h"

#include "pio_tool.h"
#include "display/max7219_dot_matrix.h"
#include "max7219.pio.h"
#include "motor_driver/dual_dc_motors.h"
#include "light_sensor/ads1115.h"

/*
-------------------------------------------------------------------
| This module implements a two wheeled vihicle with following modules:
| octuple trct5000 infrared line sensor module at the bottom front
| sound interface module at the bottom middle
| duble TOF sensor at the top front
| 16x8 led dot matrix at the top middle
| 2x8 seven segment at the top back
| raspberry pi pico controller
|
| The interposer configration is as follows: 
|   left motor:
|       ena - l1 <=> gp13
|       in1 - l2 <=> gp12
|       in2 - l3 <=> gp11
|
|   right motor:
|       ena - r1 <=> gp10
|       in1 - r2 <=> gp9
|       in2 - r3 <=> gp8
|   
|   octuple tcrt5000:
|       clk - bf5 <=> gp3
|       dat - bf4 <=> gp2
|
|   sound interface:
|       analogue large mic  - bm5 <=> gp28/ADC2
|       digital large mic   - bm4 <=> gp21
|       analogue small mic  - bm3 <=> gp27/ADC1
|       digital small mic   - bmf2 <=> gp20
|       passive buzzer      - bm1 <=> gp26/ADC0
|
|   dual TOF ultrasonic:
|       s1  - tf1 <=> gp6
|       cs2 - tf2 <=> gp5
|       cs1 - tf3 <=> gp4
|       clk - tf4 <=> gp3
|       dat - tf5 <=> gp2
|   
|   dual 8x8 led dot matrix:
|       dat - tm5 <=> gp17
|       clk - tm4 <=> gp18
|       ena - tm3 <=> gp19
|   
|   dual 8xseven segment:
|       dat - tb5 <=> gp14
|       clk - tb4 <=> gp15
|       ena - tb3 <=> gp16
|
-------------------------------------------------------------------
*/

#define TWOWHEEL_LM_ENA 13  // PWM enable for left motor
#define TWOWHEEL_LM_IN1 12  // dir pin 1 for left motor
#define TWOWHEEL_LM_IN2 11  // dir pin 2 for left motor

#define TWOWHEEL_RM_ENA 10   // PWM enable for right motor
#define TWOWHEEL_RM_IN1 9   // dir pin 1 for right motor
#define TWOWHEEL_RM_IN2 8  // dir pin 2 for right motor

#define TWOWHEEL_BF_DAT 2   // data for ADC I2C
#define TWOWHEEL_BF_CLK 3   // clk for ADC I2C

#define TWOWHEEL_BM_A_LM 28 // analogue large mic
#define TWOWHEEL_BM_D_LM 20 // digital large mic
#define TWOWHEEL_BM_A_SM 27 // analogue small mic
#define TWOWHEEL_BM_D_SM 20 // digital small mic
#define TWOWHEEL_BM_BUZZER 26   // passive buzzer

#define TWOWHEEL_TF_DAT 2   // data for TOF I2C
#define TWOWHEEL_TF_CLK 3   // clk for TOF I2C
#define TWOWHEEL_TF_CS1 4   // xshut pin from TOF1 for readressing
#define TWOWHEEL_TF_CS2 5   // xshut pin from TOF2 for readressing
#define TWOWHEEL_TF_SERVO 6 // servo PWM

#define TWOWHEEL_TM_DAT 17  // data to MAX7219 led driver
#define TWOWHEEL_TM_CLK 18  // ckl to MAX7219 led driver
#define TWOWHEEL_TM_ENA 19  // load to MAX7219 led driver

#define TWOWHEEL_TB_DAT 14  // data to MAX7219 led driver
#define TWOWHEEL_TB_CLK 15  // ckl to MAX7219 led driver
#define TWOWHEEL_TB_ENA 16  // load to MAX7219 led driver

#define TWOWHEEL_HIGHSPEED 2047
#define TWOWHEEL_LOWSPEED 1047

void start_two_wheel_drive();

uint8_t bin16_to_unary8(uint16_t i);

void sweep_sound();

#endif
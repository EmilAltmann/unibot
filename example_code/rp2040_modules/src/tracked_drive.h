#ifndef _TRACKED_DRIVE_H_
#define _TRACKED_DRIVE_H_

#include "pico/stdlib.h"
#include <stdio.h>

#include "motor_driver/l298n.h"
#include "light_sensor/tcs34725.h"
#include "display/ws2812_8x8.h"
#include "shiftreg.pio.h"

/*
-------------------------------------------------------------------
| This module implements a tracked vihicle with following modules:
| triple RGB sensor at the bottom front
| duble servo ultrasonic sensor at the top front
| 8x8 RGB matrix at the top middle
| dual seven segment at the top back
| raspberry pi pico controller
|
| The interposer configration is as follows: 
|   left motor:
|       ena - l1 <=> gp6
|       in1 - l2 <=> gp7
|       in2 - l3 <=> gp8
|
|   right motor:
|       ena - r1 <=> gp9
|       in1 - r2 <=> gp10
|       in2 - r3 <=> gp11
|   
|   triple RGB:
|       clk - bf5 <=> gp3
|       d0  - bf4 <=> gp2
|       d1  - bf3 <=> gp14
|       d2  - bf2 <=> gp18
|
|   dual servo ultrasonic:
|       s1  - tf1 <=> gp4
|       s2  - tf2 <=> gp5
|       ech - tf4 <=> gp13
|       tri - tf5 <=> gp12
|   
|   8x8 rgb matrix:
|       dat - tm5 <=> gp19
|   
|   dual seven segment:
|       lat - tb3 <=> gp15
|       clk - tb4 <=> gp16
|       dat - tb5 <=> gp17
|
-------------------------------------------------------------------
*/

#define RGB_PIN 19

#define LATCH_PIN 15
#define CLOCK_PIN 16
#define DATA_PIN 17

#define PITCH_PIN 4
#define YAW_PIN 5
#define TRIG_PIN 12
#define ECHO_PIN 13

void start_tracked_drive();

uint32_t compute_color(uint16_t color_data[],uint8_t sensor);

#endif
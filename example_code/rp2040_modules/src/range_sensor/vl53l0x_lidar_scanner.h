#ifndef _VL53L0X_LIDAR_SCANNER_H_
#define _VL53L0X_LIDAR_SCANNER_H_

#include "src/i2c/i2c_tool.h"
#include <stdio.h>
#include "vl53l0x.h"
#include <math.h>
#include "hardware/pwm.h"

// this module raslizes a simple LiDAR scaner using a 180deg servo and two VL53L0x sensors.

// standard address for unconfigured sensor, plese check with i2c search script
#define VL53L0X_STANDARD_ADDRESS 0x29

void init_vl53l0x_lidar_scanner(uint8_t xshut_sensor_a,
								uint8_t xshut_sensor_b,
								uint8_t address_sensor_a,
								uint8_t address_sensor_b,
								uint8_t servo_pin);

#endif

#ifndef _VL53L0X_H_
#define _VL53L0X_H_

//----------------------------------------------------+
// Edited by Emil Altmann for use with the rp2040 mcu |
// based on https://github.com/bitbank2/VL53L0X       |
//----------------------------------------------------+

// VL53L0X time of flight range sensor
// Library to read the distance
// from the I2C bus
//
//----------------------------------------
// originaly by Larry Bank
// Copyright (c) 2017 Larry Bank
// email: bitbank@pobox.com
//-----------------------------------------
//
// This code is based on Pololu's Arduino library
// https://github.com/pololu/vl53l0x-arduino
// (see LICENSE.txt for more info)
//
// My version is an attempt to simplify that code and 
// create a generic C library for Linux
//


#include "src/i2c/i2c_tool.h"
#include <stdio.h>

// standard address 0x29
// altered to 0x70 and 0x71

#define VL53LXX_I2C i2c_0

// set to 1 for verbose debug!
#define VL53L0X_DEBUG 0

static unsigned char stop_variable;
static uint32_t measurement_timing_budget_us;

static int vl53l0x_perform_single_ref_calibration(uint8_t dev_addr, uint8_t vhv_init_byte);
static int vl53l0x_set_measurement_timing_budget(uint8_t dev_addr, uint32_t budget_us);

#define calcMacroPeriod(vcsel_period_pclks) ((((uint32_t)2304 * (vcsel_period_pclks) * 1655) + 500) / 1000)
// Encode VCSEL pulse period register value from period in PCLKs
// based on VL53L0X_encode_vcsel_period()
#define encodeVcselPeriod(period_pclks) (((period_pclks) >> 1) - 1)

#define SEQUENCE_ENABLE_FINAL_RANGE 0x80
#define SEQUENCE_ENABLE_PRE_RANGE   0x40
#define SEQUENCE_ENABLE_TCC         0x10
#define SEQUENCE_ENABLE_DSS         0x08
#define SEQUENCE_ENABLE_MSRC        0x04

typedef enum vcselperiodtype { VcselPeriodPreRange, VcselPeriodFinalRange } vcselPeriodType;
static int vl53l0x_set_vcsel_pulse_period(uint8_t dev_addr, vcselPeriodType type, uint8_t period_pclks);

typedef struct tagSequenceStepTimeouts
    {
      uint16_t pre_range_vcsel_period_pclks, final_range_vcsel_period_pclks;

      uint16_t msrc_dss_tcc_mclks, pre_range_mclks, final_range_mclks;
      uint32_t msrc_dss_tcc_us,    pre_range_us,    final_range_us;
    } SequenceStepTimeouts;

// VL53L0X internal registers
#define REG_IDENTIFICATION_MODEL_ID				0xc0
#define REG_IDENTIFICATION_REVISION_ID			0xc2
#define REG_SYSRANGE_START						0x00

#define REG_RESULT_INTERRUPT_STATUS 			0x13
#define RESULT_RANGE_STATUS      				0x14
#define ALGO_PHASECAL_LIM                       0x30
#define ALGO_PHASECAL_CONFIG_TIMEOUT            0x30

#define GLOBAL_CONFIG_VCSEL_WIDTH               0x32
#define FINAL_RANGE_CONFIG_VALID_PHASE_LOW      0x47
#define FINAL_RANGE_CONFIG_VALID_PHASE_HIGH     0x48

#define PRE_RANGE_CONFIG_VCSEL_PERIOD           0x50
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI      0x51
#define PRE_RANGE_CONFIG_VALID_PHASE_LOW        0x56
#define PRE_RANGE_CONFIG_VALID_PHASE_HIGH       0x57

#define REG_MSRC_CONFIG_CONTROL                 0x60
#define FINAL_RANGE_CONFIG_VCSEL_PERIOD         0x70
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI    0x71
#define MSRC_CONFIG_TIMEOUT_MACROP              0x46
#define FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT  0x44
#define SYSRANGE_START                          0x00
#define SYSTEM_SEQUENCE_CONFIG                  0x01
#define SYSTEM_INTERRUPT_CONFIG_GPIO            0x0A
#define RESULT_INTERRUPT_STATUS                 0x13
#define VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV       0x89
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_0        0xB0
#define GPIO_HV_MUX_ACTIVE_HIGH                 0x84
#define SYSTEM_INTERRUPT_CLEAR                  0x0B

uint8_t vl53l0x_change_address(uint8_t old_address, uint8_t new_address);

//
// Read the current distance in mm
//
int vl53l0x_read_distance(uint8_t dev_addr);

//
// sets the device continous capture mode
//
int init_vl53l0x(uint8_t dev_addr, int bLongRangeMode);

#endif // _TOFLIB_H

#ifndef _APP_DRIVE_H_
#define _APP_DRIVE_H_

#include <math.h>

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/watchdog.h"

#include "ws2812.pio.h"
#include "lcd1602a.pio.h"
#include "src/motor_driver/quad_stepper_motors.h"
#include "src/light_sensor/tcs34725.h"

/*
// This is a saple programm for interfacing via USART to an raspberry pi zero.
// you can send driving commands for the quad stepper mecanum module,
// as well as interfaing with the 1602 LCD and button module.
// The docuentation for the USART commands arre below.
*/


#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

//-PIN-DEFINITIONS------

// UART pins for Raspberry pi pico to Raspberry pi zero w communication
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// 1602A LCD display an quad button array
#define APP_DRIVE_1602A_LCD_DATA_PIN 19
#define APP_DRIVE_1602A_LCD_DATA_CLK 17
#define APP_DRIVE_1602A_LCD_DATA_ENA 16
#define APP_DRIVE_1602A_LCD_DATA_REG 15
#define APP_DRIVE_1602A_LCD_DATA_BUT_A 26
#define APP_DRIVE_1602A_LCD_DATA_BUT_I 20

/*
 * status LED colors:
 * - red-green: init
 * - blue: waiting for connection
 * - red: error
 * - green: connected and running
 * - green-blue: waiting on user input
 * - red-blue: resetting
 */
 #define STLED_INIT		0x10100000
 #define STLED_WAIT_CON	0x00001000
 #define STLED_ERROR	   0x00100000
 #define STLED_IS_CON	0x10000000
 #define STLED_WAIT_USR	0x10001000
 #define STLED_RST		0x00101000

// for alternative costom chars redefine the fllowing array.
 static uint8_t custom_chars[8*8] = {
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
    0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00, // ':-)' Char
 };

 /* 
 Communication Raspberry pi zero w -> Rasberry pi pico:
      "S" := first char to enable communication between the two

      "D[xx]":= drive 
         xx can be:
            ff forward
            fr forward right
            rr rightward
            br backward right
            bb backward
            bl backward left
            ll leftward
            fl forward left
            tr turn right
            tl turn left
      
      "T[i;xxxxxxxxxxxxxxxx]"" := print to lcd
         i can be 1 or 2
         xxxxxxxxxxxxxxxx exactly 16 ascii (0x30-0x7f) or costom (0x01-0x08) chars

      "R" := Reset the raspberry pi pico

Communication Raspberry pi pico -> Rasberry pi zero w:
      B[iiii] := button with analoge value iiii
 
*/

void init_uart_for_app_drive();
void start_app_drive();
void manage_driving_commands();
void manage_printing_commands();

#endif

#include "pico/stdlib.h"
#include <stdio.h>

#include "lcd1602a.pio.h"
#include "shiftreg.pio.h"

#include "display/max7219_dot_matrix.h"
#include "max7219.pio.h"
#include "light_sensor/tcs34725.h"
#include "light_sensor/ads1115.h"
#include "range_sensor/vl53l0x.h"
#include "range_sensor/vl53l0x_lidar_scanner.h"
#include "range_sensor/hy_srf05.h"
#include "imu/adxl345.h"
#include "imu/qmc5883.h"
#include "motor_driver/l298n.h"
#include "motor_driver/dual_dc_motors.h"
#include "motor_driver/servo_lib.h"
#include "motor_driver/dual_stepper_motors.h"

#include "app_drive.h"
#include "tracked_drive.h"
#include "two_wheel_drive.h"

#include "ws2812.pio.h"
#include "display/ws2812_test.h"
#include "display/ws2812_8x8.h"

#include "hardware/adc.h"

// send data or chars to 1602 LCD
void sendData() {
	int data = 0;
	int is_data = 0;
	while (true) {
		scanf(" %x", &data);
		scanf(" %d", &is_data);
		printf("data: %x %d \n",data,is_data);
		lcd1602a_send(data, is_data);
		sleep_ms(1);
    }
}

// send chars to 1602 LCD
void sendChar() {

	int data = 0;
	int is_data = 1;
	while (true) {
		scanf("%c", &data);
		if ((data >= 0x20) && (data <= 0x7f)) {
			printf("data: %c\n",data);
			lcd1602a_send(data, is_data);
			sleep_ms(10);
		}
    }

}

int main() {

	//# alwas needed
    stdio_init_all();

	//# Example project with mecanum wheels
	//# reacting and send over USART
	// start_app_drive();


	//# Example project with tracked propulsion
	// start_tracked_drive();

	//# Example project with signle wheel dc motors
	// start_two_wheel_drive();

	

	//# Example how to use lcd1602 display
    // lcd1602a_init(0, 1, 2, 3, 26, 20);
	// lcd1602a_reset();
	// lcd1602a_print("     Hello      ",1);
	// lcd1602a_print("     World!     ",2);
	// sendData();
    

	//# Example how to send serial data to 74hc595 shift registers
	// shiftreg_init();
	// shiftreg_send(0b000000111111111111110000111111);


	//# Example for RGB sensor
    // init_tcs34725();
    // test_tcs34725();
    

	//# Example for Inertial Mesurement Unit
	// init_adxl345();
	// test_adxl345();
	
	
	//# Example for srf05/4 ultrasonic distance sensor
	// init_hy_srf05();
	

	//# Example for octuple infrared line sensor
	// ads1115_init();
	// test_ads1115();
 
	//# Example for mgnetic compass
	// init_qmc5883();
	// while(1) {
		// printf("Azimuth : %d \n", (uint16_t) get_qmc5883_azimuth());
		// sleep_ms(10);
	// }


	//# Example for smoothed pwm servo contoll
	// servo_test();
	
	
	//# Example for dual lidar scanner
	// init_vl53l0x_lidar_scanner(0,1,0x70,0x71,2);


	//# Example for simple motor driver
	// init_l298n();
	// while (1) {
		// printf("set speed to: ");
		// int left  = 0;
		// scanf(" %d", &left);
		// printf("Speed %d|\n",left);
		// l298n_set_speed(left,0);
	// }
	

	//# Example for simple motor driver
	// init_dual_dc_drive();
	// set_dual_dc_speed(30000,30000);
	// while (1) {
		// printf("set speed to: ");
		// int left  = 0;
		// scanf(" %d", &left);
		// printf("Speed %d|\n",left);
		// set_dual_dc_speed(0,left);
	// }
	

	//# Example for different 8x8 RGB led test
	//# alwas needed
	// struct pio_inst test_inst = ws2812_program_init(0, 800000);
	// clear_ws2812_current_state();
	//# choose only one
	// test_ws2812_orientation(test_inst);
	// test_ws2812_color_scrolling(test_inst);
	// test_ws2812_compass_free_running(0);
	// test_ws2812_compass(2);
	

	//# Example for stepper driver
	// init_dual_stepper_drive();
	// while (1) {
		// printf("set speed to: ");
		// int left  = 0;
		// scanf(" %d", &left);
		// printf("Speed %d|\n",left);
		// set_dual_stepper_speed(left,0);
	// }
	
	
	//# Example for max7219 ontrolled displays
	//# alwas needed
	//  struct pio_inst dotmatrix = max7219_init(17,18,19);

	//# following are for dual 8x8 dot matrix
	//# scroll trow all avaiable chars
	// while (1) {
	// 	max7219_scroll_all_char(dotmatrix);
	// }
	//# repeadedly scroll Hello World!
	// while (1) {
	// 	max7219_scroll_string("Hello World!", 100);
	// }

	//# following are for dual octuple seven segment display
	//# Example for prinitng Hello World!
	// uint8_t seven_segment_string[16] = {
	// 	0,0b10100000,0b00111101,0b00001110,0b00000101,0b0011101,0b00111100,0b00011110,
	// 	0,0,0,0b00011101,0b00001110,0b00001110,0b01001111,0b00110111
	// 	}; // "HELLo___UUorLd!_"
	// max7219_disply_array_on_2x8x8(seven_segment_string);
	
	//# Example for sending data to max27219 chips
	//~ while (1) {
		//~ int data = 0;
		//~ scanf(" %x", &data);
		//~ printf("data: %x\n",data);
		//~ max7219_send_dot_char(data);
		//~ max7219_send(data);
		//~ sleep_ms(1);
	//~ }

	// //# exapmple of servo lib
	// add_servo_at_pin(0);
	// while (1)  {
	// set_servo_to_pos(0,220);
	// sleep_ms(2000);
	// set_servo_to_pos(0,1700);
	// sleep_ms(2000);
	// }

	// //# exapmple of servo lib for five servos
	// int pos0 = 0;
	// int pos1 = 0;
	// int pos2 = 0;
	// int pos3 = 0;
	// int pos4 = 0;
	// add_servo_at_pin(APP_DRIVE_TF5_PWM,500);
	// add_servo_at_pin(APP_DRIVE_TF4_PWM,500);
	// add_servo_at_pin(APP_DRIVE_TF3_PWM,500);
	// add_servo_at_pin(APP_DRIVE_TM5_PWM,600);
	// add_servo_at_pin(APP_DRIVE_TM4_PWM,1200);
	// while (true) {
	// 	printf("new pos:");
	// 	scanf("%d %d %d %d %d", &pos0, &pos1, &pos2, &pos3, &pos4);
	// 	printf("%d %d %d %d %d\n",pos0, pos1, pos2, pos3, pos4);
	// 	set_servo_to_pos(APP_DRIVE_TF5_PWM,pos0);
	// 	set_servo_to_pos(APP_DRIVE_TF4_PWM,pos1);
	// 	set_servo_to_pos(APP_DRIVE_TF3_PWM,pos2);
	// 	set_servo_to_pos(APP_DRIVE_TM5_PWM,pos3);
	// 	set_servo_to_pos(APP_DRIVE_TM4_PWM,pos4);
	// 	sleep_ms(10);
    // }


	//# needed for stopping the RP2040 going to sleep
	while(1);
}




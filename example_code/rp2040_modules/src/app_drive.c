#include "app_drive.h"

// PIO instnce for the ws2812 LED on the conroller module
struct pio_inst status_led;

void start_app_drive() {
	stdio_init_all();

	// init status LED on gpio22 with frequency of 800kHz
	status_led = ws2812_program_init(22,800000);
	
	//############################################
	// Iitialisation of the modules
	
	// set status to yellow <-> init
	put_all_pixel(STLED_INIT, 1, status_led);
	
	// init uart on pins 0 and 1 for communication with the rp zero
	init_uart_for_app_drive();
	
	// init the quad stepper mecanum drive
	initDrive();

	// init 1602A lcd
	lcd1602a_init(APP_DRIVE_1602A_LCD_DATA_PIN,
				APP_DRIVE_1602A_LCD_DATA_CLK, 
				APP_DRIVE_1602A_LCD_DATA_ENA,
				APP_DRIVE_1602A_LCD_DATA_REG, 
				APP_DRIVE_1602A_LCD_DATA_BUT_A,
				APP_DRIVE_1602A_LCD_DATA_BUT_I);

	// after initing the 1602 LCD you have to reset it
	lcd1602a_reset();

	// store costom chars to LCD
	lcd1602a_set_custom_chars(custom_chars);

	// set display as test
	lcd1602a_print("################",1);
	lcd1602a_print("################",2);
	
	//############################################
	// wait for connection/ wait on reciving 'S'
	
	// set status to blue <-> waiting for connection
	put_all_pixel(STLED_WAIT_CON, 1, status_led);
	
	// the last recieved char
	uint8_t current_char;
	
	do {
	// wait for a new char
	current_char = uart_getc(UART_ID);
	} while (current_char != 'S');
	
	//############################################
	// main loop

	// set status to green <-> is connected
	put_all_pixel(STLED_IS_CON, 1, status_led);

	// reset lcd
	lcd1602a_reset();
	
	while (1) {
		
		// set status to green-blue <-> wait for unser input
		put_all_pixel(STLED_WAIT_USR, 1, status_led);
		
		// wait for a new char
		current_char = uart_getc(UART_ID);
		switch (current_char) {
			case 'D':
				// drive
				manage_driving_commands();
				break;
			case 'T':
				// type to LCD
				manage_printing_commands();
				break;
			case 'R':
				// reset after 10ms!!!
				put_all_pixel(STLED_RST, 1, status_led);
				watchdog_enable(10,0);
				while(1);
			default:
		
		}

	}
	
}

// check for correct format of driving command and execute it.
void manage_driving_commands() {
	// wait for '['
	uint8_t current_char = uart_getc(UART_ID);
	if (current_char != '[') {
		put_all_pixel(STLED_ERROR, 1, status_led);
		return;
	}
	
	// wait for direction {ff,fr,rr,br,bb,bl,ll,fl,tr,tl,ss}
	uint16_t chars = (uint16_t)(uart_getc(UART_ID)) << 8;
	chars |= uart_getc(UART_ID);
	
	//wait for ']'
	current_char = uart_getc(UART_ID);
	if (current_char != ']') {
		put_all_pixel(STLED_ERROR, 1, status_led);
		return;
	}
	
	// decide direction
	switch (chars) {
		case (uint16_t)('f')<<8|'f':
			driveForeward();
			break;
		case (uint16_t)('f')<<8|'r':
			driveForewardRight();
			break;
		case (uint16_t)('r')<<8|'r':
			driveRight();
			break;
		case (uint16_t)('b')<<8|'r':
			driveBackwardRight();
			break;
		case (uint16_t)('b')<<8|'b':
			driveBackward();
			break;
		case (uint16_t)('b')<<8|'l':
			driveBackwardLeft();
			break;
		case (uint16_t)('l')<<8|'l':
			driveLeft();
			break;
		case (uint16_t)('f')<<8|'l':
			driveForewardLeft();
			break;
		case (uint16_t)('t')<<8|'r':
			rotateRight();
			break;
		case (uint16_t)('t')<<8|'l':
			rotateLeft();
			break;
		case (uint16_t)('s')<<8|'s':
			stop();
			break;
		default:
			// something whent wrong!
			put_all_pixel(STLED_ERROR, 1, status_led);
			return;
	}
}

// check for correct format of printing command and execute it.
void manage_printing_commands(){
	// wait for '['
	uint8_t current_char = uart_getc(UART_ID);
	if (current_char != '[') return;
	
	// wait for row subtract hex 0x30 to convert from ASCII to dec
	uint8_t row = uart_getc(UART_ID);
	row -= 0x30;
	if (row != 1 && row != 2) {
		put_all_pixel(STLED_ERROR, 1, status_led);
		return;
	}

	//wait for ';'
	current_char = uart_getc(UART_ID);
	if (current_char != ';') {
		put_all_pixel(STLED_ERROR, 1, status_led);
		return;
	}
	
	// string ary for building the message
	uint8_t str[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	// build the string
	for (int i = 0; i < 16; i++) {
		str[i] = uart_getc(UART_ID);

		// error if out of 7bit ASXII range
		if (str[i] > 0x7f) {
			put_all_pixel(STLED_ERROR, 1, status_led);
			return;
		}
	}

	// add null termination
	str[16] = '\0';

	//wait for ']'
	current_char = uart_getc(UART_ID);
	if (current_char != ']') {
		put_all_pixel(STLED_ERROR, 1, status_led);
		return;
	}

	// print to LCD
	lcd1602a_print(str,row);

}

void init_uart_for_app_drive() {
	// Set up our UART with a basic baud rate.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
}

#include "ws2812_test.h"

#define LED_X_CNT 8
#define LED_Y_CNT 8
#define DELAY 1000

// array of current rgb values for constructin the new image
uint32_t ws2812_current_state[LED_Y_CNT][LED_X_CNT];

// set array to all 0
void clear_ws2812_current_state() {
	for (uint8_t x = 0; x < LED_X_CNT; x++) {
		for (uint8_t y = 0; y < LED_Y_CNT; y++) {
			ws2812_current_state[y][x] = 0;
		}	
	}
}

// draw an example compass witout senor input
void test_ws2812_compass_free_running(uint8_t pin) {
	rgb_8x8_matrix_init(pin);
	while (1) {
		for (int d = 0; d < 360; d++) {
			rgb_8x8_matrix_clear();
			//~ rgb_8x8_matrix_fill(urgb_u32(10,10,10));
			rgb_8x8_matrix_circle( 3.5, 3.5, 1, 3.3, true, urgb_u32(0,0,25));
			rgb_8x8_matrix_circle( 3.5, 3.5, 1, 3.3, false, urgb_u32(10,10,25));
			rgb_8x8_matrix_line(3.5,3.5,sin(d/57.2957795)*3+3.5,cos(d/57.2957795)*3+3.5,1,urgb_u32(25,0,0));
			rgb_8x8_matrix_update();
			sleep_ms(1);
		}
	}
}

// draw an exmple compass using the qmc5883 magnectic sensor 
void test_ws2812_compass(uint8_t pin) {
	rgb_8x8_matrix_init(pin);
	
	init_qmc5883();
	reset_qmc5883();
	
	while (1) {
			float_t north = get_qmc5883_azimuth();
			printf("North: %f \n",north);
			rgb_8x8_matrix_clear();
			//~ rgb_8x8_matrix_fill(urgb_u32(10,10,10));
			rgb_8x8_matrix_circle( 3.5, 3.5, 1, 3.3, true, urgb_u32(0,0,25));
			rgb_8x8_matrix_circle( 3.5, 3.5, 1, 3.3, false, urgb_u32(10,10,25));
			rgb_8x8_matrix_line(3.5,3.5,sin(north/57.2957795)*3+3.5,cos(north/57.2957795)*3+3.5,1,urgb_u32(25,0,0));
			rgb_8x8_matrix_update();
			sleep_ms(50);
	}
}

// print a example test screen
void test_ws2812_orientation(struct pio_inst inst) {
	for (uint8_t x = 0; x < LED_X_CNT; x++) {
		for (uint8_t y = 0; y < LED_Y_CNT; y++) {
			if (x == 0 && y == 0) {
				ws2812_current_state[y][x] = urgb_u32(0,255,0);
			} else if (x==y) {
				ws2812_current_state[y][x] = urgb_u32(255,255,255);
			} else if (x == 0) {
				ws2812_current_state[y][x] = urgb_u32(255,0,0);
			} else if (y == 0) {
				ws2812_current_state[y][x] = urgb_u32(0,0,255);
			}
		}	
	}
	put_pixels( &ws2812_current_state[0][0],LED_X_CNT*LED_Y_CNT,inst);
}

// set all pixels to white
void test_ws2812_fully_on(struct pio_inst inst) {
		put_all_pixel(urgb_u32(255,255,255),LED_X_CNT*LED_Y_CNT,inst);
}

// scroll trow all colors
void test_ws2812_color_scrolling(struct pio_inst inst) {
	while (1) {
		// Hold r fade in g
        for (uint8_t i = 0; i < 255; i++) {
			put_all_pixel(urgb_u32(255,i,0),LED_X_CNT*LED_Y_CNT,inst);
			sleep_us(DELAY);
		}
		// Hold g fade out r
		for (uint8_t i = 255; i >0 ; i--) {
			put_all_pixel(urgb_u32(i,255,0),LED_X_CNT*LED_Y_CNT,inst);
			sleep_us(DELAY);
		}
		// Hold g fade in b
		for (uint8_t i = 0; i < 255; i++) {
			put_all_pixel(urgb_u32(0,255,i),LED_X_CNT*LED_Y_CNT,inst);
			sleep_us(DELAY);
		}
		// Hold b fade out g
		for (uint8_t i = 255; i >0 ; i--) {
			put_all_pixel(urgb_u32(0,i,255),LED_X_CNT*LED_Y_CNT,inst);
			sleep_us(DELAY);
		}
		// Hold b fade in R
		for (uint8_t i = 0; i < 255; i++) {
			put_all_pixel(urgb_u32(i,0,255),LED_X_CNT*LED_Y_CNT,inst);
			sleep_us(DELAY);
		}
		// Hold R fade out b
		for (uint8_t i = 255; i >0 ; i--) {
			put_all_pixel(urgb_u32(255,0,i),LED_X_CNT*LED_Y_CNT,inst);
			sleep_us(DELAY);
		}
    }
}

#include "ws2812_8x8.h"

// array for the current RGB values
uint32_t rgb_8x8_matrix_state[8][8];

struct pio_inst rgb_8x8_matrix_instance;

// init pio for ws2812 leds
void rgb_8x8_matrix_init(uint pin) {
	rgb_8x8_matrix_instance = ws2812_program_init(pin, 800000);
	rgb_8x8_matrix_clear();
}

// clear matrix
void rgb_8x8_matrix_clear() {
	for (uint8_t x = 0; x < 8; x++) {
		for (uint8_t y = 0; y < 8; y++) {
			rgb_8x8_matrix_state[y][x] = 0;
		}	
	}
}

// print new data to the rgb matrix
void rgb_8x8_matrix_update() {
	put_pixels(&rgb_8x8_matrix_state[0][0],8*8,rgb_8x8_matrix_instance);
}

//fill the array with one color 
void rgb_8x8_matrix_fill(uint32_t color) {
	for (uint8_t x = 0; x < 8; x++) {
		for (uint8_t y = 0; y < 8; y++) {
			rgb_8x8_matrix_state[y][x] = color;
		}	
	}
}

// draw a circle around x and y position with radious r.
// w is line thickness, optionally can be filled
void rgb_8x8_matrix_circle( float_t x, float_t y, float_t w, float_t r, uint8_t filled, uint32_t color) {
	for (uint8_t px = 0; px < 8; px++) {
		for (uint8_t py = 0; py < 8; py++) {
			float_t dist = sqrt((px-x)*(px-x)+(py-y)*(py-y));
			if (dist <= r + w/2.0 && (filled || dist > r-w/2.0)) {
				rgb_8x8_matrix_state[py][px] = color;
			}
		}	
	}
}

// draw a line between two pionts with width w and color
void rgb_8x8_matrix_line( float_t x1, float_t y1, float_t x2, float_t y2, float_t w, uint32_t color) {
	float_t dist = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	uint8_t dist_int = ((int8_t) dist) + 1 ;
	//~ printf("dist: %f, dist_int: %d\n",dist,dist_int);
	for (int i = 0; i <= dist_int; i++ ) {
		uint8_t ip_x = round((x2 - x1)*i/dist_int + x1);
		uint8_t ip_y = round((y2 - y1)*i/dist_int + y1);
		//~ printf("mid_x: %f, mid_y: %f\n",mid_x,mid_y);
		rgb_8x8_matrix_state[ip_y][ip_x] = color;
	}
}

// draw a filled rectangle between two pionts with color
// point 1 should be always smaller than point 2
void rgb_8x8_matrix_square( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t color) {
	for (uint8_t px = 0; px < 8; px++) {
		for (uint8_t py = 0; py < 8; py++) {
			if ( py >= y1 && py <= y2 && px >= x1 && px <= x2) {
				rgb_8x8_matrix_state[py][px] = color;
			}
		}	
	}
}

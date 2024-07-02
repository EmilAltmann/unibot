#include "two_wheel_drive.h"

// example robot cofigutation
void start_two_wheel_drive() {

struct pio_inst dotmatrix =  max7219_init(TWOWHEEL_TM_DAT,  TWOWHEEL_TM_CLK,  TWOWHEEL_TM_ENA);
struct pio_inst sevensegment =  max7219_init(TWOWHEEL_TB_DAT,  TWOWHEEL_TB_CLK,  TWOWHEEL_TB_ENA);

uint8_t seven_segment_string[16] = {
	0,0b10100000,0b00111101,0b00001110,0b00000101,0b0011101,0b00111100,0b00011110,
	0,0,0,0b00011101,0b00001110,0b00001110,0b01001111,0b00110111
	}; // "HELLo___UUorLd!_"
max7219_disply_array_on_2x8x8(seven_segment_string,sevensegment);

// max7219_scroll_all_char(dotmatrix);
max7219_scroll_string("Hello World!", 25,dotmatrix);


//clear display
max7219_disply_clear(sevensegment);


// init motor drivers
init_dual_dc_drive();

// init line sensors
ads1115_init();

// set motor speeds
set_dual_dc_speed(TWOWHEEL_HIGHSPEED, TWOWHEEL_HIGHSPEED);

uint8_t sees_black = 0;

// the main loop
while (1) {

    sees_black = 0;

    // display bar graph of values on dotmatrix display
    for (int i = 0; i < 8; i++) {
        seven_segment_string[15-2*i] = bin16_to_unary8(ads1115_sample(i));
        seven_segment_string[14-2*i] = seven_segment_string[15-2*i];
        if (seven_segment_string[15-2*i] < 2 ) {
            sees_black++;
        }
    }
    max7219_disply_array_on_2x8x8(seven_segment_string,dotmatrix);

    if (sees_black > 2) {
        set_dual_dc_speed(-TWOWHEEL_LOWSPEED,-TWOWHEEL_LOWSPEED);
        sweep_sound();
        set_dual_dc_speed(TWOWHEEL_LOWSPEED,-TWOWHEEL_LOWSPEED);
        sweep_sound();
        set_dual_dc_speed(TWOWHEEL_HIGHSPEED, TWOWHEEL_HIGHSPEED);
    }
    
}
}



// biased 16-bit to 8-bit unary conversion
uint8_t bin16_to_unary8(uint16_t i) {
    return (
          ((i>999)<<0) | ((i>1999)<<1) 
        | ((i>2999)<<2) | ((i>3999)<<3) 
        | ((i>4999)<<4) | ((i>5999)<<5)
        | ((i>6999)<<6) | ((i>7999)<<7)
    );
}

void sweep_sound() {
    gpio_set_function(TWOWHEEL_BM_BUZZER, GPIO_FUNC_PWM);
    uint8_t slice   = pwm_gpio_to_slice_num(TWOWHEEL_BM_BUZZER);
	uint8_t channel = pwm_gpio_to_channel(TWOWHEEL_BM_BUZZER);

    pwm_set_clkdiv(slice, 0.1f);
    pwm_set_wrap(slice, 65535);
    pwm_set_enabled(slice, true);

    for (uint8_t i = 1; i <= 20; i++) {
        pwm_set_clkdiv(slice, (float)i);  /// Setting the divider to slow down the clock
        sleep_ms(10);
    }
        for (uint8_t i = 20; i > 0; i--) {
        pwm_set_clkdiv(slice, (float)i);  /// Setting the divider to slow down the clock
        sleep_ms(10);
    }

    pwm_set_enabled(slice, false);
     gpio_set_function(TWOWHEEL_BM_BUZZER, GPIO_FUNC_NULL);


}
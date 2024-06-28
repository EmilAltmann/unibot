#include "dual_dc_motors.h"

static int motor_offset;

/// int PWM and IO for driving the h-bridges
void init_dual_dc_drive(){
	
	// init pins for output
	gpio_init(LDA);
	gpio_init(LDB);
	gpio_init(RDA);
	gpio_init(RDB);
	gpio_init(REN);
	gpio_init(LEN);
	
	gpio_set_dir(LDA, GPIO_OUT);
    gpio_set_dir(LDB, GPIO_OUT);
    gpio_set_dir(RDA, GPIO_OUT);
    gpio_set_dir(RDB, GPIO_OUT);
    gpio_set_dir(REN, GPIO_OUT);
    gpio_set_dir(LEN, GPIO_OUT);
    
    // set drection to known levels
    gpio_put(LDA, 0 );
    gpio_put(LDB, 0 );
	gpio_put(RDA, 0 );
	gpio_put(RDB, 0 );
	
	// init PWM
	gpio_set_function(LEN, GPIO_FUNC_PWM);
    gpio_set_function(REN, GPIO_FUNC_PWM);
    dual_dc_slice_L   = pwm_gpio_to_slice_num(LEN);
	dual_dc_channel_L = pwm_gpio_to_channel(LEN);
	dual_dc_slice_R   = pwm_gpio_to_slice_num(REN);
	dual_dc_channel_R = pwm_gpio_to_channel(REN);
	
	// for the left side
    pwm_set_clkdiv(dual_dc_slice_L, 1);  /// Setting the divider to slow down the clock
    pwm_set_enabled(dual_dc_slice_L, false);
    pwm_set_wrap(dual_dc_slice_L, 65535);
    // for the right side
    pwm_set_clkdiv(dual_dc_slice_R, 1);  /// Setting the divider to slow down the clock
    pwm_set_enabled(dual_dc_slice_R, false);
    pwm_set_wrap(dual_dc_slice_R, 65535);
}

// set speed 0 is stop, sign is negative for reverse, max is 2047
void set_dual_dc_speed(int16_t speed_l, int16_t speed_r) {
	
	if (speed_l == 0) {
		pwm_set_enabled(dual_dc_slice_L, false);
	} else {
		// Set rotation direction; left side is inverted
		if (speed_l < 0) {
			speed_l *= -1;
			gpio_put(LDA, 0 );
			gpio_put(LDB, 1 );
		} else {
			gpio_put(LDA, 1 );
			gpio_put(LDB, 0 );
		}
		
		//offset for max speed and inverse to higher is faster
		speed_l = (65535 - speed_l) << 1;
		
		pwm_set_chan_level(dual_dc_slice_L, dual_dc_channel_L, speed_l);
		pwm_set_enabled(dual_dc_slice_L, true);
	}
	
	if (speed_r == 0) {
		pwm_set_enabled(dual_dc_slice_R, false);
	} else {
		// Set rotation direction; left side is inverted
		if (speed_r < 0) {
			speed_r *= -1;
			gpio_put(RDA, 1 );
			gpio_put(RDB, 0 );
		} else {
			gpio_put(RDA, 0 );
			gpio_put(RDB, 1 );		
		}
		
		//offset for max speed and inverse to higher is faster
		speed_r = (65535 - speed_r) << 1;
		
		pwm_set_chan_level(dual_dc_slice_R, dual_dc_channel_R, speed_r);
		pwm_set_enabled(dual_dc_slice_R, true);
	}
}

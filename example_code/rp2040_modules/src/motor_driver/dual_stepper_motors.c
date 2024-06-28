#include "dual_stepper_motors.h"

static int motor_offset;

/// int PWM and IO for driving the stepper motors
void init_dual_stepper_drive(){
	
	// init pins for output
	gpio_init(LD);
	gpio_init(LS);
	gpio_init(RD);
	gpio_init(RS);
	
	gpio_set_dir(LD, GPIO_OUT);
    gpio_set_dir(LS, GPIO_OUT);
    gpio_set_dir(RD, GPIO_OUT);
    gpio_set_dir(RS, GPIO_OUT);
    
    // set drection to known levels
    gpio_put(LD, 1 );
	gpio_put(RD, 1 );
	
	// init PWM
	gpio_set_function(LS, GPIO_FUNC_PWM);
    gpio_set_function(RS, GPIO_FUNC_PWM);
    slice_L   = pwm_gpio_to_slice_num(LS);
	channel_L = pwm_gpio_to_channel(LS);
	slice_R   = pwm_gpio_to_slice_num(RS);
	channel_R = pwm_gpio_to_channel(RS);
	
	// for the left side
    pwm_set_clkdiv(slice_L, 0xFFFF);  /// Setting the divider to slow down the clock
    pwm_set_enabled(slice_L, false);

    // for the right side
    pwm_set_clkdiv(slice_R, 0xFFFF);  /// Setting the divider to slow down the clock
    pwm_set_enabled(slice_R, false);
}

// set speed 0 is stop, sign is negative for reverse, max is 2047
void set_dual_stepper_speed(int16_t speed_l, int16_t speed_r) {
	
	if (speed_l == 0) {
		pwm_set_enabled(slice_L, false);
	} else {
		// Set rotation direction; left side is inverted
		if (speed_l < 0) {
			speed_l *= -1;
			gpio_put(LD,1);
		} else {
			gpio_put(LD,0);
		}
		
		//offset for max speed and inverse to higher is faster
		speed_l = (2048-speed_l) << 5;
		
		pwm_set_wrap(slice_L, speed_l);
		pwm_set_chan_level(slice_L, channel_L, speed_l/2);
		
		pwm_set_enabled(slice_L, true);
	}
	
	if (speed_r == 0) {
		pwm_set_enabled(slice_R, false);
	} else {
		// Set rotation direction; left side is inverted
		if (speed_r < 0) {
			speed_r *= -1;
			gpio_put(RD, 0 );
		} else {
			gpio_put(RD, 1 );		
		}
		
		//offset for max speed and inverse to higher is faster
		speed_r = (2048-speed_r) << 5;
		
		pwm_set_wrap(slice_R, speed_r);
		pwm_set_chan_level(slice_R, channel_R, speed_r/2);
		
		pwm_set_enabled(slice_R, true);
	}
}

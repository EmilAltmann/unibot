#include "l298n.h"

/// int PWM and IO for driving the stepper motors
void init_l298n(){
	
	// init pins for output
	gpio_init(ENL);
	gpio_init(ENR);
	
	gpio_init(IN1L);
	gpio_init(IN2L);
	gpio_init(IN1R);
	gpio_init(IN2R);

	gpio_set_dir(ENL, GPIO_OUT);
    gpio_set_dir(ENR, GPIO_OUT);
    
    gpio_set_dir(IN1L, GPIO_OUT);
    gpio_set_dir(IN2L, GPIO_OUT);
    gpio_set_dir(IN1R, GPIO_OUT);
    gpio_set_dir(IN2R, GPIO_OUT);
    
    // set drection to known levels
    gpio_put(IN1L, 1 );
	gpio_put(IN2L, 1 );
	gpio_put(IN1R, 1 );
	gpio_put(IN2R, 1 );
	
	// init PWM
	gpio_set_function(ENL, GPIO_FUNC_PWM);
    gpio_set_function(ENR, GPIO_FUNC_PWM);
    slice_ENL   = pwm_gpio_to_slice_num(ENL);
	channel_ENL = pwm_gpio_to_channel(ENL);
	slice_ENR   = pwm_gpio_to_slice_num(ENR);
	channel_ENR = pwm_gpio_to_channel(ENR);

	// for the left side
    pwm_set_clkdiv(slice_ENL, 1);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_ENL, 0XFFFF);      /// setting the Wrap time to limit max speed
	pwm_set_chan_level(slice_ENL, channel_ENL, 0XFFFF);
    pwm_set_enabled(slice_ENL, false);
    
    // for the right side
    pwm_set_clkdiv(slice_ENR, 1);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_ENR, 0XFFFF);      /// setting the Wrap time to limit max speed
    pwm_set_chan_level(slice_ENR, channel_ENR, 0XFFFF);
    pwm_set_enabled(slice_ENR, false);
}

// set speed 0 is stop, sign is negative for reverse and smaller is faster
void l298n_set_speed(int16_t speed_l, int16_t speed_r) {
	
	// stop l if zero
	if (speed_l == 0) {
		pwm_set_enabled(slice_ENL, false);
	} else {
		pwm_set_enabled(slice_ENL, true);
	}

	// stop r if zero
	if (speed_r == 0) {
		pwm_set_enabled(slice_ENR, false);
	} else {
		pwm_set_enabled(slice_ENR, true);
	}
	
	// configure l direcion
	// left is inverted
	if (speed_l < 0) {
		speed_l *= -1;
		gpio_put(IN1L, 1 );
		gpio_put(IN2L, 0 );
	} else {
		gpio_put(IN1L, 0 );
		gpio_put(IN2L, 1 );
	}
	
	// configure r direcion
	if (speed_r < 0) {
		speed_r *= -1;
		gpio_put(IN1R, 0 );
		gpio_put(IN2R, 1 );
	} else {
		gpio_put(IN1R, 1 );
		gpio_put(IN2R, 0 );
	}

	// disable pwm at max
	if (speed_l == 0x7fff) {
		gpio_set_function(ENL, GPIO_FUNC_SIO);
		gpio_put(ENL, 1 );

	} else {
		gpio_set_function(ENL, GPIO_FUNC_PWM);
	}

	// disable pwm at max
	if (speed_r == 0x7fff) {
		gpio_set_function(ENR, GPIO_FUNC_SIO);
		gpio_put(ENR, 1 );

	} else {
		gpio_set_function(ENR, GPIO_FUNC_PWM);
	}
	
	// set pwm for l and r side
	pwm_set_chan_level(slice_ENL, channel_ENL, speed_l <<1);
	pwm_set_chan_level(slice_ENR, channel_ENR, speed_r <<1);
}

void l298n_lMotor(){
	l298n_set_speed(L298N_HIGHSPEED,0);
	}
	
void l298n_rMotor(){
	l298n_set_speed(0,L298N_HIGHSPEED);
	}

void l298n_driveForeward(){
	l298n_set_speed(L298N_HIGHSPEED,L298N_HIGHSPEED);
}

void l298n_driveBackward(){
	l298n_set_speed(-L298N_HIGHSPEED,-L298N_HIGHSPEED);
}

void l298n_rotateLeft(){
	l298n_set_speed(-L298N_HIGHSPEED,L298N_HIGHSPEED);
}

void l298n_turnLeft() {
	l298n_set_speed(0,L298N_HIGHSPEED);
	}

void l298n_rotateRight(){
	l298n_set_speed(L298N_HIGHSPEED,-L298N_HIGHSPEED);
}

void l298n_turnRight() {
	l298n_set_speed(L298N_HIGHSPEED,0);
	}

void l298n_stop(){
	l298n_set_speed(0,0);
}

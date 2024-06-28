#include "quad_stepper_motors.h"

static int motor_offset;

/// int PWM and IO for driving the stepper motors
void initDrive(){
	
	// init pins for output
	gpio_init(LFD);
	gpio_init(LFS);
	gpio_init(RFD);
	gpio_init(RFS);
	gpio_init(LBD);
	gpio_init(LBS);
	gpio_init(RBD);
	gpio_init(RBS);
	
	gpio_set_dir(LFD, GPIO_OUT);
    gpio_set_dir(LFS, GPIO_OUT);
    gpio_set_dir(RFD, GPIO_OUT);
    gpio_set_dir(RFS, GPIO_OUT);
    gpio_set_dir(LBD, GPIO_OUT);
    gpio_set_dir(LBS, GPIO_OUT);
    gpio_set_dir(RBD, GPIO_OUT);
    gpio_set_dir(RBS, GPIO_OUT);
    
    // set drection to known levels
    gpio_put(LFD, 1 );
	gpio_put(RFD, 1 );
	gpio_put(LBD, 1 );
	gpio_put(RBD, 1 );
	
	// init PWM
	gpio_set_function(LFS, GPIO_FUNC_PWM);
    gpio_set_function(RFS, GPIO_FUNC_PWM);
    gpio_set_function(LBS, GPIO_FUNC_PWM);
    gpio_set_function(RBS, GPIO_FUNC_PWM);
    slice_LF   = pwm_gpio_to_slice_num(LFS);
	channel_LF = pwm_gpio_to_channel(LFS);
	slice_RF   = pwm_gpio_to_slice_num(RFS);
	channel_RF = pwm_gpio_to_channel(RFS);
	slice_LB   = pwm_gpio_to_slice_num(LBS);
	channel_LB = pwm_gpio_to_channel(LBS);
	slice_RB   = pwm_gpio_to_slice_num(RBS);
	channel_RB = pwm_gpio_to_channel(RBS);

	// for the left side
    pwm_set_clkdiv(slice_LF, MAXSPEED);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_LF, WRAPVAL);      /// setting the Wrap time to limit max speed
	pwm_set_chan_level(slice_LF, channel_LF, WRAPVAL/2);
    pwm_set_enabled(slice_LF, false);
    
    pwm_set_clkdiv(slice_LB, MAXSPEED);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_LB, WRAPVAL);      /// setting the Wrap time to limit max speed
	pwm_set_chan_level(slice_LB, channel_LB, WRAPVAL/2);
    pwm_set_enabled(slice_LB, false);
    
    // for the right side
    pwm_set_clkdiv(slice_RF, MAXSPEED);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_RF, WRAPVAL);      /// setting the Wrap time to limit max speed
    pwm_set_chan_level(slice_RF, channel_RF, WRAPVAL/2);
    pwm_set_enabled(slice_RF, false);
    
    pwm_set_clkdiv(slice_RB, MAXSPEED);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_RB, WRAPVAL);      /// setting the Wrap time to limit max speed
    pwm_set_chan_level(slice_RB, channel_RB, WRAPVAL/2);
    pwm_set_enabled(slice_RB, false);
}

// set speed 0 is stop, sign is negative for reverse and smaller is faster
void set_speed(int8_t speed_lf, int8_t speed_rf, int8_t speed_lb, int8_t speed_rb) {
	
	if (speed_lf == 0) {
		pwm_set_enabled(slice_LF, false);
	} else {
		pwm_set_enabled(slice_LF, true);
	}
	
	if (speed_lb == 0) {
		pwm_set_enabled(slice_LB, false);
	} else {
		pwm_set_enabled(slice_LB, true);
	}
	
	if (speed_rf == 0) {
		pwm_set_enabled(slice_RF, false);
	} else {
		pwm_set_enabled(slice_RF, true);
	}
	
	if (speed_rb == 0) {
		pwm_set_enabled(slice_RB, false);
	} else {
		pwm_set_enabled(slice_RB, true);
	}
	
	// Set rotation direction; left side is inverted
	gpio_put(LFD, (speed_lf < 0) );
	gpio_put(RFD, (speed_rf > 0) );
	gpio_put(LBD, (speed_lb < 0) );
	gpio_put(RBD, (speed_rb > 0) );
	
	// set clock divider
	pwm_set_clkdiv(slice_LF, (speed_lf && 127));
	pwm_set_clkdiv(slice_RF, (speed_rf && 127));
	pwm_set_clkdiv(slice_LB, (speed_lb && 127));
	pwm_set_clkdiv(slice_RB, (speed_rb && 127));
}

void lfMotor(){
	set_speed(HIGHSPEED,0,0,0);
	}
	
void rfMotor(){
	set_speed(0,HIGHSPEED,0,0);
	}
	
void lbMotor(){
	set_speed(0,0,HIGHSPEED,0);
	}
	
void rbMotor(){
	set_speed(0,0,0,HIGHSPEED);
	}

void driveForeward(){
	set_speed(-HIGHSPEED,-HIGHSPEED,-HIGHSPEED,-HIGHSPEED);
}

void driveBackward(){
	set_speed(HIGHSPEED,HIGHSPEED,HIGHSPEED,HIGHSPEED);
}

void rotateLeft(){
	set_speed(LOWSPEED,-LOWSPEED,LOWSPEED,-LOWSPEED);
}

void turnLeft() {
	set_speed(0,HIGHSPEED,0,HIGHSPEED);
	}

void rotateRight(){
	set_speed(-LOWSPEED,LOWSPEED,-LOWSPEED,LOWSPEED);
}

void turnRight() {
	set_speed(HIGHSPEED,0,HIGHSPEED,0);
	}
	
void driveRight() {
	set_speed(-HIGHSPEED,HIGHSPEED,HIGHSPEED,-HIGHSPEED);
	}

void driveLeft() {
	set_speed(HIGHSPEED,-HIGHSPEED,-HIGHSPEED,HIGHSPEED);
	}
	
void driveForewardRight() {
	set_speed(-HIGHSPEED,0,0,-HIGHSPEED);
	}

void driveForewardLeft() {
	set_speed(0,-HIGHSPEED,-HIGHSPEED,0);
	}
	
void driveBackwardRight() {
	set_speed(0,HIGHSPEED,HIGHSPEED,0);
	}

void driveBackwardLeft() {
	set_speed(HIGHSPEED,0,0,HIGHSPEED);
	}

void stop(){
	set_speed(0,0,0,0);
}

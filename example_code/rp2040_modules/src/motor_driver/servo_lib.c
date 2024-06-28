#include "servo_lib.h"

// servo pin
const uint PIN_OUT_A = 2;

// start, current and new positon
static int pos_A = 202;
static int start_pos_A = 202;
int new_pos_A = 0;

// pwm slice
static uint slice_A;
static uint channel_A;

// last called time 
static float timestamp = 0;

// isn't declared because not needed for example
void init_servo_at_pin();

// This method is called repeadedly for calculating the new sevo position.
// For smooth motion the sigmoid functon is used.
bool repeating_timer_callback(struct repeating_timer *t) {
    pos_A = start_pos_A + (new_pos_A - start_pos_A) * (0.5* (1+tanh(timestamp/2)));
    timestamp += 0.1;
    //printf("start_pos_A: %d , pos_A: %d , new_pos_A: %d\n",start_pos_A,pos_A,new_pos_A);
	pwm_set_chan_level(slice_A, channel_A, pos_A);
    
    // return true for contiouus repeat 
    return true;
}

static struct repeating_timer timer;

int servo_test() {
    gpio_set_function(PIN_OUT_A, GPIO_FUNC_PWM);  /// Set the pin 0 to be PWM
    slice_A   = pwm_gpio_to_slice_num(PIN_OUT_A);
	channel_A = pwm_gpio_to_channel(PIN_OUT_A);

    pwm_set_clkdiv(slice_A, 256.0f);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_A, 9804);      /// setting the Wrap time to 9764 (20 ms)
    pwm_set_enabled(slice_A, true);
    pwm_set_chan_level(slice_A, channel_A,202);
    
    while (1) {
		
        // read new position
		printf("set pos to: ");
		scanf(" %d ", &new_pos_A);
		
        // let run for approximatly 80 ms 
		cancel_repeating_timer(&timer);
		timestamp = -4;
		start_pos_A = pos_A;
		
        // start the timer
		printf("new_pos %d, pos %d\n",new_pos_A,start_pos_A);
		add_repeating_timer_ms(-10, repeating_timer_callback, NULL, &timer);
		sleep_ms(100);
		//printf("start_pos_A: %d , pos_A: %d , new_pos_A: %d\n",start_pos_A,pos_A,new_pos_A);
		
    }
    return 0;
}

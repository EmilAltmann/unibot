#include "servo_lib.h"

static struct servo_inst servo_list[26];
static uint8_t servo_cnt = 0;
static uint8_t servo_lib_inited = 0;

static struct repeating_timer timer;


// This method is called repeadedly for calculating the new sevo position.
// For smooth motion the sigmoid functon is used.
bool repeating_timer_callback(struct repeating_timer *t) {
    
    for (int i = 0; i < servo_cnt; i++) {
        // only run if more than one step away
        if (servo_list[i].timestamp < 4) {
            servo_list[i].current_pos = servo_list[i].start_pos + (servo_list[i].new_pos - servo_list[i].start_pos) * (0.5* (1+tanh(servo_list[i].timestamp/2)));
            servo_list[i].timestamp += 0.1;
            // printf("start_pos_A: %d , pos_A: %d , new_pos_A: %d, time: %f\n",servo_list[i].start_pos,servo_list[i].current_pos,servo_list[i].new_pos,servo_list[i].timestamp);
            pwm_set_chan_level(servo_list[i].slice, servo_list[i].channel, servo_list[i].current_pos);
        } else {
            // update new pos to follwing list and reset time
            servo_list[i].start_pos = servo_list[i].current_pos;
            servo_list[i].new_pos = servo_list[i].following_pos;
            servo_list[i].timestamp = -4;
        }
    }
    
    // return true for contiouus repeat 
    return true;
}

// add a new servo to handler
void add_servo_at_pin(uint8_t pin,uint16_t init_pos) {

    // start timer once
    if (!servo_lib_inited) {
        add_repeating_timer_ms(-10, repeating_timer_callback, NULL, &timer);
        servo_lib_inited = 1;
    }

    struct servo_inst inst; 

    inst.pin = pin;

    gpio_set_function(pin, GPIO_FUNC_PWM);  /// Set the pin 0 to be PWM
    inst.slice   = pwm_gpio_to_slice_num(pin);
	inst.channel = pwm_gpio_to_channel(pin);

    pwm_set_clkdiv(inst.slice, 256.0f);  /// Setting the divider to slow down the clock
    pwm_set_wrap(inst.slice, 9804);      /// setting the Wrap time to 9764 (20 ms)
    pwm_set_enabled(inst.slice, true);

    inst.start_pos = init_pos;
    inst.new_pos = init_pos; // set to min
    inst.following_pos = init_pos; // set to min

    servo_list[servo_cnt++] = inst; // save and increment servo count;
}

void set_servo_to_pos(uint8_t pin,int pos) {
    // printf("currently %d servos\n", servo_cnt);
    for (int i = 0; i < servo_cnt; i++) {
        // printf("currently servo pin is %d looking for %d\n", servo_list[i].pin,pin);
        if (servo_list[i].pin == pin) {
            // printf("set servo %d to pos %d\n", pin,pos);
            servo_list[i].following_pos = pos;
            return;
        }
    }
}


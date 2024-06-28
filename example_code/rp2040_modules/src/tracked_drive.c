#include "tracked_drive.h"

void start_tracked_drive() {
    stdio_init_all();
    
    // init motor drivers
    init_l298n();
    // int rgb sensor
    init_tcs34725();
    // init ws2812a rgb matrix
    rgb_8x8_matrix_init(RGB_PIN);
    // init dual seven segment display
    struct pio_inst shifreg_inst = shiftreg_init(LATCH_PIN,CLOCK_PIN,DATA_PIN);

    // init servos

    // pwm slice and channels
    uint slice_pitch;
    uint channel_pitch;
    uint slice_yaw;
    uint channel_yaw;

    // set pindir for pwm
    gpio_set_function(PITCH_PIN, GPIO_FUNC_PWM);
    gpio_set_function(YAW_PIN, GPIO_FUNC_PWM);

    // determen slice and cahnnel
    slice_pitch   = pwm_gpio_to_slice_num(PITCH_PIN);
    slice_yaw   = pwm_gpio_to_slice_num(YAW_PIN);
	channel_pitch = pwm_gpio_to_channel(PITCH_PIN);
	channel_yaw = pwm_gpio_to_channel(YAW_PIN);

    pwm_set_clkdiv(slice_pitch, 256.0f);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_pitch, 9804);      /// setting the Wrap time to 9764 (20 ms)
    pwm_set_clkdiv(slice_yaw, 256.0f);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_yaw, 9804);      /// setting the Wrap time to 9764 (20 ms)

    // set pitch to center and enable
    pwm_set_chan_level(slice_pitch, channel_pitch,900);
    pwm_set_enabled(slice_pitch, true);

    // set yaw to center and enable
    pwm_set_chan_level(slice_yaw, channel_yaw,900);
    pwm_set_enabled(slice_yaw, true);

    uint16_t color_data[16];

    uint8_t shiftreg_alive = 0;

    while (1) {

        // measure the rgb values beneath the robot and display them over the 8x8 rgb matrix
        sample_tcs34725(color_data);

        //clear rgb matrix
        rgb_8x8_matrix_clear();

        //draw updated colors
        rgb_8x8_matrix_square(0,0,7,1,compute_color(color_data,0));
        rgb_8x8_matrix_square(0,3,7,4,compute_color(color_data,1));
        rgb_8x8_matrix_square(0,6,7,7,compute_color(color_data,2));

        rgb_8x8_matrix_update();

        sleep_ms(25);



        // this code count from 0 to 99 on the seven segment display
        shiftreg_send(int2seven[shiftreg_alive%10]|int2seven[shiftreg_alive/10]<<8,shifreg_inst);
        if (shiftreg_alive >= 99) {
            shiftreg_alive = 0;
        } else {
            shiftreg_alive++;
        }
    }

}

// extract the color data from sensor no x and create rgb value for ws2812a leds
uint32_t compute_color(uint16_t color_data[],uint8_t sensor) {
    return (color_data[0+5*sensor]&0xff00)<<8
        | (color_data[1+5*sensor]&0xff00)<<16
        | (color_data[2+5*sensor]&0xff00);
}
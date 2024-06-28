#include "hy_srf05.h"

struct ultrasonic_inst init_hy_srf05(uint8_t echo_pin, uint8_t trig_pin) {
	
	struct ultrasonic_inst instance;
	instance.trig_pin = trig_pin;
	instance.echo_pin = echo_pin;

	// init gpio
	gpio_init(trig_pin);
	gpio_set_dir(trig_pin, GPIO_OUT);
	gpio_put(trig_pin, 0);
	
	gpio_init(echo_pin);
	gpio_set_dir(echo_pin, GPIO_IN);
	gpio_pull_down(echo_pin);
	
	return instance;
}

// take one measurement in cm
uint16_t sample_hy_srf05(struct ultrasonic_inst instance) {

	uint64_t timestamp_start;
	uint64_t timestamp_end;
	uint64_t pulse_duration;
	uint16_t distance;

	// send trigger pulse
	gpio_put(instance.trig_pin, 1);
	sleep_us(10);
	gpio_put(instance.trig_pin, 0);
	
	// messure time of the return sinal
	while (gpio_get(instance.echo_pin) == 0) {
		timestamp_start = time_us_64();
	}
	while (gpio_get(instance.echo_pin) == 1) {
		timestamp_end = time_us_64();
	}
	
	// calculate distance
	// the timestamp of the mc is 64 bit in us so a overflow accures after many years ;-)
	pulse_duration = timestamp_end - timestamp_start;
	distance = pulse_duration * 17165 / 1000000;

	return distance;
}

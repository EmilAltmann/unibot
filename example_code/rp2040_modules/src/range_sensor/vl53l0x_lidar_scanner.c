#include "vl53l0x_lidar_scanner.h"

// both sensors need to be readressed:
// xshut_x is the enable pin
// address_sensor_x is the new adress
// servo_pin is the PWM signal pin to the servo
void init_vl53l0x_lidar_scanner(uint8_t xshut_sensor_a,
								uint8_t xshut_sensor_b,
								uint8_t address_sensor_a,
								uint8_t address_sensor_b,
								uint8_t servo_pin) {
	// debug is defined in "vl53l0x.h"
	if (VL53L0X_DEBUG) printf("Start init vl53l0x lidar scanner.\n");
	
	// int i2c bus 0
	init_i2c_0();

	// disable both sensors
	gpio_init(xshut_sensor_a);
	gpio_set_dir(xshut_sensor_a, GPIO_OUT);
	gpio_put(xshut_sensor_a, false);
	
	gpio_init(xshut_sensor_b);
	gpio_set_dir(xshut_sensor_b, GPIO_OUT);
	gpio_put(xshut_sensor_b, false);
	
	if (VL53L0X_DEBUG) printf("try to change address\n");
	
	uint8_t rxdata;
	int ret;
	
	// enable sensor a and readdress it
	gpio_put(xshut_sensor_a, true);
	gpio_put(xshut_sensor_b, false);
	
	ret = i2c_read_blocking(VL53LXX_I2C, VL53L0X_STANDARD_ADDRESS, &rxdata, 1, false);
	if (VL53L0X_DEBUG) printf("test reading before a readdressing returned %d\n", ret);

	if (ret >= 0) {
		if (VL53L0X_DEBUG) printf("sensor a has adress 0x29 now changing to %x\n",address_sensor_a);
		sleep_ms(10);
		vl53l0x_change_address(VL53L0X_STANDARD_ADDRESS, address_sensor_a);
		sleep_ms(10);
		if (VL53L0X_DEBUG) printf("start initing a under new address\n");
		init_vl53l0x(address_sensor_a ,0);
	}
	
	if (VL53L0X_DEBUG) ret = i2c_read_blocking(VL53LXX_I2C, address_sensor_a, &rxdata, 1, false);
	if (VL53L0X_DEBUG) printf("test reading after a readdressing returned %d\n", ret);
	
	// enable sensor b and readdress it

	//~ gpio_put(xshut_sensor_a, false); // don't do this because it will reset the sensor
	gpio_put(xshut_sensor_b, true);
	
	ret = i2c_read_blocking(VL53LXX_I2C, VL53L0X_STANDARD_ADDRESS, &rxdata, 1, false);
	if (VL53L0X_DEBUG) printf("test reading before b readdressing returned %d\n", ret);
	
	if (ret >= 0) {
		if (VL53L0X_DEBUG) printf("sensor b has adress 0x29 now changing to %x\n",address_sensor_b);
		sleep_ms(10);
		vl53l0x_change_address(VL53L0X_STANDARD_ADDRESS, address_sensor_b);
		sleep_ms(10);
		if (VL53L0X_DEBUG) printf("start initing a under new address\n");
		init_vl53l0x(address_sensor_b ,0);
	}
	
	
	if (VL53L0X_DEBUG) ret = i2c_read_blocking(VL53LXX_I2C, address_sensor_b, &rxdata, 1, false);
	if (VL53L0X_DEBUG) printf("test reading after b readdressing returned %d\n", ret);
	
	if (VL53L0X_DEBUG) printf ("Sensor inited succsessfull ?!\n");
	
	// from this point on: never disable the two sensors, or you have to recall this method
	gpio_put(xshut_sensor_a, true);	
	gpio_put(xshut_sensor_b, true);


	//####################################################
	// scan the sourrunding by sweeping the servo and sampleing the distances to a 8x8 matrix

	uint16_t object_map[8][8];
	
	// configre servo pwm signal
	static uint slice_servo;
	static uint channel_servo;
	
	gpio_set_function(servo_pin, GPIO_FUNC_PWM);  /// Set the servo_pin to be PWM
    slice_servo   = pwm_gpio_to_slice_num(servo_pin);
	channel_servo = pwm_gpio_to_channel(servo_pin);

    pwm_set_clkdiv(slice_servo, 256.0f);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice_servo, 9804);      /// setting the Wrap time to 9764 (20 ms)
    pwm_set_enabled(slice_servo, true);
    pwm_set_chan_level(slice_servo, channel_servo,220);
	

	// scan, calculate and print...
	while (1) {
		
		for (uint8_t y = 0; y < 8; y++) {
				for (uint8_t x = 0; x < 8; x++) {
						object_map[y][x] = 0;
				}
		}
		
		for (uint16_t dir = 220; dir < 1200; dir += 10) {
			pwm_set_chan_level(slice_servo, channel_servo,dir);
			
			int dist_a = vl53l0x_read_distance(address_sensor_a);
			int dist_b = vl53l0x_read_distance(address_sensor_b);
			
			int x0 = dist_a * cos( dir / 0.082 *M_PI );
			int y0 = dist_a * sin( dir / 0.082 *M_PI);
			int x1 = dist_b * cos( (dir+180) / 0.082 *M_PI);
			int y1 = dist_b * sin( (dir+180) / 0.082 *M_PI);
			
			if (dist_a < 1200) {
				object_map[y0 / 300 + 3][x0 / 300 + 3]++;
			}
			if (dist_b < 1200) {
				object_map[y1 / 300 + 3][x1 / 300 + 3]++;
			}
			
			//printf("distances: [x:%d|y:%d], [x:%d|y:%d], [a:%d|b:%d], dir :%d \n",x0,y0,x1,y1,dist_a,dist_b,dir);
			
		}
		
		for (uint8_t y = 0; y < 8; y++) {
			printf("#===#===#===#===#===#===#===#===#\n");
				for (uint8_t x = 0; x < 8; x++) {
						printf("#%3d",object_map[y][x]);
				}
			printf("#\n");
		}
		printf("#===#===#===#===#===#===#===#===#\n");
		
	}
}

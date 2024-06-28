#include "ads1115.h"

// for more inputs https://github.com/ControlEverythingCommunity/ADS1115/blob/master/C/ADS1115_4Channel.c

void ads1115_init() {
	
	// init the i2c bus
	init_i2c_0();
	uint8_t data[8];
	
	// Select configuration register(0x01)
	// AINP = AIN0 and AINN = AIN1, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x85;
	data[3] = 0x83;
	data[4] = 0x80;
	data[5] = 0x00;
	data[6] = 0x7F;
	data[7] = 0xFF;
    reg_write(i2c_0, ADS1115_ADDR, 0x00, &data[0], 8);
    reg_write(i2c_0, ADS1115_ADDR + 1, 0x00, &data[0], 8);
}

uint16_t ads1115_sample(uint8_t port) {
	uint8_t data[2];
	
	// Select configuration register(0x01)
	// AINP = AIN0 and AINN = AIN1, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	data[0] = 0x44 + (port % 4)*0x10 ;
	data[1] = 0x83;
    reg_write(i2c_0, ADS1115_ADDR + ((port >= 4)?1:0), 0x01, &data[0], 2);
    
    //printf("read from port %x with reg %x%x ",ADS1115_ADDR + ((port >= 4)?1:0),data[0],data[1]);
	
	uint16_t value = 0;
	
	// uncomment for averaging the samples
	//~ for (int i = SAMPLE_CNT; i > 0; i--) {
		reg_read(i2c_0, ADS1115_ADDR + ((port >= 4)?1:0), 0x00, data, 2);
		value = (data[0] * 256 + data[1]);
	//~ }
	//~ value /= SAMPLE_CNT;
	return value;
}




void test_ads1115() {
 	while(1) {
		printf("\n\n\n\n\n\n\n\n\n\n");
		for (int i = 0; i<8; i++) {
			printf("Value of sensor %d is:%d\n",i,ads1115_sample(i));
			sleep_ms(40);
		}
		sleep_ms(240);
	}
}

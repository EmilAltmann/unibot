#include "qmc5883.h"

// I had serious problems interfacing with my sensor
// after some test only the configuration from keepworking was functional. 
// thanks to https://github.com/keepworking/Mecha_QMC5883

void init_qmc5883() {
	
	// init i2c_0
	init_i2c_0();
	
	// mag levels and rotation
	qmc5883_xMag = 0;
	qmc5883_yMag = 0;
	qmc5883_zMag = 0;
	qmc5883_azimuth = 0;
	
	uint8_t data[1];
	
	// set Set/Reset period
	data[0] == 0x01;
	reg_write(i2c_0, QMC5883_ADDR, 0x0B, &data[0], 1);

	/*
	OSR = 512
	Full Scale Range = 2G(Gauss)
	ODR = 100HZ
	set continuous measurement mode
	*/
	data[0] = (QMC5883_Mode_Continuous|QMC5883_ODR_100Hz|QMC5883_RNG_2G|QMC5883_OSR_512);
	reg_write(i2c_0, QMC5883_ADDR, 0x09, &data[0], 1);

	//printf("%x %d [%d|%d|%d|%d|%d|%d|%d|%d]\n", i,j, !!(data[0]&128),!!(data[0]&64),!!(data[0]&32),!!(data[0]&16),!!(data[0]&8),!!(data[0]&4),!!(data[0]&2),!!(data[0]&1));	
}

void reset_qmc5883(){
	uint8_t data[1];
	data[0] == 0x80;
	reg_write(i2c_0, QMC5883_ADDR, 0x0A, &data[0], 1);
}


float get_qmc5883_azimuth() {
	uint8_t data[6];
	reg_read(i2c_0, QMC5883_ADDR, 0x00, data, 6);
	
	qmc5883_xMag += (data[0] | data[1] << 8);
	qmc5883_yMag += (data[2] | data[3] << 8);
	qmc5883_zMag += (data[4] | data[5] << 8);
	qmc5883_xMag /= 2;
	qmc5883_yMag /= 2;
	qmc5883_zMag /= 2;
	
	float current_azimuth = atan2(qmc5883_yMag,qmc5883_xMag) * 180.0/M_PI;
	if (current_azimuth < 0) {
		current_azimuth += 360;
	}
	
	qmc5883_azimuth = (9 * qmc5883_azimuth + current_azimuth)/10;
	return qmc5883_azimuth;
}


void test_qmc5883() {
	// Output data to screen
	printf("\n\n\n");
	printf("Azimuth : %d \n", (uint16_t) get_qmc5883_azimuth());
	printf("Magnetic field in X-Axis : %d \n", qmc5883_xMag);
	printf("Magnetic field in Y-Axis : %d \n", qmc5883_yMag);
	printf("Magnetic field in Z-Axis : %d \n", qmc5883_zMag);
}

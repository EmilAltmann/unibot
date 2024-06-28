#include "adxl345.h"


void init_adxl345() {
	
	// int i2c_0
	init_i2c_0();
	
	uint8_t data[1]; 
	
	// Set bit 3 to 1 to enable measurement mode
	data[0] = 0x08;
	reg_write(i2c_0, ADXL345_ADDRESS, ADXL345_POWER_CTL, data, 1);
	// Set data format to full resolution, +/- 16g  
	data[0] = 0x0B;
	reg_write(i2c_0, ADXL345_ADDRESS, ADXL345_DATA_FORMAT, data, 1);
}


// xyz_accelation contains acceleration in xyz and roll, pitch and yaw
void get_acceleration(int16_t* xyz_acceleration, double* xyz_rotation) {
	
	uint8_t data[6]; 
	
	reg_read(i2c_0, ADXL345_ADDRESS, ADXL345_DATAX0, data, 6);
	xyz_acceleration[0] = (data[1]<<8) + data[0];
	xyz_acceleration[1] = (data[3]<<8) + data[2];
	xyz_acceleration[2] = (data[5]<<8) + data[4];
	xyz_rotation[0] = atan2( xyz_acceleration[1], sqrt( pow(xyz_acceleration[0],2) + pow(xyz_acceleration[2],2))) * (180 / M_PI);
	xyz_rotation[1] = atan2( xyz_acceleration[0], sqrt( pow(xyz_acceleration[1],2) + pow(xyz_acceleration[2],2))) * (180 / M_PI);
	xyz_rotation[2] = atan2( xyz_acceleration[2], sqrt( pow(xyz_acceleration[0],2) + pow(xyz_acceleration[1],2))) * (180 / M_PI);
}

void test_adxl345() {
	int16_t acceleration[3];
	double rotation[3];
	
    while(1) {
		get_acceleration(acceleration,rotation);
		printf("Acceleration x: %4d, y: %4d, z: %4d, pitch: %5.2f, yaw: %5.2f, roll: %5.2f\n",acceleration[0],acceleration[1],acceleration[2],rotation[0],rotation[1],rotation[2]);
		sleep_ms(250);
	} 	
}

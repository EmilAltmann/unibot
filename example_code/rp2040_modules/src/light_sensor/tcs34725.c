#include "tcs34725.h"

void reset_tcs34725() {

	// set all registers to default
	uint8_t data[1];
	data[0] == 0x00;
	reg_write(i2c_1, TCS34725_ADDR, 0x80, &data[0], 1);
	data[0] == 0xFF;

	reg_write(i2c_1, TCS34725_ADDR, 0x81, &data[0], 1);

	data[0] == 0xFF;
	reg_write(i2c_1, TCS34725_ADDR, 0x83, &data[0], 1);

	data[0] == 0x00;
	reg_write(i2c_1, TCS34725_ADDR, 0x84, &data[0], 1);
	reg_write(i2c_1, TCS34725_ADDR, 0x85, &data[0], 1);
	reg_write(i2c_1, TCS34725_ADDR, 0x86, &data[0], 1);
	reg_write(i2c_1, TCS34725_ADDR, 0x87, &data[0], 1);
	reg_write(i2c_1, TCS34725_ADDR, 0x8C, &data[0], 1);
	reg_write(i2c_1, TCS34725_ADDR, 0x8D, &data[0], 1);
	reg_write(i2c_1, TCS34725_ADDR, 0x8F, &data[0], 1);
}

// init the three sensors
void init_tcs34725() {

	// init i2c_1 bus. We use the bus1 bacuse of our switching.
	init_i2c_1();

	// Buffer to store raw reads
	uint8_t data[1];

	// iterate throw each sensor
	for (int i = 0; i<3; i++) {
		
		// configure the three clock lines, so only on is connected.  
		gpio_set_function(2 , (i==0)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
		gpio_set_function(14 , (i==1)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
		gpio_set_function(18, (i==2)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
		sleep_ms(10);

		// reset the selected sensor
		reset_tcs34725();

		// Select enable register(0x80)
		// Power ON, RGBC enable, wait time disable(0x03)
		data[0] == 0x03;
		reg_write(i2c_1, TCS34725_ADDR, 0x80, &data[0], 1);

		// Select ALS time register(0x81)
		// Atime = 700 ms(0x00)
		data[0] == 0x00;
		reg_write(i2c_1, TCS34725_ADDR, 0x81, &data[0], 1);

		// Select Wait Time register(0x83)
		// WTIME : 2.4ms(0xFF)
		data[0] == 0xFF;
		reg_write(i2c_1, TCS34725_ADDR, 0x83, &data[0], 1);

		// Select control register(0x8F)
		// AGAIN = 1x(0x00)
		data[0] == 0x00;
		reg_write(i2c_1, TCS34725_ADDR, 0x8F, &data[0], 1);
		
	}
}

// sample all three sensors, the input array should be 15 elements in size
// order is [r0,g0,b0,i0,l0,r1,g1,b1,i1,l1,r2,g2,b2,i2,l2]
void sample_tcs34725(uint16_t returnvalues[]){

	// Buffer to store raw reads
	uint8_t data[10];

	for (int i=0; i<3; i++) {
			
			// select the corresponding sensor
			gpio_set_function(2 , (i==0)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
			gpio_set_function(14 , (i==1)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
			gpio_set_function(18, (i==2)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
			sleep_ms(10);
		
			// Read 8 bytes of data from register(0x94)
			// cData lsb, cData msb, red lsb, red msb, green lsb, green msb, blue lsb, blue msb
			reg_read(i2c_1, TCS34725_ADDR, 0x94, data, 8);
			// Convert the data
			int cData = (data[1] * 256 + data[0]);
			int red = (data[3] * 256 + data[2]);
			int green = (data[5] * 256 + data[4]);
			int blue = (data[7] * 256 + data[6]);

			// Calculate luminance
			float luminance = (-0.32466) * (red) + (1.57837) * (green) + (-0.73191) * (blue);
			if(luminance < 0)
			{
				luminance = 0;
			}

			returnvalues[0+(i*5)] = red;
			returnvalues[1+(i*5)] = green;
			returnvalues[2+(i*5)] = blue;
			returnvalues[3+(i*5)] = cData;
			returnvalues[4+(i*5)] = luminance;
		}
}

// repeadetly sample the three sensors
void test_tcs34725(){
    
	// Buffer to store raw reads
	uint8_t data[10];
    
    while (1){

		// iterate throw each sensor and sample the color 
		for (int i=0; i<3; i++) {
			
			// select the corresponding sensor
			gpio_set_function(2 , (i==0)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
			gpio_set_function(14 , (i==1)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
			gpio_set_function(18, (i==2)?GPIO_FUNC_I2C:GPIO_FUNC_NULL);
			sleep_ms(10);
		
			// Read 8 bytes of data from register(0x94)
			// cData lsb, cData msb, red lsb, red msb, green lsb, green msb, blue lsb, blue msb
			reg_read(i2c_1, TCS34725_ADDR, 0x94, data, 8);
			// Convert the data
			int cData = (data[1] * 256 + data[0]);
			int red = (data[3] * 256 + data[2]);
			int green = (data[5] * 256 + data[4]);
			int blue = (data[7] * 256 + data[6]);

			// Calculate luminance
			float luminance = (-0.32466) * (red) + (1.57837) * (green) + (-0.73191) * (blue);
			if(luminance < 0)
			{
				luminance = 0;
			}

			// Output data to screen
			printf("\n---%d---\n",i);
			printf("Red color luminance : %d lux \n", red);
			printf("Green color luminance : %d lux \n", green);
			printf("Blue color luminance : %d lux \n", blue);
			printf("IR  luminance : %d lux \n", cData);
			printf("Ambient Light Luminance : %.2f lux \n", luminance);
			
		}
			// wait for 1sec and rerun 
			sleep_ms(1000);
	}
}

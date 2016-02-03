#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <errno.h>
#include <stdio.h>

#include "thermostats.h"
#include "CursorCntl.h"


int init_temp_sensor()
{

	printOK("Initializing Chip Enabled Pins\n");

	pinMode(CE_BOTTOM, OUTPUT);
	pinMode(CE_TOP, OUTPUT);

	printOK("Setting Chip Enabled Pins to High\n");

	digitalWrite(CE_BOTTOM, HIGH);
	digitalWrite(CE_TOP, HIGH);

	printOK("Initializing SPI Bus\n");

	temp_fd = wiringPiSPISetup (SPI_TEMP_CHANNEL, SPI_SPEED);
	if (temp_fd < 0)
	{
		printError("Could not Initialize SPI Bus");
	}

	return temp_fd;


}

float get_temp(sensor_t sensor)
{
	unsigned char buffer[TEMP_BUFFER_SIZE];
	int raw_temp_data;
	float temperature;
	int sensorWPin;

	switch (sensor)
	{
		case TOP_SENSOR:
		{
			sensorWPin = CE_TOP;
			break;
		}
		case BOTTOM_SENSOR:
		{
			sensorWPin = CE_BOTTOM;
			break;
		}
	}

	digitalWrite(sensorWPin, LOW);

	buffer[0] = 0x00;
	buffer[1] = 0x00;
	raw_temp_data = 0x0000;

	wiringPiSPIDataRW(SPI_TEMP_CHANNEL,buffer, TEMP_BUFFER_SIZE);
	
	raw_temp_data = 0x0FFF & ((buffer[0] << 5) + (buffer[1]>>3));

	temperature = ((raw_temp_data * .25) * 9/5) + 32;

	digitalWrite(sensorWPin, HIGH);

	return temperature;

}
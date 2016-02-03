///////////////////////////////////////////////// THERMOSTATS_H ////////////////////////////////////
/*
	Created BY: Sergio Coronado 
*/
#ifndef THERMOSTATS_H
#define THERMOSTATS_H 

#define CE_BOTTOM (21)
#define CE_TOP (22)
#define SPI_TEMP_CHANNEL (1)
#define SPI_SPEED (4300000)
#define TEMP_BUFFER_SIZE (2)

typedef enum temp_sensors sensor_t;
enum temp_sensors 
{
	TOP_SENSOR,
	BOTTOM_SENSOR
};

int temp_fd;

int init_temp_sensor();

float get_temp(sensor_t sensor);

int close_temp_sensor();


#endif



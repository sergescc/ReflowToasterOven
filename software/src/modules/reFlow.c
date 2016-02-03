#include <stdio.h>
#include <wiringPi.h>
#include <errno.h>
#include <pthread.h>

#include "CursorCntl.h"
#include "thermostats.h"
#include "heaters.h"


#define WELCOME_X(a) ((2*a)/10)
#define WELCOME_Y(b) (b/3)
#define TEMP_READING_X(a) ((8*a)/10)
#define TEMP_READING_Y (1)
#define TOP_X (0)
#define TOP_Y (1)
#define sleep_sec 	(1000 * 1000)
#define sleep_msec	(1000)

int i;
int last_state;
int lights[4];







int main (int argc, char ** argv)
{
	i = 0;

	int new_state;
	int rotary_a;
	int rotary_b;
	int rotary_c;
	int delta;

	

	float temperature;

	struct winsize w;

	getWinSize(&w);
	
	clearPAGE();

	gotoXY(WELCOME_X(w.ws_col),WELCOME_Y(w.ws_row));

	setColor(YELLOW);

	printf("Welcome to reFlow 0.1\n");

	usleep(3*sleep_sec);

	setColor(RESET);

	gotoXY(TOP_X,TOP_Y);

	printOK("Initializing GPIO helper\n");

	wiringPiSetup ();

	if ( init_temp_sensor() < 0)
	{
		gotoXY(WELCOME_X(w.ws_col),WELCOME_Y(w.ws_row));
		printf("\tError Initializing Sensors ERROR: %d\n", errno);
		return 0;
	}

	usleep(1*sleep_sec);

	clearPAGE();

	
	fflush(stdout);


	lights[0] = TOP_HALF;
	lights[1] = TOP_FULL;
	lights[2] = BOTTOM_HALF;
	lights[3] = BOTTOM_FULL;


	pinMode(TOP_HALF, OUTPUT);
	pinMode(TOP_FULL, OUTPUT);
	pinMode(BOTTOM_HALF, OUTPUT);
	pinMode(BOTTOM_FULL, OUTPUT);

	printOK("Setting Chip Enabled Pins to High\n");

	digitalWrite(TOP_FULL, LOW);
	digitalWrite(TOP_HALF, HIGH);
	digitalWrite(BOTTOM_HALF, LOW);
	digitalWrite(BOTTOM_FULL, LOW);



	while (1)
	{
		// gotoXY(TEMP_READING_X(w.ws_col),TEMP_READING_Y);
		// temperature = get_temp(TOP_SENSOR);
		// setColor(CYAN);
		// clearEOL();
		// printf("Top:    %4.2f%cF", temperature, DEGREES_CHAR);
		
		// gotoXY(TEMP_READING_X(w.ws_col),TEMP_READING_Y + 1);
		// temperature = get_temp(BOTTOM_SENSOR);
		// setColor(CYAN);
		// clearEOL();
		// printf("Bottom: %4.2f%cF", temperature, DEGREES_CHAR);
		// fflush(stdout);

	

		if (digitalRead(4))
		{
			rotary_a = 1;
		}
		else
		{
			rotary_a = 0;
		}

		if(digitalRead(5))
		{
			rotary_b = 1;
		}
		else
		{
			rotary_b = 0;
		}


		rotary_c = rotary_a ^ rotary_b;

		new_state = (rotary_a << 2) + (rotary_b << 1) + rotary_c;

		delta = (new_state - last_state) % 4;

		last_state = new_state;

		if (delta == 1)
		{
			printf("Scrolled Down\n");
			digitalWrite(lights[i], LOW);
			i++;
			if (i > 3) i = 0;
			digitalWrite(lights[i], HIGH);

		}
		else if (delta == 3)
		{
			printf("Scrolled Up\n");
			digitalWrite(lights[i], LOW);
			i--;
			if (i < 0) i = 3;
			digitalWrite(lights[i], HIGH);
		}
		
	}

    return 0;
}
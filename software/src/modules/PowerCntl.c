#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define PWR_GPIO 7

void TimeStamp ( char timeStamp[])
{
	time_t ltime;
	ltime = time(NULL);
	strcpy(timeStamp, asctime( localtime(&ltime)));
}

void turnOff (void)
{
	printf("In Interrupt\n");
	int logFile;
	char log_buffer[100];
	char timeStamp[20];
	logFile = open("/var/PowerCntl/on_off.log", O_APPEND || O_CREAT || O_WRONLY, S_IRWXU);
	if (logFile > 0)
	{
		TimeStamp(timeStamp);
		sprintf(log_buffer, "%s Powered Off by GPIO\n", timeStamp);
		write(logFile, log_buffer, 100);
		close(logFile);
	}
	else
	{
		printf("could not create log file\n");
	}
	pinMode( PWR_GPIO, OUTPUT);
	digitalWrite(PWR_GPIO, HIGH);

	// Clean up 


	digitalWrite(PWR_GPIO, LOW);
	system("shutdown -P now");

}

int main (int argc, char ** argv)
{
	printf("Initiated Program");
	char timeStamp[20];
	int logFile;
	char log_buffer[100];
	wiringPiSetup();

	pinMode( PWR_GPIO , INPUT);

	pullUpDnControl(PWR_GPIO, PUD_UP);
	printf("Initiated Program\n");

	logFile = open("/var/PowerCntl/on_off.log", O_APPEND ||  O_WRONLY || O_CREAT, S_IRWXU);

	if (logFile > 0)
	{
		printf("OpenedFile to log power on_off\n");
		sprintf(log_buffer, "Powered ON\n");
		write(logFile, log_buffer, 100);
		close(logFile);
	}
	else
	{
		printf("could not create log file\n");
	}

	wiringPiISR( PWR_GPIO , INT_EDGE_FALLING, &turnOff);

	while(1)
	{
		usleep(1000*50000);
	}

	return 0;

}
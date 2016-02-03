#ifndef CURSOR_CONTROL
#define CURSOR_CONTROL

//#define DEBUG

#include <unistd.h>
#include <sys/ioctl.h>

#define DEGREES_CHAR (176)

typedef enum {
	BLACK,
	BOLDBLACK, 
	RED,
	ORANGE,
	GREEN,
	BOLDGRAY,
	YELLOW,
	BOLDGRAY2,
	BLUE,
	BOLDSTANDARD,
	MAGENTA,
	PURPLE,
	CYAN,
	WHITE,
	BOLDWHITE,
	RESET
}Colors;

void setColor( Colors color);

void gotoXY(int X, int Y);

void saveCursor();

void clearEOL();

void clearPAGE();

void recallCursor();

void clearBelowLine(int line);

void clearLine(int line);

void printError(char * message);

void printOK(char * message);

void printWarning(char * message);

void printPrompt(char * message);

void getWinSize(struct winsize * w);

void moveDown();

void moveUp();

void moveRight();

void moveLeft();

void moveXY(int x, int y);

#endif

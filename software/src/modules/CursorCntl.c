#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CursorCntl.h"

void setColor(Colors color)
{
	switch (color)
	{
		case BLACK :
		{
			printf("\033[0;30m");
			break;
		}
		case BOLDBLACK :
		{
			printf("\033[1;30[m");
		} 
		case RED :
		{
			printf("\033[0;31m");
			break;
		}
		case ORANGE : 
		{
			printf("\033[1;31m");
			break;
		}
		case GREEN :
		{
			printf("\033[0;32m");
			break;
		}
		case BOLDGRAY :
		{
			printf("\033[1;32m");
			break;
		}
		case YELLOW :
		{
			printf("\033[0;33m");
			break;
		}
		case BOLDGRAY2 :
		{
			printf("\033[1;33m");
			break;
		}
		case BLUE :
		{
			printf("\033[0;34m");
			break;
		}
		case BOLDSTANDARD :
		{
			printf("\033[1;34m");
			break;	
		}
		case MAGENTA :
		{
			printf("\033[0;35m");
			break;
		}
		case PURPLE :
		{
			printf("\033[1;35m");
		}
		case CYAN :
		{
			printf("\033[0;36m");
			break;
		}
		case WHITE :
		{
			printf("\033[0;37m");
			break;
		}
		case BOLDWHITE :
		{
			printf("\033[1;37m");
			break;
		}
		case RESET :
		{
			printf("\033[m");
			break;
		}
	}
}

void gotoXY(int X, int Y)
{
	#ifdef DEBUG
		printf("\n");
	#else
		printf("\033[%d;%dH", Y, X);
	#endif
}

void saveCursor()
{
	printf ("\033[s");
}

void clearEOL()
{
	#ifdef DEBUG
		printf("\n");
	#else
		printf ("\033[K");
	#endif
}

void clearPAGE()
{
#ifndef DEBUG
	printf ("\033[2J");
#endif
}

void recallCursor()
{
	printf ("\033[u");
}
void clearBelowLine(int line)
{
	printf ("\033[J");
}

void clearLine(int line)
{
#ifndef DEBUG
	printf ("\033[s\033[%d;0H\033[2K\033[u", line);
#endif
}

void printError(char * message)
{
	printf("[ ");
	setColor(RED);
	printf("ERROR ");
	setColor(RESET);
	printf("] %s", message);
}

void printOK(char * message)
{
	printf("[ ");
	setColor(GREEN);
	printf("OK ");
	setColor(RESET);
	printf("] %s", message);
}

void printWarning(char * message)
{
	printf("[ ");
	setColor(YELLOW);
	printf("NOTE ");
	setColor(RESET);
	printf("] %s", message);
}


void printPrompt(char * message)
{
	setColor(BOLDGRAY);
	printf(" %s > ", message);
	setColor(RESET);
}

//////////////////////// getWinSize //////////////////
/*
	Description assigns window size structure of ioctl
 	
struct winsize
{
  unsigned short ws_row;	// rows, in characters 
  unsigned short ws_col;	// columns, in characters 
  unsigned short ws_xpixel;	// horizontal size, pixels 
  unsigned short ws_ypixel;	// vertical size, pixels 
};


*/

void getWinSize(struct winsize * w)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
}

void moveDown()
{
	printf("\033[B");
}

void moveUp()
{
	printf("\033[A");
}

void moveRight()
{
	printf("\033[C");
}

void moveLeft()
{
	printf("\033[D");
}

void moveXY(int x, int y)
{
	int i;

	if ( x < 0 )
	{
		if (y < 0)
		{
			for ( i = y ; i < 0; i++)
			{
				moveDown();
			}
		}
		else
		{
			for ( i = 0 ; i < y; i ++)
			{
				moveUp();
			}
		}

		for ( i = x ; i < 0; i ++)
		{
			moveLeft();
		}
	}
	else
	{
		if (y < 0)
		{
			for ( i = y ; i < 0; i++)
			{
				moveDown();
			}
		}
		else
		{
			for ( i = 0 ; i < y; i ++)
			{
				moveUp();
			}
		}

		for ( i = 0 ; i < y; i ++)
		{
			moveRight();
		}
	}
}
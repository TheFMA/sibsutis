#include "myTerm.h"
#include <iostream>

using namespace std;

int mt_clrscr()
{
	printf("\E[H\E[2J");
	return 0;
}

int mt_gotoXY(int x, int y)
{
	int rows, cols;

	mt_getscreensize(&rows, &cols);
	if ((y < rows) && (x < cols) && (x >= 0) && (y >= 0)) {
		printf("\E[%d;%dH", y, x);
		return 0;
	}
	else
		return -1;
}

int mt_getscreensize(int *rows, int *cols)
{
	struct winsize w;

	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
		*rows = w.ws_row;
		*cols = w.ws_col;
		return 0;
	}
	else
		return -1;
}

int mt_setfgcolor(enum colors color)
{
	switch (color) {
		case black:
			printf("\E[30m");
			break;
		case red:
			printf("\E[31m");
			break;
		case green:
			printf("\E[32m");
			break;
		case brown:
			printf("\E[33m");
			break;	
		case blue:
			printf("\E[34m");
			break;
		case magenta:
			printf("\E[35m");
			break;
		case cyan:
			printf("\E[36m");
			break;
		case light_blue:
			printf("\E[37m");
			break;
		case _default:
			printf("\E[39m");
			break;
		default:
			return -1;
	}
	return 0;
}

int mt_setbgcolor(enum colors color)
{
	switch (color) {
		case black:
			printf("\E[40m");
			break;
		case red:
			printf("\E[41m");
			break;
		case green:
			printf("\E[42m");
			break;
		case brown:
			printf("\E[43m");
			break;
		case blue:
			printf("\E[44m");
			break;
		case magenta:
			printf("\E[45m");
			break;
		case cyan:
			printf("\E[46m");
			break;
		case light_blue:
			printf("\E[47m");
			break;
		case _default:
			printf("\E[49m");
			break;
		default:
			return -1;
	}
	return 0;
}

int main()
{
    mt_clrscr();
    printf("111111111111111111111111111111111111111111");
    printf("\n");
    mt_gotoXY(4,4);
    mt_setbgcolor(blue);
    mt_setfgcolor(green);
    printf("How to live without TikTok");
    printf("\n");
    return 0;
}
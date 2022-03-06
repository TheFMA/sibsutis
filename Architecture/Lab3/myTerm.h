#ifndef __GUARD_MYTERM
#define __GUARD_MYTERM

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

enum colors {
	black,
	red,
	green,
	brown,
	blue,
	magenta,
	cyan,
	light_blue,
	_default
};

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);

#endif /* __GUARD_MYTERM */
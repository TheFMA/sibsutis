#ifndef OUTPUT_H
#define OUTPUT_H

#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

#define OUT_OF_MEMORY_BOUNDS 1
#define WRONG_FLAG 2
#define INCORRECT_COMMAND 3
#define IGNORE_TIMER 4
#define WRONG_ACCUMULATOR 5

using namespace std;

enum colors {
    Dark,
    Red,
    Green,
    Yellow,
    Blue,
    Black,
    Cyan,
    White,
    Standart = 9
};
enum keys {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    LOAD,
    SAVE,
    RESET,
    RUN,
    STEP,
    ENTER,
    F5,
    F6,
    EXIT,
    ERROR
};
extern int cell;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit();
int sc_regSet(int regist, int value);
int sc_regGet(int regist, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
bool check_command(int command);

int mt_clrscr();
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors colour);
int mt_setbgcolor(enum colors colour);

#endif
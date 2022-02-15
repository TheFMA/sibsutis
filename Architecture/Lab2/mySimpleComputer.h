#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define memory 100
#define OUT_OF_MEMORY -1
#define GET_VALUE(flag, k) (flag >> (k - 1)) & 0x1
#define IN_EDINUA(flag, k) flag = flag | (1 << (k - 1))
#define IN_NULL(flag, k) flag = flag & (~(1 << (k - 1)))
#define NUM_COMMANDS 38

int flag;
int simplememory[memory];
const int commands[NUM_COMMANDS] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43,
                                    0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
                                    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76};
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
int sc_regInit(void);
int sc_regSet(int register1, int value);
int sc_regGet(int register1, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);
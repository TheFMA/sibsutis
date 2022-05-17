#pragma once
#define MEMORY_SIZE 100

//названия флагов в регистре
#define REG_OVERFLOW 0
#define REG_DEVISION_BY_ZERO 1
#define REG_OUT_OF_MEMORY_RANGE 2
#define REG_IGNORE_TACTS 3
#define REG_INVALID_COMMAND 4

class Register {
private:
    int flags;
public:
    Register();
    int set(int address, bool value);
    int get(int address, bool& value);
    int clear();
};

class Memory {
private:
    int memory[MEMORY_SIZE];
public:
    Register reg;
    Memory();
    int set(int address, int value);
    int get(int address, int &value);
    int save(char* filename);
    int load(char* filename);
    int reset();
};

int commandEncode(int command, int operand, int &value);
int commandDecode(int& command, int& operand, int value, Memory memory);
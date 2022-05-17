#pragma once
#include <memory.hpp>
#include <console.hpp>

#define OPER_PLUS 1
#define OPER_MINUS 2
#define OPER_MULTI 3
#define OPER_DIVISION 4

enum commands{  READ = 0x10, WRITE, 
                LOAD = 0x20, STORE, 
                ADD = 0x30, SUB, DIVIDE, MUL, 
                JUMP = 0x40, JNEG, JZ, HALT, 
                NOT = 0x51, AND, OR, XOR, JNS, JC, JNC, JP, JNP, CHL, SHR, RCL, RCR, 
                NEG, ADDC, SUBC, LOGLC, LOGRC, RCCL, RCCR, MOVA, MOVR, MOVCA, MOVCR};

class CPU{
private:
    int currentMemory = 0;
    int command = 0;
    int operand = 0;
    int accumulator = 0;
    int commandEncode(int command, int operand, int &value);
    int commandDecode(int& command, int& operand, int value);
public:
    int getCommand();
    int getOperand();
    int getCurrentMemory();
    void setCurrentMemory(int value, Memory& memory);
    void stepCurrentMemory(Memory& memory);
    int getAccumulator();
    void setAccumulator(int value);
    int CU(Memory& memory, Console console, bool& isDrawing);
    int ALU(int oper, int a, int b, Memory& memory);
    int fromDirectToAdditional(int a);
    int fromAdditionalToDirect(int a);
};
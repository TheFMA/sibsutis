#pragma once
#include <interface.hpp>
#include <cpu.hpp>

enum keys{L = 109, S = 116, R = 115, T = 117, I = 106, F5 = 1790, F6 = 5550, LEFT = 8203, RIGHT = 5627, UP = 475, DOWN = 3051};

class Keyboard{
private:
public:
    int readKeys(Console console, Interface &interface, Memory &memory, CPU& cpu, bool& isDrawing);
    int readStr(char buf[200]);
    int readHex();
    int readDec();
    int saveTermParam();
};
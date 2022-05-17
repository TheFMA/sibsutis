#pragma once
#include <memory.hpp>
#include <structs.hpp>
#include <bigChars.hpp>
#include <console.hpp>
#include <cpu.hpp>
#include <iostream>

class Interface{
private:
    Bounds memoryBox;
    Bounds accumulatorBox;
    Bounds counterBox;
    Bounds operationBox;
    Bounds flagBox;
    Bounds bigCharBox;
    Bounds tipBox;
    void printBeautifulHex(int value);
public:
    int bigChars[5];
    Interface(Memory memory, CPU cpu);
    int updateMemory(Console console, Memory memory, CPU cpu);
    int updateBigChars(Console console, Memory memory, CPU cpu);
    int updateAccumulator(Console console, CPU cpu);
    int updateInstructionCounter(Console console, CPU cpu);
    int updateOperation(Console console, CPU cpu);
    int updateFlags(Console console, Memory memory);
    int clearAndGoToAccumulatorBox(Console console);
    int clearAndGoToCounterBox(Console console);
    int drawBoxes(Console console);
    int drawInterface(Console console, Memory memory, CPU cpu);
    int addBigChars(Memory memory, CPU cpu);
    int printWhiteSpaces(int number);
};

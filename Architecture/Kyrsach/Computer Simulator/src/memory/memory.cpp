#include <iostream>
#include "memory.hpp"

using namespace std;

Register::Register(){
    flags = 0b01000;
}

int Register::set(int address, bool value){
    if (address >= sizeof(int) * 8) {
        return -1;
    }
    int mask = 1;
    mask <<= address;
    if (value) {
        flags |= mask;
    }
    else {
        mask = ~mask;
        flags &= mask;
    }
    return 0;
}

int Register::get(int address, bool& value){
    if (address >= sizeof(int) * 8) {
        return -1;
    }
    int mask = 1;
    mask <<= address;
    value = (flags & mask) >> address;

    return 0;
}

int Register::clear(){
    flags = 0;
    return 0;
}

Memory::Memory(){
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = i + 10 << 7;
    }
}

int Memory::set(int address, int value){
    if (address >= MEMORY_SIZE) {
        reg.set(REG_OUT_OF_MEMORY_RANGE, 1);
        return -1;
    }
    reg.set(REG_OUT_OF_MEMORY_RANGE, 0);
    memory[address] = value;
    return 0;
}

int Memory::get(int address, int &value){
    if (address >= MEMORY_SIZE) {
        reg.set(REG_OUT_OF_MEMORY_RANGE, 1);
        return -1;
    }
    reg.set(REG_OUT_OF_MEMORY_RANGE, 0);
    value = memory[address];
    return 0;
}

int Memory::reset(){
    for (int i = 0; i < 100; i++)
    {
        memory[i] = 0;
    }
    reg.clear();
    return 0;
}

int Memory::save(char* filename){
    FILE* f;
    f = fopen(filename, "wb");

    for(int i = 0; i < 100; i++){
        fwrite(&memory[i], sizeof(int), 1, f);
    }

    fclose(f);
    return 0;
}

int Memory::load(char* filename){
    FILE* f;

    f = fopen(filename, "rb");

    for(int i = 0; i < 100; i++){
        fread(&memory[i], sizeof(int), 1, f);
    }

    fclose(f);

    return 0;
}
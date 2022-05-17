#include <iostream>
#include <keyboard.hpp>
#include <cmath>
#include <termios.h>
#include <unistd.h>
#include <string>
using namespace std;

int Keyboard::readHex(){
    char buf[200];
    int numberOfSymbols = readStr(buf) - 2;
    int result = 0;
    string hexDigits = "0123456789abcdef";
    for(int i = 0; i <= numberOfSymbols; i++){
        int j = 0;
        while(hexDigits[j] != '\0'){
            if(buf[i] == hexDigits[j]){
                result += pow(16, numberOfSymbols - i) * j;
                break;
            }
            j++;
        }
        if(j == 17){
            return 0;
        }
    }
    return result;
}

int Keyboard::readStr(char buf[200]){
    for(int i = 0; i < 200; i++){
        buf[i] = 0;
    }
    return read(0, buf, 199);
}

int Keyboard::readKeys(Console console, Interface &interface, Memory &memory, CPU& cpu, bool& isDrawing){
    
    char buf[200];
    readStr(buf);

    int hash = 1;
    for(int i = 0; i < 200; i++){
        //Пропускаем enter
        if(buf[i] != 10){
            hash = (hash * (buf[i] + 1)) % 9973;
        }
    }

    bool isIgnore;
    memory.reg.get(REG_IGNORE_TACTS, isIgnore);
    if(!isIgnore){
        if(hash == R){
                    cout << "1";

            memory.reg.set(REG_IGNORE_TACTS, true);
        }
        return -1;
    }

    char fileName[] = "data.o";
    switch (hash)
    {
    case L:
        memory.load(fileName);
        cpu.setCurrentMemory(0, memory);
        break;
        
    case S:
        memory.save(fileName);
        break;

    case R:
        memory.reg.set(REG_IGNORE_TACTS, 0);
        break;

    case T:
        cpu.CU(memory, console, isDrawing);
        break;

    case I:
        memory.reset();
        memory.reg.set(REG_IGNORE_TACTS, true);
        cpu.setAccumulator(0);
        cpu.setCurrentMemory(0, memory);
        break;

    case F5:
        isDrawing = false;
        console.changeCanon();
        interface.clearAndGoToAccumulatorBox(console);
        cpu.setAccumulator(readHex());
        isDrawing = true;
        console.changeCanon();
        break;

    case F6:
        isDrawing = false;
        console.changeCanon();
        interface.clearAndGoToCounterBox(console);
        cpu.setCurrentMemory(readHex(), memory);
        isDrawing = true;
        console.changeCanon();
        break;

    case RIGHT:
        if(cpu.getCurrentMemory() % 10 < 9){
            cpu.setCurrentMemory(cpu.getCurrentMemory() + 1, memory);
        }
        break;

    case LEFT:
        if(cpu.getCurrentMemory() % 10 > 0){
            cpu.setCurrentMemory(cpu.getCurrentMemory() - 1, memory);
        }
        break;

    case UP:
        if(cpu.getCurrentMemory() > 9){
            cpu.setCurrentMemory(cpu.getCurrentMemory() - 10, memory);
        }
        break;

    case DOWN:
        if(cpu.getCurrentMemory() < 90){
            cpu.setCurrentMemory(cpu.getCurrentMemory() + 10, memory);
        }
        break;
    
    default:
        break;
    }

    return 1;
}
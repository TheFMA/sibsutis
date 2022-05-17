#include <interface.hpp>
#include <string>
using namespace std;

int Interface::printWhiteSpaces(int number){
    while (number > 0)
    {
        cout << " ";
        number--;
    }
    return 0;
}

int Interface::addBigChars(Memory memory, CPU cpu){
    int value;
    memory.get(cpu.getCurrentMemory(), value);
    if(!(1 << 14 & value)){
        bigChars[0] = 16;
    }
    else{
        bigChars[0] = 17;
    }
    for (int i = 4; i > 0; i--)
    {
        bigChars[i] = value % 16;
        value /= 16;
    }
    return 0;
}

Interface::Interface(Memory memory, CPU cpu){
    addBigChars(memory, cpu);
}

int Interface::updateAccumulator(Console console, CPU cpu){
    console.goTo(accumulatorBox.y + 1, accumulatorBox.x + 1);
    int accumulator = cpu.getAccumulator();
    int digits = 1, tmp = abs(accumulator);
    do{
        tmp /= 16;
        digits++;
    } while(tmp > 0);
    int center = accumulatorBox.width / 2 - 3;
    printWhiteSpaces(center);
    cout << hex << accumulator << dec;
    printWhiteSpaces(accumulatorBox.width - center - digits - 2);
    return 0;
}

int Interface::updateInstructionCounter(Console console, CPU cpu){
    console.goTo(counterBox.y + 1, counterBox.x + 1);
    int currentMemory = cpu.getCurrentMemory();
    int tmp = currentMemory, digits = 1;
    do{
        tmp /= 16;
        digits++;
    } while(tmp > 0);
    int center = counterBox.width / 2 - 2;
    printWhiteSpaces(center);
    cout << "+" << hex << currentMemory << dec;
    printWhiteSpaces(counterBox.width - center - digits - 2);
    return 0;
}

int Interface::updateOperation(Console console, CPU cpu){
    console.goTo(operationBox.y + 1, operationBox.x + 1);
    int command = cpu.getCommand();
    int operand = cpu.getOperand();

    int digits = 3, a = command, b = operand;
    do{
        a /= 10;
        digits++;
    } while(a > 0);
    do{
        b /= 10;
        digits++;
    } while(b > 0);
    int center = operationBox.width / 2 - 4;

    printWhiteSpaces(center);
    cout << hex << command << " : " << dec << operand;
    printWhiteSpaces(operationBox.width - center - digits - 2);
    return 0;
}

int Interface::updateFlags(Console console, Memory memory){
    console.goTo(flagBox.y + 1, flagBox.x + 1);
    int center = flagBox.width / 2 - 4;
    int countSymbols = 0;
    printWhiteSpaces(center);
    string flagNames = "OZMIC";
    bool currentReg;
    for(int i = 0; i < 5; i++){
        memory.reg.get(i, currentReg);
        if(currentReg){
            cout << flagNames[i] << " ";
            countSymbols += 2;
        }
    }
    printWhiteSpaces(flagBox.width - center - countSymbols - 2);
    return 0;
}

void Interface::printBeautifulHex(int value){
    int mask = 0b1111000000000000;
    while(mask > 0b1111){
        if(mask & value){
            break;
        }
        cout << "0";
        mask >>= 4;
    }
}

int Interface::updateMemory(Console console, Memory memory, CPU cpu){
    const int margin = 2;
    for(int i = 0; i < 10; i++){
        console.goTo(i + margin, margin);
        for(int j = 0; j < 10; j++){
            int value;
            memory.get(i * 10 + j, value);
            if(cpu.getCurrentMemory() % 10 == j && cpu.getCurrentMemory() / 10 == i){
                console.setBackgroundColor(white);
                console.setTextColor(black);
            } 
            if(1 << 14 & value){
                cout << " ";
            }
            else{
                cout << "+";
            }
            printBeautifulHex(value);
            cout << hex << value << dec;
            console.setBackgroundColor(original);
            console.setTextColor(original);
            if(j != 9){
                cout << " ";
            }
        }        
    }
    return 0;
}

int Interface::updateBigChars(Console console, Memory memory, CPU cpu){
    addBigChars(memory, cpu);
    for(int i = 0; i < 5; i++){
        BigChar currentSymbol(original, original, bigCharBox.x + i + 1 + i * 8, bigCharBox.y + 1);
        currentSymbol.setContent(bigChars[i]);
        console.printBigChar(currentSymbol, i < 4);
    }
    return 0;
}

int Interface::clearAndGoToAccumulatorBox(Console console){
    console.goTo(accumulatorBox.y + 1, accumulatorBox.x + 1);
    printWhiteSpaces(accumulatorBox.width - 2);
    console.goTo(accumulatorBox.y + 1, accumulatorBox.x + accumulatorBox.width / 2 - 2);
    return 1;
}

int Interface::clearAndGoToCounterBox(Console console){
    console.goTo(counterBox.y + 1, counterBox.x + 1);
    printWhiteSpaces(counterBox.width - 2);
    console.goTo(counterBox.y + 1, counterBox.x + counterBox.width / 2 - 2);
    return 1;
}

int Interface::drawBoxes(Console console){
    Bounds consoleSize;
    console.getSize(consoleSize);

    //Блок с памятью
    const int margin = 2;
    const int numberSize = 6;
    memoryBox = Bounds(1, 1, 61, 12);
    
    string title = "Memory";
    //Если ровно 10 элементов в строчке
    console.printBox(memoryBox, title);
    
    //Блок аккумулятор
    title = "accumulator";
    accumulatorBox = Bounds(memoryBox.width + 1, 1, consoleSize.width - memoryBox.width, 3);
    console.printBox(accumulatorBox, title);

    //Блок счётчик
    title = "instructionCounter";
    counterBox = Bounds(memoryBox.width + 1, 4, consoleSize.width - memoryBox.width, 3);
    console.printBox(counterBox, title);

    //Блок операций
    title = "operation";
    operationBox = Bounds(memoryBox.width + 1, 7, consoleSize.width - memoryBox.width, 3);
    console.printBox(operationBox, title);

    //Блок с флагами
    title = "flags";
    flagBox = Bounds(memoryBox.width + 1, 10, consoleSize.width - memoryBox.width, 3);
    console.printBox(flagBox, title);
    console.goTo(10, flagBox.x + flagBox.width / 2 - 3);

    //Блок с большими символами
    title  = "";
    bigCharBox = Bounds(1, memoryBox.height + 1, 46, 10);
    console.printBox(bigCharBox, title);

    //Блок-подсказка по управлению
    title = "Keys";
    tipBox = Bounds(bigCharBox.x + bigCharBox.width, bigCharBox.y, consoleSize.width - bigCharBox.width, bigCharBox.height);
    console.printBox(tipBox, title);
    console.goTo(tipBox.y + 1, tipBox.x + 1);
    cout << "l - load";
    printWhiteSpaces(tipBox.width - 10);
    console.goTo(tipBox.y + 2, tipBox.x + 1);
    cout << "s - save";
    printWhiteSpaces(tipBox.width - 10);
    console.goTo(tipBox.y + 3, tipBox.x + 1);
    cout << "r - run";
    printWhiteSpaces(tipBox.width - 9);
    console.goTo(tipBox.y + 4, tipBox.x + 1);
    cout << "t - step";
    printWhiteSpaces(tipBox.width - 10);
    console.goTo(tipBox.y + 5, tipBox.x + 1);
    cout << "i - reset";
    printWhiteSpaces(tipBox.width - 11);
    console.goTo(tipBox.y + 6, tipBox.x + 1);
    cout << "f5 - accumulator";
    printWhiteSpaces(tipBox.width - 18);
    console.goTo(tipBox.y + 7, tipBox.x + 1);
    cout << "f6 - instructionCounter";
    printWhiteSpaces(tipBox.width - 25);
    console.goTo(tipBox.y + 8, tipBox.x + 1);
    printWhiteSpaces(tipBox.width - 2);

    /*console.goTo(bigCharBox.y + bigCharBox.height, 0);
    printWhiteSpaces(consoleSize.width);
    console.goTo(bigCharBox.y + bigCharBox.height + 1, 0);
    printWhiteSpaces(consoleSize.width);*/

    return 0;
}

int Interface::drawInterface(Console console, Memory memory, CPU cpu){
    drawBoxes(console);
    updateBigChars(console, memory, cpu);
    updateAccumulator(console, cpu);
    updateInstructionCounter(console, cpu);
    updateOperation(console, cpu);
    updateFlags(console, memory);
    updateMemory(console, memory, cpu);
    return 0;
}
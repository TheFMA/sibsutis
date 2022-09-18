#include <loading.hpp>
#include <console.hpp>
#include <structs.hpp>
#include <unistd.h>
#include <iostream>

using namespace std;

void drawTitle(Console console){
    Bounds consoleSize;
    console.getSize(consoleSize);

    console.goTo(2, consoleSize.width / 2 - 17);
    cout << "████─████─█───█─████─█─█─███─███─████";
    console.goTo(3, consoleSize.width / 2 - 17);
    cout << "█──█─█──█─██─██─█──█─█─█──█──█───█──█";
    console.goTo(4, consoleSize.width / 2 - 17);
    cout << "█────█──█─█─█─█─████─█─█──█──███─████";
    console.goTo(5, consoleSize.width / 2- 17);
    cout << "█──█─█──█─█───█─█────█─█──█──█───█─█";
    console.goTo(6, consoleSize.width / 2 - 17);
    cout << "████─████─█───█─█────███──█──███─█─█";
    console.goTo(8, consoleSize.width / 2 - 18);
    cout << "███─███─█───█─█─█─█───████─███─████─████";
    console.goTo(9, consoleSize.width / 2 - 18);
    cout << "█────█──██─██─█─█─█───█──█──█──█──█─█──█";
    console.goTo(10, consoleSize.width / 2 - 18);
    cout << "███──█──█─█─█─█─█─█───████──█──█──█─████";
    console.goTo(11, consoleSize.width / 2 - 18);
    cout << "──█──█──█───█─█─█─█───█──█──█──█──█─█─█";
    console.goTo(12, consoleSize.width / 2 - 18);
    cout << "███─███─█───█─███─███─█──█──█──████─█─█";
}

void drawProgressBar(Console console, int value){
    Bounds consoleSize;
    console.getSize(consoleSize);
    Bounds progressBar(consoleSize.width / 2 - 18, consoleSize.height / 2 + 3, 40, 3);
    console.printBox(progressBar, "");
    console.goTo(consoleSize.height / 2 + 4, consoleSize.width / 2 - 17);
    for(int i = 0; i < value; i++){
        console.printExtraCharsetString(FILL);
    }    
}

void loading(Console console){
    drawTitle(console);
    for(int i = 1; i < 39; i++){
        drawProgressBar(console, i);
        usleep(100000);
    }
}
#include <iostream>
#include <memory.hpp>
#include <interface.hpp>
#include <keyboard.hpp>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <hdd.hpp>
#include <cpu.hpp>
#include <loading.hpp>
#include <string>

using namespace std;

CPU cpu;
Memory memory;
Interface interface(memory, cpu);
Console console;
bool isDrawing = true;

void updateCounter(int signo)
{
    bool isIgnore;
    memory.reg.get(REG_IGNORE_TACTS, isIgnore);
    if (!isIgnore)
    {
        cpu.CU(memory, console, isDrawing);
    }
    if (isDrawing)
    {
        interface.drawInterface(console, memory, cpu);
    }
}

int main(int argc, char *argv[])
{
    console.clear();
    console.changeCursorVisible(false);
    Keyboard keyboard;

    string loadKey;
    if (argc >= 2)
    {
        loadKey = argv[1];
    }

    string l = "-noload";
    if (loadKey != l)
    {
        cout << loadKey;
    }

    setbuf(stdout, NULL);

    struct itimerval nval, oval;
    signal(SIGALRM, updateCounter);
    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 100000;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &nval, &oval);

    console.changeCanon();
    cpu.setCurrentMemory(0, memory);
    while (keyboard.readKeys(console, interface, memory, cpu, isDrawing))
    {
    }
    return 0;
}
#pragma once

#include <structs.hpp>
#include <bigChars.hpp>
#include <memory.hpp>
#include <string>

#define RIGHT_BOTTOM_ANGLE "j"
#define RIGHT_TOP_ANGLE "k"
#define LEFT_BOTTOM_ANGLE "m"
#define LEFT_TOP_ANGLE "l"
#define TOP_LINE "q"
#define BOTTOM_LINE "r"
#define VERTICAL_LINE "x"
#define FILL "a"

class Console{
private:
    Bounds size;
public:
    Console();
    int clear();
    int changeCursorVisible(bool value);
    int goTo(int row, int column);
    int getSize(Bounds& size);
    void setSize(Bounds size);
    int setTextColor(int color);
    int setBackgroundColor(int color);
    int printExtraCharsetString(std::string str);
    int printBox(Bounds& boxSize, std::string title);
    int printBigChar(BigChar bigChar, bool isLast);
    int saveParams();
    int loadParams();
    int changeCanon();
    int changeCanon(bool value);
    int input();
    void output(int value);
};

int saveBigChars(char *path, BigChar bigChars[], int count);
int loadBigChars(char *path, BigChar bigChars[], int count);
#pragma once
#include <bigChars.hpp>

enum colors {black, red, green, yellow, blue, purple, lightBlue, white, original = 9};

class Coord{
    public:
    int x = 0;
    int y = 0;
};

class Bounds{
public:
    Bounds(int x = 1, int y = 1, int width = 10, int height = 10);
    int x;
    int y;
    int width;
    int height;
};

class BigChar{
private:
    Bounds bounds;
    int content[2];
public:
    colors textColor;
    colors backgroundColor;
    BigChar(colors textColor, colors backgroundColor, int x = 1, int y = 1);  
    Bounds getBounds();
    int getContent(int index, int &value);
    int setContent(int content1, int content2);
    int setContent(int value);
    int getTextColor(int color);
    int getBackgroundColor(int color);
    int setValue(int x, int y, bool value);
    int getValue(int x, int y, int &value);
};
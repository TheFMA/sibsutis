#include <structs.hpp>

Bounds::Bounds(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
};

BigChar::BigChar(colors textColor, colors backgroundColor, int x, int y){ 
    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.width = 8;
    this->bounds.height = 8;
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;
}

Bounds BigChar::getBounds(){
    return bounds;
}

int BigChar::getContent(int index, int &value){
    value = content[index];
    return 0;
}

int BigChar::setContent(int content1, int content2){
    content[0] = content1;
    content[1] = content2;
    return 0;
}

int BigChar::setContent(int digit){
    int currentDigit[2];
    switch (digit)
    {
    case 0:
        setContent(ZERO);
        break;
    case 1:
        setContent(ONE);
        break;
    case 2:
        setContent(TWO);
        break;
    case 3:
        setContent(THREE);
        break;
    case 4:
        setContent(FOUR);
        break;
    case 5:
        setContent(FIVE);
        break;
    case 6:
        setContent(SIX);
        break;
    case 7:
        setContent(SEVEN);
        break;
    case 8:
        setContent(EIGHT);
        break;
    case 9:
        setContent(NINE);
        break;
    case 10:
        setContent(TEN);
        break;
    case 11:
        setContent(ELEVEN);
        break;
    case 12:
        setContent(TWELVE);
        break;
    case 13:
        setContent(THIRTEEN);
        break;
    case 14:
        setContent(FOURTEEN);
        break;
    case 15:
        setContent(FIVETEEN);
        break;
    case 16:
        setContent(PLUS);
        break;
    case 17:
        setContent(0, 0);
        break;
    default:
        break;
    }
    
    return 0;
}

int BigChar::setValue(int x, int y, bool value){
    int index = y < 5 ? 0 : 1;
    int mask = 1 << (((y - 1) % 4) * 8) + (8 - x);
    if(value){
        content[index] |= mask;
    }
    else{
        mask = ~mask;
        content[index] &= mask;
    }
    return 0;
}

int BigChar::getValue(int x, int y, int &value){
    int index = y < 5 ? 0 : 1;
    int address = ((y - 1) % 4) * 8 + 8 - x;
    int mask = 1 << address - 1;

    value = content[index] & mask >> address;

    return 0;
}
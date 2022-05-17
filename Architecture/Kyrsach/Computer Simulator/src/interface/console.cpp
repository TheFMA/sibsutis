#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <cmath>
#include <console.hpp>
#include <termios.h>

using namespace std;

Console::Console(){
    getSize(size);
}

int Console::clear(){
    cout << "\E[H\E[J";
    return 0;
}

int Console::changeCursorVisible(bool value){
    if(value){
        cout << "\E[?25h";
    }
    else{
        cout << "\E[?25l";
    }
    return 0;
}

int Console::goTo(int row, int column){
    cout << "\E[" << to_string(row) << ";" << to_string(column) << "H";
    return 0;
}

int Console::getSize(Bounds &size){
    winsize ws;
    if(!ioctl(1, TIOCGWINSZ, &ws)){
        this->size.width = (int)ws.ws_col;
        this->size.height = (int)ws.ws_row;
        this->size.x = 1;
        this->size.y = 1;
    }
    size = this->size;
    return -1;
}

void Console::setSize(Bounds size){
    winsize ws;
    ws.ws_row = size.width;
    ws.ws_col = size.height;
    ioctl(1, TIOCSWINSZ, &ws);
}

int Console::setTextColor(int color){
    cout << "\E[3" << to_string(color) << "m";
    return 0;
}

int Console::setBackgroundColor(int color){
    cout << "\E[4" << to_string(color) << "m";
    return 0;
}

int Console::printExtraCharsetString(string str){
    cout << "\E(0" << str << "\E(B";
    return 0;
}

int Console::printBox(Bounds &boxSize, string title){
    if(boxSize.width < 2 || boxSize.height < 2){
        return -1;
    }

    goTo(boxSize.y, boxSize.x);

    //Рисуем верхнюю грань
    printExtraCharsetString(LEFT_TOP_ANGLE);
    printExtraCharsetString(TOP_LINE);
    cout << title;
    int topBorderWidth = boxSize.width - 2 - title.size();
    if(topBorderWidth >= 1){
        for(int i = 1; i < topBorderWidth; i++){
            printExtraCharsetString(TOP_LINE);
        }
    }
    
    printExtraCharsetString(RIGHT_TOP_ANGLE);

    //Боковые грани
    for(int i = 1; i <= boxSize.height - 2; i++){
        goTo(boxSize.y + i, boxSize.x);
        printExtraCharsetString(VERTICAL_LINE);
        goTo(boxSize.y + i, boxSize.x + boxSize.width - 1);
        printExtraCharsetString(VERTICAL_LINE);
    }

    //Нижняя грань
    goTo(boxSize.y + boxSize.height - 1, boxSize.x);
    printExtraCharsetString(LEFT_BOTTOM_ANGLE);
    for(int i = 0; i < boxSize.width - 2; i++){
        printExtraCharsetString(TOP_LINE);
    }
    printExtraCharsetString(RIGHT_BOTTOM_ANGLE);
    return 0;
}

int Console::printBigChar(BigChar bigChar, bool isLast){

    setTextColor(bigChar.textColor);
    setBackgroundColor(bigChar.backgroundColor);

    Bounds bigCharBounds = bigChar.getBounds();

    goTo(bigCharBounds.y, bigCharBounds.x);
    for(int i = 0; i < 2; i++){
        int content;
        bigChar.getContent(i, content);
        for(int j = 0; j < 4; j++){
            for(int z = 0; z < 8; z++){
                if(0b10000000 >> z & content){
                    printExtraCharsetString(FILL);
                    continue;
                }
                cout << " ";
            }
            if(isLast){
                cout << " ";
            }
            goTo(bigCharBounds.y + ((i * 4) + (j + 1)), bigCharBounds.x);
            content >>= 8;
        }
    }
    return 0;
}

int Console::saveParams(){
    termios* buf = new termios;
    tcgetattr(0, buf);

    FILE* f;
    f = fopen("2.txt", "wb");

    fwrite(buf, sizeof(termios), 1, f);

    fclose(f);
    return 0;
}

int Console::loadParams(){
    FILE* f;
    f = fopen("2.txt", "rb");
    termios* buf = new termios;

    fread(buf, sizeof(termios), 1, f);
    fclose(f);

    tcsetattr(0, TCSAFLUSH, buf);
    return 0;
}

int Console::changeCanon(){
    termios* params = new termios;
    tcgetattr(0, params);
    params->c_lflag ^= (ICANON|ECHO);
    params->c_cc[VTIME] = 3;
    params->c_cc[VMIN] = 0;
    tcsetattr(0, TCSAFLUSH, params);
    return 0;
}

//если передаём true, то ввод после enter и введённое выводится в консоль
int Console::changeCanon(bool value){
    termios* params = new termios;
    tcgetattr(0, params);
    if(value){
        params->c_lflag |= (ICANON|ECHO);
    }
    else{
        params->c_lflag &= ~(ICANON|ECHO);
    }
    tcsetattr(0, TCSAFLUSH, params);
    return 0;
}

int Console::input(){
    changeCanon();
    goTo(23, 0);
    for(int i = 0; i < size.width; i++){
        cout << " ";
    }
    goTo(23, 0);
    int input;
    cout << "Input: ";
    cin >> input;
    changeCanon();
    return input;
}

void Console::output(int value){
    goTo(23, 0);
    for(int i = 0; i < size.width; i++){
        cout << " ";
    }
    goTo(23, 0);
    cout << "Output: " << value;
}

int saveBigChars(char *path, BigChar bigChars[2], int count){
    FILE* f;
    f = fopen(path, "wb");

    for(int i = 0; i < count; i++){
        int content;
        bigChars[i].getContent(0, content);
        fwrite(&content, sizeof(int), 1, f);
        bigChars[i].getContent(1, content);
        fwrite(&content, sizeof(int), 1, f);
    }

    fclose(f);
    return 0;
}

int loadBigChars(char *path, BigChar bigChars[2], int count){
    FILE* f;
    f = fopen(path, "rb");

    for(int i = 0; i < count; i++){
        int content1, content2;
        fread(&content1, sizeof(int), 1, f);
        fread(&content2, sizeof(int), 1, f);
        bigChars[i].setContent(content1, content2);
    }

    fclose(f);
    return 0;
}
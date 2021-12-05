#pragma once
#include <iostream>

using namespace std;

int menu();

void printLine();

template <typename T>
T random(T min, T max);

class Institution {
private:
    static int countOfObj;

protected:
    string type;
    int number;
    int year;
    int countOfGraduates;
    int countOfApplicants;
    string city;

public:
    static int getCount();

    Institution();
    ~Institution();
    void setType(string value);
    void setNumber(int value);
    void setYear(int value);
    void setcountOfGraduates(int value);
    void setCountOfApplicants(int value);
    void setCity(string value);

    string getType();
    int getNumber();
    int getYear();
    int getCountOfGraduates();
    int getCountOfApplicants();
    string getCity();

    virtual void print() = 0;
};

class Gymnasium : public Institution {
private:
    int scoreForStudy;

public:
    Gymnasium();
    Gymnasium(int number, int year, int cOfG, int cOfA, string city, int score);

    void setScoreForStudy(int value);
    int getScoreForStudy();

    void print() override;
};

class Lyceum : public Institution {
private:
    int moneyForStudy;

public:
    Lyceum();
    Lyceum(int number, int year, int cOfG, int cOfA, string city, int money);

    void setMoneyForStudy(int value);
    int getMoneyForStudy();

    void print() override;
};
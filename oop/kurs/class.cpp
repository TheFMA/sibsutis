#include "class.h"
#include <ctime>
#include <iostream>

using namespace std;

int menu()
{
    int command;
    printLine();
    cout << " 0 - Выход" << endl;
    cout << " 1 - Рандом гимназия" << endl;
    cout << " 2 - Создать гимназию" << endl;
    cout << " 3 - Рандом лицей" << endl;
    cout << " 4 - Создать лицей" << endl;
    cout << " 5 - Отобразить все" << endl;
    cout << " 6 - Удалить по индексу" << endl;
    printLine();
    cout << "?";

    scanf("%d", &command);
    return command;
}

void printLine()
{
    cout << endl << "===============================================" << endl;
}

template <typename T>
T random(T min, T max)
{
    srand(time(NULL) * rand());
    max++;
    return abs(rand() % (max - min)) + min;
}

static const string cities[]
        = {"Кемерово",
           "Новосибирск",
           "Барнаул",
           "Москва",
           "Санкт-Петербург",
           "Казань",
           "Самара",
           "Краснодар"};

int Institution::countOfObj = 0;

int Institution::getCount()
{
    return countOfObj;
}

Institution::Institution()
    : type(""),
      number(0),
      year(0),
      countOfGraduates(0),
      countOfApplicants(0),
      city("")
{
    countOfObj++;
}

Institution::~Institution()
{
    countOfObj--;
}

void Institution::setType(string value)
{
    this->type = value;
}

void Institution::setNumber(int value)
{
    this->number = value;
}

void Institution::setYear(int value)
{
    this->year = value;
}

void Institution::setcountOfGraduates(int value)
{
    this->countOfGraduates = value;
}

void Institution::setCountOfApplicants(int value)
{
    this->countOfApplicants = value;
}

void Institution::setCity(string value)
{
    this->city = value;
}

string Institution::getType()
{
    return this->type;
}

int Institution::getNumber()
{
    return this->number;
}

int Institution::getYear()
{
    return this->year;
}

int Institution::getCountOfGraduates()
{
    return this->countOfGraduates;
}

int Institution::getCountOfApplicants()
{
    return this->countOfApplicants;
}

string Institution::getCity()
{
    return this->city;
}

Gymnasium::Gymnasium()
{
    setType("Гимназия");
    setNumber(random(0, 10));
    setYear(random(1970, 2015));
    setcountOfGraduates(random(100, 200));
    setCountOfApplicants(random(200, 300));
    int size = sizeof(cities) / sizeof(string) - 1;
    setCity(cities[random(0, size)]);
    setScoreForStudy(random(65, 100));
}

Gymnasium::Gymnasium(
        int number, int year, int cOfG, int cOfA, string city, int score)
{
    setType("Гимназия");
    setNumber(number);
    setYear(year);
    setcountOfGraduates(cOfG);
    setCountOfApplicants(cOfA);
    setCity(city);
    setScoreForStudy(score);
}

void Gymnasium::setScoreForStudy(int value)
{
    this->scoreForStudy = value;
}

int Gymnasium::getScoreForStudy()
{
    return this->scoreForStudy;
}

void Gymnasium::print()
{
    cout << endl << "Тип заведения: " << getType() << endl;
    cout << "Номер заведения: " << getNumber() << endl;
    cout << "Год основания: " << getYear() << endl;
    cout << "Количество выпускников: " << getCountOfGraduates() << endl;
    cout << "Количество абитуриентов: " << getCountOfApplicants() << endl;
    cout << "Город: " << getCity() << endl;
    cout << "Минимальный вступительный балл: " << getScoreForStudy() << endl
         << endl;
}

Lyceum::Lyceum()
{
    setType("Лицей");
    setNumber(random(34, 77));
    setYear(random(2005, 2020));
    setcountOfGraduates(random(50, 100));
    setCountOfApplicants(random(100, 200));
    int size = sizeof(cities) / sizeof(string) - 1;
    setCity(cities[random(0, size)]);
    setMoneyForStudy(random(50, 120));
}

Lyceum::Lyceum(int number, int year, int cOfG, int cOfA, string city, int money)
{
    setType("Лицей");
    setNumber(number);
    setYear(year);
    setcountOfGraduates(cOfG);
    setCountOfApplicants(cOfA);
    setCity(city);
    setMoneyForStudy(money);
}

void Lyceum::setMoneyForStudy(int value)
{
    this->moneyForStudy = value;
}

int Lyceum::getMoneyForStudy()
{
    return this->moneyForStudy;
}

void Lyceum::print()
{
    cout << endl << "Тип заведения: " << getType() << endl;
    cout << "Номер заведения: " << getNumber() << endl;
    cout << "Год основания: " << getYear() << endl;
    cout << "Количество выпускников: " << getCountOfGraduates() << endl;
    cout << "Количество абитуриентов: " << getCountOfApplicants() << endl;
    cout << "Город: " << getCity() << endl;
    cout << "Средняя стоимость обучения за год: " << getMoneyForStudy()
         << " тыс.руб" << endl
         << endl;
}

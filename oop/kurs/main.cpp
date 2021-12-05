#include "class.h"
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <vector>

using namespace std;
vector<Institution*> v;
vector<Institution*>::iterator obj;

int main()
{
    system("clear");
    setlocale(LC_ALL, "");

    int countOfObjs, countOfLyceum, countOfGymnasium;
    int number, year, cOfG, cOfA, score, money;
    string city;
    int index;

    int command = 0;
    while (command != -1) {
        printLine();
        cout << endl
             << "Общее количество объектов = " << v[0]->getCount() << endl
             << endl;
        cout << "Размер массива = " << v.capacity() << endl;
        command = menu();
        switch (command) {
            //Выход
        case 0:
            command = -1;
            break;
        case 1:
            //Рандом гимназия
            cout << "Введите количество гимназий: ";
            cin >> countOfGymnasium;
            for (int i = 0; i < countOfGymnasium; i++) {
                v.push_back(new Gymnasium);
            }
            system("clear");
            break;
        case 2:
            //Создать гимназию
            cout << "Введите номер гимназии: ";
            cin >> number;
            cout << "Введите год гимназии: ";
            cin >> year;
            cout << "Введите количество выпускников: ";
            cin >> cOfG;
            cout << "Введите количество абитуриентов: ";
            cin >> cOfA;
            cout << "Введите город: ";
            cin >> city;
            cout << "Введите минимальный вступительный балл: ";
            cin >> score;
            v.push_back(new Gymnasium(number, year, cOfG, cOfA, city, score));
            system("clear");
            break;
        case 3:
            //Рандом лицей
            cout << "Введите количество лицеев: ";
            cin >> countOfLyceum;
            for (int i = 0; i < countOfLyceum; i++) {
                v.push_back(new Lyceum);
            }
            system("clear");
            break;
        case 4:
            //Создать лицей
            cout << "Введите номер лицея: ";
            cin >> number;
            cout << "Введите год лицея: ";
            cin >> year;
            cout << "Введите количество выпускников: ";
            cin >> cOfG;
            cout << "Введите количество абитуриентов: ";
            cin >> cOfA;
            cout << "Введите город: ";
            cin >> city;
            cout << "Введите стоимость обучения в год: ";
            cin >> money;
            v.push_back(new Lyceum(number, year, cOfG, cOfA, city, money));
            system("clear");
            break;
        case 5:
            //Отобразить все
            system("clear");
            printLine();
            countOfObjs = v[0]->getCount();
            if (countOfObjs > 0) {
                for (int i = 0; i < countOfObjs; i++) {
                    cout << "Индекс объекта: " << i + 1;
                    v[i]->print();
                }
                break;
            } else {
                cout << "Не существует объектов" << endl;
            }
            break;
        case 6:
            // Удалить по индексу
            cout << "Введите индекс удаляемого объекта" << endl;
            cin >> index;
            if ((index > v[0]->getCount()) || index < 1) {
                cout << "Объекта с таким индексом не существует" << endl;
                break;
            } else {
                delete v[index - 1];
                v.erase(v.begin() + (index - 1));
                v.shrink_to_fit();
                cout << "Удален объект с индексом " << index << endl;
            }
            system("clear");
            break;
        default:
            cout << "Некорректная команда" << endl;
        }
    }

    for (obj = v.begin(); obj != v.end(); ++obj) {
        delete *obj;
    }
    v.clear();
    v.shrink_to_fit();

    return 0;
}

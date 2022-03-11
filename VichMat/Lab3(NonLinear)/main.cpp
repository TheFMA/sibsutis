#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const double a = 1;
const double b = 2;
const float epsl = 0.000000001;

double func(double x)
{
    return (pow(x, 2) - 2);
}

double func1(double x)
{
    //производная
    return (2 * x);
}

double find_c(double a, double b)
{
    return ((a + b) / 2);
}
double find_c2(double a, double b)
{
    return ((a * func(b) - b * func(a)) / (func(b) - func(a)));
}

int main()
{
    double step = 0;
    double x, c, buf;
    double a1, b1;
    char choice = ' ';
    double x1;
    setlocale(0, "");

    while (choice != 'b') {
        cout << "Выберите метод решения: \n";
        cout << "1 - метод бисекции.\n";
        cout << "2 - метод хорд.\n";
        cout << "3 - метод Ньютона.\n";

        cout << "Ввод: ";
        cin >> choice;

        x = 10;
        c = 0;
        buf = 0;
        double x0 = 2;
        x1 = 2;
        a1 = a;
        b1 = b;
        //Задаём значения по умолчанию, чтобы корень уравнения находился
        //корректно
        switch (choice) {
            //Метод бисекции
        case '1':
            // 1. Находим интервал a, b на котором функция меняет свой знак:

            while (x > epsl) {
                step++;
                c = find_c(a1, b1);
                if ((func(a1)) * (func(c)) < 0) {
                    b1 = c;
                } else if ((func(c)) * (func(b1)) < 0) {
                    a1 = c;
                }
                x = abs(a1 - b1) / 2;
            }
            cout << "Ответ: " << c << endl;
            cout << "Кол-во шагов: " << step << endl;

            break;

            /*Метод хорд*/
        case '2':
            step = 0;

            while (x > epsl) {
                step++;
                c = find_c2(a1, b1);
                if ((func(a1)) * (func(c)) < 0) {
                    b1 = c;
                } else if ((func(c)) * (func(b1)) < 0) {
                    a1 = c;
                }
                x = abs(c - buf);
                buf = c;
            }
            cout << "Ответ: " << c << endl;
            cout << "Кол-во шагов: " << step << endl;

            break;

        /*Метод Ньютон*/
        case '3':
            step = 0;
            do {
                step++;
                x0 = x1;
                x1 = x0 - (func(x0) / func1(x0));

            } while (abs(x0 - x1) > epsl);

            cout << "Ответ: " << x1 << endl;
            cout << "Кол-во шагов: " << step << endl;

            break;

        case 'b':
            break;

        default:
            cout << "Ошибка: Введены неверные данные\n";
            break;
        }
    }

    return 0;
}
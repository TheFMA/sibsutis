#include <iostream>
#include <math.h>
#include <vector>

#define eps 0.0000000001

using namespace std;

double f(double x)
{
    return 1 / x;
}

double method_trapezium(double a, double b, int points, double width)
{
    double S = 0;

    double h = a;
    double array_X;

    for (int i = 0; i <= points; ++i) {
        h += width;
        S += (f(h) + f(h + width)) / 2 * width;
    }
    return S;
}

double SimpsonMethod(double a, double b, int points, double width)
{
    double result = 0;
    vector<double> array_Y(points);
    double h = a;
    for (int i = 0; i < points + 1; ++i) {
        array_Y[i] = h;
        h += width;
    }

    for (int i = 2; i <= points; i += 2) {
        result += (array_Y[i] - array_Y[i - 2])
                * (f(array_Y[i - 2]) / 6 + 2 * f(array_Y[i - 1]) / 3
                   + f(array_Y[i]) / 6);
    }
    return result;
}

int main()
{
    double a = 1, b = 2;
    int x = 0, points = 10;
    double width = (b - a) / points;

    double res = SimpsonMethod(a, b, points, width);
    double res1 = 0;

    while (fabs(res - res1) > 15 * eps) {
        res1 = res;

        printf("Метод Симпсона: "
               "%.15f\n",
               res);
        x++;
        printf("Шаг = %f\n", width);
        points *= 2;
        width = (b - a) / points;
        res = SimpsonMethod(a, b, points, width);
    }
    x = 0;
    cout << endl;
    points = 10;
    width = (b - a) / points;
    res = method_trapezium(a, b, points, width);
    res1 = 0;

    while (fabs(res - res1) > 3 * eps) {
        res1 = res;

        printf("Метод трапеций: %.15f\n", res);
        x++;
        printf("Шаг = %.10f\n", width);
        points *= 2;
        width = (b - a) / points;
        res = method_trapezium(a, b, points, width);
    }
}
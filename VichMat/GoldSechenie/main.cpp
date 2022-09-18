#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;
#define eps 0.001

double function(float x)
{
    double y = x * x - 6 * x;
    return y;
}

int main()
{
    double a = 0, b = 5;
    double x;
    int step = 0;
    double Lamb, Lamb2;
    Lamb = a + 0 + 0.382 * (b - a);
    Lamb2 = a + 0 + 0.618 * (b - a);
    double Function_Lamb = function(Lamb);
    double Function_Lamb2 = function(Lamb2);

    while ((b - a) / 2 > eps) {
        if (Function_Lamb < Function_Lamb2) {
            b = Lamb2;
            Lamb2 = Lamb;
            Lamb = a + 0 + 0.382 * (b - a);
            Function_Lamb2 = Function_Lamb;
            Function_Lamb = function(Lamb);

        } else {
            a = Lamb;
            Lamb = Lamb2;
            Lamb2 = a + 0 + 0.618 * (b - a);
            Function_Lamb = Function_Lamb2;
            Function_Lamb2 = function(Lamb2);
        }
        x = (a + b) / 2;
        cout << "Step " << ++step << endl;
        cout << "Lamb variable = " << Lamb << " "
             << "Lamb2 variable = " << Lamb2 << endl;
        cout << "Function(l1) = " << function(Lamb) << ' '
             << "Function(l2) = " << function(Lamb2) << endl;
        cout << "New range = "
             << "(" << a << ";" << b << ")" << endl;
        cout << "x variable = " << x << ' ' << "Function(x) = " << function(x)
             << endl;
        cout << endl;
    }
}
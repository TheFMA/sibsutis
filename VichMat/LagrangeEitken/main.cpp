#include <math.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

#define N 4 // кол-во точек

double Eitken(int flag, double X[N], double Y[N], double x)
{
    double P, y, temp1[N], temp2[N];
    int l;
    for (int i = 0; i < N - 1; i++) {
        l = 0;
        for (int j = i + 1; j < N; j++) {
            temp1[l] = Y[l] * (x - X[j]) - Y[j - i] * (x - X[l]);
            temp2[l] = X[l] - X[j];
            Y[l] = temp1[l] / temp2[l];
            P = Y[l];
            printf("P=%f  \n", Y[l]);
            l++;
        }
    }
    return P;
}

float Lagrange(double x, double X[N], double Y[N])
{
    int i, j;
    double num = 1, denom = 1, P = 0;
    for (i = 0; i < N; i++) {
        num = 1;
        denom = 1;
        for (j = 0; j < N; j++)
            if (j != i) {
                num = num * (x - X[j]);
                denom = denom * (X[i] - X[j]);
            }
        P = P + Y[i] * (num / denom);
    }
    return P;
}

int main()
{
    double y, x, find;
    double findY;
    int i;
    cout << "Enter the value x "
            "\nx = ";
    cin >> find;

    double xValue[N] = {1, 1.5, 2, 2.5},
           yFound[N] = {1, 1.2247, 1.4142, 1.5811};

    cout << "Lanrange: " << Lagrange(find, xValue, yFound) << endl;
    cout << "Eitken: " << Eitken(1, xValue, yFound, find);
    cout << endl;

    return 0;
}
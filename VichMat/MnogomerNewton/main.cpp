#include <math.h>

#include <iostream>
#define N 2
#define eps 0.000000001
using namespace std;

double x0[N] = {2, 1};
double xn[N], x[N], y[N];
double F[N], W[N][N];
double matr[N][N + 1];

void F_calc()
{
    F[0] = x[0] * x[0] * x[1] - 3;
    F[1] = x[0] / x[1] - 2;
}

void W_calc()
{
    W[0][0] = 2 * x[0] * x[1];
    W[0][1] = x[0] * x[0];
    W[1][0] = 1 / x[1];
    W[1][1] = -x[0] / (x[1] * x[1]);
}

int main()
{
    for (int i = 0; i < N; i++) {
        x[i] = x0[i];
    }
    double norm_x = 0;
    int cnt = 0;
    do {
        cnt++;
        norm_x = 0;
        F_calc();
        W_calc();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matr[i][j] = W[i][j];
            }
            matr[i][N] = F[i];
        }
        double d;
        for (int i = 0; i < N; i++) {
            float max = fabs(matr[i][i]);
            int max_ind = i;
            for (int j = i + 1; j < N; j++) {
                if (fabs(matr[j][i]) > max_ind) {
                    max = fabs(matr[j][i]);
                    max_ind = j;
                }
            }
            if (max_ind != i)
                swap(matr[i], matr[max_ind]);
            d = matr[i][i];
            for (int j = i; j < N + 1; j++) {
                matr[i][j] /= d;
            }
            for (int j = 0; j < N; j++) {
                d = matr[j][i];

                if (j != i) {
                    for (int k = i; k <= N; k++) {
                        matr[j][k] -= matr[i][k] * d;
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N + 1; j++) {
                cout.width(3);
                cout << matr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
        for (int i = 0; i < N; i++)
            y[i] = matr[i][N];

        for (int i = 0; i < N; i++)
            xn[i] = x[i] - y[i];
        for (int i = 0; i < N; i++) {
            cout.width(3);
            cout << x[i] << " - " << y[i] << " = " << xn[i] << endl;
        }
        cout << endl << endl;

        for (int i = 0; i < N; ++i)
            norm_x += fabs(xn[i] - x[i]);
        for (int i = 0; i < N; ++i)
            x[i] = xn[i];
    } while (norm_x > eps);
    for (int i = 0; i < N; i++)
        printf("%.9f \n", x[i]);
    cout << endl << cnt << endl;
}
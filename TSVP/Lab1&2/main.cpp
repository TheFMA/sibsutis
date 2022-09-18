#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void FillDec(int*, int);
void BubbleSort(int*, int);
void PrintMas(int[], int);
void SelectSort(int*, int);
void Fill(int*, int);

int M, C;

int main()
{
    const int n = 5;
    int A[n];

    // printf("BubbleSort:\n");
    // Fill(A, n);
    // BubbleSort(A, n);
    // PrintMas(A, n);
    // cout << "С: " << C << "  M:" << M << "\n";

    printf("SelectSort:\n");
    Fill(A, n);
    SelectSort(A, n);
    PrintMas(A, n);
    cout << "С: " << C << "  M:" << M << "\n";
    return 0;
}

void FillDec(int A[], int n)
{
    int i, j = 0;
    for (i = n - 1; i >= 0; i--) {
        A[j] = i;
        j++;
    }
}

void BubbleSort(int* A, int n)
{
    M = C = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 2; j >= i; j--) {
            if (A[j] > A[j + 1]) {
                int tmp;
                tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
                M += 3;
            }
            C++;
        }
}

void PrintMas(int A[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void SelectSort(int* A, int n)
{
    M = C = 0;
    int i, j, min, num;
    min = A[1];
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (A[j] <= min) {
                min = A[j];
                num = j;
            }
            C++;
        }

        if (A[i] >= min) {
            A[num] = A[i];
            A[i] = min;
            M += 3;
        }
        min = A[j + 1];
    }
}

void Fill(int* A, int n)
{
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
}
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    const int cols = 4, rows = 3;

      fstream fi;
    fi.open("text.txt", ios::in);
    int i = 0;
    int j = 0;
    float tmp , del = 0;
    float matrix[rows][cols];

    if (!fi)
    {
        cerr << "ERROR!\n";
        exit(1);
    }
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            fi >> matrix[i][j];

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
    fi.close();

    float max;
    int max_ind;

    for (i = 0; i < rows; i++)
    {
        // int a = i; 
        // if (matrix[i][i] == 0)
        // {
        //     while(matrix[a][i] == 0 && a < rows)
        //     {
        //         a++;
        //     }
        //     for (j = 0; j < cols; j++)
        //     {
        //         tmp = matrix[i][j];
        //         matrix[i][j] = matrix[a][j];
        //         matrix[a][j] = tmp;
        //     }
        // }

        max = (matrix[i][i]);
        for (j = i + 1; j < rows; j++)
        {
            if (abs(matrix[j][i]) > abs(max))
            {
                max = matrix[j][i];
                max_ind = j;
            }
        }

    //    if (max_ind != i)
        {
            for (j = 0; j < cols; j++)
            {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[max_ind][j];
                matrix[max_ind][j] = tmp;
                // for (int b = 0; b < rows; b++)
                // {
                //     for (int o = 0; o < cols; o++)
                //     cout << matrix[b][o] << ' ';
                //     cout << endl;
                // }
            }
            for (int b = 0; b < rows; b++)
                {
                    for (int o = 0; o < cols; o++)
                    cout << matrix[b][o] << ' ';
                    cout << endl;
                }
        }

            float diag_coef = matrix[i][i];
            float del;

            for (j = 0; j < cols; j++)
            {
                matrix[i][j] = matrix[i][j] / diag_coef;
            }
    
             for (j = 0; j < rows; j++)
            { 
                del = matrix[j][i] / matrix[i][i];
                if (i != j)
                {
                    for(int z = 0; z < cols; z++)
                    {
                        matrix[j][z] -= matrix[i][z] * del;
                    }
                    /*for (int b = 0; b < rows; b++)
                {
                    for (int o = 0; o < cols; o++)
                    cout << matrix[b][o] << ' ';
                    cout << endl;
                }*/
                }
            } 
            cout << "Занулен " << i << "столбец" << endl;

            for (int u = 0; u < rows; u++)
                {
                    for (int v = 0; v < cols; v++)
                    cout << matrix[u][v] << ' ';
                    cout << endl;
                }
    }

    for (i = 0; i < rows; i++)
    {
        cout << "x" << i << "=" << matrix[i][cols-1] << endl;
    }
    


    // float max;
    // int max_ind;
    // float results[rows];
    
    // for (i = 0; i < 3; i++)
    // {
    //     max =  abs(matrix[i][i]);
    //     for (j = i + 1; j < rows; j++)
    //     {
    //         if (abs(matrix[j][i]) > abs(max))
    //         {
    //             max = matrix[j][i];
    //             max_ind = j;
    //         }
    //     }

    //     if (max_ind != i)
    //     {
    //         for (j = 0; j < cols; j++)
    //         {
    //             tmp = matrix[i][j];
    //             matrix[i][j] = matrix[max_ind][j];
    //             matrix[max_ind][j] = tmp;
    //         }
    //     }

    //     for (j = i + 1; j < rows; j++)
    //         { 
    //             del = matrix[j][i] / matrix[i][i];
    //             if (i != j)
    //             {
    //                 for(int z = 0; z < cols; z++)
    //                 {
    //                     matrix[j][z] -= matrix[i][z] * del;
    //                 }
    //             }
    //         } 
    // }

    // for (i = 0; i < rows; i++)
    // {
    //     for (j = 0; j < cols; j++)
    //         cout << matrix[i][j] << ' ';
    //     cout << endl;
    // }


//выражаем корни
    // for (i = (rows - 1); i >= 0; i--)
    // {
    //     max = matrix[i][cols - 1];
    //     for (j = (cols - 2); j > i; j--)
    //     {
    //         max = (max - (matrix[i][j] * results[j]));
    //     }
    //     results[j] = max / matrix[i][i];
    // } 

    // for (i = 0; i < rows; i++)
    // {
    //     cout << results[i] << ' ';
    // }
    // cout << endl;
}

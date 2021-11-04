#include <iostream>
#include <ctime>
 using namespace std;

 int prov(int lim,int mas[],int digit)
{
    int i;
    for(i=0;i<lim;i++)
        if(mas[i]==digit)
            return 1;
    return 0;
}

int main(){
    srand(time(NULL));
    int arr[20];
    // for (int i = 0; i < 20; ++i)
    // {
    //     arr[i] = rand() % 100;
    //     for(int j = 0; j < i; j++){
    //         if(arr[i] = arr[j] && i>0){
    //             arr[i] = rand() % 100;
    //             break;
    //         }
    //     }
    // }
    int i,j;
    for(i=0;i<20;i++)
    {
        do
        {
            arr[i]= rand() % 100;
        }
        while(prov(i,arr,arr[i]));
    }
    for(int i = 0; i<20; i++){
        cout << arr[i] << endl;
    }
    return 0;
}

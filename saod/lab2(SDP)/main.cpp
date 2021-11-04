#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
using namespace std;
struct node
{
    int data;
    node *left = NULL, *right = NULL;
};

// void print(node *p)
// {
//     if (p)
//     {
//         print(p->left);
//         cout << p->data << " ";
//         print(p->right);
//     }
// }

double sum_lens_way(node *p, int z)
{
    int s;
    if (!p)
        s = 0;
    else
    {
        s = z + sum_lens_way(p->left, z + 1) + sum_lens_way(p->right, z + 1);
    }
    return s;
}
//размер дерева
int check_size(node *p)
{
    int size_tree;
    if (!p)
        size_tree = 0;
    else
    {
        size_tree = 1 + check_size(p->left) + check_size(p->right);
    }
    return size_tree;
}
//средняя высота дерева
double mid_hight(node *p)
{
    return (sum_lens_way(p, 1) / check_size(p));
}
//контрольная сумма
int check_sum(node *p)
{
    int sum;
    if (!p)
        sum = 0;
    else
    {
        sum = p->data + check_sum(p->left) + check_sum(p->right);
    }
    return sum;
}
//высота
int tree_height(node *p)
{
    if (!p)
        return -1;
    return 1 + max(tree_height(p->left), tree_height(p->right));
}
//информация
void showInfo(node *root)
{
    cout << "    " << check_size(root) << "      " << check_sum(root) << "         " << tree_height(root) + 1 << "         " << mid_hight(root) << endl;
    // print(root);
}
//поиск
void serch(node *p, int x)
{

    while (p)
    {
        if (x < p->data)
        {
            p = p->left;
        }
        if (!p)
            break;
        if (x > p->data)
        {
            p = p->right;
        }
        if (!p)
            break;
        if (x == p->data)
            break;
    }

    if (p)
        cout << "Vershina " << p->data << " naidena po adresy " << p << endl;
    else
        cout << "Vershini net v dereve" << endl;
}

//сдп с двойной косвенностью
node *CDP2(node **root, int *D, int n)
{
    node **p = root;
    for (int i = 0; i < n; i++)
    {
        node **p = root;
        while ((*p) != NULL)
        {
            if (D[i] < (*p)->data)
            {
                p = &((*p)->left);
            }
            else if (D[i] > (*p)->data)
            {
                p = &((*p)->right);
            }
            else // В случае если элемент уже есть
            {
                break;
            }
        }

        if ((*p) == NULL)
        {
            (*p) = new node;
            (*p)->data = D[i];
            (*p)->left = (*p)->right = NULL;
        }
    }
    return (*root);
}
//сдп рекурсивно
void *CDPrec(node *&root, int D)
{
    if (root == NULL)
    {
        root = new node;
        root->data = D;
        root->left = root->right = NULL;
    }
    else if (root->data < D)
    {
        CDPrec(root->right, D);
    }
    else if (root->data > D)
    {
        CDPrec(root->left, D);
    }
    //return root;
}
//рисунок дерева
void print1(node *p, int l)
{
    if (p != NULL)
    {

        if (p->left)
            print1(p->left, l + 2);
        cout << p->data << "\n ";
        if (p->right)
            print1(p->right, l + 2);

        if (l)
        {
            std::cout << setw(l) << ' ';
        }
    }
}

 void print2(node* p, int floor)
{
if (p == NULL) {
printf("\t");
return;
}

print2(p->left, floor - 1);
if (floor == 1){
    cout << "/" << " " << "|";
}
if (floor == 0) {
printf("(%d)", p->data);
}
print2(p->right, floor - 1);
}

void print(node *p, int space)
{
    if (p == NULL)
        return;
 
    space += 3;
 
    print(p->right, space);
 
    cout<<endl;
    for (int i = 2; i < space; i++)
        cout<<"  ";
    cout<<p->data<<"\n";

    print(p->left, space);
}

//исдп
void ISDP(int L, int R, node *&p, int *a)
{
    if (L > R)
        p = NULL;
    else
    {
        p = new node;
        int m = (L + R) / 2;
        p->data = a[m];
        ISDP(L, m - 1, p->left, a);
        ISDP(m + 1, R, p->right, a);
    }
}

 int prov(int lim,int mas[],int digit)
{
    int i;
    if(lim == 0) return 0;
    for(i=0;i<lim;i++)
        if(mas[i]==digit)
            return 1;
    return 0;
}

int main()
{
    srand(time(0));
    node *p = NULL;
    node *v = NULL;
    const int n = 20;
    int arr[n];
    for(int i=0;i<n;i++)
    {
         do
        {
            arr[i]= rand() % 150;
        }
        while(prov(i,arr,arr[i]));
    }
    cout << "n=" << n << "    "
         << "Razmer"
         << "    "
         << "KontrolSum"
         << "    "
         << "Visota"
         << "    "
         << "Sredn visota" << endl;
    ISDP(0, n-1, p, arr);
    cout << "ISDP"
         << "   ";
    showInfo(p);
   
    //p = CDP2(&p, arr, n);
    for (int i = 0; i < n; i++)
    {
        CDPrec(v, arr[i]);
    }
    cout << "SDP"
         << "    ";
    showInfo(v);
    int g = tree_height(v);
    // for(int i = 0; i < g+1; i++){
    // print2(v, i);
    
    // cout << endl;
    // }
    print(v, 0);
    cout << endl;

    int x;
    //cin >> x;
    //serch(p, x);
}
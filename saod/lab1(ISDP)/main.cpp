#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
struct node
{
    int data;
    node *left, *right;
};

void print(node *p)
{
    if (p)
    {
        print(p->left);
        cout << p->data << " ";
        print(p->right);
    }
}

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
    cout << "size: " << check_size(root) << " sum: " << check_sum(root) << " height: " << tree_height(root) + 1 << " mid_height: " << mid_hight(root) << endl;
    print(root);
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

void printtree(node *p, int indent){
if(p != NULL) {
if(p->right) {
printtree(p->right, indent+4);
}
if (indent) {
std::cout << std::setw(indent) << ' ';
}
if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
std::cout<< p->data << "\n ";
if(p->left) {
std::cout << std::setw(indent) << ' ' <<" \\\n";
printtree(p->left, indent+4);
}
}
}

// void printtree(node *p, int l)
// {
// if (p != NULL)
// {

// if (p->left)
// printtree(p->left, l + 4);
// cout<< p->data<< "\n ";
// if (p->right)
// printtree(p->right, l + 4);

// if (l)
// {
// std::cout << setw(l) << ' ';
// }
// }
// }


int main()
{
    const int n = 100;
    int arr[n];
    for (int i = 0; i < n; ++i)
    {
        arr[i] = i;
    }
    node *p = NULL;
    ISDP(0, n-1, p, arr);
    showInfo(p);
    cout << endl;
    printtree(p, 0);
    cout << endl;
}
#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left = NULL, *right = NULL;
};

void print(node *p)
{
    if (p)
    {
        print(p->left);
        print(p->right);
        cout << p->data << " ";
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

int main()
{
    node *root = new node;

    root->data = 1;
    root->left = new node;
    root->left->data = 2;
    root->right = new node;
    root->right->data = 3;

    root->right->left = new node;
    root->right->left->data = 4;
    root->right->left->left = new node;
    root->right->left->left->data = 5;
    root->right->left->right = new node;
    root->right->left->right->data = 6;

    cout << "size: " << check_size(root) << " sum: " << check_sum(root) << " height: " << tree_height(root) + 1 << " mid_height: " << mid_hight(root) << endl;
    print(root);
    cout << endl;
    return 0;
}
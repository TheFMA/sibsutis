#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
struct node
{
    int data;
    node *left, *right;
	int bal = 0;
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

    cout << check_size(root) << "\t    " << check_sum(root) << "\t    "  << tree_height(root) + 1 << "\t    "  << mid_hight(root) << endl;
    print(root);
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

bool Rost = true;

void LL_turn(node*& p) {
	node* q = p->left;
	p->bal = 0;
	q->bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR_turn(node*& p) {
	node* q = p->right;
	p->bal = 0;
	q->bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
}

void LR_turn(node*& p) {
	node* q = p->left;
	node* r = q->right;
	if (r->bal < 0)
		p->bal = 1;
	else p->bal = 0;
	if (r->bal > 0)
		q->bal = -1;
	else q->bal = 0;
	r->bal = 0;
	q->right = r->left;
	p->left = r->right;
	r->left = q;
	r->right = p;
	p = r;
}

void RL_turn(node*& p) {
	node* q = p->right;
	node* r = q->left;
	if (r->bal < 0)
		p->bal = 1;
	else p->bal = 0;
	if (r->bal > 0)
		q->bal = -1;
	else q->bal = 0;
	r->bal = 0;
	q->left = r->right;
	p->right = r->left;
	r->right = q;
	r->left = p;
	p = r;
}

void AVL(int D, node*& p) {
	if (p == NULL) {
		p = new node;
		p->data = D;
		p->left = NULL;
		p->right = NULL;
		p->bal = 0;
		Rost = true;
	}
	else if (p->data > D) {
		AVL(D, p->left);
		if (Rost == true) {
			if (p->bal > 0) {
				p->bal = 0;
				Rost = false;
			}
			else if (p->bal == 0) {
				p->bal = -1;
				Rost = true;
			}
			else if (p->left->bal < 0) {
				LL_turn(p);
				Rost = false;
			}
			else {
				LR_turn(p);
				Rost = false;
			}
		}
	}
	else if (p->data < D) {
		AVL(D, p->right);
		if (Rost == true) {
			if (p->bal < 0) {
				p->bal = 0;
				Rost = false;
			}
			else if (p->bal == 0) {
				p->bal = 1;
				Rost = true;
			}
			else if (p->right->bal > 0) {
				RR_turn(p);
				Rost = false;
			}
			else {
				RL_turn(p);
				Rost = false;
			}
		}
	}
	else {
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

bool HR = 1;
bool VR = 1;

void Btree(int D, node*& p) {
	if (p == NULL) {
		p = new node;
		p->data = D;
		p->left = p->right = NULL;
		p->bal = 0;
		VR = 1;
	}
	else if(p->data > D){
		Btree(D, p->left);
		if (VR == 1) {
			if (p->bal == 0) {
				node* q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->bal = 1;
				VR = 0;
				HR = 1;
			}
			else {
				p->bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else {
			HR = 0;
		}
	}
	else if (p->data < D) {
		Btree(D, p->right);
		if (VR == 1) {
			p->bal = 1;
			VR = 0;
			HR = 1;
		}
		else if (HR == 1) {
			if (p->bal == 1) {
				node* q = p->right;
				p->bal = 0;
				q->bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else {
				HR = 0;
			}
		}
	}
}

int main()
{
    srand(time(0));
    node *p = NULL;
    node *v = NULL;
    const int n = 100;
    int arr[n];
    for(int i=0;i<n;i++)
    {
         do
        {
            arr[i]= rand() % 100;
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
    for (int i = 0; i < n; i++)
    {
        AVL(arr[i], p);
    }
    cout << "AVL"
         << "   ";
    showInfo(p);
    cout << endl << endl;
   
    for(int i=0; i < n; i++)
	{
		Btree(arr[i],v);

	}
    cout << "DBD"
         << "    ";
    
    showInfo(v);
    cout << endl;
    
}
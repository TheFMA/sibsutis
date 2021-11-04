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

    cout << " mid_height: " << mid_hight(root) << endl;
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

bool decrease = true;
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
void RR1_turn(node*& p) {
	node* q = p->right;
	if (q->bal == 0) {
		p->bal = 1;
		q->bal = -1;
		decrease = false;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->right = q->left;
	q->left = p;
	p = q;
}

void LL1_turn(node*& p) {
	node* q = p->left;
	if (q->bal == 0) {
		p->bal = -1;
		q->bal = 1;
		decrease = false;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->left = q->right;
	q->right = p;
	p = q;
}

void BL(node*& p) {
	cout<<"BL-";
	if (p->bal == -1) {
		p->bal = 0;
	}
	else if (p->bal == 0) {
		p->bal = 1;
		decrease = false;
	}
	else if (p->bal == 1) {
		if (p->right->bal >= 0) {
			RR1_turn(p);
			cout<<"RR"<<endl;
		}
		else {
		RL_turn(p);
		cout<<"RL"<<endl;
}
	}
}

void BR(node*& p) {
	cout<<"BR-";
	if (p->bal == 1) {
		p->bal = 0;
	}
	else if (p->bal == 0) {
		p->bal = -1;
		decrease = false;

	}
	else if (p->bal == -1) {
		if (p->left->bal <= 0) {
			LL1_turn(p);
			cout<<"LL"<<endl;
		}
		else {
		LR_turn(p);
		cout<<"LR"<<endl;
	}
	}
}

void del(node*& r, node*& q) {

	if (r->right != NULL) {
		del(r->right, q);
		if (decrease) {
			BR(r);
		}
	}
	else {	
		q->data = r->data;
		q = r;
		r = r->left;
		decrease = true;
	}
}

void DeleteAVL(int x, node*& p) {
	if (p == NULL) {
		cout << "Root doesn't exist";
	}
	else if (x < p->data) {
		DeleteAVL(x, p->left);
		if (decrease) {
			BL(p);
			
		}
	}
	else if (x > p->data) {
		DeleteAVL(x, p->right);
		if (decrease) {
			BR(p);
			
		}
	}
	else {
		node * q = p;
		if (q->left == NULL) {
			p = q->right;
			decrease = true;
		}
		else if (q->right == NULL) {
			p = q->left;
			decrease = true;
		}
		else {
			del(q->left, q);
			if (decrease) {
				BL(p);
				
			}
		}
		delete(q);
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
	srand(time(NULL));
	int num, k, t = 1;
	const int n = 100;
	node* root = NULL;
	cout << "Create AVL:" << endl;
	int arr[n];
    for(int i=0;i<n;i++)
    {
         do
        {
            arr[i]= rand() % 100;
        }
        while(prov(i,arr,arr[i]));
    }
	for(int i=0; i < n; i++)
	{
		AVL(arr[i], root);

	}
	// for(int i = 0; i < 10; i++)
	// {
	// 	cout<<"\t Num = ";
	// 	cin>>num;
	// 	AVL(num, root);
	// 	//print(root);
	// 	//cout << endl;
	// }
	print(root);
	cout << endl;
	cout << "Delete AVL:" << endl;
	// for(int j = 0; j <= 10; j++)
	// {
	// 	cout<<"\t Num_Del = ";
	// 	cin>>num;
	// 	DeleteAVL(num, root);
	// 	print(root);
	// 	cout << endl;
	// }
	while (t <= 10)
	{
		cout<<"\t Num_Del = ";
		cin>>num;
		DeleteAVL(num, root);
		showInfo(root);
		print(root);
		cout << endl;
		t++;
	}
}
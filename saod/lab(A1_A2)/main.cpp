#include <iostream>
#include <time.h>
#include <math.h>
#include <iomanip>
using namespace std;

const int n = 10;
int AW[n + 1][n + 1];
int AP[n + 1][n + 1];
int AR[n + 1][n + 1];

struct Vertex
{
	int Data;
	int Weight;
	Vertex* Left;
	Vertex* Right;
};

struct V {
	bool use;
	int data;
	int weight;
};

Vertex* Root;
Vertex* Root_1;
Vertex* Root_2;

void SDP_nReq(int D, Vertex*& Root_1, int i) {
	Vertex** p = &Root_1;
	while ((*p) != NULL) {
		if (D < (*p)->Data)
			p = &((*p)->Left);
		else if (D > (*p)->Data) p = &((*p)->Right);
		else break;
	}

	if (*p == NULL) {
		(*p) = new Vertex;
		(*p)->Data = D;
		(*p)->Weight = i;
		(*p)->Left = NULL;
		(*p)->Right = NULL;
	}
}

void Build_OSTree(int L, int R, int* V, int* W) {
	if (L < R) {
		int k = AR[L][R];
		SDP_nReq(V[k], Root, W[k]);
		Build_OSTree(L, k - 1, V, W);
		Build_OSTree(k, R, V, W);
	}
}

void A1(V* el, Vertex*& Root) {
	Root = NULL;
	int i, max, index;
	for (int i = 0; i < n - 1; i++) {
		el[i].use = false;
	}
	for (int i = 0; i < n - 1; i++) {
		max = 0;
		index = 0;
		for (int j = 0; j < n - 1; j++) {
			if (el[j].weight >= max && el[j].use == false)
			{
				max = el[j].weight;
				index = j;
			}
		}
		el[index].use = true;
		SDP_nReq(el[index].data, Root, el[index].weight);
	}
}

void A2(V* el, Vertex*& Root, int L, int R) {
	int wes, sum;
	wes = sum = 0;
	int i;
	if (L <= R) {
		for(i = L; i < R; i++) {
			wes += el[i].weight;
		}
		for (i = L; i < R-1; i++) {
			if (sum < (wes / 2) && (sum + el[i].weight) > (wes / 2)) {
				break;
			}
			sum += el[i].weight;
		}
		SDP_nReq(el[i].data, Root, el[i].weight);
		A2(el,Root, L, i - 1);
		A2(el, Root, i + 1, R);
	}
}

void SDP_Req(int D, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->Data = D;
		p->Left = NULL;
		p->Right = NULL;
	}
	else if (D < p->Data) {
		SDP_Req(D, p->Left);
	}
	else if (D > p->Data) {
		SDP_Req(D, p->Right);
	}
	//else cout << "Vertex exists in the tree\n";
}



void Insp(Vertex* p) {
	if (p != NULL) {
		Insp(p->Left);
		cout << p->Data << " (" << p->Weight << ") ";
		Insp(p->Right);
	}
}

int Size(Vertex* p) {
	int n;
	if (p == NULL) n = 0;
	else n = 1 + Size(p->Left) + Size(p->Right);
	return n;
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else if (b > a) {
		return b;
	}
	else return a;
}

int Height(Vertex* p) {
	int h;
	if (p == NULL) h = 0;
	else h = 1 + max(Height(p->Left), Height(p->Right));
	return h;
}

int SumLength(Vertex* p, int L) {
	int s;
	if (p == NULL) s = 0;
	else s = L + SumLength(p->Left, L + 1) + SumLength(p->Right, L + 1);
	return s;
}

float DOPsumweight(Vertex* Root) {
	int x;
	if (Root == NULL) {
		x = 0;
	}
	else {
		x = Root->Weight + DOPsumweight(Root->Left) + DOPsumweight(Root->Right);
	}
	return x;
}

float DOPSumlenght(Vertex* Root, int L) {
	int S;
	if (Root == NULL) {
		S = 0;
	}
	else {
		S = Root->Weight*L + DOPSumlenght(Root->Left, L + 1) + DOPSumlenght(Root->Right, L + 1);
	}
	return S;
}

float DOPAverageheight(Vertex* Root) {
	float S;
	S = DOPSumlenght(Root, 1) / DOPsumweight(Root);
	return S;
}

int Checksum(Vertex* p) {
	int S;
	if (p == NULL) S = 0;
	else S = p->Data + Checksum(p->Left) + Checksum(p->Right);
	return S;
}

void Search(Vertex* Root, int x) {
	Vertex* p = Root;
	int res = 0;
	while (p != NULL) {
		if (x < p->Data) p = p->Left;
		else if (x > p->Data) p = p->Right;
		else {
			cout << "Element is found: " << &(p->Data) << " " << p->Data << endl;
			res = 1;
			break;
		}
	}
	if (res == 0)
		cout << "Element isn't found: " << endl;
}

int main() {
	
	srand(time(NULL));
	V arr[n - 1];
	for (int i = 0; i < n - 1; i++) {
		arr[i].data = i + 1;
	}
	for (int i = 0; i < n - 1; i++) {
		arr[i].weight = rand() % 100;
	}
	
	cout<<"Struct arr: "<<endl;;
	for (int i = 0; i < n - 1; i++) {
		cout << arr[i].data << "(" << arr[i].weight << ") ";
	}
	cout << endl;
	cout << endl;

    cout << "    A1: ";
	A1(arr, Root_1);
	Insp(Root_1);
	cout << endl;
    cout << "    A2: ";
	A2(arr, Root_2, 0, n - 2);
	Insp(Root_2);

	cout << "\n\n";
	cout << "\t\tSIZE\t\tSum\t\tAverageHeight\n";
	cout << "A1\t\t  " << Size(Root_1) <<"\t\t "<< Checksum(Root_1) <<"\t\t"<< DOPAverageheight(Root_1) << endl;
	cout << "A2\t\t  " << Size(Root_2) << "\t\t " << Checksum(Root_2) << "\t\t" << DOPAverageheight(Root_2) << endl;

	return 0;
}
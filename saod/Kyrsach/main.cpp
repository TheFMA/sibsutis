#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>

const int N = 4000;

using namespace std;

struct Elem
{
    char full_name[32];
    char street[18];
    short int house_num;
    short int apartment_num;
    char date[10];
};

struct List
{
    List* next;
    Elem* data;
};

struct body {
    List* head;
    List* tail;
};

struct queue
{
    List* top, * tail;
};

List* printList(List* p, short int& count, bool direction)
{
    for (int i = 0; i < 20; i++, count++)
    {
        std::cout << count << ") " << p->data->full_name << "\t" << p->data->street << "\t"
            << p->data->house_num << "\t" << p->data->apartment_num << "\t" << p->data->date
            << endl;
        p = p->next;
    }
    return p;
}

int compare(const Elem& record1, const Elem& record2) {
        if (strcmp(record1.full_name, record2.full_name)>0) {
            return -1;
        }
        else if (strcmp(record1.full_name, record2.full_name) < 0) {
            return 1;
        }
    if (strcmp(record1.street, record2.street) > 0) {
        return -1;
    }
    else if (strcmp(record1.street, record2.street) < 0) {
        return 1;
    }
    return 0;
}

List* MergeSort(List*& S, int n) {
    int t, q, r, i, m;
    List* a, * b, * k, * p;
    body c[2];
    a = S;
    b = S->next;
    k = a;
    p = b;
    int x = 0;
    while (p != NULL) {
        k->next = p->next;
        k = p;
        p = p->next;
    }
    t = 1;
    List* temp1 = a, * temp2 = b;
    while (temp1 != NULL) {
        temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        temp2 = temp2->next;
    }

    while (t < n + 1) {
        c[0].tail = c[0].head = NULL;
        c[1].tail = c[1].head = NULL;
        i = 0;
        m = n;
        while (m > 0) {
            if (m >= t) q = t;
            else q = m;
            m = m - q;
            if (m >= t) r = t;
            else r = m;
            m = m - r;
            while (q != 0 && r != 0) {
                if (compare(*a->data, *b->data) > 0) {
                    if (c[i].tail == NULL) {
                        c[i].tail = c[i].head = a;
                    }
                    else {
                        c[i].tail->next = a;
                        c[i].tail = a;
                    }
                    a = a->next;
                    q--;

                }
                else {

                    if (c[i].tail == NULL) {
                        c[i].tail = c[i].head = b;
                    }
                    else {
                        c[i].tail->next = b;
                        c[i].tail = b;
                    }
                    b = b->next;
                    r--;

                }
            }
            while (q > 0) {
                if (c[i].tail == NULL) {
                    c[i].tail = c[i].head = a;
                }
                else {
                    c[i].tail->next = a;
                    c[i].tail = a;
                }
                a = a->next;
                q--;
            }
            while (r > 0) {
                if (c[i].tail == NULL) {
                    c[i].tail = c[i].head = b;
                }
                else {
                    c[i].tail->next = b;
                    c[i].tail = b;
                }
                b = b->next;
                r--;
            }
            i = 1 - i;
            x++;
        }
        a = c[0].head;
        b = c[1].head;
        t = 2 * t;
    }
    c[0].tail->next = NULL;
    S = c[0].head;
    return S;
}

int PrintSort(List* p, short int& count)
{
    int b = 0;
    for (int i = 0; i < N / 20 + 1; i++)
    {
        p = printList(p, count, 1);
    std:: cout << "Next 20?  1/0: ";
        cin >> b;
        if (b == false)
        {
            break;
            return 1;
        }
    }
}

void make_index_array(Elem* arr[], List* root, int n = N) {
    List* p = root;
    for (int i = 0; i < n; i++) {
        arr[i] = &*(p->data);
        p = p->next;
    }
}

int strcomp(const string& str1, const string& str2, int len = -1) {
    if (len == -1) {
        len = (int)str1.length();
    }
    for (int i = 0; i < len; ++i) {
        if ((str1[i] == '\0') && (str2[i] == '\0')) {
            return 0;
        }
        else if (str1[i] == ' ' && str2[i] != ' ') {
            return -1;
        }
        else if (str1[i] != ' ' && str2[i] == ' ') {
            return 1;
        }
        else if (str1[i] < str2[i]) {
            return -1;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}

void init(queue* q)
{
    q->top = NULL;
    q->tail = NULL;
}
void Create_Queue(queue* q, Elem* R)
{
    List* q2;
    q2 = new List();
    if (q->top == NULL && q->tail == NULL)
    {
        q2->data = R;
        q2->next = NULL;
        q->tail = q2;
        q->top = q->tail;
    }
    else
    {
        List* q3;
        q3 = q->tail->next;
        q->tail->next = q2;
        q2->data = R;
        q2->next = q3;
        q->tail = q2;
    }
}

int B2Search(Elem* arr[], queue * top) {
    string key;
    std::cout << "Input key:";
    cin >> key;
    std::cout << endl;
    int L = 0;
    int R = N - 1;
    int i = 0;
    while (L < R)
    {
        int m = (L + R) / 2;
        if (strcomp(arr[m]->full_name, key, 3) < 0) L = m + 1;
        else R = m;

    }
    i = R;
    while (strcomp(arr[i]->full_name, key, 3) == 0) {
        
            Create_Queue(top, arr[i]);
            i++;
    }
    
    if (strcomp(arr[R]->full_name, key, 3) == 0) return R;
     else  std::cout << "Elements not founded";
}

void PrintQueue(queue* q, int count) {
    List* q2;
    int i = 0;
    count++;
    for (q2 = q->top; q2 != NULL; q2 = q2->next, count++)
    {
        SetConsoleCP(1251);
        
        std::cout << count << ')' << q2->data->full_name << "\t" << q2->data->street << "\t"
                            << q2->data->house_num << "\t" << q2->data->apartment_num << "\t" << q2->data->date
                            << endl;
    }


    printf("\n");
}

struct Vertex {
    Elem* data;
    Vertex* left;
    Vertex* right;
    int balance;
};

int number(queue* q) {
    List* q2;
    int i = 0;
    int count = 0;
    for (q2 = q->top; q2 != NULL; q2 = q2->next, count++)
    {

    }
    return count;
}

void print_record(Elem* data, int i) {
    std::cout << i << ')' << data->full_name << "\t" << data->street << "\t"
        << data->house_num << "\t" << data->apartment_num << "\t" << data->date
        << endl;
}

int strcompt(const string& str1, const string& str2)
{
    int c = 0;

    for (int i = 0; i < 3; ++i)
    {
        if (str1[i] == str2[i])
        {
            c++;
        }
        if (str1[i] < str2[i]) {
            return -1;
        }
        if (str1[i] > str2[i]) {
            return 1;
        }


    }

    return c;


}

bool grow;

void ll(Vertex*& p) {
    Vertex* q = p->left;
    p->balance = q->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void rr(Vertex*& p) {
    Vertex* q = p->right;
    p->balance = q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void lr(Vertex*& p) {
    Vertex* q = p->left;
    Vertex* r = q->right;
    if (r->balance < 0) {
        p->balance = 1;
    }
    else {
        p->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1;
    }
    else {
        q->balance = 0;
    }
    r->balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void rl(Vertex*& p) {
    Vertex* q = p->right;
    Vertex* r = q->left;
    if (r->balance > 0) {
        p->balance = -1;
    }
    else {
        p->balance = 0;
    }
    if (r->balance < 0) {
        q->balance = 1;
    }
    else {
        q->balance = 0;
    }
    r->balance = 0;
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
}



void add_to_avl(Vertex*& p, Elem* h) {


    if (!p) {

        p = new Vertex
        { h, nullptr, nullptr, 0 };
        grow = true;
    }
    else if (strcompt(p->data->full_name, h->full_name) > 0) {

        add_to_avl(p->left, h);
        if (grow) {

            if (p->balance > 0) {
                p->balance = 0;
                grow = false;
            }
            else if (p->balance == 0) {
                p->balance = -1;
                grow = true;
            }
            else {
                if (p->left->balance < 0) {
                    ll(p);
                    grow = false;
                }
                else {
                    lr(p);
                    grow = false;
                }
            }
        }
    }
    else if (strcompt(p->data->full_name, h->full_name) < 0) {

        add_to_avl(p->right, h);
        if (grow) {

            if (p->balance < 0) {
                p->balance = 0;
                grow = false;
            }
            else if (p->balance == 0) {
                p->balance = 1;
                grow = true;
            }
            else {
                if (p->right->balance > 0) {
                    rr(p);
                    grow = false;
                }
                else {
                    rl(p);
                    grow = false;
                }
            }
        }
    }
    else {
        std::cout << "Data already exist";
    }

}

void make_index_array_q(Elem* arr[], List* root, int n) {
    List* p = root;
    for (int i = 0; i < n; i++) {
        arr[i] = &*(p->data);
        std::cout << i << ')' << p->data->full_name << "\t" << p->data->street << "\t"
            << p->data->house_num << "\t" << p->data->apartment_num << "\t" << p->data->date
            << endl;

        p = p->next;
    }
}

void Print_tree(Vertex* p, int& i) {
    if (p) {
        Print_tree(p->left, i);
        print_record(p->data, i++);
        Print_tree(p->right, i);
    }
}

void search_in_tree(Vertex* root, const string& key, int& i) {
    if (root) {

        if (strcompt(key, root->data->street) == 3) {
            search_in_tree(root->left, key, i);
            print_record(root->data, i++);
            search_in_tree(root->right, key, i);
        }
        else {
            search_in_tree(root->left, key, i);
            search_in_tree(root->right, key, i);
        }
    }
}

List* list_move(List* p, int num) {
    for (int i = 0; i < num; i++) {
        p = p->next;
    }
    return p;
}

struct code
{
    char c;
    float p;
};
const int n_symb = 256;
code symb[n_symb];
char C[n_symb][n_symb];
int* Length;
void InsertSort(code* a, int n)
{
    int i, j, k = 0;
    code t;
    for (i = 1; i < n; i++)
    {
        t = a[i];
        j = i - 1;
        while (j >= 0 && a[j].p < t.p)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = t;
    }
}
int m = 0;
float sl = 0, sr = 0;
int Med(int L, int R, code* symb)
{
    sl = 0;
    for (int i = L; i < R; i++)
        sl += symb[i].p;
    sr = symb[R].p;
    m = R;
    while (sl >= sr)
    {
        m--;
        sl -= symb[m].p;
        sr += symb[m].p;
    }
    return m;
}

void Fano(int L, int R, int k, code* symb)
{
    if (L < R)
    {
        k++;
        int m = Med(L, R, symb);
        for (int i = L; i <= R; i++)
        {
            if (i <= m)
            {
                C[i][k] = '0';
                Length[i]++;
            }
            else
            {
                C[i][k] = '1';
                Length[i]++;
            }
        }
        Fano(L, m, k, symb);
        Fano(m + 1, R, k, symb);
    }
}

void Coding_Fano()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(866);
    FILE* f;
    f = fopen("testBase4.dat", "r");

    for (int i = 0; i < n_symb; i++)
    {
        symb[i].c = i;
        symb[i].p = 0.0;
    }

    char c;
    int size = 0;
    while (!feof(f))
    {
        size++;
        char c = getc(f);
        for (int i = 0; i < n_symb; i++)
        {
            if (c == symb[i].c)
            {
                symb[i].p++;
                break;
            }
        }
    }
    fclose(f);
    int cx = 0;
    for (int i = 0; i < n_symb; i++)
    {
        if (symb[i].p != 0)
        {
            cx++;
            symb[i].p = (float)(symb[i].p / size);
        }
    }

    Length = new int[cx];
    for (int i = 0; i < cx; i++)
        Length[i] = 0;

    InsertSort(symb, n_symb);
    Fano(0, cx - 1, 0, symb);
    cout << "\n";

    cout << "Num| Symbol| Probability |  Length  | Code word\n";
    cout << "---|-------|-------------|----------|------------\n";
    for (int i = 0; i < cx; i++)
    {
        printf("%2d ", i + 1);
        printf("%4c   ", symb[i].c);
        printf(" %9f   ", symb[i].p);
        printf("%6d    ", Length[i]);
        for (int j = 0; j <= Length[i]; j++)
            cout << C[i][j];

        cout << "\n";
    }
    cout << "\n";
    float med_length = 0;
    float entropy = 0;
    float sum_p = 0;
    for (int i = 0; i < cx; i++)
    {
        med_length += symb[i].p * Length[i];
        entropy += symb[i].p * log2(symb[i].p);
        sum_p += symb[i].p;
    }
    entropy *= (-1);
    cout << "Medium length = " << med_length << "\n";
    cout << "Entropy = " << entropy << "\n\n\n";

    cout << "Medium L >= Entropy\n";
    cout << "Medium L < Entropy + 1\n\n";
}

int main()
{
    SetConsoleCP(1200);
    SetConsoleOutputCP(1200);
    FILE* fin;
    fin = fopen("testBase4.dat", "rb");

    int z = 0, i,s_ind, s_n = -1;
    short int count;
    bool b;
    int search_ind, search_n = -1;

    Elem* ind_arr[N];
    List* head = new List;
    List* p = head;


    for (int i = 0; i < N; i++)
    {
        p->data = new Elem;
        z = fread((Elem*)p->data, sizeof(Elem), 1, fin);

        if (i != N - 1)
        {
            p->next = new List;
            p = p->next;
        }
        else
        {
            p->next = NULL;
        }
    }

    count = 1;
    p = head;
    int choice = 0;
    std::cin >> choice;
    std::cout << endl;
    if (choice == 1) {
        for (i = 0; i < N / 20 + 1; i++)
        {
            p = printList(head, count, 1);
            std::cout << "Next 20?  1/0: ";
            cin >> b;
            if (b == false)
            {
                break;
                return 1;
            }
        }
    }
    else if(choice == 2){
        p = MergeSort(head, N);
        PrintSort(head, count);
    }
    else if (choice == 3) {
        p = MergeSort(head, N);
        make_index_array(ind_arr, head);
        queue* top = new queue;
        init(top);
        int num = B2Search(ind_arr,top);
        PrintQueue(top, num);
    }
    else if (choice == 4) {
        List* l = MergeSort(head, N);
        make_index_array(ind_arr, head);
        queue* top = new queue;
        init(top);
        int num = B2Search(ind_arr, top);
        int mk = number(top);
        l = list_move(l, num);
        Elem* arr1[4000];
        make_index_array_q(arr1, l, mk);
        cout << endl;
        cout << endl;
        Vertex* root = nullptr;
        List* h = new List;
        Vertex* roots;
        for (int i = 0; i < mk; i++) {
            add_to_avl(root, arr1[i]);
        }
        int i = 1;
        Print_tree(root, i);
        string key;

        std::cout << "Input key Tree:";
        cin >> key;
        std::cout << endl;
        i = 1;

        search_in_tree(root, key, i);
    }
    else if (choice == 5)
    {
        Coding_Fano();
    }

    return 0;
}
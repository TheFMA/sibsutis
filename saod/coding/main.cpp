#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <math.h>

bool sortinrev(const pair<int, int>& a,
	const pair<int, int>& b)
{
	return (a.second > b.second);
}

struct f {
	char key;
	float P;
	float Q;
	int L = 0;
	char* C;
};
void GilbertMur(int size, f* mur) {
	mur[0].Q = 0;
	mur[0].L = -log2(mur[0].P) + 2;
	for (int i = 1; i < size; i++) {
		mur[i].Q = mur[i - 1].Q + (mur[i - 1].P) / 2;
		mur[i].L = -log2(mur[i].P) + 2;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < mur[i].L; j++) {
			mur[i].Q = mur[i].Q * 2;
			if (mur[i].Q >= 1) {
				mur[i].C[j] = '1';
				mur[i].Q -= 1;
			}
			else mur[i].C[j] = '0';
		}
	}
}

#pragma region shennon
void Shennon(int size, f shen[]) {
	shen[0].Q = 0;
	shen[0].L = -log2(shen[0].P) + 1;
	for (int i = 1; i < size; i++) {
		shen[i].Q = shen[i - 1].Q + shen[i - 1].P;
		shen[i].L = -log2(shen[i].P) + 1;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < shen[i].L; j++) {
			shen[i].Q = shen[i].Q * 2;
			if (shen[i].Q >= 1) {
				shen[i].C[j] = '1';
				shen[i].Q -= 1;
			}
			else shen[i].C[j] = '0';
		}
	}
}
#pragma endregion
#pragma region haffman
int Up(int n, float  q, f* charac)
{
	int j = 0;
	for (int i = n - 1; i > 0; i--)
	{
		if (charac[i - 1].P <= q)
			charac[i].P = charac[i - 1].P;
		else
		{
			j = i;
			break;
		}
	}
	charac[j].P = q;
	return j;
}

void Down(int n, int j, f* charac, int size)
{
	char *S = new char[size];
	for (int i = 0; i < size; i++)
		S[i] = charac[j].C[i];
	int L = charac[j].L;
	for (int i = j; i <= n - 2; i++)
	{
		for (int k = 0; k < size; k++)
			charac[i].C[k] = charac[i + 1].C[k];
		charac[i].L = charac[i + 1].L;
	}
	for (int i = 0; i < size; i++)
	{
		charac[n - 1].C[i] = S[i];
		charac[n].C[i] = S[i];
	}
	charac[n - 1].C[L] = '0';
	charac[n].C[L] = '1';
	charac[n - 1].L = L + 1;
	charac[n].L = L + 1;
}

void Haffman(f* charac, int n, int size)
{
	if (n == 1)
	{
		charac[0].C[0] = '0';
		charac[0].L = 1;
		charac[1].C[0] = '1';
		charac[1].L = 1;
	}
	else {
		float q = charac[n - 1].P + charac[n].P;
		int j = Up(n, q, charac);
		Haffman(charac, n - 1, size);
		Down(n, j, charac, size);
	}
}

#pragma endregion 
#pragma region FANO

int Med(int L, int R,f* fano) {
	int SL = 0;
	for (int i = L; i <= R; i++)
	{
		SL += fano[i].P;
	}
	int SR = fano[R].P;
	int m = R;
	while (SL >= SR)
	{
		m--;
		SL -= fano[m].P;
		SR += fano[m].P;
	}

	return m;
}
void Fano(int L, int R, int k,f* fano) {
	int m;
	if (L < R) {
		k++;
		m = Med(L, R, fano);
		for (int i = L; i <= R; i++)
		{
			if (i <= m) {
				fano[i].C[k] = '0';
				fano[i].L++;
			}
			else {
				fano[i].C[k] = '1';
				fano[i].L++;
			}
		}
		Fano(L, m, k,fano);
		Fano(m + 1, R, k,fano);
	}
}
#pragma endregion FANO
void print(int n, f * fano, int count) {
	for (int i = 0; i < n; i++)
	{
		cout << fano[i].key << " ";
		for (int j = 0; j <fano[i].L; j++)
		{
			cout << fano[i].C[j];
		}
		cout.width(4);
		cout << "  " << setprecision(4) << (fano[i].P / count);
		cout << "  " << fano[i].L;
		cout << endl;
	}
}
int main()
{
	string pathToFile = "text.txt";
	vector<pair<char, int>> probability;
	vector<char> origin_base;
	ifstream base(pathToFile, ios::binary);
	if (base.is_open()) {

		while (!base.eof())
		{
			char n;
			base.read((char*)&n, sizeof(char));
			origin_base.push_back(n);
		}
	}
	for (int i = 0; i < origin_base.size(); i++)
	{
		bool f = 0;
		for (int j = 0; j < probability.size(); j++)
		{
			if (origin_base[i] == probability[j].first) {
				f = 1;
				probability[j].second++;
			}

		}
		if (!f) {
			probability.push_back(make_pair(origin_base[i], 1));
		}
	}

	sort(probability.begin(), probability.end(), sortinrev);

	const int n = (int)probability.size();
	int k = -1;

	f* fano = new f[n];
	f* haf = new f[n];
	f* shen = new f[n];
	f* mur = new f[n];
	for (int i = 0; i < probability.size(); i++)
	{
		fano[i].P = probability[i].second;
		fano[i].key = probability[i].first;
		fano[i].C = new char[20];
		haf[i].P = (double)probability[i].second / (double)origin_base.size();
		haf[i].Q = (double)probability[i].second / (double)origin_base.size();
		haf[i].key = probability[i].first;
		haf[i].C = new char[20];
		shen[i].P = (double)probability[i].second/(double)origin_base.size();
		shen[i].key = probability[i].first;
		shen[i].C = new char[20];
		mur[i].P = (double)probability[i].second/(double)origin_base.size();
		mur[i].key = probability[i].first;
		mur[i].C = new char[20];
	}
	
	Fano(0, probability.size() - 1, k, fano);
	cout << "FANO:" << endl;
	print(probability.size(), fano, origin_base.size());
	cout << "Haffman:" << endl;
	cout << endl << endl;
	Haffman(haf, n - 1, n);
	for (int i = 0; i < n; i++)
	{
		cout << haf[i].key << " ";
		for (int j = 0; j < haf[i].L; j++)
		{
			cout << haf[i].C[j];
		}
		cout.width(4);
		cout << "  " << setprecision(4) << (haf[i].Q);
		cout << "  " << haf[i].L;
		cout << endl;
	}
	Shennon(n, shen);
	cout << "Shennon:" << endl;
	cout << endl << endl;
	GilbertMur(n, mur);
	for (int i = 0; i < n; i++)
	{
		cout << shen[i].key << " ";
		for (int j = 0; j < shen[i].L; j++)
		{
			cout << shen[i].C[j];
		}
		cout.width(4);
		cout << "  " << setprecision(4) << (shen[i].P);
		cout << "  " << shen[i].L;
		cout << endl;
	}
	cout << "Mur:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << mur[i].key << " ";
		for (int j = 0; j < mur[i].L; j++)
		{
			cout << mur[i].C[j];
		}
		cout.width(4);
		cout << "  " << setprecision(4) << (mur[i].P);
		cout << "  " << mur[i].L;
		cout << endl;
	}
	double entropy = 0;
	double avg_lenght_fano = 0;
	double avg_lenght_haf = 0;
	double avg_lenght_shen = 0;
	double avg_lenght_mur = 0;
	for (int i = 0; i < probability.size(); i++)
	{
		avg_lenght_fano += fano[i].L * (fano[i].P / origin_base.size());
		avg_lenght_haf += haf[i].L * (haf[i].Q);
		avg_lenght_shen += shen[i].L * shen[i].P;
		avg_lenght_mur += mur[i].L * mur[i].P;
		entropy -= (fano[i].P /origin_base.size()) * log2((fano[i].P / origin_base.size()));
	}
	cout << "ENTROPY\t" << "Fano\t" << "Shen\t" << "haffman\t" << "mur" << endl;
	cout << entropy << "\t" << avg_lenght_fano << "\t" << avg_lenght_shen << "\t" << avg_lenght_haf << "\t" << avg_lenght_mur << endl;


}
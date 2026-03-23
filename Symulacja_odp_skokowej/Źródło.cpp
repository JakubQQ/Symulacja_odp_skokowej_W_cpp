#include<iostream>
#include<vector>

using namespace std;

/*
* Program, który ma wizualizowaæ odpowiedŸ skokow¹ i imupulsow¹ ró¿nych uk³adów w postaci stanowej
* x[n+1] = Ax[n] + Bu[n]
* y[n] = Cx[n] + Du[n]
*/

int main(){
	int wymiar = 0;
	float wspolczynnik = 0;

	vector<vector<float>> MacierzA;
	vector<vector<float>> MacierzB;
	vector<vector<float>> MacierzC;
	vector<vector<float>> MacierzD;
	vector<float> wspolczynniki_a;
	vector<float> wspolczynniki_b;

	cout << "Podaj wymiar macierzy A "; cin >> wymiar; cout << "\n";
	cout << "Macierz A bêdzie w postaci regulatorowej \n";

	for (int i = 0; i < wymiar; i++)
	{
		cout << "Podaj wspolczynnik a" << i + 1 << "\n";
		cin >> wspolczynnik;
		wspolczynniki_a.push_back(wspolczynnik);
	}

	MacierzA.resize(wymiar);
	for (int i = 0; i < wymiar; i++)
	{
		MacierzA[i].resize(wymiar);
	}
	MacierzB.resize(wymiar);
	for (int i = 0; i < wymiar; i++)
	{
		MacierzB[i].resize(1);
	}
	MacierzC.resize(1);
	MacierzC[0].resize(wymiar);

	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (i == wymiar - 1)
			{
				MacierzA[i][j] = -wspolczynniki_a[j];
			}
			else if ((j + 1) == i)
			{
				MacierzA[i][j] = 1;
			}
			else
			{
				MacierzA[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			cout << MacierzA[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}

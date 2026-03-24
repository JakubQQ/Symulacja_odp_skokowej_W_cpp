#include<iostream>
#include<vector>
#include <fstream>

using namespace std;

/*
* Program, który ma wizualizowaæ odpowiedŸ skokow¹ i imupulsow¹ ró¿nych uk³adów w postaci stanowej
* x[n+1] = Ax[n] + Bu[n]
* y[n] = Cx[n] + Du[n]
*/

void wyswietl_macierze(vector<vector<float>>, vector<vector<float>>, vector<vector<float>>,int);
vector<float> pomnoz_macierz_wektor(vector<vector<float>>, vector<float>, int);
vector<float> pomnoz_B_u(vector<vector<float>>, float, int);
vector<float> dodaj_wektory(vector<float>, vector<float>, int);
float pomnoz_C_x(vector<vector<float>> C, vector<float> x, int wymiar);
vector<float> pomnoz_wektor_skalar(vector<float>, float, int);

int main(){
	int wymiar = 0;
	float wspolczynnik = 0;

	vector<vector<float>> MacierzA;
	vector<vector<float>> MacierzB;
	vector<vector<float>> MacierzC;
	vector<float> MacierzD;
	vector<float> wspolczynniki_a;
	vector<float> wspolczynniki_b;
	vector<float> wspolczynniki_c;
	vector<float> wspolczynniki_d;
	vector<float> x;
	vector<float> y;

	cout << "Podaj wymiar macierzy A "; cin >> wymiar; cout << "\n";
	cout << "Macierz A bedzie w postaci regulatorowej \n";

	for (int i = 0; i < wymiar; i++)
	{
		x.push_back(0);
	}
	for (int i = 0; i < wymiar; i++)
	{
		cout << "Podaj wspolczynnik a" << i + 1 << "\n";
		cin >> wspolczynnik;
		wspolczynniki_a.push_back(wspolczynnik);
	}
	for (int i = 0; i < wymiar; i++)
	{
		cout << "Podaj wspolczynnik b" << i + 1 << "\n";
		cin >> wspolczynnik;
		wspolczynniki_b.push_back(wspolczynnik);
	}
	for (int i = 0; i < wymiar; i++)
	{
		cout << "Podaj wspolczynnik c" << i + 1 << "\n";
		cin >> wspolczynnik;
		wspolczynniki_c.push_back(wspolczynnik);
	}
	cout << "Podaj wspolczynnik d" << "\n";
	cin >> wspolczynnik;

	MacierzD.push_back(wspolczynnik);
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
		MacierzC[0][i] = wspolczynniki_c[i];
	}
	for (int i = 0; i < wymiar; i++)
	{
		MacierzB[i][0] = wspolczynniki_b[i];
	}
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (i == wymiar - 1)
			{
				MacierzA[i][j] = -wspolczynniki_a[wymiar - j - 1];
			}
			else if (j == i + 1)
			{
				MacierzA[i][j] = 1;
			}
			else
			{
				MacierzA[i][j] = 0;
			}
		}
	}

	wyswietl_macierze(MacierzA, MacierzB, MacierzC, wymiar);

	ofstream plik("wyniki.csv");

	float dt = 0.01f;
	float t = 0.0f;
	int liczba_probek = 600;

	for (int i = 0; i < liczba_probek; i++)
	{
		float odp_skokowa = 1.0;
		y.push_back(pomnoz_C_x(MacierzC, x, wymiar) + (MacierzD[0] * odp_skokowa));
		cout << "Probka " << i << " y[n]: " << y[i] << "\n";
		vector<float> Ax = pomnoz_macierz_wektor(MacierzA, x, wymiar);
		vector<float> Bu = pomnoz_B_u(MacierzB, odp_skokowa, wymiar);
		vector<float> dx = dodaj_wektory(Ax, Bu, wymiar);
		vector<float> zmiana_x = pomnoz_wektor_skalar(dx, dt, wymiar);
		x = dodaj_wektory(x, zmiana_x, wymiar);
		plik << i << "," << y[i] << "\n";
		t += dt;
	}
	plik.close();
	return 0;
}


void wyswietl_macierze(vector<vector<float>> MacierzA, vector<vector<float>> MacierzB, vector<vector<float>> MacierzC,int wymiar)
{
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			cout << MacierzA[i][j] << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i < wymiar; i++)
	{
		cout << MacierzB[i][0] << "\n";
	}
	for (int i = 0; i < wymiar; i++)
	{
		cout << MacierzC[0][i] << "\n";
	}

}
vector<float> pomnoz_macierz_wektor(vector<vector<float>> M, vector<float> v, int wymiar)
{
	vector<float> wynik(wymiar, 0.0f);
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			wynik[i] += M[i][j] * v[j];
		}
	}
	return wynik;
}
vector<float> pomnoz_B_u(vector<vector<float>> B, float u, int wymiar)
{
	vector<float> wynik(wymiar, 0.0f);
	for (int i = 0; i < wymiar; i++)
	{
		wynik[i] = B[i][0] * u;
	}
	return wynik;
}
vector<float> dodaj_wektory(vector<float> v1, vector<float> v2,int wymiar)
{
	vector<float> wynik(wymiar, 0.0f);
	for (int i = 0; i < wymiar; i++)
	{
		wynik[i] = v1[i] + v2[i];
	}
	return wynik;
}
float pomnoz_C_x(vector<vector<float>> C, vector<float> x, int wymiar)
{
	float wynik = 0.0f;
	for (int i = 0; i < wymiar; i++)
	{
		wynik += C[0][i] * x[i];
	}
	return  wynik;
}
vector<float> pomnoz_wektor_skalar(vector<float> v, float skalar, int wymiar)
{
	vector<float> wynik(wymiar, 0.0f);
	for (int i = 0; i < wymiar; i++)
	{
		wynik[i] = v[i] * skalar;
	}
	return wynik;
}
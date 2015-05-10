// Komiwojazer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <io.h>
#include <iostream>
#include <fstream>
#include <regex>

#include <algorithm> //do permutacji

using namespace std;

class Dane
{
public:

	int n;
	int m;
	int *permutacje;
	int *permutacjeWlasciwe;
	int **macierz;
	int numOfUniqeElements;

	string *linia;
	Dane(char *source);
	int macierzSasiedztwa(int i);
	void wyswietlMacierz(int **macierz, int m);
	void dopelnijMacierz(int **macierz, int m);
	int wojazujkomiku(int **tab, int *permut, int rozmiar);
	int wektorMiast(int *perm, int rozmiar);
};

int Dane::wojazujkomiku(int **macierz, int *permut, int p)
{
	wyswietlMacierz(macierz, m + 1);

	for (int idx = 0; idx < Dane::numOfUniqeElements; idx++)
	{
		cout << permut[idx] << endl;
	}

	int sum = 0;
	int sum2 = 100000000;
	int min = 0;
	int nsilnia = 0;
	
	do {
		nsilnia++;
		for (int i = 0; i < Dane::numOfUniqeElements-1 ; i++)
		{
			sum += macierz[ permut[i] ][ permut[i + 1]  ];
		}
		if (sum < sum2)
			sum2 = sum;

		cout << sum2 << "=suma"<<endl;



	} while (next_permutation(permut, permut + Dane::numOfUniqeElements));

	cout << "n!= " << nsilnia<<"najkrotsza droga"<<sum2<<endl;
	return 0;
}

int Dane::wektorMiast(int *permutacje, int n)
{
	
	//eliminacja nadmiarowych elementow w tablicy permutacje
	int *tabtemp = new int[n * 2 + 1];

	
	for (int idx = 0; idx < n * 2; idx++)
	{
		tabtemp[idx] = 0;
		tabtemp[Dane::permutacje[idx]] += 1;
	}
	
	numOfUniqeElements = 0;
	for (int j = 0; j < n * 2; j++)
	{
		if (tabtemp[j] != 0)
			numOfUniqeElements++;
	}
	Dane::permutacjeWlasciwe = new int[Dane::numOfUniqeElements]; Dane::numOfUniqeElements = 0;

	for (int j = 0; j < n * 2; j++)
	{
		if (tabtemp[j] != 0)
		{
			permutacjeWlasciwe[numOfUniqeElements] = j;
			numOfUniqeElements++;
		}
	}
	/////////////////////////
	/*cout << endl <<"permutacje wlasciwe"<< endl;
	for (int idx = 0; idx < numOfUniqeElements; idx++)
	{
		cout << permutacjeWlasciwe[idx] << endl;
	}
	*/

	return *permutacjeWlasciwe;
}

void Dane::dopelnijMacierz(int **macierz, int p)
{
	for (int j = 0; j < p; j++)
	{
		for (int i = 0; i < p; i++)
		{
			if (macierz[j][i]<-100000 || macierz[j][i]>100000)
				macierz[j][i] = 0;
		}
	}
}

void Dane::wyswietlMacierz(int **macierz, int p)
{
	for (int j = 0; j < p; j++)
	{
		for (int i = 0; i < p; i++)
		{
			if (macierz[j][i]<-1000 || macierz[j][i]>10000)
				cout << " " << " ;";
			else if (macierz[j][i] == 0)
				 cout << macierz[j][i]<< " ;";
			else
				cout << macierz[j][i] << " ;";
		}
		cout << endl;
	}

}

Dane::Dane(char *source)
{


	fstream instance(source, ios::in);

	if (instance.good())
		cout << "Udalo sie otworzyc plik" << endl;
	else
	{
		cout << "nie udalo sie otworzyc pliku" << endl; getchar(); exit(0);
	}

	regex wzorzec1("([[:w:]]{1,}) ([[:w:]]{1,}) ([[:w:]]{1,})");
	smatch Matched;
	
	int i = 0;
	Dane::m = 0;
	string *test = new string[1];//sprawdzamy iloœæ wierszy w pliku
	
	while (getline(instance, test[0]))//liczenie wierszy oraz wyznaczanie maximum
	{
		regex_search(test[0], Matched, wzorzec1);

		if (Matched[1] > m)
			Dane::m = stoi(Matched[1]);
		if (Matched[2] > m)
			Dane::m = stoi(Matched[2]);
		i++;	
	}
	Dane::n = i;
	//---------------------------------------------------------------------------------------------//
	fstream instancee(source, ios::in);//nie dzialal seeking wiec trzeba bylo nowa instancje stworzyc
									   //zapytac sie o seeking w pliku instance.seekg(0, ios::beg);

	int j = 0; int tmp = 0;
	macierzSasiedztwa(m);				//Stwórz czyst¹ macierz s¹siedztwa
	
	Dane::linia = new string[i];
	permutacje = new int[i*2+1];

	while (getline(instancee, linia[j]))//pobieranie danych z wiersza sprawdzanie regexem i zapis do macierzy s¹siedztwa
	{
		regex_search(linia[j], Matched, wzorzec1);
		macierz[stoi(Matched[1])][stoi(Matched[2])] = stoi(Matched[3]);
		macierz[stoi(Matched[2])][stoi(Matched[1])] = stoi(Matched[3]);
		permutacje[j] = stoi(Matched[1]);
		permutacje[j + i] = stoi(Matched[2]);
		
		j++;
	}
	
	//eliminacja nadmiarowych elementow w tablicy permutacje
	


	//wyswietlMacierz(macierz, m+1);
	delete []linia;
	delete[]test;

	instance.close();
	instancee.close();
}

int Dane::macierzSasiedztwa(int p)
{
	p++;//inkrementacja dla brzegów macierzy

	// generowanie poszczegolnych wymiarów
	
	try {
		Dane::macierz = new int *[p];}
	catch (std::bad_alloc) {
		std::cout << "Allocation failed: " << '\n';}
	

	try 
	{
		Dane::macierz = new int *[p];
		for (int i = 0; i<p; i++)
			macierz[i] = new int[p];
	}
	catch (std::bad_alloc) 
	{
		std::cout << "Allocation failed: " << '\n';
	}
	
	/*Dane::macierz = new int *[p];
	for (int i = 0; i<p; i++)
		macierz[i] = new int[p];
*/
	// wypisywanie brzegow w tablicy
	for (int i = 0; i < p; i++)
	{
		macierz[i][0] = i;
		macierz[0][i] = i;
	}

	//wype³nianie macierzy s¹siedztwa 0
	dopelnijMacierz(macierz, p);

	return 0;
}


int main()
{

	char sourcee[]="C:\\Users\\Mat\\Desktop\\Dane_sort.txt";
	Dane komi(sourcee);
	
	komi.wektorMiast(komi.permutacjeWlasciwe, komi.n);
	komi.wojazujkomiku(komi.macierz,komi.permutacjeWlasciwe ,komi.n);
	return 0;
}


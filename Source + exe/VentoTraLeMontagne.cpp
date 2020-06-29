#include <iostream>
#include <Windows.h>
#include <cstdlib>			//serve per la funzione del numero random
#include <ctime>			//serve per generare un numero usando il tempo del computer. numero che dopo andr� passato alla funzione srand, che a sua volta comunicher� con il rand per dare un numero casuale
using namespace std;

enum colors {blue = 9, def = 15};

void Color(colors color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

const int DIM = 10;
const int RANGE = 30;				//Grandezza massima creata dai numeri casuali

struct Vetta
{
	int altezza;
	bool passato = false;
};

struct Coordinate
{
	int riga;
	int colonna;
};

void InserisciNumeriRandom(Vetta M[DIM][DIM]);
void Visualizza(Vetta M[DIM][DIM]);
Coordinate TrovaMin(Vetta M[DIM][DIM], Coordinate min);

int main()
{
	Vetta Montagne[DIM][DIM];
	Coordinate ProssimaCasella;

	Color(def);

	InserisciNumeriRandom(Montagne);

	Visualizza(Montagne);

	do
	{
		cout << "     - Da che riga vuoi partire?   ";
		cin >> ProssimaCasella.riga;
	} while (ProssimaCasella.riga < 1 || ProssimaCasella.riga >8);

	ProssimaCasella.colonna = 0;
	Montagne[ProssimaCasella.riga][ProssimaCasella.colonna].passato = true;

	do
	{
		ProssimaCasella = TrovaMin(Montagne, ProssimaCasella);
	} while (ProssimaCasella.colonna != DIM - 1);

	Sleep(1000);
	system("cls");
	Visualizza(Montagne);

	cout << "\nSei Arrivato a valle!!";
	system("pause>nul");
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------- Inserisce numeri random tranne la prima e l'ultima riga

void InserisciNumeriRandom(Vetta M[DIM][DIM])
{
	srand(time(0));																// da un numero basandosi sull'ora del pc

	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			M[i][j].altezza = 1 + (rand() % RANGE);								// usando come base il numero creato nella riga sopra, crea dei numeri """casuali""" da inserire nella matrice
		}
	}
	for (int j = 0; j < DIM; j++)
	{
		M[0][j].altezza		  = INT_MAX;
		M[0][j].passato		  = true;
		M[DIM - 1][j].altezza = INT_MAX;
		M[DIM - 1][j].passato = true;
	}
}

//--------------------------------------------------------------------------------------------------------------- Visualizza

void Visualizza(Vetta M[DIM][DIM])
{
	Color(blue);
	cout << "                                 SCORRIMENTO VENTO\n\n";
	Color(def);

	for (int i = 1; i < DIM-1; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			if (M[i][j].passato == true)
			{
				Color(blue);
				cout << M[i][j].altezza << "\t";
				Color(def);
			}
			else
			{
				cout << M[i][j].altezza << "\t";
			}
		}
		cout << endl<<endl;
	}
}

//-----------------------------------------------------------------------------------------------------------Trova il numero minore tra quelli adiacenti ma non indietro

Coordinate TrovaMin (Vetta M[DIM][DIM], Coordinate min)
{
	int piubasso = INT_MAX;
	Coordinate copiadimin;  //copia min dentro qui <===================================================================================================================================

	copiadimin.riga = min.riga;
	copiadimin.colonna = min.colonna;

	Sleep(1000);
	system("cls");
	Visualizza(M);

		if (M[min.riga-1][min.colonna].passato == false)
		{
			if (M[min.riga-1][min.colonna].altezza < piubasso)
			{
				copiadimin.riga = min.riga-1;
				piubasso = M[copiadimin.riga][copiadimin.colonna].altezza;
			}
		}

		if (M[min.riga -1][min.colonna +1].passato == false)
		{
			if (M[min.riga -1][min.colonna +1].altezza < piubasso)
			{
				copiadimin.riga = min.riga - 1;
				copiadimin.colonna = min.colonna +1;

				piubasso = M[copiadimin.riga][copiadimin.colonna].altezza;
			}
		}

		if (M[min.riga][min.colonna +1].passato == false)
		{
			if (M[min.riga][min.colonna +1].altezza < piubasso)
			{
				copiadimin.colonna = min.colonna +1;
				copiadimin.riga = min.riga;

				piubasso = M[copiadimin.riga][copiadimin.colonna].altezza;
			}
		}

		if (M[min.riga +1][min.colonna +1].passato == false)
		{
			if (M[min.riga +1][min.colonna +1].altezza < piubasso)
			{
				copiadimin.riga = min.riga +1;
				copiadimin.colonna = min.colonna +1;

				piubasso = M[copiadimin.riga][copiadimin.colonna].altezza;
			}
		}

		if (M[min.riga +1][min.colonna].passato == false)
			{
				if (M[min.riga +1][min.colonna].altezza < piubasso)
				{
					copiadimin.riga = min.riga + 1;
					copiadimin.colonna = min.colonna;

					piubasso = M[copiadimin.riga][copiadimin.colonna].altezza;
				}
			}

		M[copiadimin.riga][copiadimin.colonna].passato = true;

		return copiadimin;
}

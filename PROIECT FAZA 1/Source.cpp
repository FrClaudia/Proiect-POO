#include<iostream>
#include<string>
#include "TABELA.h"
#include "ComandaUtilizator.h"
using namespace std;

//COMENTARII:
//Comenzile merg toate in afara de UPDATE (pe care l-am comentat fiind nefinalizat). Am lasat main-ul necomentat, pentru a fi putea fi testate
//Sintaxa ce se va introduce de la tastatura va cuprinde mereu spatii intre cuvinte si operatori (=). Nu am gasit alta solutie.
//Am facut initial tot proiectul pe public (in clase) si de curand am vazut ca trebuia sa folosim doar private. 
//Am facut getteri si setteri dar nu am apucat sa inlocuim peste tot, motiv pentru care inca avem atributele pe public. 
//Urmeaza sa mai modificam peste tot si sa trecem pe private.

int main()
{
	TABELA* tab = nullptr;
	int nr_tab = 0;
	char* comanda = nullptr;
	string buffer;
	int c = 1;
	string s;
	cout << "Utilizatorul curent este: ";
	cin >> ws;
	getline(cin, s);
	TABELA::setUtilizator(s);
	while (c == 1)
	{
		cout << endl;
		cout << endl << "Introduceti comanda SQL de la tastatura:" << endl;
		cin >> ws;
		getline(cin, buffer);
		if (comanda != nullptr)
		{
			delete[] comanda;
		}
		comanda = new char[buffer.length() + 1];
		strcpy_s(comanda, buffer.length() + 1, buffer.c_str());

		cout << endl << "Comanda introdusa a fost: " << endl << comanda << endl;

		comanda_utilizator(comanda, tab, nr_tab);

		cout << endl << endl << "Daca doriti introducerea unei noi comenzi apasati tasta 1, daca nu, orice alt nr: ";
		cin >> c;

		for (int i = 0; i < nr_tab; i++)
		{
			cout << "Nume tabela: " << tab[i].nume_tabela << "   Utilizator curent: " << tab[i].getUtilizator() << endl;
		}
		cout << endl;
	}
	delete[] comanda;
}
//  ex comanda:
//  CREATE TABLE carti((titlu,text,20,null),(pagini,integer,3,0))
//  INSERT INTO carti VALUES(Divergent,200)
//  DELETE FROM carti WHERE titlu = Divergent
//  CREATE TABLE caiete((pret,float,2,0.0),(pagini,integer,3,0))
//  INSERT INTO carti VALUES(1.1,200)

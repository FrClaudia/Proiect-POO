#include<iostream>
#include<string>
#include "TABELA.h"
#include "ComandaUtilizator.h"
#include "creare_fisier_comenzi.h"
#include "citire_txt.h"

using namespace std;

//COMENTARII:
//toate comenzile obligatorii (CREATE, DISPLAY, DROP, INSERT, UPDATE, DELETE, SELECT .../ALL FROM ...) sunt functionale
//Sintaxa folosita pentru comenzile de la tastatura va cuprinde mereu spatii intre cuvinte si operatori (=). Nu am gasit alta solutie.
//Am facut initial tot proiectul pe public (in clase) si de curand am vazut ca trebuia sa folosim doar private. 
//Am facut getteri si setteri dar inca avem clasele pe public, deoarece am inlocuit getterii si setterii in anumite locuri si anumite comenzi nu mai mergeau perfect.
//Am preferat sa ramanem la varianta in care nu folosim getteri si setteri 100%, pentru ca functionalitatea aplicatiei sa fie cea dorita.

int main()
{
	int qn;
	cout << "Doriti vizualizarea comenzilor efectuate in sesiunile anterioare?" << endl;
	cout << "Daca doriti, apasati 1. Daca nu, orice alta tasta:";
	cin >> qn;
	cout << endl;
	if (qn == 1)
	{
		citire_txt ct;
		ct.citire();
	}
	cout << endl;

	TABELA* tab = nullptr;
	int nr_tab = 0;
	char* comanda = nullptr;
	string buffer;
	int c = 1;
	int ok = 0;

	cout << "Daca doriti actualizarea bazei de date cu informatiile din sesiunile precedente, apasati 1." << endl;
	cout << "Daca apasati orice alt nr, in baza de date nu va exista nicio informatie precedenta.";
	cout << "Apasati tasta dorita:";
	cin >> qn;
	cout << endl;
	if (qn == 1)
	{
		ifstream file;
		//se vor citi comenzile precedente din fisier pentru a se simula baza de date creata in sesiunile anterioare
		//la primul RUN nu se va actualiza nimic, deoarece nu exista informatii anterioare
		file.open("COMENZI.txt");
		string line;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				int ln = line.length();
				char* arr = new char[ln + 1];
				strcpy_s(arr, ln + 1, line.c_str());
				comanda_utilizator(arr, tab, nr_tab, ok);
			}
			file.close();
			cout << endl << endl << "BAZA DE DATE A FOST ACTUALIZATA. SE POATE CONTINUA." << endl;
		}
		else cout << "Nu exista actualizari!" << endl<< endl;
		file.close();
	}

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

		//cout << endl << "Comanda introdusa a fost: " << endl << comanda << endl;

		comanda_utilizator(comanda, tab, nr_tab, ok);
		if (ok == 1)
		{
			creare_fisier_comenzi cls;
			cls.creare_fisier_c(comanda);
			ofstream file("COMENZI.txt", ios::app);
			if (file.is_open())
			{
				file << comanda << '\n';
				file.close();
			}
			else cout << "Fisierul nu a putut fi deschis pt scriere in el. Comanda nu a fost inregistrata." << endl;
		}
		cout << endl << endl<< "Daca doriti introducerea unei noi comenzi apasati tasta 1, daca nu, orice alt nr: ";
		cin >> c;

		for (int i = 0; i < nr_tab; i++)
		{
			cout << "Nume tabela: " << tab[i].getnume_tabela() << "   Utilizator curent: " << tab[i].getUtilizator() << endl;
		}
	}
	delete[] comanda;
}
//  ex comenzi:
//  CREATE TABLE carti((titlu,text,20,null),(pagini,integer,3,0))
//  INSERT INTO carti VALUES(Divergent,200)
//  INSERT INTO carti VALUES(Insurgent,400)
//  UPDATE carti SET pagini = 300 WHERE titlu = Divergent
//  UPDATE carti SET titlu = DIVERGENT WHERE titlu = Divergent
//  DELETE FROM carti WHERE titlu = DIVERGENT
//  SELECT ALL FROM carti
//  CREATE TABLE caiete((pret,float,2,0.0),(pagini,integer,3,0))
//  INSERT INTO caiete VALUES(1.1,200)
//  DROP TABLE carti
#include<iostream>
#include<string>
#include "TABELA.h"
#include "ComandaUtilizator.h"
#include "creare_fisier_comenzi.h"
#include "citire_txt.h"
#include "meniu.h"
#include "extinderi.h"
using namespace std;

//COMENTARII: Toate comenzile obligatorii (CREATE, DISPLAY, DROP, INSERT, UPDATE, DELETE, SELECT .../ALL FROM ...) sunt functionale
//Avem un meniu realizat; se simuleaza o baza de date printr-o "actualizare" cu ce s-a facut in sesiunile anterioare (cu ajutorul unui fisier)
//Sintaxa folosita pentru comenzile de la tastatura va cuprinde mereu spatii intre cuvinte si operatori (=). Nu am gasit alta solutie.
//Am facut initial tot proiectul pe public (in clase) si de curand am vazut ca trebuia sa folosim doar private. 
//Am facut getteri si setteri dar inca avem clasele pe public, deoarece am inlocuit getterii si setterii in anumite locuri si anumite comenzi nu mai mergeau perfect.
//Am preferat sa ramanem la varianta in care nu folosim getteri si setteri 100%, pentru ca functionalitatea aplicatiei sa fie cea dorita.

int main()
{
	TABELA* tab = nullptr; int nr_tab = 0; int ok = 0;
	cout << "Va urma actualizarea BD. Apasati orice numar de la tastatura pentru a continua: ";
	int t; cin >> t;
	if (t)//se vor citi comenzile precedente din fisier pentru a se simula baza de date creata in sesiunile anterioare
	{     //la primul RUN nu se va actualiza nimic, deoarece nu exista informatii anterioare
		ifstream file;
		file.open("COMENZI.txt"); string line;
		if (file.is_open()) {
			while (getline(file, line)) {
				if (line[0] != 'S' && line[1] != 'I') {
					int ln = line.length();
					char* arr = new char[ln + 1];
					strcpy_s(arr, ln + 1, line.c_str());
					comanda_utilizator(arr, tab, nr_tab, ok);
				}
			}
			file.close();
			cout << endl << "BAZA DE DATE A FOST ACTUALIZATA. SE POATE CONTINUA." << endl << endl;
		}
		else cout << "Nu exista actualizari!" << endl << endl;
		file.close();
		string s;
		cout << endl << "Utilizatorul curent este: ";
		cin >> ws;
		getline(cin, s);
		TABELA::setUtilizator(s);
		cout << endl;
		meniu(tab, nr_tab);
		cout << "Fisierele text cu comenzi create in aceasta sesiune: ";
		for (list<string>::iterator it = lista_fisiere_comenzi.begin(); it != lista_fisiere_comenzi.end(); it++)
		{
			cout << *it << " ; ";
		} cout << endl;
	}
	else cout << "Nu s-a introdus un numar. Restartati aplicatia si incercati din nou!";
}
//  ex comenzi:
//  CREATE TABLE carti((titlu,text,20,null),(pagini,integer,3,0))
//  INSERT INTO carti VALUES(Divergent,200)
//  INSERT INTO carti VALUES(Insurgent,400)
//  UPDATE carti SET pagini = 300 WHERE titlu = Divergent
//  UPDATE carti SET titlu = DIVERGENT WHERE titlu = Divergent
//  DELETE FROM carti WHERE titlu = DIVERGENT
//  SELECT ALL FROM carti
//  CREATE TABLE caiete((pret,float,2,0.0),(NrPagini,integer,3,0))
//  INSERT INTO caiete VALUES(1.1,200)
//  DROP TABLE carti

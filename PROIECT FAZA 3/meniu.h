#ifndef me
#define me
#include "TABELA.h"
#include<vector>
#include "ierarhie.h"


void meniu(TABELA*& tab, int& nr_tab)
{
	vector <optiune*> v;
	vector <optiune*>::iterator it;
	optiune_introducere_comanda op1(1, "optiune de introducere comanda SQL de la tastatura");
	afis_nr_tab op2(2, "optiune de vizualizare", "numar total de tabele din BD");
	afis_nume_tab op3(3, "optiune de vizualizare", "nume tabele din BD");
	afis_inregistari_tabela op4(4, "optiune de vizualizare", "toate inregistarile din tabelele din BD");
	afis_struct_tabele op5(5, "optiune de vizualizare", "structura fiecarei tabele din BD");
	v.push_back(&op1);
	v.push_back(&op2);
	v.push_back(&op3);
	v.push_back(&op4);
	v.push_back(&op5);
	int nr_tastatura;
	cout << endl;
	cout <<  "OPTIUNI MENIU: " << endl;
	for (it = v.begin(); it != v.end(); it++)
	{
		cout << "OPTIUNE TASTA "; (*it)->afis_index();  cout << ": ";
		(*it)->afis_opt();
		cout << endl;
	}
	cout << endl << "Alegeti optiunea dorita: ";
	cin >> nr_tastatura;
	while (nr_tastatura == 1 || nr_tastatura == 2 || nr_tastatura == 3 || nr_tastatura == 4 || nr_tastatura == 5)
	{
		if (nr_tastatura == 1) v[nr_tastatura - 1]->functionalitate(tab, nr_tab);
		else
			v[nr_tastatura - 1]->functionalitate_af(tab, nr_tab);
		cout << endl;
		cout << "OPTIUNI MENIU: " << endl;
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "OPTIUNE TASTA "; (*it)->afis_index();  cout << ": ";
			(*it)->afis_opt();
			cout << endl;
		}
		cout << endl << "Alegeti optiunea dorita: ";
		cin >> nr_tastatura;
	}
}

#endif // !me

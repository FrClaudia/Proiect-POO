#ifndef ier
#define ier
#include "TABELA.h"

class afisabil_opt
{
public:
	virtual void afis_opt() = 0;
	virtual void afis_index() = 0;
};

class optiune : public afisabil_opt
{
	int index_opt;
public:
	optiune()
	{
		index_opt = 100;
	}
	optiune(int i)
	{
		index_opt = i;
	}
	void afis_index() override
	{
		cout << index_opt;
	}
	void afis_opt() override
	{
		cout << "Afisare optiune din cls de baza." << endl;
	}
	virtual void functionalitate_af(TABELA* tab, int nr_tab)
	{
		cout << "Functionalitate afis din cls de baza" << endl;
	}
	virtual void functionalitate(TABELA*& tab, int& nr_tab)
	{
		cout << "Functionalitate din cls de baza" << endl;
	}
	virtual void actualiz(TABELA*& tab, int& nr_tab, int ok)
	{
		cout << "Actualizare din cls de baza" << endl;
	}
};

class optiune_introducere_comanda : public optiune
{
	string text_opt;
public:
	optiune_introducere_comanda(int i, string s) : optiune(i)
	{
		text_opt = s;
	}
	void afis_opt() override
	{
		cout << text_opt << " ";
	}
	string getTextOpt()
	{
		return text_opt;
	}
	void functionalitate(TABELA*& tab, int& nr_tab) override
	{
		char* comanda = nullptr; string buffer;	int ok = 0;
		cout << endl << "Introduceti comanda SQL de la tastatura:" << endl;
		cin >> ws;
		getline(cin, buffer);
		if (comanda != nullptr)
		{
			delete[] comanda;
		}
		comanda = new char[buffer.length() + 1];
		strcpy_s(comanda, buffer.length() + 1, buffer.c_str());
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
		delete[] comanda;
	}
};

class optiune_afis : public optiune
{
	string text_opt;
public:
	optiune_afis(int i, string s) : optiune(i)
	{
		text_opt = s;
	}
	void afis_opt() override
	{
		cout << text_opt << " ";
	}
	string getTextOpt()
	{
		return text_opt;
	}
};

class afis_nume_tab : public optiune_afis
{
	string detalii;
public:
	afis_nume_tab(int i, string s1, string s2) : optiune_afis(i, s1)
	{
		detalii = s2;
	}
	void afis_opt() override
	{
		cout << getTextOpt() << " " << detalii;
	}
	void functionalitate_af(TABELA* tab, int nr_tab) override //afisare nume tabele
	{
		cout << "Tabelele din baza de date sunt urmatoarele:" << endl;
		for (int i = 0; i < nr_tab; i++)
		{
			cout << "Nume tabela: " << tab[i].getnume_tabela() << "   Utilizator curent: " << tab[i].getUtilizator() << endl;
		}
		cout << endl;
	}
};

class afis_nr_tab : public optiune_afis
{
	string detalii;
public:
	afis_nr_tab(int i, string s1, string s2) : optiune_afis(i, s1)
	{
		detalii = s2;
	}
	void afis_opt() override
	{
		cout << getTextOpt() << " " << detalii;
	}
	void functionalitate_af(TABELA* tab, int nr_tab) override //afisare nr total tabele
	{
		cout << "Numarul de tabele din baza de date este: " << nr_tab << "." << endl << endl;
	}
};

class afis_inregistari_tabela : public optiune_afis
{
	string detalii;
public:
	afis_inregistari_tabela(int i, string s1, string s2) : optiune_afis(i, s1)
	{
		detalii = s2;
	}
	void afis_opt() override
	{
		cout << getTextOpt() << " " << detalii;
	}
	void functionalitate_af(TABELA* tab, int nr_tab) override //afisare INREGISTRARI tabele
	{
		for (int j = 0; j < nr_tab; j++)
		{
			TABELA copie_tab = tab[j];
			cout << copie_tab;
		}
	}
};

class afis_struct_tabele : public optiune_afis
{
	string detalii;
public:
	afis_struct_tabele(int i, string s1, string s2) : optiune_afis(i, s1)
	{
		detalii = s2;
	}
	void afis_opt() override
	{
		cout << getTextOpt() << " " << detalii;
	}
	void functionalitate_af(TABELA* tab, int nr_tab) override //afisare structura tabele
	{
		for (int w = 0; w < nr_tab; w++) {
			cout << "Numele tabelei: " << tab[w].nume_tabela << endl;
			int kt = 0; int ki = 0; int kf = 0;
			for (int j = 0; j < tab[w].nr_total_coloane; j++) {//j parcurge coloanele in general, iar k de t,i,f retine pozitia parcurgerii pe tipuri
				if (tab[w].ordine_coloane[j] == 1) {
					cout << tab[w].coloane_text[kt].nume_coloana;
					cout << " text" << "(" << tab[w].coloane_text[kt].dimensiune_text << ")" << endl;
					kt++; //trece la urmatoarea coloana !! de acelasi tip !!
				}
				if (tab[w].ordine_coloane[j] == 2) {
					cout << tab[w].coloane_integer[ki].nume_coloana;
					cout << " int" << "(" << tab[w].coloane_integer[ki].getDimensiuneInteger() << ")" << endl;
					ki++;
				}
				if (tab[w].ordine_coloane[j] == 3) {
					cout << tab[w].coloane_float[kf].nume_coloana;
					cout << " float" << "(" << tab[w].coloane_float[kf].getDimensiuneFloat() << ")" << endl;
					kf++;
				}
			}
			cout << endl;
		}
	}
};

#endif // !ier


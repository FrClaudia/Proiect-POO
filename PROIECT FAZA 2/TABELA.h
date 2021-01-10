#ifndef TABELA_H
#define TABELA_H
#include "C_integer.h"
#include "C_float.h"
#include "C_text.h"

class TABELA
{
public:
	string nume_tabela;
	int nr_total_coloane = 0;
	C_text* coloane_text = nullptr;
	int nr_coloane_text = 0;
	C_integer* coloane_integer = nullptr;
	int nr_coloane_integer = 0;
	C_float* coloane_float = nullptr;
	int nr_coloane_float = 0;
	int ordine_coloane[20];// 1->text , 2->integer , 3->float  //presupunem ca nu avem mai mult de 20 de col intr-o tabela
	static string utilizator_bd;

	TABELA() //constructor implicit
	{
		nume_tabela = "necunoscut";
		nr_total_coloane = 0;
		nr_coloane_text = 0;
		nr_coloane_integer = 0;
		nr_coloane_float = 0;
		coloane_text = nullptr;
		coloane_integer = nullptr;
		coloane_float = nullptr;
	}

	TABELA(string nume, int nr_col_text, int nr_col_integer, int nr_col_float) //constructor cu parametri 1
	{
		nume_tabela = nume;
		nr_coloane_text = nr_col_text;
		coloane_text = new C_text[nr_col_text];
		nr_coloane_integer = nr_col_integer;
		coloane_integer = new C_integer[nr_col_integer];
		nr_coloane_float = nr_col_float;
		coloane_float = new C_float[nr_col_float];
		nr_total_coloane = nr_coloane_text + nr_coloane_integer + nr_coloane_float;
	}
	TABELA(string nume)//constructor cu paramteri 2
	{
		nume_tabela = nume;
		nr_total_coloane = 0;
		nr_coloane_text = 0;
		nr_coloane_integer = 0;
		nr_coloane_float = 0;
		coloane_text = nullptr;
		coloane_integer = nullptr;
		coloane_float = nullptr;
	}
	TABELA(const TABELA& t)
	{
		this->nume_tabela = t.nume_tabela;
		if (t.coloane_text != nullptr && t.nr_coloane_text > 0)
		{
			this->nr_coloane_text = t.nr_coloane_text;
			coloane_text = new C_text[t.nr_coloane_text];
			for (int j = 0; j < t.nr_coloane_text; j++)
			{
				this->coloane_text[j] = t.coloane_text[j];
			}
		}
		else
		{
			this->nr_coloane_text = 0;
			this->coloane_text = nullptr;
		}
		if (t.coloane_integer != nullptr && t.nr_coloane_integer > 0)
		{
			this->nr_coloane_integer = t.nr_coloane_integer;
			coloane_integer = new C_integer[t.nr_coloane_integer];
			for (int j = 0; j < t.nr_coloane_integer; j++)
			{
				this->coloane_integer[j] = t.coloane_integer[j];
			}
		}
		else
		{
			this->nr_coloane_integer = 0;
			this->coloane_integer = nullptr;
		}
		if (t.coloane_float != nullptr && t.nr_coloane_float > 0)
		{
			this->nr_coloane_float = t.nr_coloane_float;
			coloane_float = new C_float[t.nr_coloane_float];
			for (int j = 0; j < t.nr_coloane_float; j++)
			{
				this->coloane_float[j] = t.coloane_float[j];
			}
		}
		else
		{
			this->nr_coloane_float = 0;
			this->coloane_float = nullptr;
		}
		if (t.nr_total_coloane > 0)
		{
			this->nr_total_coloane = t.nr_total_coloane;
			for (int j = 0; j < t.nr_total_coloane; j++)
			{
				this->ordine_coloane[j] = t.ordine_coloane[j];
			}
		}
		else
		{
			this->nr_total_coloane = 0;
		}
	}

	TABELA& operator=(const TABELA& t)
	{
		if (coloane_text != nullptr)
		{
			delete[] coloane_text;
		}
		if (coloane_integer != nullptr)
		{
			delete[] coloane_integer;
		}
		if (coloane_float != nullptr)
		{
			delete[] coloane_float;
		}
		this->nume_tabela = t.nume_tabela;
		if (t.coloane_text != nullptr && t.nr_coloane_text > 0)
		{
			this->nr_coloane_text = t.nr_coloane_text;
			coloane_text = new C_text[t.nr_coloane_text];
			for (int j = 0; j < t.nr_coloane_text; j++)
			{
				this->coloane_text[j] = t.coloane_text[j];
			}
		}
		else
		{
			this->nr_coloane_text = 0;
			this->coloane_text = nullptr;
		}
		if (t.coloane_integer != nullptr && t.nr_coloane_integer > 0)
		{
			this->nr_coloane_integer = t.nr_coloane_integer;
			coloane_integer = new C_integer[t.nr_coloane_integer];
			for (int j = 0; j < t.nr_coloane_integer; j++)
			{
				this->coloane_integer[j] = t.coloane_integer[j];
			}
		}
		else
		{
			this->nr_coloane_integer = 0;
			this->coloane_integer = nullptr;
		}
		if (t.coloane_float != nullptr && t.nr_coloane_float > 0)
		{
			this->nr_coloane_float = t.nr_coloane_float;
			coloane_float = new C_float[t.nr_coloane_float];
			for (int j = 0; j < t.nr_coloane_float; j++)
			{
				this->coloane_float[j] = t.coloane_float[j];
			}
		}
		else
		{
			this->nr_coloane_float = 0;
			this->coloane_float = nullptr;
		}
		if (t.nr_total_coloane > 0)
		{
			this->nr_total_coloane = t.nr_total_coloane;
			for (int j = 0; j < t.nr_total_coloane; j++)
			{
				this->ordine_coloane[j] = t.ordine_coloane[j];
			}
		}
		else
		{
			this->nr_total_coloane = 0;
		}
		return *this;
	}

	void add_coloana_int(int i, string nume, string tip, int valoare_p, int dim) //i = contor coloana
	{
		C_integer c(nume, tip, valoare_p, dim);
		coloane_integer[i] = c;
	}

	void add_coloana_float(int i, string nume, string tip, float valoare_p, int dim)
	{
		C_float c(nume, tip, valoare_p, dim);
		coloane_float[i] = c;
	}

	void add_coloana_text(int i, string nume, string tip, string valoare_p, int dim)
	{
		C_text c(nume, tip, valoare_p, dim);
		coloane_text[i] = c;

	}

	string getnume_tabela()
	{
		return nume_tabela;
	}

	void setnume_tabela(string nume_tabela)
	{
		if (nume_tabela != "")
			this->nume_tabela = nume_tabela;
	}

	int getnr_total_coloane()
	{
		return nr_total_coloane;
	}

	int getnr_coloane_float()
	{
		return nr_coloane_float;
	}

	int getnr_coloane_text()
	{
		return nr_coloane_text;
	}

	int getnr_coloane_integer()
	{
		return nr_coloane_integer;
	}

	int* getordine_coloane()
	{
		return ordine_coloane;
	}

	void setnr_total_coloane(int nr_total_coloane)
	{
		if (nr_total_coloane != 0)
			this->nr_total_coloane = nr_total_coloane;
	}

	void setnr_coloanefloat(int nr_coloanefloat)
	{
		this->nr_coloane_float = nr_coloane_float;
	}

	void setnr_coloaneinteger(int nr_coloane_integer)
	{
		this->nr_coloane_integer = nr_coloane_integer;
	}

	void setnr_coloanetext(int nr_coloane_text)
	{
		this->nr_coloane_text = nr_coloane_text;
	}

	void setordine_coloane(int* ordine_coloane, int nr_total_coloane)
	{
		if (nr_total_coloane != 0)
			for (int i = 0; i < nr_total_coloane; i++)
				this->ordine_coloane[i] = ordine_coloane[i];
	}

	static string getUtilizator()
	{
		return utilizator_bd;
	}
	static void setUtilizator(string s)
	{
		TABELA::utilizator_bd = s;
	}

	operator int() //cast impl 
	{
		return this->nr_total_coloane;
	}

	bool operator!()
	{
		return nr_total_coloane > 0;
	}

	TABELA operator++(int i)
	{
		TABELA copie = *this;
		this->nr_total_coloane++;
		return copie;
	}

	TABELA operator+(int x)
	{
		TABELA copie = *this;
		copie.nr_total_coloane = nr_total_coloane + x;
		return copie;
	}

	C_text* getColoaneText() {
		return this->coloane_text;
	}

	C_integer* getColoaneInteger() {
		return this->coloane_integer;
	}

	C_float* getColoaneFloat() {
		return this->coloane_float;
	}

	void serializare()
	{
		ofstream f("tabela.bin", ios::binary);
		int length = nume_tabela.length();
		f.write((char*)&length, sizeof(length));
		f.write(nume_tabela.c_str(), length + 1);
		f.write((char*)&nr_total_coloane, sizeof(nr_total_coloane));
		f.write((char*)&nr_coloane_text, sizeof(nr_coloane_text));
		f.write((char*)&nr_coloane_integer, sizeof(nr_coloane_text));
		f.write((char*)&nr_coloane_float, sizeof(nr_coloane_text));
		for (int i = 0; i < nr_total_coloane; i++)
			f.write((char*)&ordine_coloane[i], sizeof(ordine_coloane[i]));
		f.close();
	}
	void deserializare()
	{
		ifstream f("tabela.bin", ios::binary);
		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* aux = new char[length + 1];
		f.read(aux, length + 1);
		nume_tabela = aux;
		delete[] aux;
		f.read((char*)&nr_coloane_text, sizeof(nr_coloane_text));
		f.read((char*)&nr_coloane_integer, sizeof(nr_coloane_text));
		f.read((char*)&nr_coloane_float, sizeof(nr_coloane_text));
		for (int i = 0; i < nr_total_coloane; i++)
			f.read((char*)&ordine_coloane[i], sizeof(ordine_coloane[i]));

		f.close();
	}

	~TABELA()
	{
		if (coloane_text != nullptr)
		{
			delete[] coloane_text;
		}
		if (coloane_integer != nullptr)
		{
			delete[] coloane_integer;
		}
		if (coloane_float != nullptr)
		{
			delete[] coloane_float;
		}
	}

	friend TABELA operator+(int, TABELA);
	friend ostream& operator<<(ostream&, TABELA);
	friend istream& operator>>(istream&, TABELA&);
	//friend ofstream& operator<<(ofstream&, TABELA);
	//friend ifstream& operator>>(ostream& out, TABELA tb);
};

string TABELA::utilizator_bd = "profesor";

ostream& operator<<(ostream& out, TABELA tb)
{
	cout << "Numele tabelei este: ";
	out << tb.nume_tabela << endl;
	cout << "Numarul total de coloane este: ";
	out << tb.nr_total_coloane << endl;
	int te = 0; //contoare
	int in = 0;
	int fl = 0;
	for (int i = 0; i < tb.nr_total_coloane; i++)
	{
		if (tb.ordine_coloane[i] == 1) //afis coloana text
		{
			out << tb.coloane_text[te];
			te++;
		}
		if (tb.ordine_coloane[i] == 2) //afis coloana integer
		{
			out << tb.coloane_integer[in];
			in++;
		}
		if (tb.ordine_coloane[i] == 3) //afis coloana float
		{
			out << tb.coloane_float[fl];
			fl++;
		}
	}
	cout << endl;
	return out;
}
istream& operator>>(istream& in, TABELA& tb)
{
	cout << "Numele tabelei este: ";
	in >> tb.nume_tabela;
	cout << endl;
	cout << "Numarul total de coloane este: ";
	in >> tb.nr_total_coloane;
	cout << endl;
	int te = 0;
	int nt = 0;
	int fl = 0;
	for (int i = 0; i < tb.nr_total_coloane; i++)
	{
		if (tb.ordine_coloane[i] == 1)
		{
			cout << "Nr coloane text: ";
			in >> tb.coloane_text[te];
			te++;
		}
		if (tb.ordine_coloane[i] == 2)
		{

			cout << "Nr coloane integer: ";
			in >> tb.coloane_integer[nt];
			nt++;
		}
		if (tb.ordine_coloane[i] == 2)
		{
			cout << "Nr coloane float: ";
			in >> tb.coloane_float[fl];
			fl++;
		}
		cout << endl;
		return in;
	}
}

//ofstream& operator<<(ofstream& out, TABELA tb)
//{
//	cout << "Numele tabelei este: ";
//	out << tb.nume_tabela;
//	cout << endl;
//	cout << "Numarul total de coloane este: ";
//	out << tb.nr_total_coloane;
//	cout << endl;
//	int te = 0; //contoare
//	int in = 0;
//	int fl = 0;
//	for (int i = 0; i < tb.nr_total_coloane; i++)
//	{
//		if (tb.ordine_coloane[i] == 1) //afis coloana text
//		{
//			out << tb.coloane_text[te];
//			te++;
//		}
//		if (tb.ordine_coloane[i] == 2) //afis coloana integer
//		{
//			out << tb.coloane_integer[in];
//			in++;
//		}
//		if (tb.ordine_coloane[i] == 3) //afis coloana float
//		{
//			out << tb.coloane_float[fl];
//			fl++;
//		}
//	}
//	cout << endl;
//	return out;
//}

//ifstream& operator>>(ifstream& in, TABELA& tb)
//{
//	cout << "Numele tabelei este: ";
//	in >> tb.nume_tabela;
//	cout << endl;
//	cout << "Numarul total de coloane este: ";
//	in >> tb.nr_total_coloane;
//	cout << endl;
//	int te = 0;
//	int nt = 0;
//	int fl = 0;
//	for (int i = 0; i < tb.nr_total_coloane; i++)
//	{
//		if (tb.ordine_coloane[i] == 1)
//		{
//			cout << "Nr coloane text: ";
//			in >> tb.coloane_text[te];
//			te++;
//		}
//		if (tb.ordine_coloane[i] == 2)
//		{
//
//			cout << "Nr coloane integer: ";
//			in >> tb.coloane_integer[nt];
//			nt++;
//		}
//		if (tb.ordine_coloane[i] == 2)
//		{
//			cout << "Nr coloane float: ";
//			in >> tb.coloane_float[fl];
//			fl++;
//		}
//		cout << endl;
//		return in;
//	}
//}

TABELA operator+(int x, TABELA t2)
{
	t2.nr_total_coloane += x;
	return t2;
}



#endif // !TABELA_H

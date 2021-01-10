#ifndef C_TEXT_H
#include "COLOANA.h"

class C_text : public COLOANA
{
public:
	int nr_valori_text = 0;
	char** valori_text = nullptr;
	char valoare_implicita_text[30] = {};
	int dimensiune_text;

	C_text()
	{
		nr_valori_text = 0;
		valori_text = nullptr;
		strcpy_s(valoare_implicita_text, " ");
		dimensiune_text = 0;
	}

	//constructor cu parametri 1, va fi folosit pt CREATE coloana text
	C_text(string nume, string tip, string valoare_p, int dim) : COLOANA(nume, tip)
	{
		nr_valori_text = 0;
		valori_text = nullptr;
		strcpy_s(valoare_implicita_text, valoare_p.c_str());
		dimensiune_text = dim;
	}

	//constructor cu parametri 2
	C_text(string nume) : COLOANA(nume)
	{
		nr_valori_text = 0;
		valori_text = nullptr;
		strcpy_s(valoare_implicita_text, " ");
		dimensiune_text = 0;
	}

	C_text(const C_text& c) : COLOANA(c) //constructor de copiere
	{
		if (c.valori_text != nullptr && c.nr_valori_text > 0)
		{
			this->nr_valori_text = c.nr_valori_text;
			this->valori_text = new char* [c.nr_valori_text];
			for (int i = 0; i < c.nr_valori_text; i++)
			{
				this->valori_text[i] = new char[c.dimensiune_text];
				strcpy_s(this->valori_text[i], strlen(c.valori_text[i]) + 1, c.valori_text[i]);
			}
		}
		else
		{
			this->valori_text = nullptr;
			this->nr_valori_text = 0;
		}
		this->dimensiune_text = c.dimensiune_text;
	}

	C_text& operator=(const C_text& c) // operator =
	{
		COLOANA::operator=(c);
		if (valori_text != nullptr)
		{
			for (int z = 0; z < nr_valori_text; z++)
			{
				delete[] valori_text[z];
			}
			delete[] valori_text;
		}
		if (c.valori_text != nullptr && c.nr_valori_text > 0)
		{
			this->nr_valori_text = c.nr_valori_text;
			this->valori_text = new char* [c.nr_valori_text];
			for (int i = 0; i < c.nr_valori_text; i++)
			{
				this->valori_text[i] = new char[c.dimensiune_text];
				strcpy_s(this->valori_text[i], strlen(c.valori_text[i])+1, c.valori_text[i]);
			}
		}
		else
		{
			this->valori_text = nullptr;
			this->nr_valori_text = 0;
		}
		this->dimensiune_text = c.dimensiune_text;
		return *this;
	}

	int getNrValoriText()
	{
		return this->nr_valori_text;
	}

	char** getValoriText()
	{
		if (this->valori_text != nullptr)
		{
			char** copie = new char* [this->nr_valori_text];
			for (int i = 0; i < nr_valori_text; i++)
			{
				copie[i] = new char[strlen(this->valori_text[i]) + 1];
				strcpy_s(copie[i], strlen(this->valori_text[i]) + 1, this->valori_text[i]);
			}
			return copie;
		}
		return NULL;
	}

	void setValoriText(char** x, int dimensiune)
	{
		if (x != nullptr && dimensiune > 0)
		{
			if (this->valori_text != nullptr)
			{
				for (int i = 0; i < this->nr_valori_text; i++)
				{
					delete[] this->valori_text[i];
				}
				delete[] this->valori_text;
			}
			this->nr_valori_text = dimensiune;
			this->valori_text = new char* [dimensiune];
			for (int i = 0; i < dimensiune; i++)
			{
				this->valori_text[i] = new char[strlen(x[i]) + 1];
				strcpy_s(this->valori_text[i], strlen(x[i]) + 1, x[i]);
			}
		}
	}

	char* getValoareImplicitaText()
	{
		return this->valoare_implicita_text;
	}
	int getDimensiuneText()
	{
		return this->dimensiune_text;
	}
	void setValoareImplicitaText(const char* x)
	{
		if (x != nullptr)
		{
			strcpy_s(this->valoare_implicita_text, strlen(x) + 1, x);
		}
	}
	void setDimensiuneText(int x)
	{
		if (x > 0)
		{
			this->dimensiune_text = x;
		}
	}

	bool operator!()
	{
		return nr_valori_text > 0;
	}

	C_text operator++(int i)
	{
		C_text copie = *this;
		this->nr_valori_text++;
		return copie;
	}

	C_text operator++()
	{
		this->nr_valori_text++;
		return *this;
	}

	C_text operator+(int x)
	{
		C_text copie = *this;
		copie.dimensiune_text = dimensiune_text + x;
		return copie;
	}

	operator int() //cast impl
	{
		return this->dimensiune_text;
	}

	void dezalocareValoriText()
	{
		if (this->valori_text != nullptr)
		{
			for (int z = 0; z < nr_valori_text; z++)
			{
				delete[] this->valori_text[z];
			}
			delete[] this->valori_text;
		}
	};

	void serializare()
	{
		ofstream f("C_text.bin", ios::binary);
		f.write((char*)&nr_valori_text, sizeof(nr_valori_text));
		for (int i = 0; i < nr_valori_text; i++)
		{
			f.write((char*)&valori_text[i], sizeof(valori_text[i]));
		}
		f.write((char*)&valoare_implicita_text, sizeof(valoare_implicita_text));
		f.write((char*)&dimensiune_text, sizeof(dimensiune_text));
		f.close();
	}

	void deserializare()
	{
		ifstream f("C_text.bin", ios::binary);
		f.read((char*)&nr_valori_text, sizeof(nr_valori_text));
		delete[] valori_text;
		valori_text = new char* [nr_valori_text];
		for (int i = 0; i < nr_valori_text; i++)
		{
			f.read((char*)&valori_text[i], sizeof(valori_text[i]));
		}
		f.read((char*)&valoare_implicita_text, sizeof(valoare_implicita_text));
		f.read((char*)&dimensiune_text, sizeof(dimensiune_text));
		f.close();
	}

	~C_text()
	{
		if (valori_text != nullptr)
		{
			for (int z = 0; z < nr_valori_text; z++)
			{
				delete[] valori_text[z];
			}
			delete[] valori_text;
		}
	}
	friend C_text operator+(int, C_text);
	friend ostream& operator<<(ostream&, C_text);
	friend istream& operator >>(istream&, C_text&);
	//friend ofstream& operator<<(ofstream&, C_text);
	//friend ifstream& operator>>(ifstream&, C_text&);
};
C_text operator+(int x, C_text ct2)
{
	ct2.dimensiune_text += x;
	return ct2;
}
ostream& operator<<(ostream& out, C_text t)
{
	out << (COLOANA&)t << endl;
	cout << "Nr valori text: ";
	out << t.nr_valori_text << endl;
	cout << "Valori text: ";
	if (t.valori_text != nullptr)
	{
		for (int j = 0; j < t.nr_valori_text; j++)
		{
			out << t.valori_text[j] << " ";
		}
		cout << endl;
	}
	else
	{
		out << "N/A";	cout << endl;
	}
	cout << "Valoare implicita text: ";
	out << t.valoare_implicita_text << endl;
	cout << "Dimensiune maxima text: ";
	out << t.dimensiune_text << endl;
	return out;
}
istream& operator >>(istream& in, C_text& te)
{
	in >> (COLOANA&)te;
	cout << "Nr valori text: ";
	in >> te.nr_valori_text;
	if (te.valori_text != nullptr)
	{
		for (int z = 0; z < te.nr_valori_text; z++)
		{
			delete[] te.valori_text[z];
		}
		delete[] te.valori_text;
	}
	cout << "Valori text: ";
	if (te.nr_valori_text > 0)
	{
		te.valori_text = new char* [te.nr_valori_text];
		for (int j = 0; j < te.nr_valori_text; j++)
		{
			te.valori_text[j] = new char[te.dimensiune_text];
		}
		for (int j = 0; j < te.nr_valori_text; j++)
		{
			char buffer[100];
			in >> ws;
			in.getline(buffer, 99);
			strcpy_s(te.valori_text[j], strlen(buffer) + 1, buffer);
		}
	}
	else
	{
		te.valori_text = nullptr;
		te.nr_valori_text = 0;
	}
	cout << endl;
	cout << "Valoare implicita text: ";
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	strcpy_s(te.valoare_implicita_text, strlen(buffer) + 1, buffer);

	cout << "Dimensiune maxima text: ";
	in >> te.dimensiune_text;
	return in;
}

//ofstream& operator<<(ofstream& out, C_text t)
//{
//	out << (COLOANA&)t << endl;
//	cout << "Nr valori text: ";
//	out << t.nr_valori_text << endl;
//	cout << "Valori text: ";
//	if (t.valori_text != nullptr)
//	{
//		for (int j = 0; j < t.nr_valori_text; j++)
//		{
//			out << t.valori_text[j] << " ";
//		}
//	}
//	else
//	{
//		out << "N/A";
//	}
//	cout << "Valoare implicita text: ";
//	out << t.valoare_implicita_text << endl;
//	cout << "Dimensiune text: ";
//	out << t.dimensiune_text << endl;
//	return out;
//}

//ifstream& operator>>(ifstream& in, C_text& t)
//{
//	in >> (COLOANA&)t;
//	cout << "Nr valori text: ";
//	in >> t.nr_valori_text;
//	if (t.valori_text != nullptr)
//	{
//		delete[] t.valori_text;
//	}
//	cout << "Valori text: ";
//	if (t.nr_valori_text > 0)
//	{
//		t.valori_text = new char* [t.nr_valori_text];
//		for (int j = 0; j < t.nr_valori_text; j++)
//		{
//			in >> t.valori_text[j];
//		}
//	}
//	else
//	{
//		t.valori_text = nullptr;
//		t.nr_valori_text = 0;
//	}
//	cout << endl;
//	cout << "Valoare implicita text: ";
//	in >> t.valoare_implicita_text;
//	cout << "Dimensiune maxima text: ";
//	in >> t.dimensiune_text;
//	return in;
//}



#endif // !C_TEXT_H

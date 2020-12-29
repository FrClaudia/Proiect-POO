#ifndef C_INTEGER_H
#include "COLOANA.h"

class C_integer : public COLOANA
{
	//private:
public:
	int nr_valori_integer = 0;
	int* valori_integer = nullptr;
	int valoare_implicita_integer = 0;
	int dimensiune_integer;

public:
	C_integer()//constructor implicit
	{
		nr_valori_integer = 0;
		valori_integer = nullptr;
		valoare_implicita_integer = 0;
		dimensiune_integer = 0;
	}

	//constructor cu parametri 1, va fi folosit pt CREATE coloana int
	C_integer(string nume, string tip, int valoare_p, int dim) : COLOANA(nume, tip)
	{
		nr_valori_integer = 0;
		valori_integer = nullptr;
		valoare_implicita_integer = valoare_p;
		dimensiune_integer = dim;
	}

	//constructor cu parametri 2
	C_integer(string nume) : COLOANA(nume)
	{
		nr_valori_integer = 0;
		valori_integer = nullptr;
		valoare_implicita_integer = 0;
		dimensiune_integer = 0;
	}

	C_integer(const C_integer& c) :COLOANA(c) //constructor de copiere
	{
		if (c.valori_integer != nullptr && c.nr_valori_integer > 0)
		{
			this->nr_valori_integer = c.nr_valori_integer;
			this->valori_integer = new int[c.nr_valori_integer];
			for (int i = 0; i < c.nr_valori_integer; i++)
			{
				this->valori_integer[i] = c.valori_integer[i];
			}
		}
		else
		{
			this->valori_integer = nullptr;
			this->nr_valori_integer = 0;
		}
		this->valoare_implicita_integer = c.valoare_implicita_integer;
		this->dimensiune_integer = c.dimensiune_integer;
	}

	C_integer& operator=(const C_integer& c)// operator =
	{
		COLOANA::operator=(c);
		if (valori_integer != nullptr)
		{
			delete[] valori_integer;
		}
		if (c.valori_integer != nullptr && c.nr_valori_integer > 0)
		{
			this->nr_valori_integer = c.nr_valori_integer;
			this->valori_integer = new int[c.nr_valori_integer];
			for (int i = 0; i < c.nr_valori_integer; i++)
			{
				this->valori_integer[i] = c.valori_integer[i];
			}
		}
		else
		{
			this->valori_integer = nullptr;
			this->nr_valori_integer = 0;
		}
		this->valoare_implicita_integer = c.valoare_implicita_integer;
		this->dimensiune_integer = c.dimensiune_integer;
		return *this;
	}

	int getNrValoriInteger()
	{
		return this->nr_valori_integer;
	}

	int* getValoriInteger()
	{
		if (this->valori_integer != nullptr)
		{
			int* copie = new int[this->nr_valori_integer];
			for (int i = 0; i < this->nr_valori_integer; i++)
			{
				copie[i] = this->valori_integer[i];
			}
			return copie;
		}
		return NULL;
	}

	void setValoriInteger(int* x, int dimensiune)
	{
		if (x != nullptr && dimensiune > 0)
		{
			this->nr_valori_integer = dimensiune;
			if (this->valori_integer != nullptr)
			{
				delete[] this->valori_integer;
			}
			this->valori_integer = new int[dimensiune];
			for (int i = 0; i < dimensiune; i++) {
				this->valori_integer[i] = x[i];
			}
		}
	}
	int getValoareImplicitaInteger()
	{
		return this->valoare_implicita_integer;
	}
	int getDimensiuneInteger()
	{
		return this->dimensiune_integer;
	}
	void setValoareImplicitaInteger(int x)
	{
		this->valoare_implicita_integer = x;
	}
	void setDimensiuneInteger(int x)
	{
		if (x > 0)
		{
			this->dimensiune_integer = x;
		}
	}

	bool operator!()
	{
		return nr_valori_integer > 0;
	}

	C_integer operator++(int i)
	{
		C_integer copie = *this;
		this->nr_valori_integer++;
		return copie;
	}

	C_integer operator++()
	{
		this->nr_valori_integer++;
		return *this;
	}

	C_integer operator+(int x)
	{
		C_integer copie = *this;
		copie.dimensiune_integer = dimensiune_integer + x;
		return copie;
	}

	operator int() //cast impl
	{
		return this->dimensiune_integer;
	}

	~C_integer()
	{
		if (valori_integer != nullptr)
		{
			delete[] valori_integer;
		}
	}
	friend C_integer operator+(int, C_integer);
	friend ostream& operator <<(ostream&, C_integer);
	friend istream& operator >>(istream&, C_integer&);
};
C_integer operator+(int x, C_integer ci2)
{
	ci2.dimensiune_integer += x;
	return ci2;
}
ostream& operator<<(ostream& out, C_integer i)
{
	out << (COLOANA&)i << endl;
	cout << "Nr valori integer: ";
	out << i.nr_valori_integer << endl;
	cout << "Valori integer: ";
	if (i.valori_integer != nullptr)
	{
		for (int j = 0; j < i.nr_valori_integer; j++)
		{
			out << i.valori_integer[j] << " ";
		}
		cout << endl;
	}
	else
	{
		out << "N/A";	cout << endl;
	}

	cout << "Valoare implicita integer: ";
	out << i.valoare_implicita_integer << endl;
	cout << "Dimensiune maxima integer: ";
	out << i.dimensiune_integer << endl;
	return out;
}
istream& operator>>(istream& in, C_integer& i)
{
	in >> (COLOANA&)i;
	cout << "Nr valori integer: ";
	in >> i.nr_valori_integer;
	if (i.valori_integer != nullptr)
	{
		delete[] i.valori_integer;
	}
	cout << "Valori integer: ";
	if (i.nr_valori_integer > 0)
	{
		i.valori_integer = new int[i.nr_valori_integer];
		for (int j = 0; j < i.nr_valori_integer; j++)
		{
			in >> i.valori_integer[j];
		}
	}
	else
	{
		i.valori_integer = nullptr;
		i.nr_valori_integer = 0;
	}
	cout << endl;
	cout << "Valoare implicita integer: ";
	in >> i.valoare_implicita_integer;
	cout << "Dimensiune maxima integer: ";
	in >> i.dimensiune_integer;
	return in;
}
#endif // !C_INTEGER_H

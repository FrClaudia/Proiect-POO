#ifndef C_FLOAT_H
#include "COLOANA.h"
class C_float : public COLOANA
{
	//private:
public:
	int nr_valori_float = 0;
	float* valori_float = nullptr;
	float valoare_implicita_float = 0.0;
	int dimensiune_float;

public:

	C_float()
	{
		nr_valori_float = 0;
		valori_float = nullptr;
		valoare_implicita_float = 0.0;
		dimensiune_float = 0;
	}

	//constructor cu parametri 1, va fi folosit pt CREATE coloana float
	C_float(string nume, string tip, float valoare_p, int dim) : COLOANA(nume, tip)
	{
		nr_valori_float = 0;
		valori_float = nullptr;
		valoare_implicita_float = valoare_p;
		dimensiune_float = dim;
	}

	//constructor cu parametri 2
	C_float(string nume) : COLOANA(nume)
	{
		nr_valori_float = 0;
		valori_float = nullptr;
		valoare_implicita_float = 0.0;
		dimensiune_float = 0;
	}

	C_float(const C_float& c) :COLOANA(c)
	{
		if (c.valori_float != nullptr && c.nr_valori_float > 0)
		{
			this->nr_valori_float = c.nr_valori_float;
			this->valori_float = new float[c.nr_valori_float];
			for (int i = 0; i < c.nr_valori_float; i++)
			{
				this->valori_float[i] = c.valori_float[i];
			}
		}
		else
		{
			this->valori_float = nullptr;
			this->nr_valori_float = 0;
		}
		this->valoare_implicita_float = c.valoare_implicita_float;
		this->dimensiune_float = c.dimensiune_float;
	}

	C_float& operator=(const C_float& c) //operator =
	{
		COLOANA::operator=(c);
		if (valori_float != nullptr)
		{
			delete[] valori_float;
		}
		if (c.valori_float != nullptr && c.nr_valori_float > 0)
		{
			this->nr_valori_float = c.nr_valori_float;
			this->valori_float = new float[c.nr_valori_float];
			for (int i = 0; i < c.nr_valori_float; i++)
			{
				this->valori_float[i] = c.valori_float[i];
			}
		}
		else
		{
			this->valori_float = nullptr;
			this->nr_valori_float = 0;
		}
		this->valoare_implicita_float = c.valoare_implicita_float;
		this->dimensiune_float = c.dimensiune_float;
		return *this;
	}

	int getNrValoriFloat()
	{
		return this->nr_valori_float;
	}

	float* getValoriFloat()
	{
		if (this->valori_float != nullptr)
		{
			float* copie = new float[this->nr_valori_float];
			for (int i = 0; i < this->nr_valori_float; i++)
			{
				copie[i] = this->valori_float[i];
			}
			return copie;
		}
		return NULL;
	}

	void setValoriFloat(float* x, int dimensiune)
	{
		if (x != nullptr && dimensiune > 0)
		{
			this->nr_valori_float = dimensiune;
			if (this->valori_float != nullptr)
			{
				delete[] this->valori_float;
			}
			this->valori_float = new float[dimensiune];
			for (int i = 0; i < dimensiune; i++)
			{
				this->valori_float[i] = x[i];
			}
		}
	}

	float getValoareImplicitaFloat()
	{
		return this->valoare_implicita_float;
	}
	int getDimensiuneFloat()
	{
		return this->dimensiune_float;
	}
	void setValoareImplicitaFloat(float x)
	{
		this->valoare_implicita_float = x;
	}
	void setDimensiuneFloat(int x)
	{
		if (x > 0)
		{
			this->dimensiune_float = x;
		}
	}

	bool operator!()
	{
		return nr_valori_float > 0;
	}

	C_float operator++(int i)
	{
		C_float copie = *this;
		this->nr_valori_float++;
		return copie;
	}

	C_float operator++()
	{
		this->nr_valori_float++;
		return *this;
	}

	C_float operator+(int x)
	{
		C_float copie = *this;
		copie.dimensiune_float = dimensiune_float + x;
		return copie;
	}

	operator int() //cast impl
	{
		return this->dimensiune_float;
	}

	void dezalocareValoriFloat() {
		if (this->valori_float != nullptr)
		{
			delete[] this->valori_float;
		}
	}

	void serializare()
	{
		ofstream f("C_float.bin", ios::binary);
		f.write((char*)&nr_valori_float, sizeof(nr_valori_float));
		for (int i = 0; i < nr_valori_float; i++)
		{
			f.write((char*)&valori_float[i], sizeof(valori_float[i]));
		}
		f.write((char*)&valoare_implicita_float, sizeof(valoare_implicita_float));
		f.write((char*)&dimensiune_float, sizeof(dimensiune_float));
		f.close();
	}

	void deserializare()
	{
		ifstream f("C_float.bin", ios::binary);
		f.read((char*)&nr_valori_float, sizeof(nr_valori_float));
		delete[] valori_float;
		valori_float = new float[nr_valori_float];
		for (int i = 0; i < nr_valori_float; i++)
		{
			f.read((char*)&valori_float[i], sizeof(valori_float[i]));
		}
		f.read((char*)&valoare_implicita_float, sizeof(valoare_implicita_float));
		f.read((char*)&dimensiune_float, sizeof(dimensiune_float));
		f.close();
	}

	~C_float()
	{
		if (valori_float != nullptr)
		{
			delete[] valori_float;
		}
	}
	friend C_float operator+(int, C_float);
	friend ostream& operator <<(ostream&, C_float);
	friend istream& operator >>(istream&, C_float&);
	//friend ofstream& operator<<(ofstream&, C_float);
	//friend ifstream& operator>>(ifstream&, C_float&);
};
C_float operator+(int x, C_float cf2)
{
	cf2.dimensiune_float += x;
	return cf2;
}
ostream& operator<<(ostream& out, C_float f)
{
	out << (COLOANA&)f << endl;
	cout << "Nr valori float: ";
	out << f.nr_valori_float << endl;
	cout << "Valori float: ";
	if (f.valori_float != nullptr)
	{
		for (int j = 0; j < f.nr_valori_float; j++)
		{
			out << f.valori_float[j] << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "N/A";	cout << endl;
	}

	cout << "Valoare implicita float: ";
	out << f.valoare_implicita_float << endl;
	cout << "Dimensiune maxima float: ";
	out << f.dimensiune_float << endl;
	return out;
}
istream& operator>>(istream& in, C_float& f)
{
	in >> (COLOANA&)f;
	cout << "Nr valori float: ";
	in >> f.nr_valori_float;
	if (f.valori_float != nullptr)
	{
		delete[] f.valori_float;
	}
	cout << "Valori float: ";
	if (f.nr_valori_float > 0)
	{
		f.valori_float = new float[f.nr_valori_float];
		for (int j = 0; j < f.nr_valori_float; j++)
		{
			in >> f.valori_float[j];
		}
	}
	else
	{
		f.valori_float = nullptr;
		f.nr_valori_float = 0;
	}
	cout << endl;
	cout << "Valoare implicita float: ";
	in >> f.valoare_implicita_float;
	cout << "Dimensiune maxima float: ";
	in >> f.dimensiune_float;
	return in;
}

//ofstream& operator<<(ofstream& out, C_float f)
//{
//	out << (COLOANA&)f << endl;
//	cout << "Nr valori float: ";
//	out << f.nr_valori_float << endl;
//	if (f.valori_float != nullptr)
//	{
//		for (int j = 0; j < f.nr_valori_float; j++)
//		{
//			out << f.valori_float[j] << " ";
//		}
//	}
//	else
//	{
//		cout << "N/A";
//	}
//	cout << "Valoare implicita float: ";
//	out << f.valoare_implicita_float << endl;
//	cout << "Dimensiune float: ";
//	out << f.dimensiune_float << endl;
//	return out;
//}

//ifstream& operator>>(ifstream& in, C_float& f)
//{
//	in >> (COLOANA&)f;
//	cout << "Nr valori float: ";
//	in >> f.nr_valori_float;
//	if (f.valori_float != nullptr)
//	{
//		delete[] f.valori_float;
//	}
//	cout << "Valori float: ";
//	if (f.nr_valori_float > 0)
//	{
//		f.valori_float = new float[f.nr_valori_float];
//		for (int j = 0; j < f.nr_valori_float; j++)
//		{
//			in >> f.valori_float[j];
//		}
//	}
//	else
//	{
//		f.valori_float = nullptr;
//		f.nr_valori_float = 0;
//	}
//	cout << endl;
//	cout << "Valoare implicita float: ";
//	in >> f.valoare_implicita_float;
//	cout << "Dimensiune maxima float: ";
//	in >> f.dimensiune_float;
//	return in;
//}

#endif // !C_FLOAT_H

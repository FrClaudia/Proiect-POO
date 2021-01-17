#ifndef COLOANA_H
#define COLOANA_H
#include <string>
#include <iostream>
#include<fstream>
using namespace std;

class COLOANA
{
	//private:
public:
	string nume_coloana;
	string tip_coloana;

	COLOANA() //constructor implicit
	{
		nume_coloana = "";
		tip_coloana = "";
	}

	//constructor cu parametri 1
	COLOANA(string nume, string tip)
	{
		nume_coloana = nume;
		tip_coloana = tip;
	}
	//constructor cu parametri 2
	COLOANA(string nume)
	{
		nume_coloana = nume;
		tip_coloana = "";
	}

	COLOANA(const COLOANA& c) //constructor de copiere
	{
		this->nume_coloana = c.nume_coloana;
		this->tip_coloana = c.tip_coloana;
	}

	COLOANA& operator=(const COLOANA& c) //supraincarcare operator=
	{
		this->nume_coloana = c.nume_coloana;
		this->tip_coloana = c.tip_coloana;
		return *this;
	}

	string getNumeColoana()
	{
		return this->nume_coloana;
	}
	void setNumeColoana(string s)
	{
		this->nume_coloana = s;
	}
	string getTipColoana()
	{
		return this->tip_coloana;
	}
	void setTipColoana(string s)
	{
		this->tip_coloana = s;
	}

	operator string() //cast impl
	{
		return this->nume_coloana;
	}

	bool operator!()
	{
		if (nume_coloana == "")
			return false;
		else
			return true;
	}

	void serializare()
	{
		ofstream f("COLOANA.bin", ios::binary);
		int length = nume_coloana.length();
		f.write((char*)&length, sizeof(length));
		f.write(nume_coloana.c_str(), length + 1);
		f.write((char*)&tip_coloana, sizeof(tip_coloana));
		f.close();
	}

	void deserializare()
	{
		ifstream f("COLOANA.bin", ios::binary);
		int length = 0;
		f.read((char*)&length, sizeof(length));
		char* aux = new char[length + 1];
		f.read(aux, length + 1);
		nume_coloana = aux;
		delete[] aux;
		f.read((char*)&tip_coloana, sizeof(tip_coloana));
		f.close();
	}


	~COLOANA()
	{
	}
	friend ostream& operator<<(ostream&, COLOANA);
	friend istream& operator>>(istream&, COLOANA&);
	//friend ofstream& operator<<(ofstream&, COLOANA);
	//friend ifstream& operator>>(ifstream&, COLOANA&);
};
ostream& operator<<(ostream& out, COLOANA c)
{
	cout << "Numele coloanei este: ";
	out << c.nume_coloana << endl;
	cout << "Tipul coloanei este: ";
	out << c.tip_coloana << endl;
	return out;
}
istream& operator>>(istream& in, COLOANA& c)
{
	cout << "Numele coloanei este: ";
	in >> ws;
	getline(in, c.nume_coloana);
	cout << endl;
	cout << "Tipul coloanei este: ";
	in >> ws;
	getline(in, c.tip_coloana);
	cout << endl;
	return in;
}

//ofstream& operator<<(ofstream& out, COLOANA c)
//{
//	cout << "Numele coloanei este: ";
//	out << c.nume_coloana;
//	cout << endl;
//	cout << "Tipul coloanei este: ";
//	out << c.tip_coloana;
//	cout << endl;
//	return out;
//}

//ifstream& operator>>(ifstream& in, COLOANA& c)
//{
//	cout << "Numele coloanei este: ";
//	in >> ws;
//	getline(in, c.nume_coloana);
//	cout << endl;
//	cout << "Tipul coloanei este: ";
//	in >> ws;
//	getline(in, c.tip_coloana);
//	cout << endl;
//	return in;
//}

#endif // !COLOANA_H

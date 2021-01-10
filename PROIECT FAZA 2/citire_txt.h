#ifndef CITIRE_TXT
#define CITIRE_TXT
#include "TABELA.h"

class citire_txt
{
public:
	TABELA* tab = nullptr;
	void citire() //afisare comenzi precedente
	{
		int ok = 0;
		ifstream inFile;
		inFile.open("COMENZI.txt");
		if (!inFile.is_open())
		{
			cout << "Nu exista comenzi din sesiuni anterioare!" << endl << endl;
		}
		else
		{
			string buffer;
			char* comanda = nullptr;
			cout << "Comenzile din sesiunile anterioare au fost: ";
			while (!inFile.eof())
			{
				inFile >> ws;
				getline(inFile, buffer);
				cout << buffer << endl;
			}
			delete[] comanda;
		}

	}
};

#endif // !CITIRE_TXT
#pragma once

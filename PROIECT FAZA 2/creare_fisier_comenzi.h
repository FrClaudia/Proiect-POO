#ifndef CREARE_FISIER_COMENZI
#define CREARE_FISIER_COMENZI
#include "TABELA.h"

int counter_select = 0;
int counter_insert = 0;
int counter_drop = 0;
int counter_delete = 0;
int counter_display = 0;
int counter_create = 0;
int counter_update = 0;

class creare_fisier_comenzi
{
public:
	TABELA tabela;
	void creare_fisier_c(const char* com)
	{
		char* comanda = nullptr;
		char* copie = nullptr;
		copie = new char[strlen(com) + 1];
		strcpy_s(copie, strlen(com) + 1, com); //copie comanda
		char delimit[5] = " ,()";
		char* context = NULL; //special pt functia strtok_s
		char* t = strtok_s(copie, delimit, &context);
		char cuv[50][15]; //vector de cuvinte comanda
		int nr_cuv = 0;
		strcpy_s(cuv[nr_cuv], strlen(t) + 1, t); nr_cuv++; //nr_cuv = nr de cuvinte din comanda
		while (t)
		{
			t = strtok_s(NULL, delimit, &context);
			if (t != NULL)
			{
				strcpy_s(cuv[nr_cuv], strlen(t) + 1, t);
				nr_cuv++;
			}
		}
		delete[]copie; //stergere copie

		if (strcmp(cuv[0], "CREATE") == 0)
		{
			counter_create++;
			std::string name = "CREATE_" + intToString(counter_create) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
		if (strcmp(cuv[0], "DROP") == 0)
		{
			counter_drop++;
			std::string name = "DROP_" + intToString(counter_drop) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
		if (strcmp(cuv[0], "DISPLAY") == 0)
		{
			counter_display++;
			std::string name = "DISPLAY_" + intToString(counter_display) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
		if (strcmp(cuv[0], "INSERT") == 0)
		{
			counter_insert++;
			std::string name = "INSERT_" + intToString(counter_insert) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
		if (strcmp(cuv[0], "DELETE") == 0)
		{
			counter_delete++;
			std::string name = "DELETE_" + intToString(counter_delete) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
		if (strcmp(cuv[0], "SELECT") == 0)
		{
			counter_select++;
			std::string name = "SELECT_" + intToString(counter_select) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
		if (strcmp(cuv[0], "UPDATE") == 0)
		{
			counter_update++;
			std::string name = "UPDATE_" + intToString(counter_update) + ".txt";
			ofstream write(name.c_str());
			write << com;
			write.close();
		}
	}
};

#endif // !CREARE_FISIER_COMENZI


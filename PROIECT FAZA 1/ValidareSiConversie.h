#ifndef VALIDARE_SI_CONVERSIE_H
#include<string>
using namespace std;

//functie ce verifica daca un sir de caractere este format doar din litere
bool isCharLetter(const char* c)
{
	int len = strlen(c);
	for (int i = 0; i < len; i++)
	{
		if (isalpha(c[i]) == 0) return false; //daca un caracter nu este litera => 0
	}
	return true;
}

//functie de verifica daca un sir de caractere este format doar din cifre
bool isCharInt(const char* c)
{
	int len = strlen(c);
	for (int i = 0; i < len; i++)
	{
		if (isdigit(c[i]) == 0) return false; //daca un caracter nu este cifra => 0
	}
	return true;
}

//functie de verifica daca un sir de caractere este format doar din cifre si este un float
int isCharFloat(const char* c)
{
	int k = 1; //presupunem ca este float
	int p = 0; //numaram caracterul '.' specific unui nr float
	if (c[0] == '.') return 0; //verificam sa nu fie primul char punct; daca este => 0
	else
	{
		int len = strlen(c);
		for (int i = 0; i < len; i++)
		{
			if (c[i] == '.') p++; //ne asiguram ca exista doar o data delimitatorul punct, pt a fi corect numarul
			else
			{
				if (isdigit(c[i]) == 0) k = 0; //verificam sa fie restul caracterelor cifre
			}
		}
		if (p == 1 && k == 1) return 1; //daca fiecare caracter (in afara de pct) este cifra si exista un singur caracter punct => 1
		else return 0;
	}
}

//functie ce converteste un char (din cifre) in int 
// presupunem ca char* c contine doar cifre (se va face verificare inainte de folosirea functiei !)
int ConvertCharToInt(const char* c)
{
	string copie(c);
	int numar = stoi(copie);
	return numar;
}

//functie ce converteste un char (din cifre) in float 
// presupunem ca char* c contine doar cifre (se va face verificare inainte de folosirea functiei !)
float ConvertCharToFloat(const char* c)
{
	string copie(c);
	float numar = stof(copie);
	return numar;
}
#endif // !VALIDARE_SI_CONVERSIE_H

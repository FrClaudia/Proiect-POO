#ifndef ext
#define ext
#include "TABELA.h"

class TABELA_cu_descriere : TABELA {
public:
	string descriere_tabela;

	TABELA_cu_descriere(string nume, int nr_col_text, int nr_col_integer, int nr_col_float, string descriere_tabel) : TABELA(nume, nr_col_text, nr_col_integer, nr_col_float)
	{
		this->descriere_tabela = descriere_tabela;
	}
	TABELA_cu_descriere(const TABELA_cu_descriere& td) : TABELA(td)
	{
		this->descriere_tabela = td.descriere_tabela;
	}
	TABELA_cu_descriere operator=(const TABELA_cu_descriere& td)
	{
		TABELA::operator=(td);
		this->descriere_tabela = td.descriere_tabela;
		return *this;
	}
	string getdescriere_tabel() {
		return descriere_tabela;
	}
	void setdescriere_tabel(string s) {
		this->descriere_tabela = s;
	}
};

#endif // !ext

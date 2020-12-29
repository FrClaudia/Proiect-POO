#ifndef COMANDA_UTILIZATOR_H
#include "TABELA.h"
#include "ValidareSiConversie.h"

void comanda_utilizator(const char* com, TABELA*& tab_utilizator, int& nr_tabele)
{
	if (com == nullptr)
	{
		cout << endl << "Comanda incorecta, reintroduceti!" << endl; return;
	}
	else
	{
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
		cout << endl;
		for (int j = 0; j < nr_cuv; j++)
		{
			cout << cuv[j] << endl;
		}
		delete[]copie; //stergere copie
		cout << endl;

		int comanda_valida = 0;

		if (strcmp(cuv[0], "CREATE") == 0) //CREATE TABLE
		{
			comanda_valida = 1;
			if (strcmp(cuv[1], "TABLE") == 0)
			{
				if (cuv[2] != NULL)
				{
					int nr_col = 0; //nr total coloane
					string s(cuv[2]); //nume tabela
					int k = 1;
					for (int j = 0; j < nr_tabele; j++)
					{
						//verificare nume existent in vectorul de tabele, presupunand ca numele nou nu exista (k = 1)
						if (tab_utilizator[j].nume_tabela == s)
						{
							k = 0;
						}
					}
					if (k == 0) //daca numele exista: mesaj eroare, ne oprim
					{
						cout << "Numele tabelei deja exista!" << endl;
						return;
					}
					else
					{
						int num = nr_cuv - 2;
						if ((nr_cuv - 3) % 4 == 0) //verificare daca au fost introduse cele 4 date necesare crearii unei noi coloane
						{
							//verficare tip valid coloana: text/integer/float
							for (int j = 4; j < nr_cuv; j = j + 4)
							{
								if (strcmp(cuv[j], "text") != 0 && strcmp(cuv[j], "integer") != 0 && strcmp(cuv[j], "float") != 0)
								{
									cout << "Tipul unei coloane nu este valid" << endl;
									return;
								}
							}

							//verificare dimensiune valida coloana
							for (int j = 5; j < nr_cuv; j = j + 4)
							{
								if (isCharInt(cuv[j]) == 0)
								{
									cout << "Dimensiunea unei coloane nu este valida" << endl;
									return;
								}
								if (ConvertCharToInt(cuv[j]) < 1)
								{
									cout << "Dimensiunea unei coloane este mai mica decat minimul (1)" << endl;
									return;
								}
							}

							//verificare valoare implicita valida + numarare coloane
							int te = 0; //nr coloane text
							int in = 0; //nr coloane integer
							int fl = 0; //nr coloane float
							for (int j = 6; j < nr_cuv; j = j + 4)
							{
								if (strcmp(cuv[j - 2], "text") == 0)
								{
									if (isCharLetter(cuv[j]) == 0)
									{
										cout << "Valorea implicita pt o coloana text nu este in acord cu tipul coloanei";
										return;
									}
									else { te++; }
								}
								if (strcmp(cuv[j - 2], "integer") == 0)
								{
									if (isCharInt(cuv[j]) == 0)
									{
										cout << "Valorea implicita pt o coloana integer nu este in acord cu tipul coloanei";
										return;
									}
									else { in++; }
								}
								if (strcmp(cuv[j - 2], "float") == 0)
								{
									if (isCharFloat(cuv[j]) == 0)
									{
										cout << "Valorea implicita pt o coloana float nu este in acord cu tipul coloanei";
										return;
									}
									else { fl++; }
								}
							}

							//daca se trece de verificarile de mai sus, putem crea tabela si adauga coloanele
							nr_col = (nr_cuv - 2) / 4; //nr total coloane ale tabelei
							//creare tabela: nume, nr de coloane de fiecare tip -- urmeaza adaugarea coloanelor
							TABELA new_table(s, te, in, fl);
							cout << "A fost creata tabela " << s << " care are " << te + in + fl << " coloane" << endl;

							int t = 0; //contor pentru vector coloane_text
							int i = 0; //contor pentru vector coloane_integer
							int f = 0; //contor pentru vector coloane_float
							int o = 0; //contor pentru vector ordine_coloane
							for (int j = 3; j < nr_cuv; j = j + 4)
							{
								//adaugare coloana text in vectorul coloane
								if (strcmp(cuv[j + 1], "text") == 0)
								{
									string nume(cuv[j]);
									string tip(cuv[j + 1]);
									int dim = ConvertCharToInt(cuv[j + 2]);
									string val_imp(cuv[j + 3]);
									new_table.add_coloana_text(t, nume, tip, val_imp, dim);
									cout << "A fost creata coloana text " << t + 1 << " numita " << new_table.coloane_text[t].nume_coloana << endl;
									t++;
									new_table.ordine_coloane[o] = 1;
									o++;
								}

								//adaugare coloana int in vectorul coloane
								if (strcmp(cuv[j + 1], "integer") == 0)
								{
									string nume(cuv[j]);
									string tip(cuv[j + 1]);
									int dim = ConvertCharToInt(cuv[j + 2]);
									int val_imp = ConvertCharToInt(cuv[j + 3]);
									new_table.add_coloana_int(i, nume, tip, val_imp, dim);
									cout << "A fost creata coloana integer " << i + 1 << " numita " << new_table.coloane_integer[i].nume_coloana << endl;
									i++;
									new_table.ordine_coloane[o] = 2;
									o++;
								}

								//adaugare coloana float in vectorul coloane
								if (strcmp(cuv[j + 1], "float") == 0)
								{
									string nume(cuv[j]);
									string tip(cuv[j + 1]);
									int dim = ConvertCharToInt(cuv[j + 2]);
									float val_imp = ConvertCharToFloat(cuv[j + 3]);
									new_table.add_coloana_float(f, nume, tip, val_imp, dim);
									cout << "A fost creata coloana float " << f + 1 << " numita " << new_table.coloane_float[f].nume_coloana << endl;
									f++;
									new_table.ordine_coloane[o] = 3;
									o++;
								}
							}
							int new_nr = nr_tabele + 1;
							TABELA* copie_tab = nullptr;
							copie_tab = new TABELA[new_nr];
							for (int j = 0; j < new_nr - 1; j++)
							{
								copie_tab[j] = tab_utilizator[j];
							}
							copie_tab[new_nr - 1] = new_table;
							delete[] tab_utilizator;
							nr_tabele++;
							tab_utilizator = new TABELA[nr_tabele];
							for (int j = 0; j < nr_tabele; j++)
							{
								tab_utilizator[j] = copie_tab[j];
							}
							cout << "Finalizare creare tabela " << s;
							delete[] copie_tab;
						}
						else //daca nu sunt destul date despre coloane : mesaj eroare, ne oprim
						{
							cout << "Nu exista informatiile necesare pt fiecare coloana" << endl;
							return;
						}
					}
				}
				else //daca numele tabelei este NULL (teoretic acest lucru nu ar fi posibil folosind in functia strtok delimitator " ")
					 //dar ne asiguram : mesaj eroare, ne oprim
				{
					cout << "Nume tabela invalid" << endl;
					return;
				}
			}
			else //daca TABLE nu urmeaza dupa CREATE (comanda incorecta): mesaj eroare, ne oprim
			{
				cout << "Comanda CREATE TABLE nu este corecta!" << endl;
			}
			return;
		}

		if (strcmp(cuv[0], "DROP") == 0)
		{
			comanda_valida = 1;
			if (strcmp(cuv[1], "TABLE") == 0)
			{
				if (cuv[2] != NULL)
				{
					string s(cuv[2]);//nume tabela
					int k = 1;//nu exista tabela
					for (int i = 0; i < nr_tabele; i++)//parcurgem tabelele din bd
					{
						if (tab_utilizator[i].nume_tabela == s)//verificam daca numele tabelei este cel introdus de noi
						{
							k = 0;//exista tabela
						}
					}
					if (k == 1)
					{
						cout << "Numele tabelei nu exista in bd!";
						return;
					}
					else
					{
						TABELA* aux_tab_u = nullptr;
						aux_tab_u = new TABELA[nr_tabele - 1];//copie cu dimenisunea mai mica cu un el.
						int j = 0;//contor 
						for (int i = 0; i < nr_tabele; i++)
						{
							if (tab_utilizator[i].nume_tabela != s)
							{
								aux_tab_u[j] = tab_utilizator[i];
								j++;
							}
						}
						delete[] tab_utilizator;
						nr_tabele--;
						tab_utilizator = new TABELA[nr_tabele];
						for (int i = 0; i < nr_tabele; i++)
						{
							tab_utilizator[i] = aux_tab_u[i];
						}
						delete[] aux_tab_u;
					}
				}
				else
				{
					cout << "Nume tabela invalid" << endl;
					return;
				}
			}
			else
			{
				cout << "Comanda DROP nu este corecta!" << endl;
				return;
			}
		}

		if (strcmp(cuv[0], "DISPLAY") == 0)
		{
			comanda_valida = 1;
			if (strcmp(cuv[1], "TABLE") == 0)
			{
				if (cuv[2] != NULL)
				{
					string s(cuv[2]); //nume tabela
					int k = 0; //nu exista tabela
					int i;
					for (i = 0; i < nr_tabele; i++)//parcurgem tabelele
					{
						if (tab_utilizator[i].nume_tabela == s)//verificam daca tabela exista in baza de date
						{
							k = 1; break; //tabela exista, se retine pozitia in i
						}
					}
					if (k == 0)
					{
						cout << "Numele tabelei nu exista in baza de date!";
						return;
					}
					else
					{
						cout << "Numele tabelei: " << tab_utilizator[i].nume_tabela << endl;
						int kt = 0; int ki = 0; int kf = 0;
						for (int j = 0; j < tab_utilizator[i].nr_total_coloane; j++)
						{
							if (tab_utilizator[i].ordine_coloane[j] == 1) //j parcurge coloanele in general, iar k de t,i,f retine pozitia parcurgerii pe tipuri
							{
								cout << tab_utilizator[i].coloane_text[kt].nume_coloana;
								cout << " text";
								cout << "(" << tab_utilizator[i].coloane_text[kt].dimensiune_text << ")" << endl;
								kt++; //trece la urmatoarea coloana !! de acelasi tip !!
							}

							if (tab_utilizator[i].ordine_coloane[j] == 2)
							{
								cout << tab_utilizator[i].coloane_integer[ki].nume_coloana;
								cout << " int";
								cout << "(" << tab_utilizator[i].coloane_integer[ki].getDimensiuneInteger() << ")" << endl;
								ki++;
							}

							if (tab_utilizator[i].ordine_coloane[j] == 3)
							{
								cout << tab_utilizator[i].coloane_float[kf].nume_coloana;
								cout << " float";
								cout << "(" << tab_utilizator[i].coloane_float[kf].getDimensiuneFloat() << ")" << endl;
								kf++;
							}
						}
						return;
					}
				}
				else
				{
					cout << "Comanda DISPLAY nu este corecta!" << endl;
					return;
				}
			}
			else
			{
				cout << "Comanda DISPLAY nu este corecta!" << endl;
				return;
			}
		}

		if (strcmp(cuv[0], "INSERT") == 0)
		{
			comanda_valida = 1;
			if (strcmp(cuv[1], "INTO") == 0)
			{
				if (strcmp(cuv[3], "VALUES") == 0)
				{
					if (cuv[2] != NULL)
					{
						int nr_col = 0; //nr coloane
						string s(cuv[2]); //nume tabela
						int k = 0; //presupunem ca tabela nu exista
						int j;
						for (j = 0; j < nr_tabele; j++)
						{
							//verificare nume existent in vectorul de tabele
							if (tab_utilizator[j].nume_tabela == s)
							{
								k = 1; //tabela este gasita
								break; //j ramane la pozitia tabelei gasite
							}
						}
						if (k == 0)
						{
							cout << "Numele tabelei nu exista!";
							return;
						}
						else
						{
							int nr_val_introduse = nr_cuv - 4;
							if (nr_val_introduse == tab_utilizator[j].nr_total_coloane)//verificam ca nr de valori introduse sa fie egal cu nr de coloane al tabelei
							{
								int error = 0;//presupunem ca nu exista valori nevalide in comanda
								int a = 4;
								for (int i = 0; i < tab_utilizator[j].nr_total_coloane; i++)//verificare ordine/tip corect(a)
								{
									if (tab_utilizator[j].ordine_coloane[i] == 1)
									{
										if (isCharLetter(cuv[a]) == 0) error = 1;
									}
									if (tab_utilizator[j].ordine_coloane[i] == 2)
									{
										if (isCharInt(cuv[a]) == 0) error = 1;
									}
									if (tab_utilizator[j].ordine_coloane[i] == 3)
									{
										if (isCharFloat(cuv[a]) == 0) error = 1;
									}
									if (error == 1) i = tab_utilizator[j].nr_total_coloane + 1;
									a++;
								}
								if (error == 1)
								{
									cout << "Valorile introduse nu sunt valide!";
									return;
								}
								int ki = 0; int kf = 0; int kt = 0;
								for (int i = 0; i < tab_utilizator[j].nr_total_coloane; i++)
								{
									if (tab_utilizator[j].ordine_coloane[i] == 1)
									{
										int newsize = (tab_utilizator[j].coloane_text[kt].getNrValoriText()) + 1;//nr de valori text nou
										char** temp = new char* [newsize];//alocare spatiu nr de cuvinte
										for (int z = 0; z < newsize; z++)
										{
											temp[z] = new char[tab_utilizator[j].coloane_text[kt].getDimensiuneText()];//alocam lungimea max a unei valori text
										}

										for (int l = 0; l < newsize - 1; l++)
										{
											temp[l] = tab_utilizator[j].coloane_text[kt].getValoriText()[l];  //copiem vectorul intr o copie cu nr de elemente + 1
										}
										strcpy_s(temp[newsize - 1], strlen(cuv[4 + i]) + 1, cuv[4 + i]);

										tab_utilizator[j].coloane_text[kt].setValoriText(temp, newsize);

										kt++;  //trece la urmatoarea coloana !! de acelasi tip !!
									}
									if (tab_utilizator[j].ordine_coloane[i] == 2)
									{
										int newsize = tab_utilizator[j].coloane_integer[ki].getNrValoriInteger() + 1;
										int* temp = new int[newsize];
										for (int l = 0; l < newsize - 1; l++)
										{
											temp[l] = tab_utilizator[j].coloane_integer[ki].getValoriInteger()[l];
										}
										temp[newsize - 1] = ConvertCharToInt(cuv[4 + i]);

										tab_utilizator[j].coloane_integer[ki].setValoriInteger(temp, newsize);
										ki++;
									}

									if (tab_utilizator[j].ordine_coloane[i] == 3)
									{
										int newsize = tab_utilizator[j].coloane_float[kf].getNrValoriFloat() + 1;
										float* temp = new float[newsize];
										for (int l = 0; l < newsize - 1; l++)
										{
											temp[l] = tab_utilizator[j].coloane_float[kf].getValoriFloat()[l];
										}
										temp[newsize - 1] = ConvertCharToFloat(cuv[4 + i]);

										tab_utilizator[j].coloane_float[kf].setValoriFloat(temp, newsize);
										kf++;
									}
								}
								cout << "Inregistrarea a fost inserata.";
							}
							else
							{
								cout << "Nu ati introdus nr corect de valori de inserat!";
								return;
							}
						}
					}
					else
					{
						cout << "Nume tabela incorect!" << endl;
						return;
					}
				}
				else
				{
					cout << "Comanda INSERT incorecta!" << endl;
					return;
				}
			}
			else
			{
				cout << "Comanda INSERT incorecta!" << endl;
				return;
			}

		}

		if (strcmp(cuv[0], "DELETE") == 0)
		{
			comanda_valida = 1;
			int j;
			if (strcmp(cuv[1], "FROM") == 0)
			{
				if (cuv[2] != NULL)
				{
					string s(cuv[2]); //nume tabela
					int k = 1; //nu exista numele tabelei
					for (j = 0; j < nr_tabele; j++) //parcurgem tabelele din bd
					{
						if (tab_utilizator[j].nume_tabela == s) //verificam daca numele tabelei este cel introdus de noi
						{
							k = 0; break; //exista tabela
						}
					}
					if (k == 1)
					{
						cout << "Numele tabelei nu exista in bd!";
						return;
					}
					else
					{
						if (strcmp(cuv[3], "WHERE") == 0)
						{
							if (strcmp(cuv[5], "=") == 0)
							{
								string s(cuv[6]);
								int index_vector_init;
								int* vector_init = nullptr;
								int val_valida = 0; //daca valoarea cautata este valida va deveni 1
								if (isCharFloat(cuv[6]) == 1)
								{
									val_valida = 1;
									string s(cuv[4]);
									int k = 0;//cand nu exista nume coloana
									int y;//va retine pozitia coloanei in tab_utilizator.coloane_float
									for (y = 0; y < tab_utilizator[j].nr_total_coloane; y++)
									{
										if (tab_utilizator[j].coloane_float[y].nume_coloana == s)
										{
											k = 1; break;//cand exista nume coloana
										}
									}
									if (k == 0)
									{
										cout << "Numele coloanei nu exista in tabela!" << endl;
										return;
									}
									else
									{
										float aux_fl = ConvertCharToFloat(cuv[6]);
										int x = 0;
										//vector_init -> vector in care vom pune pozitiile pe care se afla valoarea cautata
										for (int l = 0; l < tab_utilizator[j].coloane_float[y].nr_valori_float; l++)
										{
											if (tab_utilizator[j].coloane_float[y].valori_float[l] == aux_fl)
											{
												x++;//numaram de cate ori se gaseste valoarea dorita pt stergere
											}
										}
										if (x > 0)
										{
											vector_init = new int[x];//alocam spatiu pt cele x valori gasite
											index_vector_init = 0;
											for (int l = 0; l < tab_utilizator[j].coloane_float[y].nr_valori_float; l++)
											{
												if (tab_utilizator[j].coloane_float[y].valori_float[l] == aux_fl)
												{
													vector_init[index_vector_init] = l;
													index_vector_init++;
												}
											}
										}
										else
										{
											cout << "Valoarea float cautata nu se gaseste in tabela " << tab_utilizator[j].nume_tabela << endl;
											return;
										}
									}
								}
								if ((val_valida == 0) && (isCharInt(cuv[6]) == 1))
								{
									val_valida = 1;
									string s(cuv[4]);
									int k = 1;//cand nu exista nume coloana
									int y = 0;
									for (y = 0; y < tab_utilizator[j].nr_total_coloane; y++)
									{
										if (tab_utilizator[j].coloane_integer[y].nume_coloana == s)
										{
											k = 0; break;//cand exista nume coloana
										}
									}
									if (k == 1)
									{
										cout << "Numele coloanei nu exista in tabela!" << endl;
										return;
									}
									else
									{
										int aux_int = ConvertCharToInt(cuv[6]);
										int x = 0;
										//vector_init -> vector in care vom pune pozitiile pe care se afla valoarea cautata
										for (int l = 0; l < tab_utilizator[j].coloane_integer[y].nr_valori_integer; l++)
										{
											if (tab_utilizator[j].coloane_integer[y].valori_integer[l] == aux_int)
											{
												x++;//numaram de cate ori se gaseste valoarea dorita pt stergere
											}
										}
										if (x > 0)
										{
											vector_init = new int[x];//alocam spatiu pt cele x valori gasite
											index_vector_init = 0;
											for (int l = 0; l < tab_utilizator[j].coloane_integer[y].nr_valori_integer; l++)
											{
												if (tab_utilizator[j].coloane_integer[y].valori_integer[l] == aux_int)
												{
													vector_init[index_vector_init] = l;
													index_vector_init++;
												}
											}
										}
										else
										{
											cout << "Valoarea integer cautata nu se gaseste in tabela " << tab_utilizator[j].nume_tabela << endl;
											return;
										}
									}
								}
								if ((val_valida == 0) && (isCharLetter(cuv[6]) == 1))
								{
									val_valida = 1;
									string s(cuv[4]);
									int k = 1;//cand nu exista nume coloana
									int y = 0;
									for (y = 0; y < tab_utilizator[j].nr_total_coloane; y++)
									{
										if (tab_utilizator[j].coloane_text[y].nume_coloana == s)
										{
											k = 0; break;//cand exista nume coloana
										}
									}

									if (k == 1)
									{
										cout << "numele coloanei nu exista in bd" << endl;
										return;
									}
									else
									{
										int x = 0;//de cate ori gasim valoarea cautata
										//vector_init -> vector in care vom pune pozitiile pe care se afla valoarea cautata
										for (int l = 0; l < tab_utilizator[j].coloane_text[y].nr_valori_text; l++)
										{
											string aux_s(tab_utilizator[j].coloane_text[y].valori_text[l]);
											if (aux_s == cuv[6])
											{
												x++;//numaram de cate ori se gaseste valoarea dorita pt stergere
											}
										}
										if (x > 0)
										{
											vector_init = new int[x];//alocam spatiu pt cele x valori gasite
											index_vector_init = 0;
											for (int l = 0; l < tab_utilizator[j].coloane_text[y].nr_valori_text; l++)
											{
												string aux_s(tab_utilizator[j].coloane_text[y].valori_text[l]);
												if (aux_s == cuv[6])
												{
													vector_init[index_vector_init] = l;
													index_vector_init++;
												}
											}
										}
										else
										{
											cout << "Valoarea text cautata nu se gaseste in tabela " << tab_utilizator[j].nume_tabela << endl;
											return;
										}
									}
								}
								if (val_valida == 0)
								{
									cout << "Valoarea ce se cauta in tabela " << tab_utilizator[j].nume_tabela << " nu este valida!" << endl;
									return;
								}
								//continuam cu stergerea inregistrarilor ce corespund
								//j=indexul tabelei
								//vector_init = vector de pozitii in coloane
								//index_vector_init = nr elemente vector init
								if (vector_init != nullptr)//daca se ajunge pana in acest pas, nu are cum sa fie NULL; totusi, verificam 
								{
									int nr_val_v_init = index_vector_init;
									for (int fl = 0; fl < tab_utilizator[j].nr_coloane_float; fl++)
									{
										float* copie_valori_float = new float[tab_utilizator[j].coloane_float[fl].nr_valori_float - nr_val_v_init];
										int c_copie = 0; //contor copie_valori_float
										int c_init = 0; //contor vector_init
										for (int kf = 0; kf < tab_utilizator[j].coloane_float[fl].nr_valori_float; kf++)
										{
											if (vector_init[c_init] != kf)
											{
												copie_valori_float[c_copie] = tab_utilizator[j].coloane_float[fl].valori_float[kf];
												c_copie++;
												c_init++;
											}
										}
										delete[]tab_utilizator[j].coloane_float[fl].valori_float;
										if (c_copie == 0)
											tab_utilizator[j].coloane_float[fl].valori_float = nullptr;
										else
											tab_utilizator[j].coloane_float[fl].valori_float = new float[c_copie];
										tab_utilizator[j].coloane_float[fl].nr_valori_float = c_copie;
										for (int l = 0; l < c_copie; l++)
										{
											tab_utilizator[j].coloane_float[fl].valori_float[l] = copie_valori_float[l];
										}
										delete[] copie_valori_float;
									}
									for (int in = 0; in < tab_utilizator[j].nr_coloane_integer; in++)
									{
										int* copie_valori_integer = new int[tab_utilizator[j].coloane_integer[in].nr_valori_integer - nr_val_v_init];
										int c_copie = 0; //contor copie_valori_float
										int c_init = 0; //contor vector_init
										for (int kf = 0; kf < tab_utilizator[j].coloane_integer[in].nr_valori_integer; kf++)
										{
											if (vector_init[c_init] != kf)
											{
												copie_valori_integer[c_copie] = tab_utilizator[j].coloane_integer[in].valori_integer[kf];
												c_copie++;
												c_init++;
											}
										}
										delete[]tab_utilizator[j].coloane_integer[in].valori_integer;

										if (c_copie == 0)
											tab_utilizator[j].coloane_integer[in].valori_integer = nullptr;
										else
											tab_utilizator[j].coloane_integer[in].valori_integer = new int[c_copie];
										tab_utilizator[j].coloane_integer[in].nr_valori_integer = c_copie;
										for (int l = 0; l < c_copie; l++)
										{
											tab_utilizator[j].coloane_integer[in].valori_integer[l] = copie_valori_integer[l];
										}
										delete[] copie_valori_integer;
									}

									for (int te = 0; te < tab_utilizator[j].nr_coloane_text; te++)
									{
										char** copie_valori_text = nullptr;
										copie_valori_text = new char* [tab_utilizator[j].coloane_text[te].nr_valori_text - nr_val_v_init];
										for (int cc = 0; cc < tab_utilizator[j].coloane_text[te].nr_valori_text; cc++)
										{
											copie_valori_text[cc] = new char[tab_utilizator[j].coloane_text[te].dimensiune_text];
										}
										int c_copie = 0; //contor copie_valori_float
										int c_init = 0; //contor vector_init
										for (int kf = 0; kf < tab_utilizator[j].coloane_text[te].nr_valori_text; kf++)
										{
											if (vector_init[c_init] != kf)
											{
												strcpy_s(copie_valori_text[c_copie], strlen(tab_utilizator[j].coloane_text[te].valori_text[kf]) + 1, tab_utilizator[j].coloane_text[te].valori_text[kf]);
												c_copie++;
												c_init++;
											}
										}
										delete[]tab_utilizator[j].coloane_text[te].valori_text;

										if (c_copie == 0)
											tab_utilizator[j].coloane_text[te].valori_text = nullptr;
										else
										{
											tab_utilizator[j].coloane_text[te].valori_text = new char* [c_copie];
											for (int cc = 0; cc < c_copie; cc++)
											{
												tab_utilizator[j].coloane_text[te].valori_text[cc] = new char[tab_utilizator[j].coloane_text[te].dimensiune_text];;
											}
										}
										tab_utilizator[j].coloane_text[te].nr_valori_text = c_copie;
										for (int l = 0; l < c_copie; l++)
										{
											strcpy_s(tab_utilizator[j].coloane_text[te].valori_text[l], strlen(copie_valori_text[l]) + 1, copie_valori_text[l]);
											//tab_utilizator[j].coloane_text[te].valori_text[l] = copie_valori_text[l];
										}
										/*if (copie_valori_text != nullptr)
										{
											for (int cc = 0; cc < c_copie; cc++)
											{ //nu intra in if ca sa dezaloce cum ar trebui, nu am descoperit inca problema
												delete[] copie_valori_text[cc];
											}
											delete[] copie_valori_text;
										}*/
									}
									cout << "Comanda DELETE finalizata cu succes." << endl;
									return;
								}
								cout << "DELETE nu a putut fi dus pana la capat!";
								return;
							}
						}
					}
				}
				else
				{
					cout << "Nume tabela invalid!" << endl;
					return;
				}
			}
			else
			{
				cout << "Comanda DELETE incorecta!" << endl;
				return;
			}
		}

		if (strcmp(cuv[0], "SELECT") == 0)
		{
			comanda_valida = 1;
			if (strcmp(cuv[1], "ALL") == 0) //SELECT ALL FROM ...
			{
				if (strcmp(cuv[2], "FROM") == 0)
				{
					if (cuv[3] != NULL)
					{
						int i;
						int ok = 0;//presupunem ca nu exista tabela cautata
						for (i = 0; i < nr_tabele; i++)
						{
							string num(cuv[3]);
							if (num == tab_utilizator[i].nume_tabela)
							{
								ok = 1;//tabela a fost gasita
								break; //se retine pozitia ei in contorul i
							}
						}
						if (ok == 1)//tabela exista deci se efectueaza afisarea
						{
							TABELA copie_tab = tab_utilizator[i];
							cout << copie_tab;
						}
						else
						{
							cout << "Numele tabelei nu exista" << endl;
							return;
						}
					}
					else
					{
						cout << "Nu s-a introdus numele tabelei!" << endl;
						return;
					}
				}
				else
				{
					cout << "Comanda SELECT nu este corecta!" << endl;
					return;
				}
			}
			else //SELECT coloane FROM ...
			{
				int j;
				int ok = 0;//presupunem ca nu exista FROM
				for (j = 2; j < nr_cuv; j++) //cautam FROM, presupunem ca exista macar o coloana in SELECT, deci incepem de pe pozitia 2
				{
					if (strcmp(cuv[j], "FROM") == 0)
					{
						ok = 1;//FROM a fost gasit
						break;//se retine in j pozitia lui FROM in cuv[]
					}
				}
				if (ok == 1)
				{
					//cautam sa se specifice un nume de tabela dupa FROM
					if (cuv[j + 1] != NULL)
					{
						//cautam sa existe tabela
						int i;
						int ok = 0;//presupunem ca nu exista tabela cautata
						for (i = 0; i < nr_tabele; i++)
						{
							string num(cuv[j + 1]);
							if (num == tab_utilizator[i].nume_tabela)
							{
								ok = 1;//tabela a fost gasita
								break; //se retine pozitia ei in contorul i
							}
						}
						if (ok == 1)//tabela exista, urmeaza sa cautam daca exista coloanele specificate 
						{
							int coloane_existente = 0;
							//i=pozitie tabela; j=pozitie FROM; 0=pozitie SELECT
							int poz = 1;
							int ok = 1;
							while (poz < j && ok == 1)
							{
								ok = 0; //presupun ca NU exista coloana 
								string num(cuv[poz]);
								for (int w = 0; w < tab_utilizator[i].nr_coloane_text; w++)
								{
									if (tab_utilizator[i].coloane_text[w].nume_coloana == num)
									{
										ok = 1;
										break;
									}
								}
								if (ok == 0)
								{
									for (int w = 0; w < tab_utilizator[i].nr_coloane_integer; w++)
									{
										if (tab_utilizator[i].coloane_integer[w].nume_coloana == num)
										{
											ok = 1;
											break;
										}
									}
								}
								if (ok == 0)
								{
									for (int w = 0; w < tab_utilizator[i].nr_coloane_float; w++)
									{
										if (tab_utilizator[i].coloane_float[w].nume_coloana == num)
										{
											ok = 1;
											break;
										}
									}
								}
								if (ok == 1)
								{
									coloane_existente++;
								}
								poz++;
							}

							if (ok == 1 && coloane_existente == (j - 1))//toate coloanele exista, deci le afisam
							{
								cout << endl << "Nume tabela: " << tab_utilizator[i].nume_tabela << endl;
								cout << "Coloanele ce sunt afisate prin SELECT: " << endl;
								poz = 1;
								ok = 1;
								while (poz < j && ok == 1)
								{
									string num(cuv[poz]);
									ok = 0;
									for (int w = 0; w < tab_utilizator[i].nr_coloane_text; w++)
									{
										if (tab_utilizator[i].coloane_text[w].nume_coloana == num)
										{
											cout << tab_utilizator[i].coloane_text[w];
											ok = 1;
										}
									}
									if (ok == 0)
									{
										for (int w = 0; w < tab_utilizator[i].nr_coloane_integer; w++)
										{
											if (tab_utilizator[i].coloane_integer[w].nume_coloana == num)
											{
												cout << tab_utilizator[i].coloane_integer[w];
												ok = 1;
											}
										}
									}
									if (ok == 0)
									{
										for (int w = 0; w < tab_utilizator[i].nr_coloane_float; w++)
										{
											if (tab_utilizator[i].coloane_float[w].nume_coloana == num)
											{
												cout << tab_utilizator[i].coloane_float[w];
												ok = 1;
											}
										}
									}
									poz++;
									cout << endl;
								}
							}
							else
							{
								cout << "Cel putin una dintre coloane nu exista/este scrisa incorect in comanda!";
								return;
							}
						}
						else
						{
							cout << "Numele tabelei nu exista" << endl;
							return;
						}
					}
					else
					{
						cout << "Nu s-a introdus numele tabelei!";
						return;
					}
				}
				else
				{
					cout << "Comanda SELECT nu este corecta!";
					return;
				}
			}
		}

		if (strcmp(cuv[0], "UPDATE") == 0)
		{
			comanda_valida = 1;
			////int j;
			////if (cuv[1] != NULL)
			////{
			////	int nr_col = 0; //nr coloane
			////	string s(cuv[1]); //nume tabela
			////	int k = 1;
			////	for (j = 0; j < nr_tabele; j++)
			////	{
			////		//verificare nume existent in vectorul de tabele, presupunand ca numele nou nu exista (k = 1)
			////		if (tab_utilizator[j].nume_tabela == s)
			////		{
			////			k = 0; break; //j ramane la valoarea gasita
			////		}
			////	}

			////	if (k == 1) {
			////		cout << "Tabelul nu exista!"; return;
			////	}
			////	else {
			////		if (strcmp(cuv[2], "SET") == 0)
			////		{
			////			if (strcmp(cuv[6], "WHERE") == 0)
			////			{
			////				string nume(cuv[7]); int ok = 0; int x = 0;
			////				for (int i = 0; i < tab_utilizator[j].nr_coloane_integer; i++)
			////				{
			////					if (nume == tab_utilizator[j].coloane_integer[i].nume_coloana)
			////					{
			////						ok = 1; x = 1; break;
			////					}

			////				}

			////				if (ok == 0) {
			////					for (int i = 0; i < tab_utilizator[j].nr_coloane_float; i++)
			////					{
			////						if (nume == tab_utilizator[j].coloane_float[i].nume_coloana)
			////						{
			////							ok = 1; x = 2; break;
			////						}

			////					}
			////					if (ok == 0)
			////					{
			////						for (int i = 0; i < tab_utilizator[j].nr_coloane_text; i++)
			////						{
			////							if (nume == tab_utilizator[j].coloane_text[i].nume_coloana)
			////							{
			////								ok = 1; x = 3; break;
			////							}

			////						}
			////					}
			////				}

			////				if (ok == 0) {
			////					cout << "Nu exista coloana din WHERE";
			////					return;
			////				}
			////			}
			////			else {
			////				cout << "Comanda incorecta."; return;
			////			}


			////		}
			////	}
			//}
		}

		if (comanda_valida == 0)
		{
			cout << "Cuvantul cheie al comenzii nu este corect sau nu exista!" << endl;
			return;
		}
	}
}

#endif // !COMANDA_UTILIZATOR_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> 
#include <conio.h>
#define LICZBA_KOLOROW 4
#define PIK_LICZBA 1
#define KIER_LICZBA 2
#define KARO_LICZBA 3
#define TREFL_LICZBA 4
#define PIK_ROZMIAR 4
#define KIER_ROZMIAR 5
#define KARO_ROZMIAR 5
#define TREFL_ROZMIAR 6
#define GRACZ_1 1
#define GRACZ_2 2
#define REMIS 3

using namespace std;

//-----------------------------------------------------
//const int MADRA_WOJNA = 1;
const char PIKI[] = { 'P', 'I', 'K', '\0' };
const char KIERY[] = { 'K', 'I', 'E', 'R', '\0' };
const char KARA[] = { 'K', 'A', 'R', 'O', '\0' };
const char TREFLE[] = { 'T', 'R', 'E', 'F', 'L', '\0' };

typedef struct
{
	int moc;
	char symbol[3];
	char rodzaj[6];

}karta_t;

typedef enum
{
	NIE_ROZPOCZETA,
	W_TOKU,
	ZAKONCZONA

}stan_gry_t;

typedef struct reka
{
	karta_t karta;
	struct reka* nastepny;
	int liczba_kart;
	int indeks;
	char strategia;

}reka_t;

typedef struct
{
	reka_t reka;

}gracz_t;

typedef struct
{
	char wariant;
	int talia_kart;
	stan_gry_t stan;
	int liczba_ruchow;
	char czy_madra;
	char strategia_pierwszego;
	char strategia_drugiego;
	//int ranga_reki_pierwszego;
	//int ranga_reki_drugiego;
	int wybiera_z_dwoch;

}gra_t;

//----------------------------------------------------
void Rozpocznij_Gre(gra_t*);
void Interfejs(gracz_t*, gracz_t*, gra_t*);
void Przelec_Do_Konca(gracz_t*, gracz_t*, gra_t*);
void Tworz_Talie(gracz_t*, gracz_t*, gra_t*);
void Rozdziel_Karty(gracz_t*, gracz_t*, karta_t[], gra_t*);
void Inicjuj(reka_t*, karta_t);
void Dodaj_Na_Koncu(reka_t*, karta_t);
reka_t Po_Usunieciu_Z_Poczatku(reka_t*, gra_t*);
void Bitwa(reka_t*, reka_t*, gra_t*);
void Koniec_Bitwy(reka_t*, reka_t*, gra_t*);
void Wojna(reka_t*, reka_t*, gra_t*);
void Pomocnik_Wojny(reka_t*, reka_t*, reka_t*, reka_t*, const char, int*, gra_t*);
void Wariant_A(reka_t*, reka_t*, reka_t*, reka_t*, gra_t*);
void Wariant_B(reka_t*, reka_t*, reka_t*, reka_t*, int*, gra_t*);
void Standardowa_Wojna(reka_t*, reka_t*, reka_t*, reka_t*, gra_t*);
void Przekaz_Jedna_Karte(reka_t*, reka_t*, reka_t*, reka_t*, int*, gra_t*);
void Przekaz_Dwie_Karty(reka_t*, reka_t*, reka_t*, reka_t*, int*, gra_t*);
void Zostaly_Po_Trzy_Karty(reka_t*, reka_t*, gra_t*);
void Przenies_Karte(reka_t*, reka_t*);
void Przenies_Wszystko(reka_t*, reka_t*, reka_t*, reka_t*, int, gra_t*);
void Sprawdz_Czy_Mozesz_Usunac(reka_t*, reka_t*, const int, gra_t*);
void Koniec_Gry(const int, gra_t*);
void Wypisz_Karty(reka_t*, reka_t*);
//---------------dodatkowe funkcje do madrej wojny-----
void Podmien_Karty_Madra(reka_t*, reka_t*, const char);
void Przenies_Wszystko_Madra(reka_t*, reka_t*, reka_t*, reka_t*, int, gra_t*);
void Interfejs_Madra(gracz_t*, gracz_t*, gra_t*);
void Wypisz_Karty_Madra(reka_t*, reka_t*, const char);

int main()
{
	srand(time(NULL));
	gracz_t gracz_pierwszy, gracz_drugi;
	gra_t rozgrywka;
	//for (int k = 20; k <= 52; k += 4)
	//{
	//rozgrywka.talia_kart = 52;

	//Sleep(800);
	//rozgrywka.stan = NIE_ROZPOCZETA;
	//rozgrywka.liczba_ruchow = 0;
	//rozgrywka.ranga_reki_pierwszego = 0;
	//rozgrywka.ranga_reki_drugiego = 0;
	//if (MADRA_WOJNA == 1)
	//{
	/*for (int j = 0; j < 6; j++)
	{
		if (j == 0)
		{
			rozgrywka.strategia_pierwszego = 'L';
			rozgrywka.strategia_drugiego = 'L';
		}
		else if (j == 1)
		{
			rozgrywka.strategia_pierwszego = 'L';
			rozgrywka.strategia_drugiego = 'W';
		}
		else if (j == 2)
		{
			rozgrywka.strategia_pierwszego = 'L';
			rozgrywka.strategia_drugiego = 'P';
		}
		else if (j == 3)
		{
			rozgrywka.strategia_pierwszego = 'W';
			rozgrywka.strategia_drugiego = 'W';
		}
		else if (j == 4)
		{
			rozgrywka.strategia_pierwszego = 'W';
			rozgrywka.strategia_drugiego = 'P';
		}
		else
		{
			rozgrywka.strategia_pierwszego = 'P';
			rozgrywka.strategia_drugiego = 'P';
		}
		for (int i = 0; i < 1000; i++)
		{
			rozgrywka.stan = NIE_ROZPOCZETA;
			rozgrywka.wariant = 'A';
			rozgrywka.liczba_ruchow = 0;
			rozgrywka.czy_madra = 'M';
			//rozgrywka.talia_kart = 52;*/
	rozgrywka.wybiera_z_dwoch = GRACZ_2;
	//Tworz_Talie(&gracz_pierwszy, &gracz_drugi, &rozgrywka);
	/*while (rozgrywka.stan != ZAKONCZONA)
	{
		Wypisz_Karty(&gracz_pierwszy.reka, &gracz_drugi.reka);
		Bitwa(&gracz_pierwszy.reka, &gracz_drugi.reka, &rozgrywka);
	}*/
	//while (rozgrywka.stan != ZAKONCZONA)
	//{
	//	Bitwa(&gracz_pierwszy.reka, &gracz_drugi.reka, &rozgrywka);
	//}
//}
//}
//}
//else
//{
	//rozgrywka.strategia_pierwszego = 'P';
	//rozgrywka.strategia_drugiego = 'W';
	Rozpocznij_Gre(&rozgrywka);
	Tworz_Talie(&gracz_pierwszy, &gracz_drugi, &rozgrywka);
	if (rozgrywka.czy_madra == 'Z')
	{
		Interfejs(&gracz_pierwszy, &gracz_drugi, &rozgrywka);
	}
	else
	{
		Interfejs_Madra(&gracz_pierwszy, &gracz_drugi, &rozgrywka);
	}
	//}


//}
}


void Interfejs(gracz_t* gracz_pierwszy, gracz_t* gracz_drugi, gra_t* rozgrywka)
{
	char znak = 'a';
	while (znak != '0' && rozgrywka->stan != ZAKONCZONA)
	{
		cout << "-------------------------" << endl;
		//cout << rozgrywka->liczba_ruchow << endl;
		//cout << rozgrywka->ranga_reki_pierwszego << " " << rozgrywka->ranga_reki_drugiego << endl;
		//cout << rozgrywka->wariant << endl;
		Wypisz_Karty(&gracz_pierwszy->reka, &gracz_drugi->reka);
		if (rozgrywka->stan == ZAKONCZONA)
		{
			break;
		}
		//cout << "-------------------------" << endl << endl;
		cout << "Wcisnij:" << endl << endl;
		cout << "- '0', aby przeleciec na koniec rozgrywki" << endl;
		cout << "- dowolny inny przycisk, aby przejsc do kolejnej tury" << endl;
		cout << endl << "a nastepnie zatwierdz ENTEREM" << endl;
		cin >> znak;
		Bitwa(&gracz_pierwszy->reka, &gracz_drugi->reka, rozgrywka);
		system("cls");
		//if (rozgrywka->czy_madra == 'M')
		//{
		//	cout << "          ************* GRA W MADRA WOJNE! *************        " << endl << endl;
		//}
		//else
		//{
		cout << "          ************* GRA W WOJNE! *************        " << endl << endl;
		//}
		if (znak == '0')
		{
			Przelec_Do_Konca(gracz_pierwszy, gracz_drugi, rozgrywka);
			break;
		}
	}
}


void Interfejs_Madra(gracz_t* gracz_pierwszy, gracz_t* gracz_drugi, gra_t* rozgrywka)
{
	rozgrywka->strategia_pierwszego = '0';
	rozgrywka->strategia_drugiego = 'L';
	char znak;
	while (rozgrywka->stan != ZAKONCZONA)
	{
		cout << "-------------------------" << endl;
		//Wypisz_Karty(&gracz_pierwszy->reka, &gracz_drugi->reka);
		if (rozgrywka->stan == ZAKONCZONA)
		{
			break;
		}
		//cout << "Wcisnij:" << endl << endl;
		//cout << "- '0', aby przeleciec na koniec rozgrywki" << endl;
		system("cls");
		cout << "          ************* GRA W MADRA WOJNE! *************        " << endl << endl;
		Wypisz_Karty(&gracz_pierwszy->reka, &gracz_drugi->reka);
		Bitwa(&gracz_pierwszy->reka, &gracz_drugi->reka, rozgrywka);
		if (rozgrywka->stan != ZAKONCZONA)
		{
			cout << endl << "Wcisnij dowolny przycisk i zatwierdz ENTEREM, aby przejsc do kolejnej tury" << endl;
			cin >> znak;
		}
		//cout << endl << "a nastepnie zatwierdz ENTEREM" << endl;
		//if (rozgrywka->czy_madra == 'M')
		//{

		//}
		//else
		//{
		//	cout << "          ************* GRA W WOJNE! *************        " << endl << endl;
		//}
		//if (znak == '0')
		//{
		//	Przelec_Do_Konca(gracz_pierwszy, gracz_drugi, rozgrywka);
		//	break;
		//}
	}
}


//funkcja, która przewija rozgrywkę aż do momentu wyświetlenia zwycięzcy
void Przelec_Do_Konca(gracz_t* gracz_pierwszy, gracz_t* gracz_drugi, gra_t* rozgrywka)
{
	while (rozgrywka->stan != ZAKONCZONA)
	{
		system("cls");
		//cout << rozgrywka->liczba_ruchow << endl;
		if (rozgrywka->czy_madra == 'M')
		{
			cout << "          ************* GRA W MADRA WOJNE! *************        " << endl << endl;
		}
		else
		{
			cout << "          ************* GRA W WOJNE! *************        " << endl << endl;
		}
		Wypisz_Karty(&gracz_pierwszy->reka, &gracz_drugi->reka);
		cout << endl;
		Bitwa(&gracz_pierwszy->reka, &gracz_drugi->reka, rozgrywka);
	}
}


//funkcja z inicjalizacją i nadaniem początkowych wartości zmiennym
void Rozpocznij_Gre(gra_t* rozgrywka)
{
	system("cls");
	rozgrywka->stan = NIE_ROZPOCZETA;
	cout << "          ************* WITAMY W GRZE W WOJNE! *************        " << endl << endl;
	cout << "Wybierz tryb gry: " << endl;
	cout << "-Wpisz 'M' i zatwierdz ENTEREM jesli chcesz zagrac w madra wojne" << endl;
	cout << "-Wpisz 'Z' i zatwierdz ENTEREM jesli chcesz zagrac w zwykla wojne" << endl;
	cin >> rozgrywka->czy_madra;
	if (rozgrywka->czy_madra != 'M' && rozgrywka->czy_madra != 'Z')
	{
		Rozpocznij_Gre(rozgrywka);
		return;
	}
	cout << "Podaj liczbe kart (podzielna przez 4 oraz z przedzialu <20,52> ): ";
	scanf_s("%d", &rozgrywka->talia_kart);
	while (rozgrywka->talia_kart % 4 != 0 || rozgrywka->talia_kart < 20 || rozgrywka->talia_kart > 52)
	{
		char x;
		x = getchar();
		system("cls");
		cout << "          ************* WITAMY W GRZE W WOJNE! *************        " << endl << endl;
		cout << "Podaj liczbe kart (podzielna przez 4 oraz z przedzialu <20,52> ): ";
		scanf_s("%d", &rozgrywka->talia_kart);
	}
	if (rozgrywka->czy_madra == 'Z')
	{
		cout << endl << "Podaj wariant gry (A lub B): ";
		scanf_s("%c", &rozgrywka->wariant, 1);
		while (!(rozgrywka->wariant == 'A' || rozgrywka->wariant == 'B'))
		{
			system("cls");
			cout << "          ************* WITAMY W GRZE W WOJNE! *************        " << endl << endl;
			cout << "Podaj liczbe kart (podzielna przez 4 oraz z przedzialu <20,52> ): " << rozgrywka->talia_kart;
			cout << endl << endl << "Podaj wariant gry (A lub B): ";
			scanf_s("%c", &rozgrywka->wariant, 1);
			char x;
			x = getchar();
		}
		rozgrywka->liczba_ruchow = 0;
	}
	//rozgrywka->ranga_reki_pierwszego = 0;
	//rozgrywka->ranga_reki_drugiego = 0;
}


void Tworz_Talie(gracz_t* gracz_pierwszy, gracz_t* gracz_drugi, gra_t* rozgrywka)
{
	rozgrywka->stan = W_TOKU;
	const int TALIA_KART = rozgrywka->talia_kart;
	karta_t* talia_uporzadkowana = (karta_t*)malloc(TALIA_KART * sizeof(karta_t));
	gracz_pierwszy->reka.indeks = GRACZ_1;
	gracz_drugi->reka.indeks = GRACZ_2;

	for (int i = 0; i < TALIA_KART; i++)
	{
		int kolor = i % LICZBA_KOLOROW + 1;
		switch (kolor)
		{
		case PIK_LICZBA:
			//talia_uporzadkowana[i].kolor = PIK;
			for (int k = 0; k < PIK_ROZMIAR; k++)
			{
				talia_uporzadkowana[i].rodzaj[k] = PIKI[k];
			}break;
		case KIER_LICZBA:
			//talia_uporzadkowana[i].kolor = KIER;
			for (int k = 0; k < KIER_ROZMIAR; k++)
			{
				talia_uporzadkowana[i].rodzaj[k] = KIERY[k];
			}break;
		case KARO_LICZBA:
			for (int k = 0; k < KARO_ROZMIAR; k++)
			{
				talia_uporzadkowana[i].rodzaj[k] = KARA[k];
			}break;
		case TREFL_LICZBA:
			for (int k = 0; k < TREFL_ROZMIAR; k++)
			{
				talia_uporzadkowana[i].rodzaj[k] = TREFLE[k];
			}break;
		}
		const int stala_do_kart = 15;
		int sila_karty = (i / LICZBA_KOLOROW) % (TALIA_KART / LICZBA_KOLOROW) + stala_do_kart - (TALIA_KART / LICZBA_KOLOROW);
		talia_uporzadkowana[i].moc = sila_karty;
		if (char(sila_karty + 48) >= '2' && char(sila_karty + 48) <= '9')
		{
			talia_uporzadkowana[i].symbol[0] = char(sila_karty + 48);
			talia_uporzadkowana[i].symbol[1] = '\0';
		}
		else
		{
			switch (sila_karty)
			{
			case 10:
				talia_uporzadkowana[i].symbol[0] = '1';
				talia_uporzadkowana[i].symbol[1] = '0';
				talia_uporzadkowana[i].symbol[2] = '\0'; break;
			case 11:
				talia_uporzadkowana[i].symbol[0] = 'J';
				talia_uporzadkowana[i].symbol[1] = '\0'; break;
			case 12:
				talia_uporzadkowana[i].symbol[0] = 'Q';
				talia_uporzadkowana[i].symbol[1] = '\0'; break;
			case 13:
				talia_uporzadkowana[i].symbol[0] = 'K';
				talia_uporzadkowana[i].symbol[1] = '\0'; break;
			case 14:
				talia_uporzadkowana[i].symbol[0] = 'A';
				talia_uporzadkowana[i].symbol[1] = '\0'; break;
			}
		}
	}
	Rozdziel_Karty(gracz_pierwszy, gracz_drugi, talia_uporzadkowana, rozgrywka);
}


void Rozdziel_Karty(gracz_t* gracz_pierwszy, gracz_t* gracz_drugi, karta_t talia_uporzadkowana[], gra_t* rozgrywka)
{
	bool* czy_nowa = NULL;
	karta_t* talia_koncowa = NULL;
	const int TALIA_KART = rozgrywka->talia_kart;
	czy_nowa = (bool*)malloc(TALIA_KART * sizeof(bool));
	if (czy_nowa == NULL)
	{
		cout << "Brak pamieci!";
		exit(0);
	}
	for (int i = 0; i < TALIA_KART; i++)
	{
		czy_nowa[i] = false;
	}
	talia_koncowa = (karta_t*)malloc(TALIA_KART * sizeof(karta_t));
	if (talia_koncowa == NULL)
	{
		cout << "Brak pamieci!";
		exit(0);
	}
	for (int i = 0; i < TALIA_KART; i++)
	{
		int indeks = rand() % TALIA_KART;
		if (!czy_nowa[indeks])
		{
			czy_nowa[indeks] = true;
			talia_koncowa[indeks] = talia_uporzadkowana[i];
		}
		else
		{
			i--;
		}
	}
	gracz_pierwszy->reka.liczba_kart = 0;
	gracz_drugi->reka.liczba_kart = 0;
	for (int i = 0; i < TALIA_KART; i += 2)
	{
		//rozgrywka->ranga_reki_pierwszego += talia_koncowa[i].moc;
		//rozgrywka->ranga_reki_drugiego += talia_koncowa[i+1].moc;

		if (i == 0)
		{
			Inicjuj(&gracz_pierwszy->reka, talia_koncowa[i]);
			Inicjuj(&gracz_drugi->reka, talia_koncowa[i + 1]);
		}
		else
		{
			Dodaj_Na_Koncu(&gracz_pierwszy->reka, talia_koncowa[i]);
			Dodaj_Na_Koncu(&gracz_drugi->reka, talia_koncowa[i + 1]);
		}
	}
	//Wypisz_Karty(&gracz_pierwszy->reka, &gracz_drugi->reka);
	free(talia_uporzadkowana);
	free(talia_koncowa);
	free(czy_nowa);
}


//funkcja tworząca listę
void Inicjuj(reka_t* glowa, karta_t karta)
{
	glowa->liczba_kart++;
	glowa->karta = karta;
	glowa->nastepny = NULL;
}


void Dodaj_Na_Koncu(reka_t* juz_obecny, karta_t karta)
{
	juz_obecny->liczba_kart++;
	reka_t* nowy = (reka_t*)malloc(sizeof(reka_t));
	while (juz_obecny->nastepny != NULL)
	{
		juz_obecny = juz_obecny->nastepny;
	}

	if (nowy)
	{
		juz_obecny->nastepny = nowy;
		nowy->karta = karta;
		nowy->indeks = juz_obecny->indeks;
		nowy->nastepny = NULL;
	}
	else
	{
		cout << "BRAK PAMIECI!";
	}
}


reka_t Po_Usunieciu_Z_Poczatku(reka_t* glowa, gra_t* rozgrywka)
{
	glowa->nastepny->liczba_kart = glowa->liczba_kart;
	glowa->nastepny->indeks = glowa->nastepny->indeks;
	glowa = glowa->nastepny;
	glowa->liczba_kart--;
	rozgrywka->liczba_ruchow = rozgrywka->liczba_ruchow + 1;
	return *glowa;
}


void Wypisz_Karty(reka_t* reka_pierwsza, reka_t* reka_druga)
{
	cout << "GRACZ 1:   GRACZ 2: " << endl << endl;
	while (reka_pierwsza != NULL && reka_druga != NULL)
	{
		cout << reka_pierwsza->karta.symbol << " " << reka_pierwsza->karta.rodzaj;
		cout << "      " << reka_druga->karta.symbol << " " << reka_druga->karta.rodzaj << endl;
		reka_pierwsza = reka_pierwsza->nastepny;
		reka_druga = reka_druga->nastepny;
	}
	while (reka_pierwsza != NULL)
	{
		cout << reka_pierwsza->karta.symbol << " " << reka_pierwsza->karta.rodzaj << endl;
		reka_pierwsza = reka_pierwsza->nastepny;
	}
	while (reka_druga != NULL)
	{
		cout << "          " << reka_druga->karta.symbol << " " << reka_druga->karta.rodzaj << " " << endl;
		reka_druga = reka_druga->nastepny;
	}
	cout << endl << "------------------------------" << endl;
}


void Bitwa(reka_t* gracz_pierwszy, reka_t* gracz_drugi, gra_t* rozgrywka)
{
	if (rozgrywka->czy_madra == 'M')
	{
		if (rozgrywka->wybiera_z_dwoch == GRACZ_1 && gracz_pierwszy->liczba_kart > 1)
		{
			rozgrywka->wybiera_z_dwoch = GRACZ_2;
			Podmien_Karty_Madra(gracz_pierwszy, gracz_drugi, rozgrywka->strategia_pierwszego);
		}
		else if (rozgrywka->wybiera_z_dwoch == GRACZ_2 && gracz_drugi->liczba_kart > 1)
		{
			rozgrywka->wybiera_z_dwoch = GRACZ_1;
			Podmien_Karty_Madra(gracz_drugi, gracz_pierwszy, rozgrywka->strategia_drugiego);
		}
		else
		{
			cout << endl << "GRACZ 1:   KOMPUTER: " << endl << endl;
			cout << gracz_pierwszy->karta.symbol << " " << gracz_pierwszy->karta.rodzaj;
			cout << "      " << gracz_drugi->karta.symbol << " " << gracz_drugi->karta.rodzaj << endl;
		}
	}

	if (gracz_pierwszy->karta.moc != gracz_drugi->karta.moc)
	{
		if (gracz_pierwszy->karta.moc > gracz_drugi->karta.moc)
		{
			Koniec_Bitwy(gracz_pierwszy, gracz_drugi, rozgrywka);
		}
		else
		{
			Koniec_Bitwy(gracz_drugi, gracz_pierwszy, rozgrywka);
		}

	}
	else if (gracz_pierwszy->karta.moc == gracz_drugi->karta.moc)
	{
		Wojna(gracz_pierwszy, gracz_drugi, rozgrywka);
	}

}


//funkcja podmieniająca lub niepodmieniająca karty w zależności od decyzji gracza/komputera
void Podmien_Karty_Madra(reka_t* gracz, reka_t* ten_drugi, const char STRATEGIA)
{
	karta_t pierwsza_karta, druga_karta;
	pierwsza_karta = gracz->karta;
	druga_karta = gracz->nastepny->karta;
	if (STRATEGIA == 'L')
	{
		int flaga = rand() % 2;
		if (flaga)
		{
			gracz->karta = druga_karta;
			gracz->nastepny->karta = pierwsza_karta;
		}
		cout << endl << "GRACZ 1:   KOMPUTER: " << endl << endl;
		cout << ten_drugi->karta.symbol << " " << ten_drugi->karta.rodzaj;
		cout << "      " << gracz->karta.symbol << " " << gracz->karta.rodzaj << endl;
	}
	else if (STRATEGIA == 'W')
	{
		if (gracz->karta.moc == ten_drugi->karta.moc);
		else if (gracz->nastepny->karta.moc == ten_drugi->karta.moc)
		{
			gracz->karta = druga_karta;
			gracz->nastepny->karta = pierwsza_karta;
		}
		else if (gracz->karta.moc > ten_drugi->karta.moc&& gracz->nastepny->karta.moc > ten_drugi->karta.moc)
		{
			if (gracz->nastepny->karta.moc < gracz->karta.moc)
			{
				gracz->karta = druga_karta;
				gracz->nastepny->karta = pierwsza_karta;
			}
		}
		else if (gracz->nastepny->karta.moc > ten_drugi->karta.moc)
		{
			gracz->karta = druga_karta;
			gracz->nastepny->karta = pierwsza_karta;
		}
		else if (gracz->karta.moc < ten_drugi->karta.moc && gracz->nastepny->karta.moc < ten_drugi->karta.moc)
		{
			if (gracz->nastepny->karta.moc < gracz->karta.moc)
			{
				gracz->karta = druga_karta;
				gracz->nastepny->karta = pierwsza_karta;
			}
		}

	}
	else if (STRATEGIA == 'P')
	{
		if (gracz->karta.moc == ten_drugi->karta.moc && gracz->nastepny->karta.moc == ten_drugi->karta.moc);
		else if (gracz->karta.moc == ten_drugi->karta.moc && gracz->nastepny->karta.moc != ten_drugi->karta.moc)
		{
			gracz->karta = druga_karta;
			gracz->nastepny->karta = pierwsza_karta;
		}
		else if (gracz->karta.moc > ten_drugi->karta.moc&& gracz->nastepny->karta.moc > ten_drugi->karta.moc)
		{
			if (gracz->nastepny->karta.moc < gracz->karta.moc)
			{
				gracz->karta = druga_karta;
				gracz->nastepny->karta = pierwsza_karta;
			}
		}
		else if (gracz->karta.moc < ten_drugi->karta.moc && gracz->nastepny->karta.moc < ten_drugi->karta.moc)
		{
			if (gracz->nastepny->karta.moc < gracz->karta.moc)
			{
				gracz->karta = druga_karta;
				gracz->nastepny->karta = pierwsza_karta;
			}
		}
		else if (gracz->karta.moc > ten_drugi->karta.moc&& gracz->nastepny->karta.moc < ten_drugi->karta.moc)
		{
			gracz->karta = druga_karta;
			gracz->nastepny->karta = pierwsza_karta;
		}
	}
	else if (STRATEGIA == '0')
	{
		char skad = 'b';
		Wypisz_Karty_Madra(gracz, ten_drugi, skad);
		cout << endl << "Wcisnij:" << endl;
		cout << "- '1', aby wyrzucic pierwsza karte" << endl;
		cout << "- '2', aby wyrzucic druga karte" << endl;
		char numer;
		cin >> numer;
		if (numer == '2')
		{
			gracz->karta = druga_karta;
			gracz->nastepny->karta = pierwsza_karta;
		}
		Wypisz_Karty_Madra(gracz, ten_drugi, skad);
	}
}


void Wypisz_Karty_Madra(reka_t* reka_pierwsza, reka_t* reka_druga, const char SKAD)
{
	cout << endl << "GRACZ 1:   KOMPUTER: " << endl << endl;
	if (SKAD == 'b')
	{
		cout << reka_pierwsza->karta.symbol << " " << reka_pierwsza->karta.rodzaj;
		cout << "      " << reka_druga->karta.symbol << " " << reka_druga->karta.rodzaj << endl;
		if (reka_pierwsza->nastepny != NULL)
		{
			cout << reka_pierwsza->nastepny->karta.symbol << " " << reka_pierwsza->nastepny->karta.rodzaj << endl;
		}
	}
	else
	{
		while (reka_pierwsza != NULL && reka_druga != NULL)
		{
			cout << reka_pierwsza->karta.symbol << " " << reka_pierwsza->karta.rodzaj;
			cout << "      " << reka_druga->karta.symbol << " " << reka_druga->karta.rodzaj << endl;
			reka_pierwsza = reka_pierwsza->nastepny;
			reka_druga = reka_druga->nastepny;
		}
	}
}


void Koniec_Bitwy(reka_t* gracz_wygrany, reka_t* gracz_przegrany, gra_t* rozgrywka)
{
	int flaga = rand() % 2;
	if (!flaga && rozgrywka->czy_madra == 'M')
	{
		Dodaj_Na_Koncu(gracz_wygrany, gracz_przegrany->karta);
		Dodaj_Na_Koncu(gracz_wygrany, gracz_wygrany->karta);
	}
	else
	{
		Dodaj_Na_Koncu(gracz_wygrany, gracz_wygrany->karta);
		Dodaj_Na_Koncu(gracz_wygrany, gracz_przegrany->karta);
	}
	*gracz_wygrany = Po_Usunieciu_Z_Poczatku(gracz_wygrany, rozgrywka);
	rozgrywka->liczba_ruchow -= 1;
	Sprawdz_Czy_Mozesz_Usunac(gracz_przegrany, gracz_wygrany, gracz_wygrany->indeks, rozgrywka);
	rozgrywka->liczba_ruchow += 1;
}


void Wojna(reka_t* karty_pierwszego, reka_t* karty_drugiego, gra_t* rozgrywka)
{
	int licznik = 0, wojny_z_przekazaniem_karty = 0;
	reka_t pierwszy_wygrywa, drugi_wygrywa;
	while (karty_pierwszego->karta.moc == karty_drugiego->karta.moc && rozgrywka->stan != ZAKONCZONA)
	{
		if (licznik == 0)
		{
			Inicjuj(&pierwszy_wygrywa, karty_pierwszego->karta);
			Inicjuj(&drugi_wygrywa, karty_drugiego->karta);
		}
		else
		{
			Dodaj_Na_Koncu(&pierwszy_wygrywa, karty_pierwszego->karta);
			Dodaj_Na_Koncu(&drugi_wygrywa, karty_drugiego->karta);
		}
		licznik++;
		Pomocnik_Wojny(karty_pierwszego, karty_drugiego, &pierwszy_wygrywa, &drugi_wygrywa, rozgrywka->wariant, &wojny_z_przekazaniem_karty, rozgrywka);
	}
	if (rozgrywka->stan == ZAKONCZONA)
	{
		return;
	}
	Dodaj_Na_Koncu(&pierwszy_wygrywa, karty_pierwszego->karta);
	Dodaj_Na_Koncu(&drugi_wygrywa, karty_drugiego->karta);

	if (rozgrywka->czy_madra == 'M')
	{
		char skad = 'w';
		Wypisz_Karty_Madra(&pierwszy_wygrywa, &drugi_wygrywa, skad);
		Przenies_Wszystko_Madra(karty_pierwszego, karty_drugiego, &pierwszy_wygrywa, &drugi_wygrywa, licznik, rozgrywka);
	}
	else
	{
		Przenies_Wszystko(karty_pierwszego, karty_drugiego, &pierwszy_wygrywa, &drugi_wygrywa, licznik, rozgrywka);
	}
}


//funkcja wywołująca odpowiednią funkcję w zależności od wariantu gry
void Pomocnik_Wojny(reka_t* karty_pierwszego, reka_t* karty_drugiego, reka_t* pierwszy_wygrywa, reka_t* drugi_wygrywa, const char WARIANT, int* wojny_z_przekazaniem_karty, gra_t* rozgrywka)
{
	if (WARIANT == 'B')
	{
		Wariant_B(karty_pierwszego, karty_drugiego, pierwszy_wygrywa, drugi_wygrywa, wojny_z_przekazaniem_karty, rozgrywka);
	}
	else
	{
		Wariant_A(karty_pierwszego, karty_drugiego, pierwszy_wygrywa, drugi_wygrywa, rozgrywka);
	}
}


void Wariant_A(reka_t* karty_pierwszego, reka_t* karty_drugiego, reka_t* pierwszy_wygrywa, reka_t* drugi_wygrywa, gra_t* rozgrywka)
{
	if (karty_pierwszego->liczba_kart == 2 && karty_drugiego->liczba_kart == 2)
	{
		rozgrywka->liczba_ruchow += 2;
		Koniec_Gry(REMIS, rozgrywka);
		return;
	}
	else if (karty_pierwszego->liczba_kart == 3 && karty_drugiego->liczba_kart == 3)
	{
		Zostaly_Po_Trzy_Karty(karty_pierwszego, karty_drugiego, rozgrywka);
		return;
	}
	else
	{
		Standardowa_Wojna(karty_pierwszego, karty_drugiego, pierwszy_wygrywa, drugi_wygrywa, rozgrywka);
		return;
	}
}


void Wariant_B(reka_t* karty_pierwszego, reka_t* karty_drugiego, reka_t* pierwszy_wygrywa, reka_t* drugi_wygrywa, int* wojny_z_przekazaniem_karty, gra_t* rozgrywka)
{
	if (karty_pierwszego->nastepny == NULL || karty_pierwszego->nastepny->nastepny == NULL || karty_drugiego->nastepny == NULL || karty_drugiego->nastepny->nastepny == NULL)
	{
		(*wojny_z_przekazaniem_karty)++;
		if (karty_pierwszego->liczba_kart == 2 && karty_drugiego->liczba_kart == 2)
		{
			rozgrywka->liczba_ruchow += 2;
			Koniec_Gry(REMIS, rozgrywka);
			return;
		}
		else if (karty_pierwszego->liczba_kart == 3 && karty_drugiego->liczba_kart == 3)
		{
			Zostaly_Po_Trzy_Karty(karty_pierwszego, karty_drugiego, rozgrywka);
		}
		else if (karty_pierwszego->nastepny == NULL)
		{
			if (karty_drugiego->nastepny->nastepny->nastepny != NULL)
				Przekaz_Dwie_Karty(karty_drugiego, karty_pierwszego, drugi_wygrywa, pierwszy_wygrywa, wojny_z_przekazaniem_karty, rozgrywka);
			else
			{
				Koniec_Gry(karty_drugiego->indeks, rozgrywka);
				return;
			}
		}
		else if (karty_pierwszego->nastepny->nastepny == NULL)
		{
			if (karty_drugiego->nastepny->nastepny != NULL)
				Przekaz_Jedna_Karte(karty_drugiego, karty_pierwszego, drugi_wygrywa, pierwszy_wygrywa, wojny_z_przekazaniem_karty, rozgrywka);
			else
			{
				rozgrywka->liczba_ruchow += 2;
				Koniec_Gry(karty_drugiego->indeks, rozgrywka);
				return;
			}
		}
		else if (karty_drugiego->nastepny == NULL)
		{
			if (karty_pierwszego->nastepny->nastepny->nastepny != NULL)
				Przekaz_Dwie_Karty(karty_pierwszego, karty_drugiego, pierwszy_wygrywa, drugi_wygrywa, wojny_z_przekazaniem_karty, rozgrywka);
			else
			{
				Koniec_Gry(karty_pierwszego->indeks, rozgrywka);
				return;
			}
		}
		else if (karty_drugiego->nastepny->nastepny == NULL)
		{
			if (karty_pierwszego->nastepny->nastepny != NULL)
				Przekaz_Jedna_Karte(karty_pierwszego, karty_drugiego, pierwszy_wygrywa, drugi_wygrywa, wojny_z_przekazaniem_karty, rozgrywka);
			else
			{
				rozgrywka->liczba_ruchow += 2;
				Koniec_Gry(karty_pierwszego->indeks, rozgrywka);
				return;
			}
		}
	}
	else
	{
		Standardowa_Wojna(karty_pierwszego, karty_drugiego, pierwszy_wygrywa, drugi_wygrywa, rozgrywka);
		return;
	}
}


//funkcja przeprowadzająca pojedynczą wojnę, bez przekazania kart
void Standardowa_Wojna(reka_t* karty_pierwszego, reka_t* karty_drugiego, reka_t* pierwszy_wygrywa, reka_t* drugi_wygrywa, gra_t* rozgrywka)
{
	if (rozgrywka->stan != ZAKONCZONA)
	{
		Sprawdz_Czy_Mozesz_Usunac(karty_pierwszego, karty_drugiego, karty_drugiego->indeks, rozgrywka);
	}
	if (rozgrywka->stan != ZAKONCZONA)
	{
		rozgrywka->liczba_ruchow -= 1;
		Sprawdz_Czy_Mozesz_Usunac(karty_drugiego, karty_pierwszego, karty_pierwszego->indeks, rozgrywka);
		rozgrywka->liczba_ruchow += 1;
	}
	Dodaj_Na_Koncu(pierwszy_wygrywa, karty_pierwszego->karta);
	Dodaj_Na_Koncu(drugi_wygrywa, karty_drugiego->karta);
	if (rozgrywka->stan != ZAKONCZONA)
	{
		Sprawdz_Czy_Mozesz_Usunac(karty_pierwszego, karty_drugiego, karty_drugiego->indeks, rozgrywka);
	}
	if (rozgrywka->stan != ZAKONCZONA)
	{
		rozgrywka->liczba_ruchow -= 1;
		Sprawdz_Czy_Mozesz_Usunac(karty_drugiego, karty_pierwszego, karty_pierwszego->indeks, rozgrywka);
		rozgrywka->liczba_ruchow += 1;
	}
}


//funkcja wywoływana tuż przed zakończeniem gry, w przypadku pojedynczej wojny, 
//gdy obojgu z graczy kończą się karty i trzeba zdeterminować zwycięzcę
void Zostaly_Po_Trzy_Karty(reka_t* gracz_pierwszy, reka_t* gracz_drugi, gra_t* rozgrywka)
{
	rozgrywka->liczba_ruchow += 4;
	//cout << gracz_pierwszy->nastepny->karta.moc << " " << gracz_drugi->nastepny->karta.moc << endl;
	if (gracz_pierwszy->nastepny->karta.moc == gracz_drugi->nastepny->karta.moc)
	{
		Koniec_Gry(REMIS, rozgrywka);
		return;
	}
	else if (gracz_pierwszy->nastepny->karta.moc > gracz_drugi->nastepny->karta.moc)
	{
		Koniec_Gry(gracz_pierwszy->indeks, rozgrywka);
		return;
	}
	else
	{
		Koniec_Gry(gracz_drugi->indeks, rozgrywka);
		return;
	}
}


//funkcja na potrzebę wariantu B, przekazująca jedną kartę w wojnie graczowi, któremu jej zabrakło 
void Przekaz_Jedna_Karte(reka_t* gracz_wygrywajacy, reka_t* gracz_przegrywajacy, reka_t* wygrywajacy_wygrywa, reka_t* przegrywajacy_wygrywa, int* licznik, gra_t* rozgrywka)
{
	if (*licznik < 2)
	{
		rozgrywka->liczba_ruchow -= 1;
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Sprawdz_Czy_Mozesz_Usunac(gracz_przegrywajacy, gracz_wygrywajacy, gracz_wygrywajacy->indeks, rozgrywka);
		Dodaj_Na_Koncu(wygrywajacy_wygrywa, gracz_wygrywajacy->karta);
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Dodaj_Na_Koncu(gracz_przegrywajacy, gracz_wygrywajacy->karta);
		Dodaj_Na_Koncu(przegrywajacy_wygrywa, gracz_przegrywajacy->karta);
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Sprawdz_Czy_Mozesz_Usunac(gracz_przegrywajacy, gracz_wygrywajacy, gracz_wygrywajacy->indeks, rozgrywka);
	}
	else
	{
		rozgrywka->liczba_ruchow += 2;
		Koniec_Gry(gracz_wygrywajacy->indeks, rozgrywka);
		return;
	}
}


//funkcja na potrzebę wariantu B, przekazująca dwie karty w wojnie graczowi, któremu ich zabrakło
void Przekaz_Dwie_Karty(reka_t* gracz_wygrywajacy, reka_t* gracz_przegrywajacy, reka_t* wygrywajacy_wygrywa, reka_t* przegrywajacy_wygrywa, int* licznik, gra_t* rozgrywka)
{
	if (*licznik < 2)
	{
		rozgrywka->liczba_ruchow -= 2;
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Dodaj_Na_Koncu(gracz_przegrywajacy, gracz_wygrywajacy->karta);
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Sprawdz_Czy_Mozesz_Usunac(gracz_przegrywajacy, gracz_wygrywajacy, gracz_wygrywajacy->indeks, rozgrywka);
		Dodaj_Na_Koncu(gracz_przegrywajacy, gracz_wygrywajacy->karta);
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Dodaj_Na_Koncu(przegrywajacy_wygrywa, gracz_przegrywajacy->karta);
		Dodaj_Na_Koncu(wygrywajacy_wygrywa, gracz_wygrywajacy->karta);
		Sprawdz_Czy_Mozesz_Usunac(gracz_wygrywajacy, gracz_przegrywajacy, gracz_przegrywajacy->indeks, rozgrywka);
		Sprawdz_Czy_Mozesz_Usunac(gracz_przegrywajacy, gracz_wygrywajacy, gracz_wygrywajacy->indeks, rozgrywka);
	}
	else
	{
		Koniec_Gry(gracz_wygrywajacy->indeks, rozgrywka);
		return;
	}
}


//funkcja przekazująca wszystkie karty z wojny do stosu kart zwycięzcy
void Przenies_Wszystko(reka_t* karty_pierwszego, reka_t* karty_drugiego, reka_t* pierwszy_wygrywa, reka_t* drugi_wygrywa, int licznik, gra_t* rozgrywka)
{
	for (int i = 0; i < 2 * (licznik * 2 + 1); i++)
	{
		if (i < licznik * 2 + 1)
		{
			if (karty_pierwszego->karta.moc > karty_drugiego->karta.moc)
			{
				Dodaj_Na_Koncu(karty_pierwszego, pierwszy_wygrywa->karta);
				if (i != licznik * 2)
				{
					*pierwszy_wygrywa = Po_Usunieciu_Z_Poczatku(pierwszy_wygrywa, rozgrywka);
					rozgrywka->liczba_ruchow--;
				}
			}
			else
			{
				Dodaj_Na_Koncu(karty_drugiego, drugi_wygrywa->karta);
				if (i != licznik * 2)
				{
					*drugi_wygrywa = Po_Usunieciu_Z_Poczatku(drugi_wygrywa, rozgrywka);
					rozgrywka->liczba_ruchow--;
				}
			}
		}
		else
		{
			if (karty_pierwszego->karta.moc > karty_drugiego->karta.moc)
			{
				Dodaj_Na_Koncu(karty_pierwszego, drugi_wygrywa->karta);
				if (i != licznik * 4 + 1)
				{
					*drugi_wygrywa = Po_Usunieciu_Z_Poczatku(drugi_wygrywa, rozgrywka);
					rozgrywka->liczba_ruchow--;
				}
			}
			else
			{
				Dodaj_Na_Koncu(karty_drugiego, pierwszy_wygrywa->karta);
				if (i != licznik * 4 + 1)
				{
					*pierwszy_wygrywa = Po_Usunieciu_Z_Poczatku(pierwszy_wygrywa, rozgrywka);
					rozgrywka->liczba_ruchow--;
				}
			}
		}
	}
	if (rozgrywka->stan != ZAKONCZONA)
	{
		Sprawdz_Czy_Mozesz_Usunac(karty_pierwszego, karty_drugiego, karty_drugiego->indeks, rozgrywka);
		if (rozgrywka->stan != ZAKONCZONA)
		{
			rozgrywka->liczba_ruchow -= 1;
			Sprawdz_Czy_Mozesz_Usunac(karty_drugiego, karty_pierwszego, karty_pierwszego->indeks, rozgrywka);
			rozgrywka->liczba_ruchow += 1;
		}
	}
}


void Przenies_Wszystko_Madra(reka_t* karty_pierwszego, reka_t* karty_drugiego, reka_t* pierwszy_wygrywa, reka_t* drugi_wygrywa, int licznik, gra_t* rozgrywka)
{
	int liczba_kart = 4 * licznik + 2;
	karta_t* karty = (karta_t*)malloc(liczba_kart * sizeof(karta_t));
	for (int i = 0; i < liczba_kart; i += 2)
	{
		karty[i] = pierwszy_wygrywa->karta;
		karty[i + 1] = drugi_wygrywa->karta;
		if (i < liczba_kart - 2)
		{
			*pierwszy_wygrywa = Po_Usunieciu_Z_Poczatku(pierwszy_wygrywa, rozgrywka);
			*drugi_wygrywa = Po_Usunieciu_Z_Poczatku(drugi_wygrywa, rozgrywka);
			rozgrywka->liczba_ruchow -= 2;
		}
	}
	bool* czy_powtarza = (bool*)malloc(liczba_kart * sizeof(bool));
	for (int i = 0; i < liczba_kart; i++)
	{
		czy_powtarza[i] = false;
	}
	for (int i = 0; i < liczba_kart; i++)
	{
		int indeks = rand() % liczba_kart;
		if (!czy_powtarza[indeks])
		{
			czy_powtarza[indeks] = true;
			if (karty_pierwszego->karta.moc > karty_drugiego->karta.moc)
			{
				Dodaj_Na_Koncu(karty_pierwszego, karty[indeks]);
			}
			else
			{
				Dodaj_Na_Koncu(karty_drugiego, karty[indeks]);
			}
		}
		else
			i--;
	}
	if (rozgrywka->stan != ZAKONCZONA)
	{
		Sprawdz_Czy_Mozesz_Usunac(karty_pierwszego, karty_drugiego, karty_drugiego->indeks, rozgrywka);
		if (rozgrywka->stan != ZAKONCZONA)
		{
			rozgrywka->liczba_ruchow -= 1;
			Sprawdz_Czy_Mozesz_Usunac(karty_drugiego, karty_pierwszego, karty_pierwszego->indeks, rozgrywka);
			rozgrywka->liczba_ruchow += 1;
		}
	}
}


//funkcja sprawdzająca czy przypadkiem nie usunęlibyśmy ostatnich kart ze stosu gracza.
//Jeśli tak to kończymy grę, jeśli nie to usuwamy karty ze stosu gracza
void Sprawdz_Czy_Mozesz_Usunac(reka_t* gracz_przegrywajacy, reka_t* gracz_wygrywajacy, const int INDEKS, gra_t* rozgrywka)
{
	if (gracz_przegrywajacy->nastepny == NULL)
	{
		gracz_przegrywajacy->liczba_kart--;
		Koniec_Gry(INDEKS, rozgrywka);
		return;
	}
	else
	{
		*gracz_przegrywajacy = Po_Usunieciu_Z_Poczatku(gracz_przegrywajacy, rozgrywka);
	}
}


void Koniec_Gry(const int INDEKS, gra_t* rozgrywka)
{
	static int nr = 0;
	rozgrywka->stan = ZAKONCZONA;
	rozgrywka->liczba_ruchow += 2;
	rozgrywka->liczba_ruchow /= 2;
	//cout << "-----------------------------------------" << endl;
	cout << endl;
	if (INDEKS == GRACZ_1)
	{
		cout << "      **** GRACZ PIERWSZY WYGRYWA!!! ****      " << endl;
	}
	else if (INDEKS == GRACZ_2)
	{
		cout << "      **** GRACZ DRUGI WYGRYWA!!! ****      " << endl;
	}
	else
	{
		cout << "      **** REMIS!!! ****      " << endl;
	}
	char znak;
	cout << endl << "Wpisz dowolny znak i zatwierdz ENTEREM, aby zakonczyc..." << endl;
	cin >> znak;
	//cout << endl << "      Liczba ruchow: " << rozgrywka->liczba_ruchow;
	//cout << endl << "-----------------------------------------" << endl << endl << endl;*/
	/*double wynik_dla_pierwszego, wynik_dla_drugiego;
	if (INDEKS == GRACZ_1)
	{
		wynik_dla_pierwszego = 1;
		wynik_dla_drugiego = 0;
	}
	else if (INDEKS == GRACZ_2)
	{
		wynik_dla_pierwszego = 0;
		wynik_dla_drugiego = 1;
	}
	else
	{
		wynik_dla_pierwszego = 0.5;
		wynik_dla_drugiego = 0.5;
	}
	FILE* plik;
	fopen_s(&plik, "strategie.txt", "a");
	if (plik == NULL)
	{
		cout << "blad" << endl;
	}
	else
	{
		fprintf_s(plik, "%c;%f;%c;%f;%d\n", rozgrywka->strategia_pierwszego, wynik_dla_pierwszego,
			rozgrywka->strategia_drugiego, wynik_dla_drugiego, nr);
		fclose(plik);
	}
	nr++;
	//exit(0);*/
}
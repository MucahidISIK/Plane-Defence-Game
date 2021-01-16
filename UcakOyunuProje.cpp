 
// Mücahid IÞIK -2018


#include <iostream>
#include <Windows.h>
#include <time.h> 

using namespace std;

// yönleri belirtmemizi sagliyor
enum YON
{
	YON_SOL = 1,
	YON_SAG = 2,
	YON_YUKARI = 3,
	YON_ASAGI = 4,
	YON_YOK = 5,
};
// geminin özelliklerini buradan struct ile yaziyoruz
struct gemiHucre
{
	int x;
	int y;
	YON yon;
	char karakter;
};
// merminin özelliklerini buradan struct ile yaziyoruz
struct mermiHucre
{
	int x;
	int y;
	YON yon;
	char karakter;
};
// dusmanin özelliklerini buradan struct ile yazýyoruz
struct dusmanHucre
{
	int x;
	int y;
	YON yon;
	char karakter;
};

const int genislik = 80;
const int yukseklik = 20;
char sahne[genislik][yukseklik];

const char gemiKarakteri = 206;
const char mermiKarakteri = 62;
const char dusmanKarakteri = 176;

const int gemiParcaSayisi = 5;
const int cephaneSayisi = 100;
const int dusmanSayisi = 100;

gemiHucre gemi[500];
mermiHucre mermi[500];
dusmanHucre dusman[500];
char tuslar[256];

void klavyeOku(char tuslar[]);   // klavyeden girilen harfler okunuyor
void kursoruGizle();   // kursor gizlenip guzel bir gorunum elde ediliyor
void gotoxy(int, int);  // sahnenin surekli olarak ayni yere cizilmesini sagliyor
void sahneyiTemizle();  // her seferinde sahnenin tamamen silinmesini sagliyor
void sinirlariOlustur();  // ucak oyununun etrafindaki sinirlari olusturuyor
void sahneyiCiz();   // sahneyi ciziyor

void gemiOlustur();  // gemiyi olusturuyor
void gemiyiSahneyeYerlestir();  // geminin sahnede gosterilmesini sagliyor
void gemiKontrol();  // geminin klavye ile kontrolu saglaniyor
void gemiyiHareketEttir(); // geminin klavye ile kontrolu saglaniyor


void mermiOlustur();  // mermi olusturuliyor
void mermiyiHareketEttir();  // mermi hareket ettiriliyor
void mermiyiSahneyeYerlestir();  // merminin sahnede gosterilmesini sagliyor


void dusmanOlustur();  // dusmanlar olusturuluyor
void dusmaniHareketEttir();  // dusman sola dogru hareket ettiriliyor
void dusmaniSahneyeYerlestir();  // dusmanim sahnede gosterilmesini sagliyor

void dusmanVurma();  // mermi dusmanla ayni koordinata geldiginde dusman ve merminin karakterlerine bosluk ataniyor


int main()
{
	kursoruGizle();

	gemiOlustur();
	dusmanOlustur();
	while (true)
	{
		sahneyiTemizle();
		sinirlariOlustur();
		gemiKontrol();

		gemiyiHareketEttir();
		gemiyiSahneyeYerlestir();

		mermiOlustur();
		mermiyiHareketEttir();
		mermiyiSahneyeYerlestir();


		dusmaniHareketEttir();
		dusmaniSahneyeYerlestir();

		dusmanVurma();


		gotoxy(0, 0);
		sahneyiCiz();
		Sleep(25);
	}

}

void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
	{
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
	}
}
void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO  cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void sahneyiTemizle()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			sahne[x][y] = ' ';
		}
	}
}
void sinirlariOlustur()
{
	for (int x = 0; x < genislik; x++)
	{
		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}
	for (int y = 0; y < yukseklik; y++)
	{
		sahne[0][y] = 219;
		sahne[genislik - 1][y] = 219;
	}
}
void sahneyiCiz()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << sahne[x][y];
		}
		cout << endl;
	}
}


void gemiOlustur()
{
	gemi[0].x = 1;
	gemi[0].y = 8;

	gemi[1].x = 1;
	gemi[1].y = 12;

	gemi[2].x = 2;
	gemi[2].y = 9;

	gemi[3].x = 2;
	gemi[3].y = 11;

	gemi[4].x = 3;
	gemi[4].y = 10;

}
void gemiyiSahneyeYerlestir()
{
	for (int i = 0; i < gemiParcaSayisi; i++)
	{
		int x = gemi[i].x;
		int y = gemi[i].y;
		sahne[x][y] = gemiKarakteri;
	}
}
void gemiKontrol()
{
	klavyeOku(tuslar);
	for (int i = 0; i < gemiParcaSayisi; i++)
	{
		if (gemi[0].y > 1)
		{
			if (tuslar['W'] != 0)
			{
				gemi[i].yon = YON_YUKARI;
			}
		}
		if (gemi[1].y < 18)
		{
			if (tuslar['S'] != 0)
			{
				gemi[i].yon = YON_ASAGI;
			}
		}
		if (tuslar['S'] == 0 && tuslar['W'] == 0)
		{
			gemi[i].yon = YON_YOK;
		}
	}

}
void gemiyiHareketEttir()
{
	for (int i = 0; i < gemiParcaSayisi; i++)
	{
		switch (gemi[i].yon)
		{
		case YON_ASAGI:
			gemi[i].y++;
			break;
		case YON_YUKARI:
			gemi[i].y--;
			break;
		}

	}
}


void mermiOlustur()
{
	klavyeOku(tuslar);
	for (int i = 0; i < cephaneSayisi; i++)
	{
		if (tuslar['F'] != 0)

		{
			mermi[i].x = gemi[4].x + 1;
			mermi[i].y = gemi[4].y;
			mermi[i].yon = YON_SAG;
			mermi[i].karakter = mermiKarakteri;
		}
	}
}
void mermiyiHareketEttir()
{
	for (int i = 0; i < cephaneSayisi; i++)
	{
		switch (mermi[i].yon)
		{
		case YON_SAG:
			if (mermi[i].x < genislik)
			{
				mermi[i].x++;
			}
			else
			{
				mermi[i].karakter = 219;
			}
			break;
		}

	}
}
void mermiyiSahneyeYerlestir()
{
	for (int i = 0; i < cephaneSayisi; i++)
	{
		int x = mermi[i].x;
		int y = mermi[i].y;
		sahne[x][y] = mermi[i].karakter;
	}
}


void dusmanOlustur()
{
	srand(time(NULL));
	int y;
	for (int i = 0; i < 100; i++)
	{
		y = rand() % 18 + 1;
	}
	for (int i = 0; i < dusmanSayisi; i++)
	{
		dusman[i].x = genislik - 1;
		dusman[i].y = y;
		dusman[i].yon = YON_SOL;
		dusman[i].karakter = dusmanKarakteri;
	}

}
void dusmaniHareketEttir()
{
	for (int i = 0; i < dusmanSayisi; i++)
	{
		switch (dusman[i].yon)
		{
		case YON_SOL:
			if (dusman[i].x > 0)
			{
				dusman[i].x--;
			}
			else
			{
				dusman[i].karakter = 219;
			}
			break;
		}
	}
}
void dusmaniSahneyeYerlestir()
{
	for (int i = 0; i < dusmanSayisi; i++)
	{
		int x = dusman[i].x;
		int y = dusman[i].y;
		sahne[x][y] = dusman[i].karakter;
	}
}

void dusmanVurma()
{
	for (int i = 0; i < 100; i++)
		if (dusman[i].x == mermi[i].x && dusman[i].y == mermi[i].y)
		{
			dusman[i].karakter = ' ';
			mermi[i].karakter = ' ';
		}
}
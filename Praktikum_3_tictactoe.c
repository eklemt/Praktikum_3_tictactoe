/***

Name:			TicTacToe
Beschreibung:	Programm, in welchem der User Lottozahlen tippen kann. Gespielt wird 6 aus 49. Nach Tippen der 6 Zahlen, werden die "Richtigen"
				gezogen, und die Gewinnquote bestimmt.
Autorinnen:	    Emily Klemt, Carolin Altstaedt
Datum:		    19.11.2023
Version:		1

***/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define LEER ' '

short einlesenEinerZahl(char text[], short min, short max);		// Funktion, um eine Zahl einzulesen
bool feldIstBelegt(char spielfeld[3][3], short zeile, short spalte); //Funktion, die überprüft, ob ein Feld belegt ist 
void einfacherComputergegner(char spielfeld[3][3]);					// computer soll random ein feld auswählen und belegen
void gibDasAktuelleSpielfeldAus(char spielfeld[3][3], int anzahlRunden, int spielstandComputer, int spielstandMensch); 		// Funktion, die das aktuelle Spielfeld ausgibt 
bool gewinnErmitteln(char spielfeld[3][3]);				// Funktion, die überprüft, ob es einen Gewinner gibt 

int main() {
	
	bool weiterspielen = true;  // Konstante Weiterspielen 
	int spielstandSpieler = 0; 
	int spielstandComputer = 0; 
	int anzahlRunden = 0; 

	while (weiterspielen)
	{
		char spielfeldArray[3][3]; // Beinhaltet alle 9 Felder des Spielfeldes 
		bool spielerIstDran = false; // Hier hätte ich eigentlich lieber einen boolean, mit spielerbeginnt true oder false 

		// Reset des Spielfelds, eventuell noch in FUnktion ausgliedern 
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				spielfeldArray[i][j] = LEER; // 255 = ein Leerzeichen in Ascii 
			}
		}

		// random funktion initialisieren
		srand((unsigned int)time(NULL));

		// Einführung in das Spiel und Benutzeranleitung 
		printf("Du spielst TicTacToe, das bloedeste Spiel der Welt!\n");

		// Abfrage nach dem Schwierigkeitsgrad (passende Variablen jeweils davor initialisieren):
		
		// Abfragen, wer beginnen soll: 
		printf("Moechtest du beginnen, dann druecke x. Wenn nicht druecke einfach enter.\n"); 
		if (getchar() == 'x') spielerIstDran = true; 

		// Ausgabe des Spielfelds 
		gibDasAktuelleSpielfeldAus(spielfeldArray, anzahlRunden, spielstandComputer, spielstandSpieler);

		bool niemandHatGewonnen = true;

		//schleife zum spieldurchlauf, 9 durchläufe für 9 felder
		for (int i = 0; i < 9 && niemandHatGewonnen; i++) {
			system("cls"); 

			// neues Spielfeld ausgeben
			gibDasAktuelleSpielfeldAus(spielfeldArray, anzahlRunden, spielstandComputer, spielstandSpieler);

			if (spielerIstDran) {
				// Beginn des Spiels 
				printf("Du bist an der Reihe. Setze dein erstes Kreuz. Der Computer spielt mit O.\n");

				int erstesKreuzZeile = 0;	// 
				int erstesKreuzSpalte = 0;

				// In eine While Schleife, die überprüft, ob das Feld schon getippt wurde
				bool belegt = true;
				while (belegt) {
					belegt = false;
					erstesKreuzZeile = (einlesenEinerZahl("Gib nun deine Zahl für die Zeile ein", 1, 3) - 1);
					erstesKreuzSpalte = (einlesenEinerZahl("Gib nun deine Zahl für die Spalte ein", 1, 3) - 1);
					belegt = feldIstBelegt(spielfeldArray, erstesKreuzZeile, erstesKreuzSpalte);
					if (belegt) {
						printf("Dieses Feld ist bereits belegt.\n");
					}
				}
				spielfeldArray[erstesKreuzZeile][erstesKreuzSpalte] = 'X'; // 88 in Ascii = X 

				/*// nur zum Überprüfen da
				printf("\n");
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						printf("%c, ", spielfeldArray[i][j]);
					}
				}
				*/
			}
			else {
				// spieler ist 0, funktion für computer zug aufrufen
				printf("Der Computer spielt jetzt\n");

				// hier verschiedene Möglichkeiten, für verschiedene Schwierigkeitsgrade
				einfacherComputergegner(spielfeldArray);
			}

			// Überprüfen, ob es einen Gewinner gibt oder Gleichstand ist 
			niemandHatGewonnen = gewinnErmitteln(spielfeldArray);
			printf("%d", niemandHatGewonnen);
			if (niemandHatGewonnen == false) {
				anzahlRunden++;
				// für die Optik 
				if (spielerIstDran) spielstandSpieler++;
				else spielstandComputer++;
				system("cls"); 
				gibDasAktuelleSpielfeldAus(spielfeldArray, anzahlRunden, spielstandComputer, spielstandSpieler);
				if (spielerIstDran) printf("Der Spieler hat gewonnen.\n");
				else printf("Der Computer hat gewonnen\n");
			}

			if (i == 8 && niemandHatGewonnen) {
				anzahlRunden++; 
				printf("Gleichstand, niemand hat gewonnen!\n");
				spielstandComputer++;
				spielstandSpieler++; 
			}

			// Wechseln des aktuellen Spielers 
			if (spielerIstDran == true) {
				spielerIstDran = false;
			}
			else {
				spielerIstDran = true;
			}
		}
		// Anweisung zum Weiterspielen bzw. Beenden des Spiels
		printf("Wenn du nicht mehr weitermachen willst, druecke 'x' und Enter. Sonst nur Enter.\n");

		//Beenden des Spiels 
		if (getchar() == 'x') {
			weiterspielen = false;
			printf("Auf Wiedersehen!");
			return 0; 
		}
		else {
			system("cls");
		}
	}
}

short einlesenEinerZahl(
	char text[],
	short min,
	short max)
{
	short eingelesenerWert;		//eingegebene Zahl des Benutzers
	bool fertig = false;	// Variable, die anzeigt, ob die Eingabe den Anforderungen einer Lottozahl entspricht
	char ch;			//möglicher Buchstabe nach der eingegebenen Zahl
	int Rückgabewert;			//Rückgabewert von scanf

	do {
		//Einlesen der Zahl 
		printf("%s: ", text);
		ch = '\0';
		Rückgabewert = scanf("%hd%c", &eingelesenerWert, &ch);

		// Überprüfen, ob die Zahl den Anforderungen entspricht
		if (Rückgabewert != 2) printf("Das war keine korrekte Zahl!\n");
		else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
		else if (eingelesenerWert < min || eingelesenerWert > max) printf("Zahl muss zwischen 1 und 3 liegen.\n");
		else fertig = true;
		// Input stream leeren 

		while (ch != '\n') {
			char checkChar = scanf("%c", &ch);
		}
		// wiederholen, wenn es nicht beendet ist 
	} while (!fertig);

	// Rückgabe der eingelesenen Zahl 
	return eingelesenerWert;
}

bool feldIstBelegt(char spielfeld[3][3], short zeile, short spalte) { //Funktion zum Überprüfen ob eine Zahl Bestandteil eines Arrays ist 
	bool belegt = false;
	if (spielfeld[zeile][spalte] != LEER) {
		belegt = true;
	}
	return belegt;
}

void einfacherComputergegner(char spielfeld[3][3]) {
	int zeile, spalte;
	bool freiesFeld = true;

	while (freiesFeld) {
		zeile = rand() % 3;
		spalte = rand() % 3;
		printf("\n%d", zeile);
		printf("\n%d", spalte);

		freiesFeld = feldIstBelegt(spielfeld, zeile, spalte);
	}
	spielfeld[zeile][spalte] = 'O';
}

/*void schwererComputer(char spielfeld[3][3], bool aktuellerSpieler) {
	bool dieMitteIstNichtFrei = feldIstBelegt(spielfeld, 2, 2);
	if (dieMitteIstNichtFrei == false) {
		  spielfeld[2][2] = 'O';
  }
	int zeile, spalte;
	bool freiesFeld = true;

	while (freiesFeld) {
		zeile = rand() % 3;
		spalte = rand() % 3;
		printf("\n%d", zeile);
		printf("\n%d", spalte);

		freiesFeld = feldIstBelegt(spielfeld, zeile, spalte);
	}
	spielfeld[zeile][spalte] = 'O';
}
*/

void gibDasAktuelleSpielfeldAus(char spielfeld[3][3], int anzahlRunden, int spielstandComputer, int spielstandMensch) {
	printf("Der aktuelle Spielstand nach der %d Runde ist: Computer: %d Mensch: %d\n", anzahlRunden, spielstandComputer, spielstandMensch);
	printf("\t  1   2   3\n");
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187); // macht folgende Ausgabe mit ASCII-Zeichen: ╔═══╦═══╦═══╗
	printf("1\t%c %c %c %c %c %c %c\n", 186, spielfeld[0][0], 186, spielfeld[0][1], 186, spielfeld[0][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
	printf("2\t%c %c %c %c %c %c %c\n", 186, spielfeld[1][0], 186, spielfeld[1][1], 186, spielfeld[1][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
	printf("3\t%c %c %c %c %c %c %c\n", 186, spielfeld[2][0], 186, spielfeld[2][1], 186, spielfeld[2][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188); // macht folgende Ausgabe mit ASCII-Zeichen: ╚═══╩═══╩═══╝
}

bool gewinnErmitteln(char spielfeld[3][3]) {
	bool nichtgewonnen = true;
	for (int i = 0; i < 3; ++i) {
		// Überprüfen, ob die Werte der Zeilen gleich sind 
		if ((spielfeld[i][0] == spielfeld[i][1] && spielfeld[i][1] == spielfeld[i][2]) && (spielfeld[i][0] != LEER)) {
			nichtgewonnen = false;
		}
	}
	for (int i = 0; i < 3; ++i) {
		// Überprüfen, ob die Werte der Zeilen gleich sind 
		if ((spielfeld[0][i] == spielfeld[1][i] && spielfeld[1][i] == spielfeld[2][i]) && (spielfeld[0][i] != LEER)) {
			nichtgewonnen = false;
		}
	}
	//Über Spalten und Zeilen wurde noch kein gewinner ermittelt, wir prüfen noch die diagonalen
	if (((spielfeld[0][0] == spielfeld[1][1] && spielfeld[1][1] == spielfeld[2][2]) && (spielfeld[0][0] != LEER)) ||
		((spielfeld[0][2] == spielfeld[1][1] && spielfeld[1][1] == spielfeld[2][0] && (spielfeld[1][1] != LEER)))) {
		nichtgewonnen = false;
	}
	// noch hat niemand gewonnen
	return nichtgewonnen; 
}

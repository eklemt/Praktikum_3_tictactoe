/***

Name:			TicTacToe
Beschreibung:	Programm, in welchem der Nutzer TicTacToe gegen den Computer spielen kann und entweder gegen diesen verlieren, gewinnen oder unentschieden spielen kann.
				Dabei kann der Nutzer immer weiterspielen und der Spielstand wird über mehrere Runden bestimmt. 
				Zudem kann der Nutzer entscheiden, wie schwer der Computer spielt und ob er selbst oder der Computer beginnt 
Autorinnen:	    Emily Klemt, Carolin Altstaedt
Datum:		    19.11.2023
Version:		1

***/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define LEER ' ' // KOnstante für ein leeres Feld 

short einlesenEinerZahl(char text[], short min, short max);		// Funktion, um eine Zahl einzulesen
bool feldIstBelegt(char spielfeld[3][3], short zeile, short spalte); //Funktion, die überprüft, ob ein Feld belegt ist 
void einfacherComputergegner(char spielfeld[3][3]);					// Funktion für den einfachen Computer, die nur zufällig ein Feld ausgibt
void schwererComputer(char spielfeld[3][3], bool wenigerAlsZweiRunden);			// Funktion für den schweren COmputer, die jedes Mal den bestmöglichen Zug ermittelt 
void gibDasAktuelleSpielfeldAus(char spielfeld[3][3], int anzahlRunden, int spielstandComputer, int spielstandMensch); 		// Funktion, die das aktuelle Spielfeld ausgibt 
bool hatNiemandGewonnen(char spielfeld[3][3]);				// Funktion, die überprüft, ob es einen Gewinner gibt 
bool gibtEsZweiGleiche(char spielfeld[3][3], int aktuelleSpalte, int aktuelleZeile); // Funktion, um zu überprüfen, ob es 2 gleiche in einer gewinnbringenden Form durch den aktuellen Zug gibt 

int main() {
	
	bool weiterspielen = true;  // Variable, die angibt, ob der User noch weiterspielen möchte
	int spielstandSpieler = 0;  // Anzahl der gewonnen/unentschiedenen Runden des Spielers
	int spielstandComputer = 0; // Anzahl der gewonnen/unentschiedenen Runden des Computers
	int anzahlRunden = 0; // Anzahl der gespielten Runden 

	while (weiterspielen)
	{
		char spielfeldArray[3][3]; // Beinhaltet alle 9 Felder des Spielfeldes

		// Reset des Spielfelds
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				spielfeldArray[i][j] = LEER; // 255 = ein Leerzeichen in Ascii 
			}
		}

		// random funktion initialisieren
		srand((unsigned int)time(NULL));

		// Einführung in das Spiel und Benutzeranleitung 
		printf("Du spielst TicTacToe, das bloedeste Spiel der Welt!\n");

		// Abfrage nach dem Schwierigkeitsgrad 
		bool gegenEinfachenComputerSpielen = true; //Variable die angibt, ob der Mensch gegen einen einfachen oder schweren Computer spielen möchte
		printf("Moechtest du gegen einen einfachen oder schweren Computer spielen? Wenn du gegen einen schweren Computer spielen moechtest druecke 's' und enter. Wenn du gegen einen einfachen spielen moechtest druecke nur enter."); 
		if (getchar() == 's') gegenEinfachenComputerSpielen = false; 
		while (getchar() != '\n') {}

		// Abfragen, wer beginnen soll: 
		bool spielerIstDran = false; // Variable, die wenn der Spieler selber dran ist, true ist 
		printf("Moechtest du beginnen, dann druecke x. Wenn nicht druecke einfach enter.\n"); 
		if (getchar() == 'x') spielerIstDran = true; 
		while (getchar() != '\n') {}

		// Ausgabe des Spielfelds 
		gibDasAktuelleSpielfeldAus(spielfeldArray, anzahlRunden, spielstandComputer, spielstandSpieler);

		bool niemandHatGewonnen = true; // Variable, die true ist, solange niemand gewonnen hat 

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

				// Einlesen des Feldes und überprüfen, ob dieses schon belegt wurde 
				bool belegt = true;
				while (belegt) {
					belegt = false;
					erstesKreuzZeile = (einlesenEinerZahl("Gib nun deine Zahl fuer die Zeile ein", 1, 3) - 1);
					erstesKreuzSpalte = (einlesenEinerZahl("Gib nun deine Zahl fuer die Spalte ein", 1, 3) - 1);
					belegt = feldIstBelegt(spielfeldArray, erstesKreuzZeile, erstesKreuzSpalte);
					if (belegt) {
						printf("Dieses Feld ist bereits belegt.\n");
					}
				}
				spielfeldArray[erstesKreuzZeile][erstesKreuzSpalte] = 'X'; // 88 in Ascii = X 

			}
			else {
				bool wenigerAlsZweiRunden = true; // Array für den schweren Computer, der angibt, ob mehr als zwei Runden gespielt wurden 
				if (i > 2) wenigerAlsZweiRunden = false; 
				// spieler ist 0, funktion für computer zug aufrufen
				printf("Der Computer spielt jetzt:\n");

				if (gegenEinfachenComputerSpielen) einfacherComputergegner(spielfeldArray);
				else schwererComputer(spielfeldArray, wenigerAlsZweiRunden); 
			}

			// Überprüfen, ob es einen Gewinner gibt und Ausgabe des Gewinners
			niemandHatGewonnen = hatNiemandGewonnen(spielfeldArray);
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
			// nach 8 Runden das unentschieden ausgeben, wenn noch niemand gewonnen hat 
			if (i == 8 && niemandHatGewonnen) {
				anzahlRunden++; 
				spielstandComputer++;
				spielstandSpieler++;
				system("cls");
				gibDasAktuelleSpielfeldAus(spielfeldArray, anzahlRunden, spielstandComputer, spielstandSpieler);
				printf("Gleichstand, niemand hat gewonnen!\n");
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

short einlesenEinerZahl( // Funktion, um eine Zahl einzulesen 
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

bool feldIstBelegt(char spielfeld[3][3], short zeile, short spalte) { //Funktion zum Überprüfen ob ein Feld belegt ist 
	bool belegt = false;
	if (spielfeld[zeile][spalte] != LEER) {
		belegt = true;
	}
	return belegt;
}

void einfacherComputergegner(char spielfeld[3][3]) { // einfacher Computergegner, der ein zufälliges freies Feld besetzt 
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


void schwererComputer(char spielfeld[3][3], bool wenigerAlsZweiRunden) { // schwerer Computergegner, der immer den bestmöglichen Zug ermittelt 
	bool dieMitteIstNichtFrei = feldIstBelegt(spielfeld, 2, 2);
	if (wenigerAlsZweiRunden && dieMitteIstNichtFrei == false) {
			spielfeld[2][2] = 'O';
		}
	else {
		char spielfeldkopie[3][3]; // Eine Kopie des Spielfelds erstellen 
		for (int i = 0; i < 3; i++) { // Werte in die Kopie des Spielfelds einelesen
			for (int j = 0; j < 3; j++) {
				spielfeldkopie[i][j] = spielfeld[i][j];
			}
		}
		int werteDesSpielzugs[3][3]; // Array der den Wert, beinhaltet, was es dem COmputer bringen würde, dieses zu benutzen 
		// Simulation verschiedener Spielzüge über alle Felder 
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				werteDesSpielzugs[i][j] = 0;
				// Wenn das Feld nicht belegt ist, verschiedene Szenarien für die Belegung prüfen 
				if (!feldIstBelegt(spielfeldkopie, i, j)) {
					// Überprüfen, ob der Computer mit diesem Zug gewonnen hätte 
					spielfeldkopie[i][j] = 'O';
					if (hatNiemandGewonnen(spielfeldkopie) == false) {
						werteDesSpielzugs[i][j] = 3;
					}
					// wenn es keine Möglichkeit zum Gewinnen gibt, überprüfen, ob man ein Gewinnen des Gegners verhindern muss 
					if (werteDesSpielzugs[i][j] == 0) {
						spielfeldkopie[i][j] = 'X';
						if (hatNiemandGewonnen(spielfeldkopie) == false) {
							werteDesSpielzugs[i][j] = 2;
						}
					}
					// Wenn es auch kein Gewinnen des Gegners zu vermeiden gilt, einen Zug zum eigenen Vorteil finden 
					if (werteDesSpielzugs[i][j] == 0) {
						spielfeldkopie[i][j] = 'O';
						if (gibtEsZweiGleiche(spielfeldkopie, i, j)) {
							if (werteDesSpielzugs[i][j] != 3 && werteDesSpielzugs[i][j] != 2)
								werteDesSpielzugs[i][j] = 1;
						}
					
					}
				// Feld wieder leeren 
				spielfeldkopie[i][j] = LEER;
				}
			}
			
		}
		int aktuellerSpielzugwert = 0; // Wert den der aktuell geprüfte Spielzu zugewiesen bekommen hat
		int besterSpielzugwert = 0; // Höchster Wert den ein Spielzug bisher hatte
		int besteZeile = 0; // Welche Zeile der beste bisherige Spielzug hatte
		int besteSpalte = 0; // Welche Spalte der beste bisherige Spielzug hatte 
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (werteDesSpielzugs[i][j] >= besterSpielzugwert) {
					besterSpielzugwert = werteDesSpielzugs[i][j];
					besteZeile = i;
					besteSpalte = j;
				}
			}
		}
		// optimales Feld belegen 
		spielfeld[besteZeile][besteSpalte] = 'O';
	}
}


void gibDasAktuelleSpielfeldAus(char spielfeld[3][3], int anzahlRunden, int spielstandComputer, int spielstandMensch) { // Funktion, die das aktuelle Spielfeld ausgibt 
	printf("Der aktuelle Spielstand nach der %d Runde ist: Computer: %d Mensch: %d\n", anzahlRunden, spielstandComputer, spielstandMensch); // Teil der Funktion, der den aktuellen Spielstand ausgobt 
	printf("\t  1   2   3\n");
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187); // macht folgende Ausgabe mit ASCII-Zeichen: ╔═══╦═══╦═══╗
	printf("1\t%c %c %c %c %c %c %c\n", 186, spielfeld[0][0], 186, spielfeld[0][1], 186, spielfeld[0][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
	printf("2\t%c %c %c %c %c %c %c\n", 186, spielfeld[1][0], 186, spielfeld[1][1], 186, spielfeld[1][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
	printf("3\t%c %c %c %c %c %c %c\n", 186, spielfeld[2][0], 186, spielfeld[2][1], 186, spielfeld[2][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188); // macht folgende Ausgabe mit ASCII-Zeichen: ╚═══╩═══╩═══╝
}

bool hatNiemandGewonnen(char spielfeld[3][3]) { // Funktion, die ermittelt, ob es einen Gewinner gibt 
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
	return nichtgewonnen; 
}

bool gibtEsZweiGleiche(char spielfeld[3][3], int aktuelleSpalte, int aktuelleZeile) {// Funktion, um zu überprüfen, ob es 2 gleiche in einer gewinnbringenden Form durch den aktuellen Zug gibt 
	bool zweigleichegefunden = false; 
	for (int i = 0; i < 3; i++) {
		// Überprüfen, ob zwei Werte in einer Zeile gleich sind 
		if ((spielfeld[i][0] == spielfeld[i][1] && spielfeld[i][2] == LEER) ||
			(spielfeld[i][0] == LEER && spielfeld[i][1] == spielfeld[i][2]) ||
			(spielfeld[i][0] == spielfeld[i][2] && spielfeld[i][1] == LEER)) {
			zweigleichegefunden = true;
		}
	}
	for (int i = 0; i < 3; i++) {
		// Überprüfen, ob zwei Werte in einer Spalte gleich sind 
		if ((spielfeld[0][i] == spielfeld[1][i] && spielfeld[2][i] == LEER) ||
			(spielfeld[0][i] == LEER && spielfeld[1][i] == spielfeld[2][i]) ||
			(spielfeld[0][i] == spielfeld[2][i] && spielfeld[1][i] == LEER)) {
			zweigleichegefunden = true;
		}
	}
	// Überprüfen, ob zwei Werte in den Diagonalen gleich sind 
	if ((spielfeld[0][0] == spielfeld[1][1] && spielfeld[2][2] == LEER) ||
		(spielfeld[0][0] == spielfeld[2][2] && spielfeld[1][1] == LEER) ||
		(spielfeld[1][1] == spielfeld[2][2] && spielfeld[0][0] == LEER) ||
		(spielfeld[0][2] == spielfeld[1][1] && spielfeld[2][0] == LEER) ||
		(spielfeld[0][2] == spielfeld[2][0] && spielfeld[1][1] == LEER) ||
		(spielfeld[1][1] == spielfeld[2][0] && spielfeld[0][2] == LEER)) {
		zweigleichegefunden = true; 
	}
	return zweigleichegefunden; 
}

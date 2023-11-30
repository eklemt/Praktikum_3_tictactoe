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

short einlesenEinerZahl(char text[], short min, short max);		// Funktion, um eine Zahl einzulesen
bool feldIstBelegt(int array[3][3], short zeile, short spalte); //Funktion, die überprüft, ob ein Feld belegt ist 
void einfacherComputergegner(int array[3][3]);					// computer soll random ein feld auswählen und belegen
void gibDasAktuelleSpielfeldAus(int array[3][3]); 		// Funktion, die das aktuelle Spielfeld ausgibt 

int main() {
	int spielfeldArray[3][3]; // Beinhaltet alle 9 Felder des Spielfeldes 
	char spieler = 'X'; // Hier hätte ich eigentlich lieber einen boolean, mit spielerbeginnt true oder false 

	// Reset des Spielfelds, eventuell noch in FUnktion ausgliedern 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			spielfeldArray[i][j] = 0; // 255 = ein Leerzeichen in Ascii 
		}
	}

	// random funktion initialisieren
	srand((unsigned int)time(NULL));

	// Einführung in das Spiel und Benutzeranleitung 
	printf("Du spielst TicTacToe, das blödste Spiel der Welt!\n");

	// Abfrage nach dem Schwierigkeitsgrad (passende Variablen jeweils davor initialisieren)
	// Abfragen, wer beginnen soll: 

	printf("HO");
	// Ausgabe des Spielfelds 
	gibDasAktuelleSpielfeldAus(spielfeldArray);
	
	//schleife zum spieldurchlauf, 9 durchläufe für 9 felder
	for (int i = 0; i < 9; i++) {
		// System clear screen einfügen
		
		// neues Spielfeld ausgeben

		printf("\t  1   2   3\n");
		printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187); // macht folgende Ausgabe mit ASCII-Zeichen: ╔═══╦═══╦═══╗
		printf("1\t%c %c %c %c %c %c %c\n", 186, spielfeldArray[0][0], 186, spielfeldArray[0][1], 186, spielfeldArray[0][2], 186);
		printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
		printf("2\t%c %c %c %c %c %c %c\n", 186, spielfeldArray[1][0], 186, spielfeldArray[1][1], 186, spielfeldArray[1][2], 186);
		printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
		printf("3\t%c %c %c %c %c %c %c\n", 186, spielfeldArray[2][0], 186, spielfeldArray[2][1], 186, spielfeldArray[2][2], 186);
		printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188); // macht folgende Ausgabe mit ASCII-Zeichen: ╚═══╩═══╩═══╝


		if (spieler == 'X') {
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
			spielfeldArray[erstesKreuzZeile][erstesKreuzSpalte] = 88;

			// nur zum Überprüfen da 
			printf("\n"); 
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%c, ", spielfeldArray[i][j]);
				}
			}
		}
		/*else {
			// spieler ist 0, funktion für computer zug aufrufen
			printf("der computer spielt jetzt");

			// hier verschiedene Möglichkeiten, für verschiedene Schwierigkeitsgrade
			einfacherComputergegner(spielfeldArray);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%c, ", spielfeldArray[i][j]);
				}
			}
		}

		//Überprüfen, ob jemand gewonnen hat 
		if (i >= 5) {
			// hierfür eine Funktion verfassen 
		}

		//Sobald kein weiterer Zug mehr möglich, eventuell mit elif?
		if (i = 8) {
			printf("Gleichstand, niemand hat gewonnen\n");
		}


		// würde ich am liebsten an das Ende der verschiedenen if-else packen?? 
		if (spieler == 'X') {
			spieler = 'O';
		}
		else {
			spieler = 'X';
		}
		*/
	}

	return 0;
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

bool feldIstBelegt(int array[3][3], short zeile, short spalte) { //Funktion zum Überprüfen ob eine Zahl Bestandteil eines Arrays ist 
	bool belegt = false;
	if (array[zeile][spalte] != 0) {
		belegt = true;
	}
	return belegt;
}

void einfacherComputergegner(int spielfeld[3][3]) {
	int zeile, spalte;
	bool freiesFeld = true;

	while (freiesFeld) {
		zeile = rand() % 3;
		spalte = rand() % 3;
		printf("\n%d", zeile);
		printf("\n%d", spalte);

		freiesFeld = feldIstBelegt(spielfeld, zeile, spalte);
	}
	spielfeld[zeile][spalte] = 79;
}

void gibDasAktuelleSpielfeldAus(int array[3][3]) {
	printf("\t  1   2   3\n");
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187); // macht folgende Ausgabe mit ASCII-Zeichen: ╔═══╦═══╦═══╗
	printf("1\t%c %c %c %c %c %c %c\n", 186, array[0][0], 186, array[0][1], 186, array[0][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
	printf("2\t%c %c %c %c %c %c %c\n", 186, array[1][0], 186, array[1][1], 186, array[1][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185); // macht folgende Ausgabe mit ASCII-Zeichen: ╠═══╬═══╬═══╣
	printf("3\t%c %c %c %c %c %c %c\n", 186, array[2][0], 186, array[2][1], 186, array[2][2], 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188); // macht folgende Ausgabe mit ASCII-Zeichen: ╚═══╩═══╩═══╝
}

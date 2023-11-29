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

short einlesenEinerZahl(char text[], short min, short max); //Funktion der Funktion erklären 
bool feldIstBelegt(int array[3][3], short zeile, short spalte);
void computerSpielt(int array[3][3]); // computer soll random ein feld auswählen und belegen

int main() {
	int spielfeldArray[3][3]; // Beinhaltet alle 9 Felder des Spielfeldes 
	char spieler = 'X'; // initial spieler auf x setzen, denn user setzt zuerst

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			spielfeldArray[i][j] = 0;
		}
	}

	// random funktion initialisieren
	srand((unsigned int)time(NULL));

	// Was soll der Benutzer tun
	printf("Du spielst TicTacToe, das blödste Spiel der Welt!\n");


	// Ausgabe des Spielfelds 
	int fürTabelle = 3;
	printf("\t  1   2   3\n");
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187);
	printf("1\t%c%4c%4c%4c\n", 186, 186, 186, 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
	printf("2\t%c%4c%4c%4c\n", 186, 186, 186, 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
	printf("3\t%c%4c%4c%4c\n", 186, 186, 186, 186);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188);

	//schleife zum spieldurchlauf, 9 durchläufe für 9 felder
	for (int i = 0; i < 9; i++) {
		if (spieler == 'X') {
			// Beginn des Spiels 
			printf("Du bist an der Reihe. Setze dein erstes Kreuz. Der Computer spielt mit O.\n");

			// Beginn des Spiels 
			int erstesKreuzZeile = (einlesenEinerZahl("Gib nun deine Zahl für die Zeile ein", 1, 3) - 1);
			printf("\n");
			int erstesKreuzSpalte = (einlesenEinerZahl("Gib nun deine Zahl für die Spalte ein", 1, 3) - 1);

			spielfeldArray[erstesKreuzZeile][erstesKreuzSpalte] = 88;

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%c, ", spielfeldArray[i][j]);
				}
			}
		}
		else {
			// spieler ist 0, funktion für computer zug aufrufen
			printf("der computer spielt jetzt");
			computerSpielt(spielfeldArray);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					printf("%c, ", spielfeldArray[i][j]);
				}
			}
		}
		
		if (i >= 5) {
			//funktion auf gewinner prüfen
		}

		//if i = 8, schleife ganz durchgelaufen, dann gleichstand
		// 
		// Spieler am Ende des durchlaufs wechseln wechseln
		if (spieler == 'X') {
			spieler = 'O';
		} else {
			spieler = 'X';
		}
		
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

void computerSpielt(int spielfeld[3][3]) {
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

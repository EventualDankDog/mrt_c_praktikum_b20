/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Konfigurationsdatei-Modul
 */

#include "config.h"
#include "daten.h"

// für fopen, getline, fscanf, fclose:
#include <stdio.h>

// für strncmp und memset:
#include <string.h>

// für malloc, calloc und atoi:
#include <stdlib.h>

	 
// Config und Dateiarbeit Funktionen

int delay_auslesen(char string[]){
    int t=0,i=0;
    int truedelay = 0;
    
    while (t<1) {  // Den String durchgehen bis die Zahlen beginnen und den Index der ersten Zahl speichern
    int ASCII = (unsigned char) string[i];
    if (ASCII>47 && ASCII<58){
    break;
    }
    i++;
    }
    if((unsigned char) string[strlen(string)-2]==109){  // Check ob Pause in ms gegeben (wenn vorlestztes Zeichen = m ist)
    
        const char *Zahlen = &string[i];      // Neuen String beginnend bei der ersten Zahl (Anfang abschneiden)
        float keinekommazahl = atof(Zahlen);  // Zahl Auslesen
        truedelay = (int) keinekommazahl;   // Konvertierung zu long
        return truedelay;
        
    }else{
        
        const char *Zahlen = &string[i];
        float kommazahl = atof(Zahlen)*1000;   // Umrechnung von Sekunden in Millisekunden und Kommazahl Auslesen
        truedelay = (int) kommazahl;         // Konvertierung zu long
        return truedelay;
        
    }
}




void Datei_einlesen(list_header *kopf,char* Dateipfad){

    int* x = (int*) malloc(sizeof (int));  // Speicher für alle Werte allozieren
    int* y = (int*) malloc(sizeof (int));
    int* zaehler = (int*) malloc(sizeof (int));
    int* anzahl = (int*) malloc(sizeof (int));
    int* delay = (int*) malloc(sizeof (int));
    

    FILE *datei;  // Datei öffnen und lesen
    datei = fopen(Dateipfad,"r");

    char *puffer;
    char * Textzeile = NULL;  // Hilfsvariablen
    char *string;
    string = malloc(1);

    int puffer_erreicht = 0;
    int pufferzeilen = 0;
    size_t laenge = 0;
    ssize_t Textzeilenlaenge;


    unsigned long Dateiname = strlen(Dateipfad);
    const char *letzten_Zeichen = &Dateipfad[Dateiname-4];     //Bestimmung letzte 4 Zeichen des Dateinamens

    if(strcmp(letzten_Zeichen,".txt") != 0){
        fprintf(stderr,"\nDatei ist keine .txt Datei\n"); // Fehlerüberprüfung ob es eine .txt ist
        return;
    }


    if(datei == NULL){
        fprintf( stderr, "\nDatei (%s) ist nonexistent\n",Dateipfad); // Fehler ob die Datei leer ist
        return;
    }


    while((Textzeilenlaenge=getline(&Textzeile, &laenge, datei)) != -1){ // Schleife über alle Textzeilen

    int variable = 0; // Zahlenwert der Textzeile
	string = realloc(string,Textzeilenlaenge+1); // String der Textzeilen und jedweils neue Speicherallokation

	sscanf(Textzeile, "%s %i", &string[0],&variable); // Belegung von variable und string mit den Werten aus der Datei-Textzeile

	if (strcmp(Textzeile,"\n")==0 && puffer_erreicht == 0) continue; // Leere Zeile vor dem Animations-Puffer überspringen

	if (strncmp(string,"Spalten:",8)==0){ // Überprüfung nach den jeweiligen Werten und einschreiben in die Datenstruktur
	     *x = variable;
	     set_X(kopf,x);
	     //printf("\nSpalten: %i", get_Y(kopf));

	    }
	if(strncmp(string,"Zeilen:",7)==0) {
	      *y = variable;
	      set_Y(kopf, y);
	      //printf("\nZeilen: %i", get_Y(kopf));
	 }

    if(strncmp(string,"Schritt:",8)==0) {
          *zaehler = variable,
          set_animationszaehler(kopf, zaehler);
          //printf("\nZähler: %i", *get_animationszaehler(kopf));
    }
    if(strncmp(string,"Schritte:",9)==0) {
          *anzahl = variable;
          set_animationsanzahl(kopf, anzahl);
          //printf("\nAnzahl: %i", get_animationsanzahl(kopf));
    }
    if(strncmp(string,"Pause:",6)==0) {
          int t = delay_auslesen(Textzeile);
          *delay = t;
          set_delay(kopf, delay);
          //printf("\nDelay: %i", get_delay(kopf));
    }



    if (strcmp(Textzeile,"\n")==0 && puffer_erreicht==1){ // Bescheiben des Zahlenfeldes mit den Eingelesen


    	int *zahlenfeld = neues_zahlenfeld(kopf); // Neues Feld erstellen was später beschrieben wird
    	int Zeilen = get_Y(kopf)+2;
    	int Spalten = get_X(kopf)+2;   // Hilfsvariablen zur Besetzung des Feldes
    	int Feldgroesse = Zeilen*Spalten;
    	int puffergroesse = strlen(puffer);
    	int pufferspalten = (puffergroesse)/(pufferzeilen);
    	//printf("Pgröße: %i \n Pspalten: %i", puffergroesse, pufferspalten); // Ausgabe zur Überprüfung
    	int horizontaler_Rahmen = (Spalten-pufferspalten)/2;
    	int vertikaler_Rahmen = (Zeilen-pufferzeilen)/2;
    	int zahlenfeld_startindex = vertikaler_Rahmen*Spalten + horizontaler_Rahmen;

    	//printf("\nIndex: %i", zahlenfeld_startindex); // Ausgabe zur Überprüfung
    	int hR_gerade = Spalten-pufferspalten%2;
    	int vR_gerade = Zeilen-pufferzeilen%2;


    	 if (((Feldgroesse-puffergroesse)%2)==1 || (hR_gerade==1) || (vR_gerade==1)){
    		 fprintf(stderr, "\n\n Platzierung des Puffers aufgrund der Größe nicht mittig möglich.\n");
    	      }




    	memset(zahlenfeld, 0, Feldgroesse);  // Feld auf 0 initialisieren

    	for (int k=0; k < pufferzeilen ;k++){
    		if(k != 0)zahlenfeld_startindex = zahlenfeld_startindex + Spalten;
    		//printf("\nIndex: %i", zahlenfeld_startindex);
    		for (int m = 0; m < pufferspalten; m++){
    			int Animationszahl = 0;
    			if (puffer[m+k*pufferspalten] == 'x') Animationszahl = 1;
    			zahlenfeld[zahlenfeld_startindex + 1 + m] = Animationszahl;
    		}
    	}
    	set_zahlenfeld(kopf, zahlenfeld);

    	return;

    	/*for (int u=0;u<Zeilen;u++) {  // Testausgabefunktion des Feldes
    	            	printf("\n");
    	            	for (int w=0;w<Spalten;w++){
    	            		printf("%i ",zahlenfeld[u*Spalten+w]);
    	            	}
            }*/

    	return;

    	}


    if(strncmp(string, "Animations-Puffer:",17)==0) { // Check ob man beim Puffer ist
              puffer_erreicht = 1;
              puffer=malloc((get_X(kopf)+2)*(get_Y(kopf)+2));
              //printf("\nPufferrechreicht: %i", puffer_erreicht);
              continue;
        }
    if (puffer_erreicht==1) {                      //Puffer einlesen
                strcat(puffer,string);              //Pufferzeilen verbinden
                pufferzeilen = pufferzeilen+1;
                //printf("\nAnimationspuffer:%s",puffer);
                    }

    }
    perror ("\n config");
}

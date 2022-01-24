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


long delay_auslesen(char string[]){
    int t=0,i=0;
    long truedelay = 0;
    
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
        truedelay = (long) keinekommazahl;   // Konvertierung zu long
        return truedelay;
        
    }else{
        
        const char *Zahlen = &string[i];
        float kommazahl = atof(Zahlen)*1000;   // Umrechnung von Sekunden in Millisekunden und Kommazahl Auslesen
        truedelay = (long) kommazahl;         // Konvertierung zu long
        return delay;
        
    }
}




void Datei_einlesen(list_header *kopf,char* Dateipfad){

    int* x = (int*) malloc(sizeof (int));
    int* y = (int*) malloc(sizeof (int));
    int* zaehler = (int*) malloc(sizeof (int));
    int* anzahl = (int*) malloc(sizeof (int));
    long* delay = (long*) malloc(sizeof (long));
    
    int variable;

    FILE *datei;
    datei = fopen(Dateipfad,"r");

    char * Textzeile = NULL;
    char *string;
    string = malloc(1);
    char *puffer;
    int puffer_erreicht = 0;
    int pufferzeilen = 0;
    size_t laenge = 0;
    ssize_t Textzeilenlaenge;
    int horizontaler_Rahmen;
    int vertikaler_Rahmen;

    unsigned long Dateiname = strlen(Dateipfad);
    const char *letzten_Zeichen = &Dateipfad[length-4];           //Bestimmung letzte 4 Zeichen des Dateinamens

    if(strcmp(letzten_Zeichen,".txt") != 0){
        fprintf(stderr,"\nDatei ist keine .txt Datei\n");
        return;
    }


    if(datei == NULL){
        fprintf( stderr, "\nDatei (%s) ist nonexistent\n",Dateipfad);
        return;
    }


    while((Textzeilenlaenge=getline(&Textzeile, &laenge, datei)) != -1){

	string = realloc(string,Textzeilenlaenge+1);

	sscanf(Textzeile, "%s %i", &string[0],&variable);        

        variable = 0;

	if (strcmp(Textzeile,"\n")==0 && puffer_erreicht==1){
	
	int *zahlenfeld = neues_zahlenfeld(kopf);
	int Zeilen = get_Y(kopf)+2;
	int Spalten = get_X(kopf)+2;
	int Feldgroesse = (Zeilen)*(Spalten);
	int puffergroesse = (int) strlen(puffer);
	int pufferspalten = (puffergroesse)/(pufferzeilen);
	int verschiebung = 0;
	
	if((Spalten-pufferspalten)%2 || (Zeilen-pufferzeilen)%2){
		horizontaler_Rahmen = (Spalten-pufferspalten)/2;
		vertikaler_Rahmen = (Zeilen-pufferzeilen)/2;
	}else{
		horizontaler_Rahmen = (Spalten-pufferspalten-1)/2;
		vertikaler_Rahmen = (Zeilen-pufferzeilen-1)/2;
		fprintf(stderr, "\n\n Platzierung des Puffers aufgrund der Größe nicht mittig möglich.\n");
		if((Spalten-pufferspalten)%2 == 1 ) verschiebung = 1;
	}
	int zahlenfeld_startindex = (vertikaler_Rahmen-1)*Spalten + horizontaler_Rahmen-1;
	
	memset(zahlenfeld, 0, Feldgroesse);

	int k, m;

	for (k=0; k < pufferzeilen ;k++){
		zahlenfeld_startindex = zahlenfeld_startindex + (Spalten-pufferspalten) + verschiebung;
		for (m = 0; m < pufferspalten; m++){
			int Animationszahl = 0;
			if (puffer[m+k*pufferspalten] == "x") Animationszahl = 1;
			zahlenfeld[zahlenfeld_startindex + 1 + m] = Animationszahl;
		}
	}
	set_zahlenfeld(kopf, zahlenfeld);	
        }
    
        if (strcmp(Textzeile,"\n")==0) continue;
    
        if (strncmp(string,"Spalten:",8)==0){
            *x = variable;
            set_X(kopf,x);
        }
        if(strncmp(string,"Zeilen:",7)==0) {
            *y = variable;
            set_Y(kopf, y);
        }
        else if(strncmp(string,"Schritt:",8)==0) {
            *zaehler = variable,
            set_animationszaehler(kopf, zaehler);
        }
        else if(strncmp(string,"Schritte:",9)==0) {
            *anzahl = variable;
            set_animationsanzahl(kopf, anzahl);
        }
        else if(strncmp(string,"Pause:",6)==0) {
            long t = delay_auslesen(Textzeile);
            *delay = t;
            set_delay(kopf, delay);
        }
        else if(strncmp(string, "Animations-Puffer:",17)==0) {
            puffer_erreicht = 1;
            puffer=malloc((get_X(kopf)+2)*(get_Y(kopf)+2));
            continue;
        }
	if (puffer_erreicht==1) {                //Puffer einlesen
            strcat(puffer,string);              //Pufferzeilen verbinden
            pufferzeilen = pufferzeilen+1;
            //printf("\nAnimationspuffer:%s",puffer);
    	}

	perror ("\n config");
    }
}

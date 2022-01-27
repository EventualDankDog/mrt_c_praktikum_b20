/* BOF MAIN_C
 Praktikumsversuch: Einführung in die Sprache C
 Haupt-Programm
 */

#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "daten.h"
#include "config.h"
#include "gfx.h"
#include "engine.h"
#include "ui.h"

// Forwarddeklaration der später definierten Hilfsfunktionen:
void goodbye_msg(void);
static void init_exit(void);


int main(void)
{
    list_header *kopf = neueDatensammlung();
    Datei_einlesen(kopf, "./glider.txt");

    int i = 0;
	if(get_animationsanzahl(kopf)== *get_animationszaehler(kopf)){
		i = 1;
		fprintf(stderr ,"\n Maximale Schritte Zahl gleich der Startschrittzahl, Animation nicht möglich!");
	}
	else {
		init_exit();
	    init_frame(kopf);
	}


    while(0 == i){


        print_animation(kopf);
        i = ui(kopf);
        
    }

    void goodbye_msg();
    return 0;
}


// -- Hilfsfunktionen ---
static void init_exit(void)
{
        if(atexit(goodbye_msg)){
                fprintf(stderr, "Fehler bei Registrierung der Exitfunktion\n");
                exit(-1);
        }
}

void goodbye_msg(void)
{
        printf("MRT1, V3, Programm beendet.\n");
}

/* EOF MAIN_C */

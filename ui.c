/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Nutzerinteraktions-Modul
 */

#include "ui.h"

// für vorgegebene UI Funktionen: grafik_user_input()
#include "graphic.h"

// für die Funktion `exit`
#include <stdlib.h>
#include "gfx.h"
#include "engine.c"

// Funktionen um Nutzerinteraktionen zu behandeln

void ui(list_header* kopf){

	while(grafik_user_input(10) > Fehler);

	switch(grafik_user_input(delay_auslesen))
	{
	case Beenden:
		exit(0); //q = 0, beenden
	case Pause:
	{
			while(1) //1 = Leertaste --> Pause
			{
				while(grafik_user_input(10) > Fehler);

				switch(grafik_user_input(delay_auslesen))
					{
					case Beenden:
						exit(0); //q = 0, beenden
					case Pause:
						return; //mit Leertaste weitermachen
					case Schritt:
						if(get_animationsanzahl(kopf)== *get_animationszaehler(kopf)){ //überprüft ob noch eine Entwicklung gemacht werden muss
							continue;
						}
						animationStep(list_header* datenliste);
						print_animations_buffer(list_header* datenliste);
						continue; //in der Pause wird animationsschritt gezeigt
			}
	}
	}
	case Schritt:

	{
		animationStep(list_header* datenliste); //nächster Animationschritt
		while(1) //1 = Leertaste --> Pause
					{
						while(grafik_user_input(10) > Fehler);

						switch(grafik_user_input(delay_auslesen))
							{
							case Beenden:
								exit(0); //q = 0, beenden
							case: Pause:
								return; //mit Leertaste weitermachen
							case Schritt:
								if(get_animationsanzahl(kopf)== *get_animationszaehler(kopf)){ //überprüft ob noch eine Entwicklung gemacht werden muss
									continue;
								}
								animationStep(list_header* datenliste);
								print_animations_puffer(list_header* datenliste);
								continue; //in der Pause wird animationsschritt gezeigt
							}
					}

}
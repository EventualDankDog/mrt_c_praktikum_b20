/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Nutzerinteraktions-Modul
 */

#include "ui.h"
#include "engine.h"
// für vorgegebene UI Funktionen: grafik_user_input()
#include "graphic.h"

// für die Funktion `exit`
#include <stdlib.h>
#include "gfx.h"


// Funktionen um Nutzerinteraktionen zu behandeln

void ui(list_header* kopf){

	while(grafik_user_input(10) > Fehler);

		switch(grafik_user_input(get_delay(kopf)))
		{
			case Beenden:
				exit(0); //q = 0, beenden
			case Pause:
			{
				while(1) //1 = Leertaste --> Pause
				{
					while(grafik_user_input(10) > Fehler);


					switch(grafik_user_input(get_delay(kopf)))
						{
						case Beenden:
							exit(0); //q = 0, beenden
						case Pause:
							return; //mit Leertaste weitermachen
						case Schritt:
							if(get_animationsanzahl(kopf)== get_animationszaehler(kopf)){ //überprüft ob noch eine Entwicklung gemacht werden muss
								continue;
							}

							evolution(kopf);
							print_animation(kopf);
							continue; //in der Pause wird animationsschritt gezeigt
						}
				}
		}
		case Schritt:
		{
			evolution(kopf); //nächster Animationschritt
			while(1) //1 = Leertaste --> Pause
						{
							while(grafik_user_input(10) > Fehler);

							switch(grafik_user_input(get_delay(kopf)))
								{
								case Beenden:
									exit(0); //q = 0, beenden
								case Pause:
									return; //mit Leertaste weitermachen
								case Schritt:
									if(get_animationsanzahl(kopf) == get_animationszaehler(kopf)){ //überprüft ob noch eine Entwicklung gemacht werden muss
										continue;
									}
									evolution(kopf);
									print_animation(kopf);
									continue; //in der Pause wird animationsschritt gezeigt
								}
						}

		default:

				if(get_animationsanzahl(kopf)== get_animationszaehler(kopf)){
					return ;
				}


				evolution(kopf);

				return; // normales Ablaufen der Animation


	}
}
}

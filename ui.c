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


int naechster_Schritt(list_header* kopf){

	int j = 0;
	if(get_animationsanzahl(kopf)== *get_animationszaehler(kopf)){
		// check ob programm am ende
			j = 1;
			return j;
	}

	evolution(kopf);
	print_animation(kopf);
	return j;

}

int ui(list_header* kopf){

	int k = 0;

		switch(grafik_user_input(get_delay(kopf)))
		{
			case Beenden: // k = 1 zurückgeben --> Ende
				k = 1;
				return k;
			case Pause: // Leertaste --> Pausieren
			{
				while(1) // Endlosschleife für Pause
				{

					switch(grafik_user_input(get_delay(kopf)))
						{
						case Beenden:
							k= 1;
							return k ;
						case Pause:

							return k; //mit Leertaste weitermachen
						case Schritt:
							k = naechster_Schritt(kopf); // Nächsten Schritt machen
							continue;

						}
				}
		}

		case Schritt:
		{
			k = naechster_Schritt(kopf);

			while(1) //Leertaste --> Pause
						{

							switch(grafik_user_input(get_delay(kopf)))
								{
								case Beenden:
									k= 1;
									return k ;
								case Pause:
									return k; //mit Leertaste weitermachen
								case Schritt:
									k = naechster_Schritt(kopf);
									continue; //in der Pause wird animationsschritt gezeigt
								}
						}


		default:

				if(get_animationsanzahl(kopf)== *get_animationszaehler(kopf)){
					k = 1;
					return k;
				}


				evolution(kopf);

				return k; // normales Ablaufen der Animation


	}
}
}

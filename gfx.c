/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Grafikausgabe-Modul
 */

#include "gfx.h"

// für vorgegebene Grafik Funktionen grafik_paint_point() und andere:
#include "graphic.h"


// Funktionen zur Grafikausgabe

void init_frame(list_header* kopf){ //Fenster
	grafik_init_window();
	grafik_create_paint_area(1, get_X(kopf)+1,1, get_Y(kopf)+1, get_X(kopf), get_Y(kopf)); //Zeichenfläsche initialisieren
}

print_animation(list_header* kopf){
	int* current_array = get_zahlenfeld(kopf);
	int* animationspuffer = neues_zahlenfeld(kopf);

	memcpy(animationspuffer, current_array, (get_X(kopf)+2)*(get_Y(kopf)+2)*sizeof(int ));

	int Spalten = get_X(kopf) + 2;
	int Zeilen = get_Y(kopf) + 2;
	color_name_t Farbe;

	grafik_lock_for_painting();

	for (int y = 0; y != Zeilen+1; y++) {
		for(int x = 0; x != Spalten+1; x++) {

			if(animationspuffer[y * Spalten + x]==1) {
				Farbe = Valhalla;
			}else if (animationspuffer[y * Spalten + x]==0){
				Farbe = Viking;
			}
			grafik_paint_point(x,y,Farbe);
		}
	}
	grafik_unlock_and_show();
	free(animationspuffer);

}

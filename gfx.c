/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Grafikausgabe-Modul
 */

#include "gfx.h"

// für vorgegebene Grafik Funktionen grafik_paint_point() und andere:
# include "graphic.h"

// Funktionen zur Grafikausgabe

void init_frame(list_header* kopf){ //Fenster
	grafik_init_window();
	grafik_create_paint_area(1, get_X(kopf)+1,1, get_Y(kopf)+1, get_X(kopf), get_Y(kopf); //Zeichenfläsche initialisieren
}

void print_animation_puffer(list_header* kopf){
	int* current_array = get_array(kopf)
	int* animationspuffer = new_arry(kopf);

	memcpy(animationspuffer, current_array, (get_X(kopf)+2)*(get_Y(kopf)+2)*sizeof(int ));

	int cols = get_X(kopf) + 2;
	int rows = get_Y(kopf) + 2;
	color_name_t color;

void grafik_lock_for_painting();

	for (int y = 0; y != get_Y(kopf)+1; y++) {
		for(int x = 0; x != get_X(kopf)+1; x++) {

			if(animationspuffer[y * cols + x]==1) {
				color = Mandy;
			}else if (animationspuffer[y * cols + x]==0){
				color = Opal;
			}
			grafik_paint_point(x,y,color);
		}
	}
void grafik_unluck_and_show();
	free(animationspuffer);

}

/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

#include "engine.h"
#include "daten.h"


list_header* animationStep (list_header* datenliste){

	//relevante Daten holen und definieren
	int *feld = get_zahlenfeld(datenliste);
	int *neuesfeld = neues_zahlenfeld(datenliste);
	int x = get_X(datenliste) + 2;
	int y = get_Y(datenliste) + 2;

	//zahlenfeld analysieren

	for (int j = 0; j<=y;j++){
		for (int i = 0;i<=x;i++){
			int tempCount=0; //zähler um anzahl belegter Nachbarpixel zu speichern

			for (int k = j-1;k<=j+1;k++){
				if (k==-1 || k==y+1){ //falls Pixel außerhalb des Gebietes liegt, wird es als frei angenommen
					continue;
				}
				for (int l=i-1;l<=i+1;l++){
					if(l==-1 || l==x+1){ //falls Pixel außerhalb des Gebietes liegt, wird es als frei angenommen
						continue;
					}
					if(k==j && l==i){
						continue; //mittleres Pixel wird ignoriert
					}
					tempCount=tempCount+feld[k*l];

					//weiter mit regeln für Folgeschritt


					if (feld[i*j]==0 && tempCount==3){
						neuesfeld[i*j]=1;

					}
					if (feld[i*j]==0){
						if (tempCount<2){
							neuesfeld[i*j]=0;
						}
						if (tempCount==2 || tempCount==3){
							neuesfeld[i*j]=1;
						}
						if (tempCount>3){
							neuesfeld[i*j]=0;
						}

					}


				}
			}


		}



	}

	int* counter = get_animationszaehler();
	*counter = *counter+1;




	return neuesfeld;
}

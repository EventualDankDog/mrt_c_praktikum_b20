/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

#include "engine.h"
#include "daten.h"
#include <string.h>


void evolution(list_header* datenliste){

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
				if (k<0 || k>y){ //falls Pixel außerhalb des Gebietes liegt, wird es als frei angenommen
					continue;
				}
				for (int l=i-1;l<=i+1;l++){
					if(l<0 || l>x){ //falls Pixel außerhalb des Gebietes liegt, wird es als frei angenommen
						continue;
					}
					if(k==j && l==i){
						continue; //mittleres Pixel wird ignoriert
					}
					tempCount=tempCount+feld[k*x+l];

					//weiter mit regeln für Folgeschritt


					if (feld[j*x+i]==0 && tempCount==3){
						neuesfeld[j*x+i]=1;

					}
					if (feld[j*x+i]==0){
						if (tempCount<2){
							neuesfeld[j*x+1]=0;
						}
						if (tempCount==2 || tempCount==3){
							neuesfeld[j*x+1]=1;
						}
						if (tempCount>3){
							neuesfeld[j*x+i]=0;
						}

					}


				}
			}


		}



	}

	

	//altes Zahlenfeld überschreiben
	/*
	for (int j = 0;j<=y;j++){
		for (int i = 0;i<=x;i++){
			feld[j*x + i]=neuesfeld[j*x + i];
		}
	}
	*/
	int counter = get_animationszaehler(datenliste);
	*counter = *counter+1;
	

	//direkt auf speicher zugreifen
	memcpy(feld, neuesfeld, (x*y*sizeof(int)));
	free (neuesfeld);


	//return neuesfeld;
}



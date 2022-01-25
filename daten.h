#ifndef C_PRAKTIKUM_DATEN_H
#define C_PRAKTIKUM_DATEN_H

#include <stdlib.h>
#include <stdio.h>

//Struktur mit allen notwendigen Daten --> Enthält: Zeilen,Spalten , Aktuelle_Schrittzahl, Schrittzahl, Delay, Array, Zusatzinformationen
//  X = Zeilen (Int)
//  Y = Spalten (Int)
//  ZAEHLER = Aktuelle_Schrittzahl (Int)    
//  ANZAHL = Schrittzahl (Int)
//  DELAY = Delay (Int)
//  ZAHLENFELD = Array (list)

typedef enum {

    X,Y,ZAEHLER,ANZAHL,DELAY,ZAHLENFELD

}datenart;


typedef struct list_el_t{       //Aufbau des Listenelements

   struct list_el *next;
   void *payload;
   datenart *datenart;

} list_element;


typedef struct list_t{          //Aufbau des Listenheaders
   list_element *head;
   list_element *tail;
}list_header;

list_header* neueDatensammlung();

//getter setter X-Achse
int get_X(list_header* kopf);
void set_X(list_header* kopf, int* x);

//getter setter Y-Achse
int get_Y(list_header* kopf);
void set_Y(list_header* kopf, int* y);

//getter setter Animationszähler
int* get_animationszaehler(list_header* kopf);
void set_animationszaehler(list_header* kopf, int* zaehler);

//getter setter maximale Animationsschritte
int get_animationsanzahl(list_header* kopf);
void set_animationsanzahl(list_header* kopf, int* anzahl);

//getter setter Pause zwischen Animationsschritten
int get_delay(list_header* kopf);
void set_delay(list_header* kopf, long* delay);

//getter setter array-pointer
int* get_zahlenfeld(list_header* kopf);
void set_zahlenfeld(list_header* kopf, int* zahlenfeld);

//erzeugt ein Array aus Liste mit der Größe (Zeilen+2)*(Spalten+2)
int* neues_zahlenfeld(list_header* kopf);

void free_all(list_header* kopf);



#endif

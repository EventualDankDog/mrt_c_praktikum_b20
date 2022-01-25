#include "daten.h"



void list_element_init(list_element *element) {
    element->next = NULL;
    element->payload = NULL;
    element->datenart = NULL;
}

list_element* list_element_new() {

    list_element *new = (list_element *) malloc(sizeof(list_element));
    list_element_init(new);
    return (new);
}

void list_header_init(list_header *header) {
    header->head = NULL;
    header->tail = NULL;

}

list_header* list_header_new() {
    list_header *new = (list_header *) malloc(sizeof(list_header));
    list_header_init(new);
    return (new);
}


//neues Element + Daten in diesem hinzufügen
void listelement_append(list_header *l, list_element *le, void *payload, datenart *datenart) {

    le->payload = payload;      //Der Listenelementpayloadzeiger zeig tauf die Paylaodadresse 
    le->next = NULL;            //Next wird auf Null gesetzt, da das nächste Listenelement noch nicht bekannt ist
    le->datenart = datenart;    //-

 if (l->head == NULL && l->tail == NULL){   //nur für das 1. Element erforderlich, Head und Tailpointer zeigen dann auf das gleiche Element
        l->head = le;
        l->tail = le;
        return;
    }

    /*
    if (l->head == l->tail) {
        //l->head->next = le;
        l->tail = le;
        return;
    }
    */

    l->tail->next =  le;
    l->tail = le;
}

//gesamter Inhalt der Liste wird vom header gelöst (z.B. zum neubefüllen der List)
void list_clear(list_header *header) { //Headerpointer werden Null gesetzt, damit ist die Liste gelöscht
    header->head = NULL;
    header->tail = NULL;
}

list_header* neueDatensammlung(){

    //speicher für die einzelnen Datenarten der Liste reservieren
    datenart* Zeile = (datenart*) malloc(sizeof(datenart));
    *Zeile = X;
    datenart* Spalte = (datenart*) malloc(sizeof(datenart));
    *Spalte = Y;
    datenart* Aktuelle_Schrittzahl = (datenart*) malloc(sizeof(datenart));
    *Aktuelle_Schrittzahl = ZAEHLER;
    datenart* Schrittzahl = (datenart*) malloc(sizeof(datenart));
    *Schrittzahl = ANZAHL;
    datenart* Delay = (datenart*) malloc(sizeof(datenart));
    *Delay = DELAY;
    datenart* Array = (datenart*) malloc(sizeof(datenart));
    *Array = ZAHLENFELD;

    //Erstellen eines neuen Listheaders
    list_header* Datensammlung = list_header_new();

    //Erstellen der einzelnen Listenelemente
    list_element* x = list_element_new();
    list_element* y = list_element_new();
    list_element* zaehler = list_element_new();
    list_element* anzahl = list_element_new();
    list_element* delay = list_element_new();
    list_element* zahlenfeld = list_element_new();
    //Anhängen der Listenelemente an die oben erstellte Liste
    listelement_append(Datensammlung, x ,NULL ,Zeile);
    listelement_append(Datensammlung, y, NULL,Spalte);
    listelement_append(Datensammlung, zaehler, NULL, Aktuelle_Schrittzahl);
    listelement_append(Datensammlung, anzahl, NULL, Schrittzahl);
    listelement_append(Datensammlung, delay, NULL, Delay);
    listelement_append(Datensammlung, zahlenfeld, NULL, Array);

    return Datensammlung;
}

//Für get & set Funktionen benötigen wir Suchfunktionen

list_element* finde_daten(list_header *kopf, datenart datum){   // (nochmal Kommentieren) Findet Daten eines Datentyps aus unserer verlinkten Liste

    list_element* t;
    t = kopf->head;

    if(kopf->head == NULL && kopf->tail == NULL){               // Fehlerprüfung, falls eine Liste nicht existiert
	fprintf(stderr, "Listenfehler (Gewünschte Liste ist nonexistent)");
	return NULL;
    }
    while(t != NULL){                                           //Durchgehen der Liste bis das Element des Datentyps gefunden wird
        if(*(t -> datenart) == datum){
            return t;                                           //Ausgabe des gesuchten Elements
        }
        t = t -> next;
    }
    return NULL;
}

void daten_setzen(list_header *kopf, datenart datum, void* payload){ //selbe Prozedur wie beim Daten finden
    list_element *t;
    t = kopf->head;

    if(kopf->head == NULL && kopf->tail == NULL){
	fprintf(stderr, "Listenfehler (Gewünschte Liste ist nonexistent)");
	return;
    }
    while(t != NULL){
        if(*(t -> datenart) == datum){
            t-> payload = payload;                                  //Daten werden gesetzt 
            return;
        }
        t = t -> next;
    }
    return;
}

// Funktionen, um Werte zu bekommen
int get_X(list_header* kopf){
    list_element *t = finde_daten(kopf,X);
    return *((int*) t->payload);
}

int get_Y(list_header* kopf){
    list_element *t = finde_daten(kopf,Y);
    return *((int*) t->payload);
}

int* get_animationszaehler(list_header* kopf){
    list_element *t = finde_daten(kopf,ZAEHLER);
    return ((int*) t->payload);
}

int get_animationsanzahl(list_header* kopf){
    list_element *t = finde_daten(kopf,ANZAHL);
    return *((int*) t->payload);
}

int get_delay(list_header* kopf){
    list_element *t = finde_daten(kopf,DELAY);
    return *((int*) t->payload);
}

int* get_zahlenfeld(list_header* kopf){
    list_element *t = finde_daten(kopf,ZAHLENFELD);
    return ((int*) t->payload);
}

// Funktionen, um Werte zu setzen
void set_X(list_header* kopf, int* x){
    daten_setzen(kopf,X,x);
    return;
}

void set_Y(list_header* kopf, int* y){
    daten_setzen(kopf,Y,y);
    return;
}

void set_animationszaehler(list_header* kopf, int* zaehlerstand){
    daten_setzen(kopf,ZAEHLER,zaehlerstand);
    return;
}

void set_animationsanzahl(list_header* kopf, int* anzahl){
    daten_setzen(kopf,ANZAHL,anzahl);
    return;
}

void set_delay(list_header* kopf, long* delay){
    daten_setzen(kopf,DELAY,delay);
    return;
}

void set_zahlenfeld(list_header* kopf, int* array){
    daten_setzen(kopf,ZAHLENFELD,array);
    return;
}
int* neues_zahlenfeld(list_header* kopf){               //Speicher wird in der benötigten Größe des Arrays reserviert (Allokation)
    int* nz = (int *)malloc((get_X(kopf)+2)*(get_Y(kopf)+2)*sizeof (int ));
    return nz;
}
void free_all(list_header* kopf){
    free(finde_daten(kopf,ZAHLENFELD));
}


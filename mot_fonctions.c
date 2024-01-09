#include "mot_struct.h"
#include <stdio.h>
#include <stdlib.h>

Mot *creerMaillon(int x){
    Mot *m = malloc(sizeof(Mot));
    m->valeur = x;
    m->suivant = NULL;
    return m;
}

Mot *insererElement(Mot *L, int x){
    Mot *m = creerMaillon(x);

    if (L == NULL) {
        return m;
    }

    Mot *courant = L;

    while (courant->suivant != NULL){
        courant = courant->suivant;
    }

    courant->suivant = m;

    return L;
}


Mot *saisirMot(){
    Mot *L = NULL;
    int nombre;

    printf("Entrez votre mot (entrez -1 pour terminer):\n");

    while (1) {
        printf("Entrez une lettre du mot ou (-1 pour terminer) : ");
        scanf("%d", &nombre);

        if (nombre == -1) {
            break;
        }

        L = insererElement(L, nombre);
    }

    return L;
}

void afficherMot(Mot *L) {
    printf("Ton mot : ");
    while (L != NULL) {
        printf("%d ", L->valeur);
        L = L->suivant;
    }
    printf("\n");
}




#ifndef H_mot_struct_H
#define H_mot_struc_H

typedef struct Mot Mot;
struct Mot {
    int valeur;
    Mot *suivant;
};

Mot *creerMaillon(int x);
Mot *insererElement(Mot *L, int x);
Mot *saisirMot();
void afficherMot(Mot *L);

#endif

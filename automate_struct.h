#ifndef H_automate_struct_H
#define H_automate_struc_H

typedef struct {
    int nb_symboles;
    int nb_etats;
    int nb_transitions;
    int etatInitial;
    int nb_etats_finaux;
    int *etatsFinaux;
    int ***automate;
} Automate;

Automate *lireAutomate(const char *nomFichier);

int **entrerTransitions(int nb_transitions);

Automate *saisirAutomate();

void afficherAutomate(Automate *automate);

void sauvegarderAutomateDansFichier(Automate *automate, const char *nomFichier);

int est_un_etat_final(Automate *automate, int etat_courant);

int fct_aux(int etat_courant, Automate *automate, Mot *mot);

int reconnaissanceMot(Automate *automate, Mot *mot);

int estComplet(Automate *automate);

int estDeterministe(Automate *automate);

Automate *fonctionMiroir(Automate *automate);

int verifierTrans(Automate *automate, int etat, int symbole);

Automate *fonctionProduit(Automate *automate1, Automate *automate2);

Automate *fonctionConcatenation(Automate *automate1, Automate *automate2);

#endif
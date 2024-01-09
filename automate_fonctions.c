#include "mot_struct.h"
#include "automate_struct.h"
#include <stdio.h>
#include <stdlib.h>

Automate *lireAutomate(const char *nomFichier){

// LECTURE DE NOTRE FICHIER CONTENANT LES INFORMATIONS DE NOTRE AUTOMATE (etats, symboles, transitions ...) 

    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }

    // printf("***************** LECTURE FICHIER *****************\n\n");
    // Lire la première ligne (nb_etats)
    int nb_etats = 0;
    fscanf(fichier, "%d", &nb_etats);
    // printf("Nombre d'états : %d \n", nb_etats);

    
    // Lire la deuxième ligne (nb_symboles)
    int nb_symboles;
    fscanf(fichier, "%d", &nb_symboles);
    // printf("Nombre de symboles : %d\n", nb_symboles);
    

    // Lire l'état initial
    int etat_initial;
    fscanf(fichier, "%d", &etat_initial);
    // printf("Etat initial lu : %d\n", etat_initial);

    // Lire le nombre d'états finaux
    int nb_etats_finaux;
    fscanf(fichier, "%d", &nb_etats_finaux);
    // printf("Nombre d'états finaux : %d\n", nb_etats_finaux);

    // Lire les états finaux stockées dans une liste 
    int *etats_finaux = malloc(nb_etats_finaux * sizeof(int)); // initialisation de la liste d'états finaux 
    for (int i = 0; i < nb_etats_finaux; i++) {
        fscanf(fichier, "%d ", &etats_finaux[i]);
    }

    /*for (int i = 0; i < nb_etats_finaux; i++) {
        printf("Etat final %d : %d \n", i+1, etats_finaux[i]);
    }*/

    // Lire le nombre de transitions 
    int nb_transitions;
    fscanf(fichier, "%d", &nb_transitions);
    // printf("Nombre de transitions : %d\n", nb_transitions);

        
    // Initialisation de la liste 2D transitions (tiplets [debut, symbole, fin])
    int **transitions = (int **)malloc(nb_transitions * sizeof(int *));
    for (int i = 0; i < nb_transitions; i++) {
        transitions[i] = (int *)malloc(3 * sizeof(int));
    }

    // Lecture des transitions 
    for (int i = 0; i < nb_transitions; i++){
        fscanf(fichier, "%d %d %d", &transitions[i][0], &transitions[i][1], &transitions[i][2]);
    }
    /*for (int i = 0; i < nb_transitions; i++){
        printf("%d  %d  %d\n",transitions[i][0], transitions[i][1], transitions[i][2]);
    }*/

    fclose(fichier);


// CREATION DE L'AUTOMATE  
    
    // Initialisation structure automate
    Automate *automate = (Automate *)malloc(sizeof(Automate));

    // Remplissage de notre structure automate 
    automate->nb_symboles = nb_symboles;
    automate->nb_etats = nb_etats;
    automate->nb_transitions = nb_transitions;
    automate->nb_etats_finaux = nb_etats_finaux;
    automate->etatInitial = etat_initial;
    automate->etatsFinaux = (int *)malloc(nb_etats_finaux * sizeof(int));
    for (int i = 0; i < nb_etats_finaux; i++) {
        automate->etatsFinaux[i] = etats_finaux[i];
    } 

    // Controle pour afficher les infos de l'automate
    /*printf("\n");
    printf("***************** INFOS STRUCTURE AUTOMATE ***************** \n\n");
    printf("Nombre d'états : %d \n", automate->nb_etats);
    printf("Nombre de symboles : %d \n", automate->nb_symboles);
    printf("Etat initial : %d \n", automate->etatInitial);
    printf("Nombre d'états finaux : %d \n", automate->nb_etats_finaux);
    for (int i = 0; i < nb_etats_finaux; i++) {
        printf("Etat final %d : %d \n", i+1, automate->etatsFinaux[i]);
    }
    printf("Nombre de transitions : %d \n", automate->nb_transitions);*/

    // Allocation de memoire pour le tableau 3D automate
    automate->automate = (int ***)malloc(nb_etats * sizeof(int **));
    // Initialisation du tableau automate avec des -1
    for(int i = 0; i < nb_etats; i++) {
        automate->automate[i] = (int **)malloc(nb_symboles * sizeof(int *));
        for(int j = 0; j < nb_symboles; j++) {
            automate->automate[i][j] = (int *)malloc(nb_etats * sizeof(int));
            for(int k =0;k<nb_etats;k++){
                automate->automate[i][j][k]= -1;
            }
        }
    }

    // Controle pour afficher le tableau 3D automate 
    /*printf("\n");
    printf("***************** AUTOMATE INITIALISE ****************** \n\n");
    for(int i = 0; i < nb_etats; i++){
        for(int j = 0; j < nb_symboles; j++){
            for(int k =0; k < nb_etats;k++){
                printf("automate[%d][%d][%d] : %d \n", i,j,k, automate->automate[i][j][k]);
            }
        }
    }*/

    // Remplissage de l'automate (si la transitions existe bien remplir l'automate avec 1)
    for (int z = 0; z < nb_transitions; z++){
        int deb = transitions[z][0];
        int symb = transitions[z][1];
        int fin = transitions[z][2];

        automate->automate[deb][symb][fin] = 1;
    }

    // Controle pour afficher le tableau 3D automate rempli avec les transitions
    /*printf("\n");
    printf("***************** AUTOMATE REMPLI ***************** \n\n");
    for(int i = 0; i < nb_etats; i++){
        for(int j = 0; j < nb_symboles; j++){
            for(int k =0; k < nb_etats;k++){
                printf("automate[%d][%d][%d] : %d \n", i,j,k, automate->automate[i][j][k]);
            }
        }
    }*/

    return automate;
  
}

void afficherAutomate(Automate *automate){ 

    printf("\n");
    printf("***************** AFFICHAGE AUTOMATE AVEC FONCTION ****************** \n\n");
    printf("Nombre d'états : %d \n", automate->nb_etats);
    printf("Nombre de symboles : %d \n", automate->nb_symboles);
    printf("Etat initial : %d \n", automate->etatInitial);
    printf("Nombre d'états finaux : %d \n", automate->nb_etats_finaux);
    for (int i = 0; i < automate->nb_etats_finaux; i++) {
        printf("Etat final %d : %d \n", i+1, automate->etatsFinaux[i]);
    }
    printf("Nombre de transitions : %d \n\n", automate->nb_transitions);

    for(int i = 0; i < automate->nb_etats; i++){
        for(int j = 0; j < automate->nb_symboles; j++){
            for(int k =0; k < automate->nb_etats;k++){
                if (automate->automate[i][j][k] == 1){
                    printf("° q(%d) ---> a(%d) : q(%d)\n", i,j,k);
                }
                
               // else {
               //     printf("° q(%d) ---> a(%d) : _ \n", i,j);
               // }
                
            }
        }
    }
    printf("\n");
}

void sauvegarderAutomateDansFichier(Automate *automate, const char *nomFichier) {
    FILE *fichier;
    fichier = fopen(nomFichier, "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    // Ecriture nb_etats, nb_symboles, etat initial 
    fprintf(fichier, "%d\n", automate->nb_etats);
    fprintf(fichier, "%d\n", automate->nb_symboles);
    fprintf(fichier, "%d\n", automate->etatInitial);
    
    // Ecriture du nombre d'états finaux et des états finaux
    fprintf(fichier, "%d\n", automate->nb_etats_finaux);
    for (int i = 0; i < automate->nb_etats_finaux; i++) {
        fprintf(fichier, "%d ", automate->etatsFinaux[i]);
    }
    
    fprintf(fichier, "\n");


    // Ecriture du nombre de transitions et des transtions 
    fprintf(fichier, "%d\n", automate->nb_transitions); 
    for (int i = 0; i < automate->nb_etats; i++) {
        for (int j = 0; j < automate->nb_symboles; j++) {
            for (int k = 0; k < automate->nb_etats; k++) {
                if (automate->automate[i][j][k] == 1) {
                    fprintf(fichier, "%d %d %d \n", i,j,k);
                }       
            }
        }
    }

    fclose(fichier);
}

int **entrerTransitions(int nb_transitions){
    
    // Allocation de mémoire pour le tableau 2D transitions qui sert a remplir le tableau automate 3D (voir fonction créer automate)
    int **transitions = malloc(nb_transitions * sizeof(int *));
    for(int i = 0; i < nb_transitions; i++) {
        transitions[i] = malloc(3 * sizeof(int));
    }

    // Demande de saisie à l'utilisateur de chaque transitions de la matrice 
    for (int i = 0; i < nb_transitions; i++){
        printf("Saisir la transition %d (état début, symbole, état fin) :", i+1);
        scanf("%d", &transitions[i][0]);
        scanf("%d", &transitions[i][1]);
        scanf("%d",&transitions[i][2]);
    } 

    return transitions;
}

Automate *saisirAutomate() {

    // Saisie des infos de l'automate par l'utilisateur
    int nb_etats;
    printf("Saisissez le nombre d'états : ");
    scanf("%d", &nb_etats);

    int nb_symboles;
    printf("Saisissez le nombre de symboles : ");
    scanf("%d", &nb_symboles);

    int nb_transitions;
    printf("Saisissez le nombre de transitions : ");
    scanf("%d", &nb_transitions);

    int etat_initial;
    printf("Saisissez l'état initial : ");
    scanf("%d", &etat_initial);

    int nb_etats_finaux;
    printf("Saisissez le nombre d'etats finaux : ");
    scanf("%d", &nb_etats_finaux);

    int *etats_finaux = malloc(nb_etats_finaux * sizeof(int));

    for (int i = 0; i < nb_etats_finaux; i++) {
        printf("Saisissez l'etat final %d : ", i + 1);
        scanf("%d", &etats_finaux[i]);
    }

    // Initialisation automate
    Automate *automate = (Automate *)malloc(sizeof(Automate));

    // Remplissage de la structure automate 
    automate->nb_symboles = nb_symboles;
    automate->nb_etats = nb_etats;
    automate->nb_transitions = nb_transitions;
    automate->nb_etats_finaux = nb_etats_finaux;
    automate->etatInitial = etat_initial;
    automate->etatsFinaux = (int *)malloc(nb_etats_finaux * sizeof(int)); // etatsFinaux est une liste donc allocation de mémoire
    for (int i = 0; i < nb_etats_finaux; i++) {
        automate->etatsFinaux[i] = etats_finaux[i];
    } 

    // Controle pour afficher les infos de l'automate
    printf("\n");
    printf("***************** INFOS AUTOMATE ***************** \n\n");
    printf("nb syboles : %d \n", automate->nb_symboles);
    printf("nb etats : %d \n", automate->nb_etats);
    printf("nb transitions : %d \n", automate->nb_transitions);
    printf("etat initial : %d \n", automate->etatInitial);
    for (int i = 0; i < nb_etats_finaux; i++) {
        printf("etat final %d : %d \n", i+1, automate->etatsFinaux[i]);
    } 

    // Saisie des transitions 
    int **trans = entrerTransitions(nb_transitions);

    // Controle pour afficher le tableau 2D trans (il contient les transitions)
    printf("\n");
    printf("***************** TRANSITIONS ***************** \n\n");
    for (int i = 0; i < nb_transitions; i++){
        for (int j = 0; j < 3; j++ )
        printf("transitions[%d][%d] = %d \n",i,j,trans[i][j]);
    }

    // Allocation de memoire pour automate + Initialisation à -1
    automate->automate = (int ***)malloc(nb_etats * sizeof(int **));
    for(int i = 0; i < nb_etats; i++) {
        automate->automate[i] = (int **)malloc(nb_symboles * sizeof(int *));
        for(int j = 0; j < nb_symboles; j++) {
            automate->automate[i][j] = (int *)malloc(nb_etats * sizeof(int));
            for(int k =0;k<nb_etats;k++){
                automate->automate[i][j][k]= -1;
            }
        }
    }

    // Controle pour afficher le tableau 3D automate 
    printf("\n");
    printf("***************** AUTOMATE INITIALISE ****************** \n\n");
    for(int i = 0; i < nb_etats; i++){
        for(int j = 0; j < nb_symboles; j++){
            for(int k =0; k < nb_etats;k++){
                printf("automate[%d][%d][%d] : %d \n", i,j,k, automate->automate[i][j][k]);
            }
        }
    }

    // Remplissage de l'automate (si la transitions existe bien remplir l'automate avec 1)
    for (int z = 0; z < nb_transitions; z++){
        int deb = trans[z][0];
        int symb = trans[z][1];
        int fin = trans[z][2];

        automate->automate[deb][symb][fin] = 1;
    }

    // Controle pour afficher le tableau 3D automate rempli avec les transitions
    printf("\n");
    printf("***************** AUTOMATE REMPLI ***************** \n\n");
    for(int i = 0; i < nb_etats; i++){
        for(int j = 0; j < nb_symboles; j++){
            for(int k =0; k < nb_etats;k++){
                printf("automate[%d][%d][%d] : %d \n", i,j,k, automate->automate[i][j][k]);
            }
        }
    }

    return automate;

}

int fct_aux(int etat_courant, Automate *automate, Mot *mot){
        for(int i = 0; i < automate->nb_etats; i++){
        if (automate->automate[etat_courant][mot->valeur][i] != -1){
            return i;
        }
        }
    
    printf("Le mot n'est pas reconnu ! \n");
    return -1;
}

int est_un_etat_final(Automate *automate, int etat_courant){
    for(int i = 0; i < automate->nb_etats_finaux; i++){
        if (automate->etatsFinaux[i] != etat_courant){
            printf("L'état courant n'est pas un état final ! \n");
            return -1;
        }else{
            return 1;
        }
    }
}

int reconnaissanceMot(Automate *automate, Mot *mot){
    int etat_courant = automate->etatInitial;

    while (mot != NULL)
    {
        if (fct_aux(etat_courant, automate, mot) == -1){
            return -1;
        } else {
            etat_courant = fct_aux(etat_courant, automate, mot);
            mot = mot->suivant;
        }
    }

    if (est_un_etat_final(automate, etat_courant) == -1){
        return -1;
    }else{
        printf("Le mot est reconnu par l'automate. \n");
    }
}

int estComplet(Automate*automate){
    int compteur=0;
    for(int i=0;i<automate->nb_etats;i++){
        for (int j=0;j < automate->nb_symboles;j++) {
            for (int k=0;k<automate->nb_etats;k++){
                if (automate->automate[i][j][k]==1){
                    compteur++;
                }
            }
        if (compteur<1){
            // printf("L'automate n'est pas complet. \n");
            return -1;
        }
        else{
            compteur=0;
        }
                
        }
    }

    // printf("L'automate est complet. \n");
    return 0;
}

int estDeterministe(Automate*automate){
    int compteur=0;
    for(int i=0;i<automate->nb_etats;i++){
        for (int j=0;j < automate->nb_symboles;j++) {
            for (int k=0;k<automate->nb_etats;k++){
                if (automate->automate[i][j][k]==1){
                    compteur++;
                }
            }
        if (compteur>=2){
            // printf("L'automate n'est pas deterministe. \n");
            return -1;
        }
        else{
            compteur=0;
        }
                
        }
    }

    // printf("L'automate est deterministe. \n");
    return 0;
}

Automate *fonctionMiroir(Automate *automate){

    if (estDeterministe(automate) == -1){
        return NULL;    
    }
    
    if(automate->nb_etats_finaux > 1){
        printf("L'automate contient plusieurs états finaux");
        return NULL;
    }

    Automate *miroir = (Automate *)malloc(sizeof(Automate));
    // Initialisation des infos de notre structure pour l'automate miroir 
    miroir->nb_symboles = automate->nb_symboles;
    miroir->nb_etats = automate->nb_etats;
    miroir->nb_transitions = automate->nb_transitions;
    miroir->nb_etats_finaux = 1;
    miroir->etatInitial = automate->etatsFinaux[0];
    miroir->etatsFinaux = (int *)malloc(miroir->nb_etats_finaux * sizeof(int));
    miroir->etatsFinaux[0] = automate->etatInitial;


    // Allocation de mémoire et Initialisation de l'automate miroir 
    miroir->automate = (int ***)malloc(miroir->nb_etats * sizeof(int **));
    for(int i = 0; i < miroir->nb_etats; i++) {
        miroir->automate[i] = (int **)malloc(miroir->nb_symboles * sizeof(int *));
        for(int j = 0; j < miroir->nb_symboles; j++) {
            miroir->automate[i][j] = (int *)malloc(miroir->nb_etats * sizeof(int));
            for(int k =0; k < miroir->nb_etats;k++){
                miroir->automate[i][j][k]= -1;
            }
        }
    }


    // Remplissage de la matrice de l'automate miroir 
    for(int i = 0; i < miroir->nb_etats; i++){
        for(int j = 0; j < miroir->nb_symboles; j++){
            for(int k =0; k < miroir->nb_etats;k++){
                if(automate->automate[i][j][k] ==1 ){
                    miroir->automate[k][j][i] = 1;
                }
            }
        }
    }

    // Controle pour afficher le tableau 3D automate de notre miroir
    printf("\n");
    printf("***************** AUTOMATE MODIFIE ****************** \n\n");
    for(int i = 0; i < miroir->nb_etats; i++){
        for(int j = 0; j < miroir->nb_symboles; j++){
            for(int k =0; k < miroir->nb_etats;k++){
                printf("automate[%d][%d][%d] : %d \n", i,j,k, miroir->automate[i][j][k]);
            }
        }
    }

    return miroir;
   
}

int verifierTrans(Automate *automate, int etat, int symbole){
    for(int k = 0; k < automate->nb_etats;k++){
        if(automate->automate[etat][symbole][k] == 1){
            return 1;
        }    
    }
}

int destinationTrans(Automate *automate, int etat, int symbole){
    for(int k = 0; k < automate->nb_etats;k++){
        if(automate->automate[etat][symbole][k] == 1){
            return k;
        }    
    }
}

int indiceCouple(int couples[][2], int taille, int *couple_arrive){
    for(int i=0; i<taille;i++){
        if(couples[i][0] == couple_arrive[0] && couples[i][1] == couple_arrive[1]){
            return i;
        } 
    }
    return -1;
}
    

Automate *fonctionProduit(Automate *automate1, Automate *automate2){

    // avant tout testons si les automates sont deterministes, 
    // si les automates ne sont pas deterministes on sort de la fonction

    if (estDeterministe(automate1) == -1 || estDeterministe(automate2) == -1){
        printf("Un des deux automates n'est pas déterministe.");
        return NULL;    
    }

    if(automate1->nb_symboles != automate2->nb_symboles){
        printf("Les automates n'ont pas le même nombre de symboles");
        return NULL;
    }

    // INITIALISATION STRUCT DE PRODUIT 
    Automate *produit = (Automate *)malloc(sizeof(Automate)); 
    produit->nb_symboles = automate1->nb_symboles;
    produit->nb_etats = automate1->nb_etats * automate2->nb_etats ;
    produit->nb_transitions = automate1->nb_symboles * automate1->nb_etats * automate2->nb_etats;
    produit->etatInitial = 0;
    produit->nb_etats_finaux = automate1->nb_etats_finaux * automate2->nb_etats_finaux;
    produit->etatsFinaux = (int *)malloc(produit->nb_etats_finaux * sizeof(int));

    // ALLOCATION DE LA MATRICE + REMPLISSAGE AVEC -1
    produit->automate = (int ***)malloc(produit->nb_etats * sizeof(int **));
    for(int i = 0; i < produit->nb_etats; i++) {
        produit->automate[i] = (int **)malloc(produit->nb_symboles * sizeof(int *));
        for(int j = 0; j < produit->nb_symboles; j++) {
            produit->automate[i][j] = (int *)malloc(produit->nb_etats * sizeof(int));
            for(int k =0; k < produit->nb_etats;k++){
                produit->automate[i][j][k]= -1;
            }
        }
    }

    // TEST AFFICHAGE INFOS AUTOMATES PRODUITS
    // afficherAutomate(produit);

    // CREATION DES ETATS DU PRODUIT CARTESIEN 

    int k = automate1->nb_etats; 
    int n = automate2->nb_etats;  

    // Déclarez un tableau de couples avec une taille suffisante (k+1)*(n+1)
    int couples[(k+1)*(n+1)][2]; 

    // Variable pour suivre le nombre de couples générés
    int count = 0;

    // Boucle pour générer les couples
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            couples[count][0] = i;
            couples[count][1] = j;
            count++;
        }
    }   

    // Affichez les couples générés
    /*printf("{");
    for (int i = 0; i < count; i++) {
        printf("{%d, %d}", couples[i][0], couples[i][1]);
        if (i < count - 1) {
            printf(",");
        }
    }

    printf("}\n");*/

    // ETAPE CORRESPONDANCE

    for(int z=0; z<count; z++){
        for(int a=0; a<automate1->nb_symboles; a++){
            if(verifierTrans(automate1, couples[z][0],a) == 1 && verifierTrans(automate2, couples[z][1],a) == 1){
                int couple_arrive[2]={destinationTrans(automate1,couples[z][0],a), destinationTrans(automate2,couples[z][1],a)};
                // printf("couple_arrive : %d, %d \n", couple_arrive[0], couple_arrive[1]);
                int indice = indiceCouple(couples, count, couple_arrive);
                // printf("indice : %d \n", indice);
                produit->automate[z][a][indice] = 1;
            }
        }
    }

   

    // ETATS FINAUX DE NOTRE AUTOMATE PRODUIT 
    int indiceEtatFinal = 0;
    for(int i=0;i<count;i++){
        for(int j=0;j<automate1->nb_etats_finaux;j++){
            for(int k=0;k<automate2->nb_etats_finaux;k++){
                if(couples[i][0] == automate1->etatsFinaux[j] && couples[i][1] == automate2->etatsFinaux[k]){
                    produit->etatsFinaux[indiceEtatFinal] = i;
                    indiceEtatFinal++;
                }

            }
        }
    }

    return produit;

}

Automate *fonctionConcatenation(Automate *automate1, Automate *automate2){

    if (estDeterministe(automate1) == -1 || estDeterministe(automate2) == -1){
        printf("Un des deux automates n'est pas déterministe.");
        return NULL;    
    }

    // INITIALISATION STRUCT DE CONCATENATION : attention il faut corriger la structure !!!
    Automate *concatenation = (Automate *)malloc(sizeof(Automate)); 
    concatenation->nb_symboles = automate1->nb_symboles + automate2->nb_symboles + 1 ; 
    concatenation->nb_etats = automate1->nb_etats + automate2->nb_etats ;
    concatenation->nb_transitions = automate1->nb_transitions + automate2->nb_transitions + 1;
    concatenation->etatInitial = automate1->etatInitial;
    concatenation->nb_etats_finaux = automate2->nb_etats_finaux ;
    concatenation->etatsFinaux = (int *)malloc(concatenation->nb_etats_finaux * sizeof(int));
    for (int i = 0; i < automate2->nb_etats_finaux; i++) {concatenation->etatsFinaux[i] = automate2->etatsFinaux[i];} 

    // ALLOCATION DE LA MATRICE + REMPLISSAGE AVEC -1
    concatenation->automate = (int ***)malloc(concatenation->nb_etats * sizeof(int **));
    for(int i = 0; i < concatenation->nb_etats; i++) {
        concatenation->automate[i] = (int **)malloc(concatenation->nb_symboles * sizeof(int *));
        for(int j = 0; j < concatenation->nb_symboles; j++) {
            concatenation->automate[i][j] = (int *)malloc(concatenation->nb_etats * sizeof(int));
            for(int k =0; k < concatenation->nb_etats;k++){
                concatenation->automate[i][j][k]= -1;
            }
        }
    }

    afficherAutomate(concatenation);

}

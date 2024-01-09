#include "mot_struct.h"
#include "automate_struct.h"
#include <stdio.h>
#include <stdlib.h>



int main() {

    Automate *autom1 = lireAutomate("automate1.txt");
    afficherAutomate(autom1);

    Automate *autom2 = lireAutomate("automate2.txt");
    afficherAutomate(autom2);
    
    // fonctionConcatenation(autom1,autom2);

    // Automate *produit = fonctionProduit(autom1, autom2);
    // afficherAutomate(produit);

    // Automate *mir = fonctionMiroir(autom1); 
    // afficherAutomate(autom1);
    // afficherAutomate(mir); 


    // Reconnaissance du mot a b b
    
    // Mot *mot = saisirMot();
    // afficherMot(mot);

    // reconnaissanceMot(autom, mot);

    // estComplet(autom);

    // estDeterministe(autom);

}


/* TERMINAL : 

    gcc -o MyExecution automate_fonctions.c main.c
    ./MyExecution
    
*/
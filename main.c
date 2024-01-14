#include "mot_struct.h"
#include "automate_struct.h"
#include <stdio.h>
#include <stdlib.h>



int main() {

    Automate *autom1 = lireAutomate("automate.txt");
    afficherAutomate(autom1);

}
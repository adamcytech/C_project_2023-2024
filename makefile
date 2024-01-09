all : MyExecution 
	./MyExecution
MyExecution : automate_fonctions.o mot_fonctions.o main.o
	gcc -o MyExecution automate_fonctions.o mot_fonctions.o main.o
automate_fonctions.o : automate_fonctions.c
	gcc -c automate_fonctions.c -o automate_fonctions.o
mot_fonctions.o : mot_fonctions.c
	gcc -c mot_fonctions.c -o mot_fonctions.o
main.o : main.c
	gcc -c main.c -o main.o
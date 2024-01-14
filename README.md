# C project automate CY-TECH 2023-2034

author : Adam Ilias Abdoulkarim Kiane Hatim

teacher : Dajouida ZAOUCHE

This project consists of 7 files:

-automate.txt: an example of the automaton used for the 'import an FSA (Finite State Automaton) from a file' part. Our automata and this file are structured as follows:
    
    number of states?
    
    number of symbols?
    
    what is the initial state? (the initial state is always 0)
    
    how many final states are there?
    
    What are the final states?(of the form a b c ..., where a,b,c are final states)
    
    How many transitions are there?
    
    What's the first transition (of the form x y z, where x is the initial state, y the transition and z the final state)?
    
    What's the ith transition?

-automate_functions.c: contains all the functions on the automata we've made

-automate_struct.h: contains the structure we've used on our functions, as well as the names of these functions

-main.c: contains the functions to be executed with make

-makefile: a script for automating the running of this project.

-mot_functions.c: contains functions used on aef words

-mot_struct.h: contains our FSA's word structure, which is a chained list

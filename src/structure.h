/* # Nom ......... : structure.h
# Rôle ........ : proto des fonctions et déclaration des structures
# Auteur ...... : Avrile Floro 
# Version ..... : V0.1 du 17/11/23
# Licence ..... : réalisé dans le cadre du cours d'Algo 1
# Usage : fichier header */

typedef char * string ;
#define NULLCHAR "\0"

#define car(doublet) ((doublet)->car) 
    // macro plutôt que fonction, pour écrire car(x) = ...
#define cdr(doublet) ((doublet)->cdr)
    // macro plutôt que fonction, pour écrire cdr(x) = ...


typedef struct Doublet {
    void * car ; 
    struct Doublet * cdr ;
} * list ; // structure de Base ; list est un pointeur sur un doublet

typedef struct MotDictionnaire {
    struct Base * anglais;
    struct Trad * traduction;
    struct MotDictionnaire * cdr ;
} * une_entree ;

typedef struct Base {
    char* mot;
    char* original;
    struct Category * categorie;
} * forme_anglais, * forme_espagnol ;

typedef struct Trad {
    struct Base * espagnol;
    struct Trad * cdr;
} * trad_espagnol, * trad_anglais ;

typedef struct Category{
    char* chaine; 
    int cat;
} * la_categorie ;


// les prototypes des fonctions

list cons(void *, const list) ; /* construction liste */

list reverse(list L) ; /* inversion liste */

une_entree div_eng_esp(list L); /* renvoie l'entrée */

forme_anglais eng_cat(string anglais); /* renvoie la forme anglaise */

trad_espagnol spanish(string esp, string cat); /* renvoie la trad esp */

forme_espagnol subdiv_esp(string token, string cat); /* renvoie la forme esp */

la_categorie assoc_categorie(string cat_originale); /* association catégorie */

void initialisation_fichiers(); /* initialisation préalable des fichiers en W */

void creation_tests(une_entree dictionnaire); /* création des tests si -DTEST */

void traduction(une_entree dictionnaire); /* programme de la traduction */
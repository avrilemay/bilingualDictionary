/* # Nom ......... : category.c
# Rôle ........ : màj des cat grammaticales des mots
# Auteur ...... : Avrile Floro 
# Version ..... : V0.1 du 17/11/23
# Licence ..... : réalisé dans le cadre du cours d'Algo 1
# Usage : compilé via "make" ou "make -f makefile_tests" */

#include "sys.h"
#include "structure.h"

#define NOUN 1
#define VERB 2
#define ADJECTIVE 3
#define ADVERB 4
#define INTERJECTION 5
#define PRONOUN 6
#define PREFIX 7
#define SUFFIX 8
#define PROVERB 9
#define PROPER_NOUN 10
#define PHRASE 11
#define PREP_PHRASE 12
#define CONJUNCTION 13
#define DETERMINER 14
#define CONTRACTION 15
#define ART 16
#define SYMBOL 17
#define CARDINAL_NUM 18
#define ACRONYM 19
#define PREPOSITION 20
#define ABBREVIATION 21
#define INITIALISM 22
#define PARTICLE 23
#define NUM 24
#define NOM_MASCULIN 25
#define NOM_FEMININ 26
#define NOM_PLURIEL 27
#define NOM_MASCULIN_PLURIEL 28
#define NOM_FEMININ_PLURIEL 29
#define NOM_EPICENE 30
#define SINGULIER 31


/*; NAME : assoc_categorie ; associe str cat et int du mot
; ARGS : string cat_originale
; USAGES : assoc_categorie(cat_originale)
; GLOBALS : none
; CALL : none
; USER :  eng_cat, subdiv_esp */

la_categorie assoc_categorie(string cat_originale){

    la_categorie cat = (malloc(sizeof(struct Category)));
    string cat_dup = strdup(cat_originale);
    cat->chaine = cat_dup; /* association cat->chaîne*/
    /* définition du int de la catégorie */
    if (strcmp(cat_dup, "{n}") == 0 || strcmp(cat_dup, "{n} ") == 0) {
        cat->cat = NOUN;
    } 
    else if (strcmp(cat_dup, "{v}") == 0) {
        cat->cat = VERB;
    } 
    else if (strcmp(cat_dup, "{adj}") == 0) {
        cat->cat = ADJECTIVE;
    } 
    else if (strcmp(cat_dup, "{adv}") == 0) {
        cat->cat = ADVERB;
    } 
    else if (strcmp(cat_dup, "{interj}") == 0) {
        cat->cat = INTERJECTION;
    } 
    else if (strcmp(cat_dup, "{pron}") == 0) {
        cat->cat = PRONOUN;
    } 
    else if (strcmp(cat_dup, "{prefix}") == 0) {
        cat->cat = PREFIX;
    } 
    else if (strcmp(cat_dup, "{suffix}") == 0) {
        cat->cat = SUFFIX;
    } 
    else if (strcmp(cat_dup, "{proverb}") == 0) {
        cat->cat = PROVERB;
    } 
    else if (strcmp(cat_dup, "{prop}") == 0) {
        cat->cat = PROPER_NOUN;
    } 
    else if (strcmp(cat_dup, "{phrase}") == 0) {
        cat->cat = PHRASE;
    } 
    else if (strcmp(cat_dup, "{prep phrase}") == 0) {
        cat->cat = PREP_PHRASE;
    } 
    else if (strcmp(cat_dup, "{conj}") == 0) {
        cat->cat = CONJUNCTION;
    } 
    else if (strcmp(cat_dup, "{determiner}") == 0) {
        cat->cat = DETERMINER;
    } 
    else if (strcmp(cat_dup, "{contraction}") == 0) {
        cat->cat = CONTRACTION;
    } 
    else if (strcmp(cat_dup, "{art}") == 0) {
        cat->cat = ART;
    } 
    else if (strcmp(cat_dup, "{symbol}") == 0) {
        cat->cat = SYMBOL;
    } 
    else if (strcmp(cat_dup, "{cardinal num}") == 0) {
        cat->cat = CARDINAL_NUM;
    } 
    else if (strcmp(cat_dup, "{acronym}") == 0) {
        cat->cat = ACRONYM;
    } 
    else if (strcmp(cat_dup, "{prep}") == 0) {
        cat->cat = PREPOSITION;
    } 
    else if (strcmp(cat_dup, "{abbr}") == 0) {
        cat->cat = ABBREVIATION;
    } 
    else if (strcmp(cat_dup, "{initialism}") == 0) {
        cat->cat = INITIALISM;
    } 
    else if (strcmp(cat_dup, "{particle}") == 0) {
        cat->cat = PARTICLE;
    } 
    else if (strcmp(cat_dup, "{num}") == 0) {
        cat->cat = NUM;
    }
    else if (strcmp(cat_dup, "{m}") == 0) {
        cat->cat = NOM_MASCULIN;
    } 
    else if (strcmp(cat_dup, "{f}") == 0) {
        cat->cat = NOM_FEMININ;
    } 
    else if (strcmp(cat_dup, "{p}") == 0) {
        cat->cat = NOM_PLURIEL;
    }
    else if (strcmp(cat_dup, "{m.p}") == 0) {
        cat->cat = NOM_MASCULIN_PLURIEL;
    }
    else if (strcmp(cat_dup, "{f.p}") == 0) {
        cat->cat = NOM_FEMININ_PLURIEL;
    }
    else if (strcmp(cat_dup, "{f}{m}") == 0 || strcmp(cat_dup, "{f}/{m}") == 0 || 
    strcmp(cat_dup, "{m}{f}") == 0 || strcmp(cat_dup, "{m}/{f}") == 0){
        cat->cat = NOM_EPICENE;
    }
    else if (strcmp(cat_dup, "{s}") == 0) {
        cat->cat = SINGULIER;
    }


    return cat; /* renvoie la catégorie */
}
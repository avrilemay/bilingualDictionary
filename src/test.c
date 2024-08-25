/* # Nom ......... : test.c
# Rôle ........ : initialise les fichiers et lance les tests
# Auteur ...... : Avrile Floro 
# Version ..... : V0.1 du 17/11/23
# Licence ..... : réalisé dans le cadre du cours d'Algo 1
# Usage : compilé seulement pour réaliser les tests
# Usage : pour les tests de reconstruction > make -f makefile_tests 
#         puis > ./dictionnaire_test */


#include "sys.h"
#include "structure.h"


/*; NAME : initialisation_fichier(); init fichier en W si -DTEST
; ARGS : 
; USAGES : initialisation_fichier()
; GLOBALS : none
; CALL : none
; USER :  main */

void initialisation_fichiers(){ 
    /* initialisation des fichiers en W pour effacer les contenus précédents */
    /* fermeture */
    FILE *f_mot_anglais = fopen("mot_anglais.txt", "w");   
    fclose(f_mot_anglais);
    FILE *f_all_words_traduc_esp = fopen("all_words_traduc_esp.txt", "w"); 
    fclose(f_all_words_traduc_esp);
    FILE *f_all_trad_esp_treated = fopen("all_trad_esp_treated.txt", "w"); 
    fclose(f_all_trad_esp_treated);
    FILE *f_cat_anglais = fopen("cat_mot_anglais.txt", "w"); 
    fclose(f_cat_anglais);
    FILE *f_cat_esp = fopen("cat_mot_esp.txt", "w"); 
    fclose(f_cat_esp);
    FILE *f_reconstruction = fopen("reconstruction.txt", "w");
    fclose(f_reconstruction);
    FILE *f_anglais = fopen("tout_anglais.txt", "w");
    fclose(f_anglais);
    FILE *f_espagnol = fopen("trad_espagnol.txt", "w"); 
    fclose(f_espagnol); 
}


/*; NAME : creation_tests ; lance les tets vers fichiers en A
; ARGS : dictionnaire
; USAGES : creation_tests(dictionnaire)
; GLOBALS : none
; CALL : none
; USER :  main */

void creation_tests(une_entree dictionnaire){

    une_entree p_dico = dictionnaire; /* ptr pour pas modif orignal */
    
    while (p_dico != NULL){ 
        /* ouverture fichiers en mode append pour ajouter à chaque boucle */
        /* fermeture des fichiers */
        FILE *f_mot_anglais = fopen("mot_anglais.txt", "a");
        fprintf(f_mot_anglais, "%s\n", p_dico->anglais->mot);
        fclose(f_mot_anglais);
        FILE *f_cat_anglais = fopen("cat_mot_anglais.txt", "a"); 
        fprintf(f_cat_anglais, "%s\n", p_dico->anglais->categorie->chaine);
        fclose(f_cat_anglais);
        FILE *f_anglais = fopen("tout_anglais.txt", "a");
        fprintf(f_anglais, "%s\n", p_dico->anglais->original);
        fclose(f_anglais);
        FILE *f_reconstruction = fopen("reconstruction.txt", "a");
        fprintf(f_reconstruction, "%s", p_dico->anglais->original);
        fclose(f_reconstruction);

        trad_espagnol temp = p_dico->traduction; /* ptr pour pas altérer original */
        while(temp != NULL){ /* parcourt des trads */

            /* ouverture en mode append */
            FILE *f_all_words_traduc_esp = fopen("all_words_traduc_esp.txt", "a"); 
            FILE *f_all_trad_esp_treated = fopen("all_trad_esp_treated.txt", "a");
            FILE *f_cat_esp = fopen("cat_mot_esp.txt", "a");
            FILE *f_espagnol = fopen("trad_espagnol.txt", "a"); 
            f_reconstruction = fopen("reconstruction.txt", "a");

            /* impression dans les fichiers*/
            fprintf(f_all_words_traduc_esp, "%s\n", temp->espagnol->mot);
            fprintf(f_all_trad_esp_treated, "%s %s\n", temp->espagnol->mot, temp->espagnol->categorie->chaine);
            fprintf(f_cat_esp, "%s\n", temp->espagnol->categorie->chaine);
            fprintf(f_reconstruction, "%s", temp->espagnol->original);
            fprintf(f_espagnol, "%s", temp->espagnol->original);

            /* fermeture des fichiers */
            fclose(f_all_words_traduc_esp);
            fclose(f_all_trad_esp_treated);
            fclose(f_cat_esp);
            fclose(f_reconstruction);
            fclose(f_espagnol); 

            if (temp->cdr != NULL){
                f_reconstruction = fopen("reconstruction.txt", "a");
                f_espagnol = fopen("trad_espagnol.txt", "a");
                fprintf(f_reconstruction, ",");
                fprintf(f_espagnol, ",");
                fclose(f_reconstruction);
                fclose(f_espagnol);
            }

            temp = temp->cdr; /* parcourt des trads du dico */
        }
        if (p_dico->cdr != NULL){
        f_reconstruction = fopen("reconstruction.txt", "a");
        FILE *f_espagnol = fopen("trad_espagnol.txt", "a");
        fprintf(f_reconstruction, "\n");
        fprintf(f_espagnol, "\n");
        fclose(f_reconstruction);
        fclose(f_espagnol);
        }
        p_dico = p_dico->cdr; /* parcourt des entrées du dico */
    }
}
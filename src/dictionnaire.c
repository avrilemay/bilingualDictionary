/* # Nom ......... : dictionnaire.c
# Rôle ........ : un dictionnaire bilingue eng-esp
# Auteur ...... : Avrile Floro 
# Version ..... : V0.1 du 17/11/23
# Licence ..... : réalisé dans le cadre du cours d'Algo 1
# Usage : pour le dico bilingue > make > puis ./dictionnaire
# Usage : pour les tests de reconstruction > make -f makefile_tests 
#         puis > ./dictionnaire_test */


#include "sys.h"
#include "structure.h"


int main(int argc, char *argv[]) {
    
    # ifdef TEST /* si -DTEST on initialise les fichiers */
    initialisation_fichiers(); 
    # endif

    FILE* f_entree = NULL;
    char p_chaine[1000]; 

    /* ouverture du fichier en lecture */
    f_entree = fopen("mon_dico.txt", "r"); 

    list L = NULL ; 

if (f_entree != NULL) {
    /* mise en mémoire du dico */
    while (fgets(p_chaine, sizeof(p_chaine), f_entree)) {    
        p_chaine[strcspn(p_chaine, "\n")] = '\0'; /* on supprime le \n */
        L = cons(strdup(p_chaine), L); /* ajoute copie ligne à la liste */
    }
    fclose(f_entree);  
}

    /* inversion de la liste pour conserver l'ordre*/
    L = reverse(L); 
    /* obtention de notre dictionnaire traité */
    une_entree dictionnaire = div_eng_esp(L);

    #ifdef TEST /* si -DTEST on fait les tests */
        creation_tests(dictionnaire);

    #else /* sinon traducteur en ligne de commande */
        while (true) {
            traduction(dictionnaire);
            printf("\n");
        }
    #endif
    return 0;
}

/*; NAME : traduction ; donne l'esp d'un mot eng
; ARGS : dictionnaire
; USAGES : traduction(dictionnaire)
; GLOBALS : none
; CALL : none
; USER :  main */

void traduction(une_entree dictionnaire){

    /* on récupère la ligne entière */
    char ligne[100];
    printf("Quel mot voulez-vous traduire ?\n");
    fgets(ligne, sizeof(ligne), stdin); 

    /* traitement du mot */
    string mot = strtok(ligne, "{"); /* séparation avant le { */
    int len = strlen(mot);
    mot[len-1]='\0'; /* on supprime l'espace */

    /* traitement de la catégorie */
    string cat = strtok(NULL, "");
    if (cat == NULL){
        printf("Usage: mot_anglais {catégorie_recherchée}\n");
        return;
    }

    string categorie = malloc(strlen(cat) + 2); /*pour rajouter le { */
    categorie[0]= '\0'; /* initialisation */
    strcat(categorie, "{"); /* rajout { */
    strcat(categorie, cat); /* copie du strtok */
    int len2 = strlen(categorie); 
    categorie[len2-1]='\0'; /* suppression dernier caractère*/
    

    bool found = false;
    une_entree p_dico = dictionnaire; 
    /* utilisation copie pour pas parcour le dico original */

    while (p_dico != NULL && found ==false) { /* tant qu'il y a des mots */

        if ((strcmp(p_dico->anglais->mot, mot) == 0) && 
            (strcmp(p_dico->anglais->categorie->chaine, categorie) == 0)) {
                /* si mot et catégorie sont identiques */
            

            trad_espagnol temp = p_dico->traduction; 
            /* utilisation ptr temp pour conserver ordre original dico */

            while (temp != NULL) { /* tant qu'il y a des trad du mot */
                printf("%s %s", temp->espagnol->mot, temp->espagnol->categorie->chaine);
                /* on les imprime */
                if (temp->cdr != NULL) { /* et si ce n'est pas le dernier mot */
                    printf(", "); /* on ajoute une virgule entre les trads */
                }

                temp = temp->cdr; /* on parcourt les trads */
            }

            found = true; /* arrêt du parcourt du dico */
            printf("\n");
        }
        p_dico = p_dico->cdr; /* on parcourt les mots du dico */
    }

    if (!found){
        printf("Aucune traduction n'a été trouvée. \n");
    }
}


/*; NAME : cons ; ajout d'un élément au début d'une l
; ARGS : elt, L
; USAGES : cons(elt, L)
; GLOBALS : none
; CALL : none
; USER :  main */

list cons(void * elt, list L)
{ 
    list Cons = malloc(sizeof(struct Doublet)) ; 
    Cons->car = elt;
    Cons->cdr = L;
    
    return Cons ; 
}

/*; NAME : reverse ; inverse ordre liste
; ARGS : L
; USAGES : reverse(L)
; GLOBALS : none
; CALL : none
; USER :  main */

list reverse(list L) {
    list R = NULL; // liste vide
    while (L != NULL) {
        list temp = cdr(L); // sauvegarde du cdr de L
        cdr(L) = R; // le cdr de L pointe sur R
        R = L; // R pointe sur L
        L = temp; // L pointe sur le prochain élt de L
    }
    return R;
}


/*; NAME : div_eng_esp ; traitement données complet dico 
; ARGS : L
; USAGES : div_eng_esp(L)
; GLOBALS : none
; CALL : eng_cat, spanish 
; USER :  main */

une_entree div_eng_esp(list L)
{
    une_entree debut_dico = NULL; /* pour connecter les cdr */
    une_entree precedent = NULL;

    while (L != NULL){ /* parcourt de la liste */

        une_entree un_mot = malloc(sizeof(struct MotDictionnaire));
        string ligne = (string)(car(L)); /* mise en mémoire des lignes */

        /* division des catégories */
        /* anglais */
        string eng = strtok(ligne, "}"); /* premier token jusqu'à \} */
        /* espagnol */
        string esp = strtok(NULL, ""); /* 2e token jusqu'à la fin */

        /* traitement de l'anglais */
        string engl = malloc(strlen(eng) + 2); /* pour rajouter le } */
        strcpy(engl, eng);
        strcat(engl, "}"); /* rajout { manquant */

        /* formation entrée anglais */
        un_mot->anglais = eng_cat(engl);

        /* formation entrée traduction */
        un_mot->traduction = spanish(esp, un_mot->anglais->categorie->chaine);

        /* connexion des entrées dico via le cdr*/
        if (debut_dico == NULL) { /* si début de la liste */
            debut_dico = un_mot; /* 1er élément */
        } 
        else { /* si pas début de la liste */
            precedent->cdr = un_mot;  /* ajout à la fin de la liste */
        }
        precedent = un_mot; /* parcours des élts */
        L = cdr (L);

    }

    return debut_dico; /* renvoie le dico sous la bonne forme */
}


/*; NAME : eng_cat ; traitement données anglais
; ARGS : string english_part
; USAGES : eng_cat(english_part)
; GLOBALS : none
; CALL : assoc_categorie
; USER :  div_eng_esp */

forme_anglais eng_cat(string english_part){

    forme_anglais anglais = malloc(sizeof(struct Base));

    string original_str = strdup(english_part);

    /* traitement du mot anglais */
    string mot_anglais = strtok(english_part, "{");
    int len = strlen(mot_anglais); /* retire espace à la fin */
    mot_anglais[len-1]='\0';

    /* traitement de la catégorie anglaise */
    string cat_ang = strtok(NULL, "");
    /* travail sur les chaînes pour rajouter le { au début */
    string debut = "{";
    string cat_anglais = malloc(strlen(cat_ang)+2);
    strcpy(cat_anglais, debut);
    strcat(cat_anglais, cat_ang);

    /* remplissage des éléments de struct [anglais] */
    anglais->mot= strdup(mot_anglais);
    anglais->original = strdup(original_str);
    anglais->categorie=assoc_categorie(cat_anglais);

    return anglais; /* renvoie la struct remplie */
    }


/*; NAME : spanish ; traitement données traduction  esp
; ARGS : string esp_part, string cat
; USAGES : spanish(esp_part, cat)
; GLOBALS : none
; CALL : subdiv_esp
; USER :  div_eng_esp */

trad_espagnol spanish(string esp_part, string cat){

    trad_espagnol premiere_trad = NULL;
    trad_espagnol trad_prec = NULL;

    string token = NULL;

    string copy_esp_part = strdup(esp_part);
    char *ptr;
    token = strtok_r(copy_esp_part, ",", &ptr);
    /* strtok_r car subdiv_esp utilise aussi strtok */
    
    while (token) {
        trad_espagnol espagnol_trad = malloc(sizeof(struct Trad));
        forme_espagnol traduction = subdiv_esp(token, cat);

        espagnol_trad->espagnol= traduction;
        espagnol_trad->cdr = NULL; /* initialisation à NULL pour éviter bugs! */

        /* connexion des trads via le cdr */
        if (premiere_trad == NULL){ /* si début de liste */
            premiere_trad = espagnol_trad; /* 1er élément */
        }
        else { /* si pas début de la liste */
            trad_prec->cdr=espagnol_trad; /* ajout comme dernier élt */
        }
        trad_prec = espagnol_trad; /* parcours des élts */
        token= strtok_r(NULL, ",", &ptr); /* token suivant */
    }
    return premiere_trad; /* retour à partir du 1er élt */
}


/*; NAME : subdiv_esp ; traitement données forme esp
; ARGS : string esp_original, string cat
; USAGES : subdiv_esp(esp_original, cat)
; GLOBALS : none
; CALL : assoc_categorie
; USER :  spanish */

forme_espagnol subdiv_esp(string esp_original, string cat){

    forme_espagnol espagnol = malloc(sizeof(struct Base));
    string str_original = strdup(esp_original);
    string esp_original_copy = strdup(str_original);

    /* traitement du mot espagnol */
    string tok = strtok(esp_original_copy, "{");
    int len = strlen(tok);
    tok[len]='\0'; /*suppression espace final */
    string tok_bis = &tok[1]; /* suppression espace avant */

    /* catégorie esp est le strktok suivant */
    string tok2 = strtok(NULL, "");

    if (tok2 == NULL){ /* s'il n'y a pas de catégorie esp */
        espagnol->mot = tok_bis; /* le mot est le mot traité */
        espagnol->original = strdup(str_original); /* trace de l'original */
        espagnol->categorie = assoc_categorie(cat); 
            /* on utilise la catégorie du mot anglais */
    }

    else { /* s'il y a une catégorie du mot espagnol fournie */
        /* traitement de la catégorie */
        string cut_cat = tok2;
        int len_cut = strlen(tok_bis);
        tok_bis[len_cut-1]='\0'; /* supprimer dernier caractère */
        string ma_cat = (malloc(strlen(cut_cat)+2));
        ma_cat[0] = '\0'; /* initialisation */
        strcat(ma_cat, "{"); /* ajout du { */
        strcat(ma_cat, cut_cat); /* obtention cat complete */

        /* on effectue les associations pour espagnol */
        espagnol->mot = tok_bis;
        espagnol->original = strdup(str_original);
        espagnol->categorie = assoc_categorie(ma_cat);
    }
    return espagnol; /* on renvoie la struct formée */
}



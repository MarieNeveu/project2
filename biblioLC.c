#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num,char* titre,char* auteur){
    Livre* new_livre = (Livre*)malloc(sizeof(Livre));
    new_livre->titre = strdup(titre);
    new_livre->auteur = strdup(auteur);
    new_livre -> suiv = NULL;
    new_livre -> num = num;

    return new_livre;
}

void liberer_livre(Livre* l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio* creer_biblio(){
    Biblio* new_biblio = (Biblio*)malloc(sizeof(Biblio));
    new_biblio -> L = NULL;
    return new_biblio;
}

void liberer_biblio(Biblio* b){
    free(b);
}

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    Livre *new_livre = creer_livre(num,titre,auteur);
    new_livre -> suiv = b->L;
    b->L = new_livre;
}

void afficher_Livre(Livre* livre){
    printf("%d %s %s",livre->num,livre->titre,livre->auteur);
}

void afficher_Bibli(Biblio* bibli){
    Livre* bib = bibli->L;
    while(bib != NULL){
        afficher_Livre(bib);
        bib = bib -> suiv;
        printf("\n");
    }
}

Livre* recherche_ouvrage_num(Biblio* bibli, int num){
    Livre* bib = bibli->L;
    while(bib != NULL && bib->num != num){
        bib = bib -> suiv;
    }
    return bib;
}

Livre* recherche_ouvrage_titre(Biblio* bibli, char* titre){
    Livre* bib = bibli->L;
    while(bib != NULL && strcmp(bib->titre,titre)!=0){
        bib = bib -> suiv;
    }
    return bib;
}

Biblio* recherche_ouvrage_auteur(Biblio* bibli, char* auteur){
    Biblio* new_biblio = creer_biblio();
    Livre* bib = bibli->L;
    while(bib != NULL){
        if(strcmp(bib->auteur,auteur)==0){
            inserer_en_tete(new_biblio,bib->num,bib->titre,bib->auteur);
        }
        bib = bib -> suiv;
    }
    return new_biblio;
}

void supression_ouvrage(Biblio* bibli, int num, char* titre, char* auteur){
    Biblio* tmp = bibli;
    Livre* bib = tmp->L;

    //printf("\n%d: %d ; %s:%s ; %s:%s\n",bib->num,num,bib->auteur,auteur,bib->titre,titre);
    if(bib->num == num && strcmp(bib->auteur,auteur)==0 && strcmp(bib->titre,titre)==0){//il s'agit du premiere élément de la liste
        printf("\nSALUT\n");
        Livre* tmp2 = tmp ->L;
        tmp -> L = (tmp ->L) -> suiv;
        liberer_livre(tmp2);
    }

    else{
        while((bib->suiv)->suiv != NULL){
            if( (bib-> suiv)->num == num && strcmp((bib-> suiv)->auteur,auteur)==0 && strcmp((bib->suiv)->titre,titre)==0){
                Livre* tmp2 = bib->suiv;
                bib->suiv = bib->suiv->suiv;
                liberer_livre(tmp2);
                break;
            }
            bib = bib -> suiv;
        }

        //printf("\n%d %d: %d ; %s:%s ; %s:%s\n",(bib->suiv)->suiv == NULL,(bib->suiv)->num,num,(bib->suiv)->auteur,auteur,(bib->suiv)->titre,titre);
        if((bib-> suiv)->suiv == NULL && (bib-> suiv)->num == num && strcmp((bib-> suiv)->auteur,auteur)==0 && strcmp((bib->suiv)->titre,titre)==0){
            liberer_livre(bib->suiv);
            bib->suiv = NULL;
        }
    }  
}

Biblio* fusion_bibliotheque(Biblio* biblio1, Biblio* biblio2){
    Livre* bib1 = biblio1->L;
    Livre* bib2 = biblio2->L;
    while(bib1->suiv != NULL){
        bib1 = bib1 -> suiv;
    }
    bib1 -> suiv = bib2;

    return biblio1;
}

tableHachage_t* initTableHachage(int m) {
    tableHachage_t* tableH = (tableHachage_t*)malloc(siezof(tableHachage_t));
    tableH -> ne = 0;
    tableH -> m = m;
    tableH -> T = (cell_t**)malloc(sizeof(cell_t*)*m);
    int i;
    for (i=0,i<15,i++) {
        (tableH -> T)[i] = NULL;
    }
}

int fonctionClef(char *nom) {
    int clef = 0;
    int i;
    for(i=0,i<strlen(nom),i++) {
        clef = clef + nom[i];
    }
    return clef
}

    

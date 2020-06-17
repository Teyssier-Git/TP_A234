#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "pile.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

Arbre234 maxNoeudAbr = NULL;
Arbre234 pereGlobal = NULL;
int maxNoeudInt = INT_MIN;


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;

  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
}

int NombreCles (Arbre234 a)
{
    int n0 = 0;
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

    if (a == NULL) {
      return 0;
    }
    int t = a->t;
    if (t == 0) {
      return 0;
    }
    n0 = NombreCles (a -> fils[0]);
    n1 = NombreCles (a -> fils[1]);
    n2 = NombreCles (a -> fils[2]);
    n3 = NombreCles (a -> fils[3]);
    if (t == 2) {
        return t - 1 + n1 + n2;
    }
    if (t == 3) {
        return t - 1 + n0 + n1 + n2;
    }
    if (t == 4) {
        return t - 1 + n0 + n1 + n2 + n3;
    }
    return 0;
}

int CleMax (Arbre234 a)
{
  if (a == NULL) {
      return INT_MIN;
  }
  if (a->t == 0) {
      return INT_MIN;
  }
  if (a->t == 2 || a->t == 3) {
      return max(a->cles[1],CleMax(a->fils[2]));
  }
  if (a->t == 4) {
      return max(a->cles[2],CleMax(a->fils[3]));
  }
  return INT_MIN;
}

int CleMin (Arbre234 a)
{
    if (a == NULL) {
      return INT_MAX;
    }
    if (a->t == 0) {
      return INT_MAX;
    }

    int m0 = INT_MAX;
    int m1 = INT_MAX;

    m0 = CleMin(a->fils[0]);
    m1 = CleMin(a->fils[1]);

    if (a->t == 2) {
      return min(m1, a->cles[1]);
    }
    if (a->t == 3 || a->t == 4) {
      return min(m0, a->cles[0]);
    }

    return INT_MAX;
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  /*
     rechercher si la cle a est presente dans
     l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
  */
  if (a == NULL) {
      return NULL;
  }
  if (a->t == 0) {
      return NULL;
  }
  if (a->t == 2) {
      if (a->cles[1] == cle) {
          return a;
      }
      pereGlobal = a;
      if (cle > a->cles[1]) {
          return RechercherCle(a->fils[2],cle);
      }
      return RechercherCle(a->fils[1],cle);
  }
  if (a->t == 3) {
      if (a->cles[0] == cle || a->cles[1] == cle) {
          return a;
      }
      pereGlobal = a;
      if (cle < a->cles[0]) {
          return RechercherCle(a->fils[0],cle);
      }
      if (cle < a->cles[1]) {
          return RechercherCle(a->fils[1],cle);
      }
      return RechercherCle(a->fils[2],cle);
  }
  if (a->t == 4) {
      if (a->cles[0] == cle || a->cles[1] == cle || a->cles[2] == cle) {
          return a;
      }
      pereGlobal = a;
      if (cle < a->cles[0]) {
          return RechercherCle(a->fils[0],cle);
      }
      if (cle < a->cles[1]) {
          return RechercherCle(a->fils[1],cle);
      }
      if (cle < a->cles[2]) {
          return RechercherCle(a->fils[2],cle);
      }
      return RechercherCle(a->fils[3],cle);
  }
  return NULL ;
}

int estFeuille(Arbre234 a){
  if(a == NULL){
    return 0;
  }
  if(a->t == 0){
    return 0;
  }
  return a->fils[1]->t == 0;
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
    if(a == NULL){
      return;
    }
    if(a->t == 0){
      return;
    }
    if(a->t == 2){
      (*noeud2)++;
      if(estFeuille(a)){
        (*feuilles)++;
      } else {
        AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
        AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
    }
}
    if(a->t == 3){
      (*noeud3)++;
      if(estFeuille(a)){
        (*feuilles)++;
      } else {
        AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
        AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
        AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
      }
    }
    if(a->t == 4){
      (*noeud4)++;
      if(estFeuille(a)){
        (*feuilles)++;
      } else {
        AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
        AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
        AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
        AnalyseStructureArbre(a->fils[3], feuilles, noeud2, noeud3, noeud4);
      }
    }
}

void worker_nm (Arbre234 a) {
    if (a != NULL && a->t != 0) {
        int ajtCle = INT_MIN;
        if (a->t == 2) {
            ajtCle = a->cles[1];
            worker_nm(a->fils[1]);
            worker_nm(a->fils[2]);
        }
        if (a->t == 3) {
            ajtCle = a->cles[0] + a->cles[1];
            worker_nm(a->fils[0]);
            worker_nm(a->fils[1]);
            worker_nm(a->fils[2]);
        }
        if (a->t == 4) {
            ajtCle = a->cles[0] + a->cles[1] + a->cles[2];
            worker_nm(a->fils[0]);
            worker_nm(a->fils[1]);
            worker_nm(a->fils[2]);
            worker_nm(a->fils[3]);
        }

        if (ajtCle > maxNoeudInt) {
            maxNoeudInt = ajtCle;
            maxNoeudAbr = a;
        }
    }
}

Arbre234 noeud_max (Arbre234 a)
{
  worker_nm(a);
  return maxNoeudAbr;
}

void afficher_noeud (Arbre234 a)
{
    if (a != NULL && a->t != 0) {
        if (a->t == 2) {
            printf(" %d |",a->cles[1]);
        }
        if (a->t == 3) {
            printf(" %d | %d |",a->cles[0],a->cles[1]);
        }
        if (a->t == 4) {
            printf(" %d | %d | %d |",a->cles[0],a->cles[1],a->cles[2]);
        }
    }
}

void Afficher_Cles_Largeur (Arbre234 a)
{
    pfile_t f = creer_file();
    enfiler(f,a);
    while (!file_vide(f)) {
        Arbre234 cur = defiler(f);
        afficher_noeud(cur);

        if (cur->t == 2) {
            enfiler(f,cur->fils[1]);
            enfiler(f,cur->fils[2]);
        }
        if (cur->t == 3) {
            enfiler(f,cur->fils[0]);
            enfiler(f,cur->fils[1]);
            enfiler(f,cur->fils[2]);
        }
        if (cur->t == 4) {
            enfiler(f,cur->fils[0]);
            enfiler(f,cur->fils[1]);
            enfiler(f,cur->fils[2]);
            enfiler(f,cur->fils[3]);
        }
    }
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
    if (a!=NULL) {
        if (a->t == 2) {
            Affichage_Cles_Triees_Recursive(a->fils[1]);
            printf(" %d |",a->cles[1]);
            Affichage_Cles_Triees_Recursive(a->fils[2]);
        }
        if (a->t == 3) {
            Affichage_Cles_Triees_Recursive(a->fils[0]);
            printf(" %d |",a->cles[0]);
            Affichage_Cles_Triees_Recursive(a->fils[1]);
            printf(" %d |",a->cles[1]);
            Affichage_Cles_Triees_Recursive(a->fils[2]);
        }
        if (a->t == 4) {
            Affichage_Cles_Triees_Recursive(a->fils[0]);
            printf(" %d |",a->cles[0]);
            Affichage_Cles_Triees_Recursive(a->fils[1]);
            printf(" %d |",a->cles[1]);
            Affichage_Cles_Triees_Recursive(a->fils[2]);
            printf(" %d |",a->cles[2]);
            Affichage_Cles_Triees_Recursive(a->fils[3]);
        }
    }

}

pnoeud234 creeNoeud2Tr(int cle) {
    pnoeud234 p = allouer_noeud();
    p->t = 2;
    p->cles[1] = cle;

    return p;
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    if (a != NULL) {
        ppile_t pile = creer_pile();
        pnoeud234 noeud = a;
        empiler(pile,noeud,'n');
        while (!pile_vide(pile)) {
            struct casse cur = depiler(pile);
            if (cur.c == 't') {
                printf(" %d |", cur.n->cles[1]);
            } else {
                if (cur.n->t == 2) {
                    empiler(pile,cur.n->fils[2],'n');
                    empiler(pile,cur.n,'t');
                    empiler(pile,cur.n->fils[1],'n');
                } else if (cur.n->t == 3) {
                    empiler(pile,cur.n->fils[2],'n');
                    empiler(pile,creeNoeud2Tr(cur.n->cles[1]),'t');
                    empiler(pile,cur.n->fils[1],'n');
                    empiler(pile,creeNoeud2Tr(cur.n->cles[0]),'t');
                    empiler(pile,cur.n->fils[0],'n');
                } else if (cur.n->t == 4) {
                    empiler(pile,cur.n->fils[3],'n');
                    empiler(pile,creeNoeud2Tr(cur.n->cles[2]),'t');
                    empiler(pile,cur.n->fils[2],'n');
                    empiler(pile,creeNoeud2Tr(cur.n->cles[1]),'t');
                    empiler(pile,cur.n->fils[1],'n');
                    empiler(pile,creeNoeud2Tr(cur.n->cles[0]),'t');
                    empiler(pile,cur.n->fils[0],'n');
                }
            }
        }
    }
}

int cleAppartient(Arbre234 a, int cle) {
    if (a == NULL || a->t == 0) {
        return 0;
    }
    if (a->t == 2) {
        return a->cles[1] == cle;
    }
    if (a->t == 3) {
        return a->cles[1] == cle || a->cles[0] == cle;
    }
    if (a->t == 4) {
        return a->cles[0] == cle || a->cles[1] == cle || a->cles[2] == cle;
    }
    return 0;
}

int posCleA(Arbre234 a, int cle) {
    if (a == NULL || a->t == 0) {
        return -1;
    }
    if (a->t == 2) {
        return (a->cles[1] == cle ? 1 : -1);
    }
    if (a->t == 3) {
        return (a->cles[1] == cle ? 1 : (a->cles[0] == cle ? 0 : -1));
    }
    if (a->t == 4) {
        return (a->cles[0] == cle ? 0 : (a->cles[1] == cle ? 1 : (a->cles[2] == cle ? 2 : -1)));
    }
    return -1;
}

int trouverPos(Arbre234 a, int cle) {
    if (a == NULL || a->t == 0) {
        return -1;
    }
    if (a->t == 2) {
        return (cleAppartient(a->fils[1],cle) ? 1 : (cleAppartient(a->fils[2],cle) ? 2 : -1));
    }
    if (a->t == 3) {
        return (cleAppartient(a->fils[0],cle) ? 0 : (cleAppartient(a->fils[1],cle) ? 1 : (cleAppartient(a->fils[2],cle) ? 2 : -1)));
    }
    if (a->t == 4) {
        return (cleAppartient(a->fils[0],cle) ? 0 : (cleAppartient(a->fils[1],cle) ? 1 : (cleAppartient(a->fils[2],cle) ? 2 : (cleAppartient(a->fils[3],cle) ? 3 : -1))));
    }
    return -1;
}

void pivotPereFils(Arbre234 pere, int pos) {
    if (pos == -1) {
        return;
    }
    Arbre234 fils = pere->fils[pos];
        if (pere->t == 2) {
            if (pos == 1) {
                if (pere->fils[2]->t > 2) { //pivote
                    if (pere->fils[2]->t == 3) {
                        pere->fils[2]->t = 2;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[0];
                        return;
                    }
                    if (pere->fils[2]->t == 4) {
                        pere->fils[2]->t = 3;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[0];
                        pere->fils[2]->cles[0] = pere->fils[2]->cles[1];
                        pere->fils[2]->cles[1] = pere->fils[2]->cles[2];
                        return;
                    }
                } else { //fusionne
                    if (estFeuille(pere->fils[2])) {
                        fils->t = 0;
                        pere->t = 3;

                        pere->cles[0] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[1];

                        pere->fils[2]->t = 0;
                        return;
                    } else {
                        pere->t = 3;

                        pere->cles[0] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[1];

                        pere->fils[0] = fils;
                        pere->fils[1] = pere->fils[2]->fils[1];
                        pere->fils[2] = pere->fils[2]->fils[2];
                        return;
                    }
                }
            }
            if (pos == 2) {
                if (pere->fils[1]->t > 2) { //pivote
                    if (pere->fils[1]->t == 3) {
                        pere->fils[1]->t = 2;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[1];
                        pere->fils[1]->cles[1] = pere->fils[1]->cles[0];
                        return;
                    }
                    if (pere->fils[1]->t == 4) {
                        pere->fils[1]->t = 3;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[2];
                        return;
                    }
                } else { //fusionne
                    if (estFeuille(pere->fils[1])) {
                        fils->t = 0;
                        pere->t = 3;

                        pere->cles[0] = pere->fils[1]->cles[1];

                        pere->fils[1]->t = 0;
                        return;
                    } else {
                        pere->t = 3;

                        pere->cles[0] = pere->fils[1]->cles[1];

                        pere->fils[0] = pere->fils[1]->fils[1];
                        pere->fils[1] = pere->fils[1]->fils[2];
                        return;
                    }
                }
            }
        }
        if (pere->t == 3) {
            if (pos == 0) {
                if (pere->fils[1]->t > 2) { //pivote
                    if (pere->fils[1]->t == 3) {
                        pere->fils[1]->t = 2;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[1]->cles[0];
                        return;
                    }
                    if (pere->fils[1]->t == 4) {
                        pere->fils[1]->t = 3;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[1]->cles[0];
                        pere->fils[1]->cles[0] = pere->fils[1]->cles[1];
                        pere->fils[1]->cles[1] = pere->fils[1]->cles[2];
                        return;
                    }
                } else { //fusionne
                    if (estFeuille(pere->fils[1])) {
                        fils->t = 0;

                        pere->t = 2;
                        pere->fils[1]->cles[0] = pere->cles[0];
                        pere->fils[1]->t = 3;
                        return;
                    } else {
                        pere->t = 4;

                        pere->cles[2] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[1];

                        pere->fils[3] = pere->fils[2];
                        pere->fils[2] = pere->fils[1]->fils[2];
                        pere->fils[1] = pere->fils[1]->fils[1];
                        return;
                    }
                }
            }
            if (pos == 1) {//a faire
                if (pere->fils[2]->t > 2) { //pivote a droite
                    if (pere->fils[2]->t == 3) {
                        pere->fils[2]->t = 2;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[0];
                        return;
                    }
                    if (pere->fils[2]->t == 4) {
                        pere->fils[2]->t = 3;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[0];
                        pere->fils[2]->cles[0] = pere->fils[2]->cles[1];
                        pere->fils[2]->cles[1] = pere->fils[2]->cles[2];
                        return;
                    }
                } else if (pere->fils[0]->t > 2) { //pivote a gauche
                    if (pere->fils[0]->t == 3) {
                        pere->fils[0]->t = 2;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[0]->cles[1];
                        pere->fils[0]->cles[1] = pere->fils[0]->cles[0];
                        return;
                    }
                    if (pere->fils[0]->t == 4) {
                        pere->fils[0]->t = 3;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[0]->cles[2];
                        return;
                    }
                } else { //fusionne
                    // suppr tous les fils de cle
                    // for (int i=0; i<4; i++) {
                    //     free(pere->fils[0]->fils[i]);
                    // }
                    pere->fils[0]->t = 0;

                    pere->t = 2;
                    fils->t = 3;
                    fils->cles[1] = pere->cles[0];
                    // pere->cles[1] = pere->cles[0];
                    fils->cles[0] = pere->fils[0]->cles[1];
                    // pere->fils[1]->cles[1] = pere->fils[0]->cles[1];
                    return;
                }
            }
            if (pos == 2) {
                if (pere->fils[1]->t > 2) { //pivote
                    if (pere->fils[1]->t == 3) {
                        pere->fils[1]->t = 2;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[1];
                        pere->fils[1]->cles[1] = pere->fils[1]->cles[0];
                        return;
                    }
                    if (pere->fils[1]->t == 4) {
                        pere->fils[1]->t = 3;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[2];
                        return;
                    }
                } else { //fusionne
                    if (estFeuille(pere->fils[1])) {
                        pere->fils[1]->t = pere->fils[0]->t;
                        pere->fils[0]->t = 0;

                        fils->t = 3;
                        fils->cles[0] = pere->fils[1]->cles[1];
                        fils->cles[1] = pere->cles[1];

                        pere->t = 2;
                        pere->cles[1] = pere->cles[0];

                        pere->fils[1]->cles[0] = pere->fils[0]->cles[0];
                        pere->fils[1]->cles[1] = pere->fils[0]->cles[1];
                        pere->fils[1]->cles[2] = pere->fils[0]->cles[2];
                        return;
                    } else {
                        pere->t = 4;

                        pere->cles[2] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[1];

                        pere->fils[3] = pere->fils[2];
                        pere->fils[2] = pere->fils[1]->fils[2];
                        pere->fils[1] = pere->fils[1]->fils[1];
                        return;
                    }
                }
            }
        }
        if (pere->t == 4) {
            if (pos == 0) {
                if (pere->fils[1]->t > 2) { //pivote
                    if (pere->fils[1]->t == 3) {
                        pere->fils[1]->t = 2;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[1]->cles[0];
                        return;
                    }
                    if (pere->fils[1]->t == 4) {
                        pere->fils[1]->t = 3;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[1]->cles[0];
                        pere->fils[1]->cles[0] = pere->fils[1]->cles[1];
                        pere->fils[1]->cles[1] = pere->fils[1]->cles[2];
                        return;
                    }
                } else { //fusionne
                    if (estFeuille(pere->fils[1])) {
                        fils->t = 0;

                        pere->t = 3;
                        pere->fils[1]->t = 3;
                        pere->fils[1]->cles[0] = pere->cles[0];

                        pere->fils[0] = pere->fils[1];
                        pere->fils[1] = pere->fils[2];
                        pere->fils[2] = pere->fils[3];
                        pere->fils[3] = fils;

                        pere->cles[0] = pere->cles[1];
                        pere->cles[1] = pere->cles[2];
                        return;
                    } else {
                        pere->t = 3;
                        pere->fils[1]->t = 3;

                        pere->fils[1]->cles[0] = pere->cles[0];

                        pere->cles[0] = pere->cles[1];
                        pere->cles[1] = pere->cles[2];

                        pere->fils[1]->fils[0] = fils;

                        pere->fils[0] = pere->fils[1];
                        pere->fils[1] = pere->fils[2];
                        pere->fils[2] = pere->fils[3];
                        pere->fils[3] = allouer_noeud();
                        return;
                    }
                }
            }
            if (pos == 1) {// a faire
                if (pere->fils[2]->t > 2) { //pivote a droite
                    if (pere->fils[2]->t == 3) {
                        pere->fils[2]->t = 2;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[0];
                        return;
                    }
                    if (pere->fils[2]->t == 4) {
                        pere->fils[2]->t = 3;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[2]->cles[0];
                        pere->fils[2]->cles[0] = pere->fils[2]->cles[1];
                        pere->fils[2]->cles[1] = pere->fils[2]->cles[2];
                        return;
                    }
                } else if (pere->fils[0]->t > 2) { //pivote a gauche
                    if (pere->fils[0]->t == 3) {
                        pere->fils[0]->t = 2;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[0]->cles[1];
                        pere->fils[0]->cles[1] = pere->fils[0]->cles[0];
                        return;
                    }
                    if (pere->fils[0]->t == 4) {
                        pere->fils[0]->t = 3;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[0];
                        pere->cles[0] = pere->fils[0]->cles[2];
                        return;
                    }
                } else { //fusionne
                    // suppr tous les fils de cle
                    // for (int i=0; i<4; i++) {
                    //     free(fils->fils[i]);
                    // }
                    fils->t = 0;
                    pere->t = 3;
                    pere->fils[0]->t = 3;

                    pere->fils[0]->cles[0] = pere->fils[0]->cles[1];
                    pere->fils[0]->cles[1] = pere->cles[0];

                    pere->cles[0] = pere->cles[1];
                    pere->cles[1] = pere->cles[2];

                    pere->fils[1] = pere->fils[2];
                    pere->fils[2] = pere->fils[3];
                    pere->fils[3] = fils;
                    return;
                }
            }
            if (pos == 2) {// a faire
                if (pere->fils[3]->t > 2) { //pivote a droite
                    if (pere->fils[3]->t == 3) {
                        pere->fils[3]->t = 2;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[2];
                        pere->cles[2] = pere->fils[3]->cles[0];
                        return;
                    }
                    if (pere->fils[3]->t == 4) {
                        pere->fils[3]->t = 3;
                        // fils->t = 3;
                        // fils->cles[0] = fils->cles[1];
                        fils->cles[1] = pere->cles[2];
                        pere->cles[2] = pere->fils[3]->cles[0];
                        pere->fils[3]->cles[0] = pere->fils[3]->cles[1];
                        pere->fils[3]->cles[1] = pere->fils[3]->cles[2];
                        return;
                    }
                } else if (pere->fils[1]->t > 2) { //pivote a gauche
                    if (pere->fils[1]->t == 3) {
                        pere->fils[1]->t = 2;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[1];
                        pere->fils[1]->cles[1] = pere->fils[1]->cles[0];
                        return;
                    }
                    if (pere->fils[1]->t == 4) {
                        pere->fils[1]->t = 3;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[1];
                        pere->cles[1] = pere->fils[1]->cles[2];
                        return;
                    }
                } else { //fusionne
                    // suppr tous les fils de cle
                    // for (int i=0; i<4; i++) {
                    //     free(fils->fils[i]);
                    // }
                    fils->t = 0;
                    pere->t = 3;
                    pere->fils[3]->t = 3;

                    pere->fils[3]->cles[0] = pere->cles[2];

                    pere->fils[2] = pere->fils[3];
                    pere->fils[3] = fils;
                    return;
                }
            }
            if (pos == 3) {
                if (pere->fils[2]->t > 2) { //pivote
                    if (pere->fils[2]->t == 3) {
                        pere->fils[2]->t = 2;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[2];
                        pere->cles[2] = pere->fils[2]->cles[1];
                        pere->fils[2]->cles[1] = pere->fils[2]->cles[0];
                        return;
                    }
                    if (pere->fils[2]->t == 4) {
                        pere->fils[2]->t = 3;
                        // fils->t = 3;
                        fils->cles[1] = pere->cles[2];
                        pere->cles[2] = pere->fils[2]->cles[2];
                        return;
                    }
                } else { //fusionne
                    if (estFeuille(pere->fils[2])) {
                        fils->t = 0;

                        pere->t = 3;
                        pere->fils[2]->t = 3;
                        pere->fils[2]->cles[0] = pere->fils[2]->cles[1];
                        pere->fils[2]->cles[1] = pere->cles[3];
                        return;
                    } else {
                        pere->t = 3;
                        pere->fils[2]->t = 3;

                        pere->fils[2]->cles[0] = pere->fils[2]->cles[1];
                        pere->fils[2]->cles[1] = pere->cles[2];

                        pere->fils[2]->fils[0] = pere->fils[2]->fils[1];
                        pere->fils[2]->fils[1] = pere->fils[2]->fils[2];
                        pere->fils[2]->fils[2] = fils;

                        pere->fils[3] = allouer_noeud();
                        afficher_arbre(pere,0);
                        return;
                    }
                }
            }
        }
}

// void cleFilsàPere(Arbre234 pere, Arbre234 fils){
//
// }

void Detruire_Cle (Arbre234 a, int cle)
{
    Arbre234 b = RechercherCle(a, cle);
    if(b == NULL){
        return ;
    }
    if(b->t == 0){
        return ;
    }
    int posCle = trouverPos(pereGlobal,cle);
    int posCleFils = posCleA(b,cle);
    if (estFeuille(b)) {
        if (b->t == 3) { // Peut enlever 1 gartuit
            b->t = b->t-1;
            if (posCleFils == 1) {
                b->cles[1] = b->cles[0];
            }
            return;
        } else if (b->t == 4) { // doit changer le pere
            b->t = b->t-1;
            if (posCleFils == 0) {
                b->cles[0] = b->cles[1];
                b->cles[1] = b->cles[2];
            }
            if (posCleFils == 1) {
                b->cles[1] = b->cles[2];
            }
        } else if (b->t == 2) {
            pivotPereFils(pereGlobal, posCle);
            Detruire_Cle(pereGlobal, cle);
        }
        return ;
    } else {

    }
}




int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;
  afficher_arbre (a, 0) ;

  printf ("\n=== NombreCles ===\n");
  printf ("Nombre de cle : %d\n",NombreCles(a));

  printf("\n=== CleMax ===\n");
  printf("Cle Max : %d\n",CleMax(a));

  printf("\n=== CleMin ===\n");
  printf("Cle Min : %d\n",CleMin(a));

  printf ("\n==== RechercherCle ====\n") ;
  int n;
  scanf("%d",&n);
  afficher_arbre (RechercherCle(a,n), 0) ;

  printf("\n=== AnalyseStructureArbre ===\n");
  int feuilles = 0;
  int noeud2 = 0;
  int noeud3 = 0;
  int noeud4 = 0;
  AnalyseStructureArbre(a,&feuilles,&noeud2,&noeud3,&noeud4);
  printf("Feuilles : %d\nNoeuds 2 : %d\nNoeuds 3 : %d\nNoeuds 4 : %d\n",feuilles,noeud2,noeud3,noeud4);

  printf ("\n==== noeud_max ====\n") ;
  afficher_arbre(noeud_max(a),0);

  printf ("\n=== Afficher_Cles_Largeur ===\n") ;
  Afficher_Cles_Largeur(a);
  printf("\n");

  printf ("\n=== Affichage_Cles_Triees_Recursive ===\n") ;
  Affichage_Cles_Triees_Recursive(a);
  printf("\n");

  printf ("\n=== Affichage_Cles_Triees_NonRecursive ===\n") ;
  Affichage_Cles_Triees_NonRecursive(a);
  printf("\n");

  printf ("\n==== Detruire_Cle ====\n") ;
  printf("Give a key to delete it from the tree, -1 to stop\n");
  afficher_arbre(a,0);
  printf("\n");
  Affichage_Cles_Triees_Recursive(a);
  printf("\n");
  scanf("%d",&n);
  while (n!=-1) {
      Detruire_Cle(a,n) ;
      afficher_arbre(a,0);
      printf("\n");
      Affichage_Cles_Triees_Recursive(a);
      printf("\n");
      scanf("%d",&n);
  }
}

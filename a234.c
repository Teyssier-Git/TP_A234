#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "pile.h"
// #include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

Arbre234 maxNoeudAbr = NULL;
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
      if (cle > a->cles[1]) {
          return RechercherCle(a->fils[2],cle);
      }
      return RechercherCle(a->fils[1],cle);
  }
  if (a->t == 3) {
      if (a->cles[0] == cle || a->cles[1] == cle) {
          return a;
      }
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



void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
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
}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))


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

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  /*
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
}

Arbre234 noeud_max (Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */

  return NULL ;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /*
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */

}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /*
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

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
}

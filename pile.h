#include "a234.h"
#define MAX_PILE_SIZE   128

struct casse {
    pnoeud234 n;
    char c; /* traiter : c == 't' sinon c == 'n' */
};

typedef struct {
  int sommet ;
  struct casse Tab [MAX_PILE_SIZE] ;
} pile_t, *ppile_t ;

ppile_t creer_pile () ;

int detruire_pile (ppile_t p) ;

int pile_vide (ppile_t p) ;

int pile_pleine (ppile_t p) ;

struct casse depiler (ppile_t p)  ;

int empiler (ppile_t p, pnoeud234 pn, char c);

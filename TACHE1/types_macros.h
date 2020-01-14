/****************************************************************************** 
  declaration de differents types et macros
******************************************************************************/

#ifndef _TYPES_MACROS_H_
#define _TYPES_MACROS_H_

#include <stdio.h>
#include <stdlib.h>

/* type booleen */
typedef char bool;
#define false 0
#define true 1

/* type entier positif */
typedef unsigned int UINT;

/* macro qui affiche le message _m_ et arrete le programme */
#define ERREUR_FATALE(_m_)        \
  {                               \
    fprintf(stderr, "%s\n", _m_); \
    exit(1);                      \
  }

#endif

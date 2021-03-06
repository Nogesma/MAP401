/******************************************************************************
  Implémentation du module image_pbm
******************************************************************************/

#include "image.h"

/* création d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image createImage(UINT L, UINT H) {

  Image I;
  UINT i, j;

  I.L = L;
  I.H = H;

  /* alloctaion dynamique d'un tableau de L*H Pixel*/
  I.tab = malloc(sizeof(*I.tab) * L);
  for (i = 0; i < L; i++) {
    I.tab[i] = malloc(sizeof(Pixel) * H);
  }
  /* test si le tableau a ete correctement alloue */
  if (I.tab == (Pixel **)NULL) {
    ERREUR_FATALE("Impossible de creer une image");
  }

  /* remplir le tableau avec des pixels blancs */
  for (i = 0; i < L; ++i) {
    for (j = 0; j < H; ++j) {
      I.tab[i][j] = White;
    }
  }

  return I;
}

/* suppression de l'image I = *p_I*/
void deleteImage(Image *p_I) {
  free(p_I->tab);
  p_I->L = 0;
  p_I->H = 0;
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel getPixelOfImage(Image I, int x, int y) {
  if (x < 0 || x >= I.L || y < 0 || y >= I.H)
    return White;
  return I.tab[x][y];
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void setPixelOfImage(Image I, int x, int y, Pixel v) {
  if (x < 0 || x >= I.L || y < 0 || y >= I.H)
    return;
  I.tab[x][y] = v;
}

/* renvoie la largeur de l'image I */
UINT widthImage(Image I) { return I.L; }

/* renvoie la hauteur de l'image I */
UINT heightImage(Image I) { return I.H; }

/* teste si le fichier d'identificateur f debute par un en-tete
   valide pour un fichier PBM :
   - ligne 1 : P1
   - suivie de zero, une ou plusieurs lignes commen�ant toutes par #
   La fonction se termine correctement si le fichier est correct,
   et le pointeur de fichier se trouve � la suite l'entete.
   Sinon, l'ex�cution du programme est arretee avec l'affichage d'un message
   d'erreur (appel � ERREUR_FATALE)
    */
void entete_fichier_pbm(FILE *f) {
  char *ligne;
  size_t n;
  ssize_t l_ligne;

  /* se positionner en debut de fichier */
  fseek(f, 0, SEEK_SET);

  /* lecture et test de la ligne 1 */
  ligne = (char *)NULL;
  n = 0;
  l_ligne = getline(&ligne, &n, f);

  /* la ligne est correcte si et ssi ligne = {'P','1',0}
    soit une chaine de 3 caracteres (le dernier est le caractere nul) */
  if (l_ligne != 3) {
    ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
  }
  if ((ligne[0] != 'P') || (ligne[1] != '1')) {
    ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
  }
  free(ligne);

  /* lecture des �ventuelles lignes commen�ant par # */
  bool boucle_ligne_commentaire = true;
  do {
    /* tester d'abord la fin de fichier */
    if (feof(f)) {
      ERREUR_FATALE("entete_fichier_pbm : fin fichier inattendue\n");
    }

    /* lire un caractere et tester par rapport � '#' */
    char c;
    fscanf(f, "%c", &c);
    if (c == '#') {
      /* lire le reste de la ligne */
      ligne = (char *)NULL;
      n = 0;
      l_ligne = getline(&ligne, &n, f);
      free(ligne);
    } else {
      /* reculer d'un caract�re dans f */
      fseek(f, -1, SEEK_CUR);
      boucle_ligne_commentaire = false;
    }
  } while (boucle_ligne_commentaire);
}

/* lire l'image dans le fichier nomm� nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message */
Image readImageFile(char *fileName) {
  FILE *f;
  char *l = NULL;
  char *h = NULL;
  UINT L, H, x, y;
  int i = 0;
  char *res_fscanf = NULL;
  Image I;

  /* ouverture du fichier nom_f en lecture */
  f = fopen(fileName, "r");
  if (f == (FILE *)NULL) {
    ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
  }

  /* traitement de l'en-tete et arret en cas d'erreur */
  entete_fichier_pbm(f);
  /* lecture des dimensions - lecture de 2 entiers */
  size_t s = sizeof(UINT);
  getdelim(&l, &s, ' ', f);
  getdelim(&h, &s, '\n', f);
  L = atoi(l);
  H = atoi(h);

  /* cr�ation de l'image I de dimensions L x H */
  I = createImage(L, H);
  /* lecture des pixels du fichier - lecture caract�re par caract�re
     seuls les caracteres '0' (BLANC) ou '1' (NOIR)
     doivent etre pris en compte */
  s = L * H;
  getdelim(&res_fscanf, &s, '\0', f);
  for (y = 0; y < H; ++y) {
    for (x = 0; x < L; ++x) {
      while (res_fscanf[i] != '0' && res_fscanf[i] != '1') {
        ++i;
      }
      I.tab[x][y] = res_fscanf[i] - '0';
      ++i;
    }
  }

  /* fermeture du fichier */
  fclose(f);

  return I;
}

/* �crire l'image I � l'�cran */
void writeImage(Image I, char *fileName) {
  int x, y;
  FILE *f;
  fileName[strlen(fileName) - 4] = '\0';
  strcat(fileName, "1.pbm");
  f = fopen(fileName, "w+");

  fprintf(f, "P1\n%d %d\n", I.L, I.H);

  for (y = 0; y < I.H; ++y) {
    for (x = 0; x < I.L; ++x) {
      fprintf(f, "%d", I.tab[x][y]);
    }
    fprintf(f, "\n");
  }
  fclose(f);
  return;
}

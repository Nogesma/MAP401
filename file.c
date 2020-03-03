#include "file.h"

void writeOutlines(char *fileName, sequence s) {
  FILE *f;
  fileName[strlen(fileName) - 4] = '\0';
  strcat(fileName, ".contours");
  f = fopen(fileName, "w+");

  outline *o = newOutline();
  o = s.head;

  int size = 0;
  while (o->next != NULL) {
    ++size;
    o = o->next;
  }
  fprintf(f, "%d\n", size);

  cell *c = newCell();
  o = s.head;
  while (o->next != NULL) {
    c = o->o;

    size = 0;
    while (c->next != NULL) {
      ++size;
      c = c->next;
    }
    fprintf(f, "\n%d\n", size);

    c = o->o;
    while (c->next != NULL) {
      fprintf(f, "%.1f %.1f\n", c->p.x, c->p.y);
      c = c->next;
    }
    o = o->next;
  }
  fclose(f);
  fileName[strlen(fileName) - 5] = '\0';
}

void writeEps(char *fileName, sequence s, Image I, char *mode) {
  FILE *f;
  fileName[strlen(fileName) - 4] = '\0';
  strcat(fileName, ".eps");
  f = fopen(fileName, "w+");

  fprintf(f, "%%!PS−Adobe−3.0 EPSF−3.0\n");
  fprintf(f, "%%%%BoundingBox : 0 0 %d %d\n\n", I.L, I.H);
  fprintf(f,
          "/l {lineto} def\n/m {moveto} def\n/s {stroke} def\n/f {fill} def\n");
  fprintf(f, "0.2 setlinewidth\n\n");

  outline *o = newOutline();
  o = s.head;

  cell *c = newCell();
  while (o->next != NULL) {
    c = o->o;
    fprintf(f, "%.2f %.2f m ", c->p.x, I.H - c->p.y);
    c = c->next;

    while (c->next != NULL) {
      fprintf(f, "%.2f %.2f l ", c->p.x, I.H - c->p.y);
      c = c->next;
    }

    fprintf(f, "\n");

    if (strcmp(mode, "dots") == 0) {
      fprintf(f, "s\n\n");
      fprintf(f, "0 0 1 setrgbcolor\n\n");
      c = o->o;

      while (c->next != NULL) {
        fprintf(f, "newpath\n%.2f %.2f 0.3 0 360 arc\nf closepath\n\n", c->p.x,
                I.H - c->p.y);
        c = c->next;
      }
      fprintf(f, "0 0 0 setrgbcolor\n\n");
    }

    o = o->next;
  }

  if (strcmp(mode, "dots") != 0) {
    fprintf(f, "%s\n\n", mode);
  }

  fprintf(f, "showpage\n");

  fclose(f);
}
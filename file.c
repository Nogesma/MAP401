#include "file.h"

void writeContours(char *fileName, sequence s) {
  FILE *f;
  fileName[strlen(fileName) - 4] = '\0';
  strcat(fileName, ".contours");
  f = fopen(fileName, "w+");

  fprintf(f, "1\n\n");

  cell *c = newCell();
  c = s.head;

  int size = 0;
  while (c != NULL) {
    ++size;
    c = c->next;
  }
  fprintf(f, "%d\n", size);

  c = s.head;
  while (c != NULL) {
    fprintf(f, "%.2f %.2f\n", c->p.x, c->p.y);
    c = c->next;
  }
  fclose(f);
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

  cell *c = newCell();
  c = s.head;

  fprintf(f, "%.2f %.2f m ", c->p.x, I.H - c->p.y);
  c = c->next;

  while (c != NULL) {
    fprintf(f, "%.2f %.2f l ", c->p.x, I.H - c->p.y);
    c = c->next;
  }

  fprintf(f, "\n");

  if (strcmp(mode, "dots") == 0) {
    fprintf(f, "s\n\n");
    fprintf(f, "0 0 1 setrgbcolor\n\n");
    c = s.head;

    while (c != NULL) {
      fprintf(f, "newpath\n%.2f %.2f 0.3 0 360 arc\nf closepath\n\n", c->p.x,
              I.H - c->p.y);
      c = c->next;
    }
  } else {
    fprintf(f, "%s\n\n", mode);
  }

  fprintf(f, "showpage\n");

  fclose(f);
}
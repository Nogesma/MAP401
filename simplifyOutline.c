#include "file.h"

int main(int argc, char *argv[]) {
  int numberOfOutlines = 0, numberOfSegments = 0;
  outline *o = newOutline();
  cell *c = newCell();

  Image I = readImageFile(argv[2]);
  sequence s = getOutlines(I);

  printf("Results:\n");
  o = s.head;
  while (o != NULL) {
    c = o->o;
    ++numberOfOutlines;
    --numberOfSegments;
    while (c != NULL) {
      ++numberOfSegments;
      c = c->next;
    }
    o = o->next;
  }
  printf("Nombre de contours: %d\n", numberOfOutlines - 1);
  printf("Nombre de segments (avant simplification): %d\n",
         numberOfSegments - numberOfOutlines);

  s = simplifyOutline(s, atoi(argv[1]));

  numberOfSegments = 0;
  o = s.head;
  while (o != NULL) {
    c = o->o;
    --numberOfSegments;
    while (c != NULL) {
      ++numberOfSegments;
      c = c->next;
    }
    o = o->next;
  }
  printf("Nombre de segments (après simplification): %d\n",
         numberOfSegments - numberOfOutlines);

  writeEps(argv[2], s, I, "s");
  return 0;
}

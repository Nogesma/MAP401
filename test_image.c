#include "image.h"
#include "outline.h"
//#include "vectors.h"

int main() {
  Image I = readImageFile("caractere2.pbm");
  writeImage(I);
  // Point p = firstPixel(I);
  sequence s = outline(I);
  cell *c = newCell();
  c = s.head;
  while (c != NULL) {
    printf("%f, %f\n", c->p.x, c->p.y);
    c = c->next;
  }
  return 0;
}

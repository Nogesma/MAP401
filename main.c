#include "image.c"
#include "outline.c"

int main(int argc, char const *argv[]) {
  Image I = readImageFile("caractere2.pbm");
  writeImage(I);
  Point p = firstPixel(I);
  sequence s = outline(I);
  cell *c = newCell();
  c = s.head;
  while (c != NULL) {
    printf("%f, %f\n", c->p.x, c->p.y);
    c = c->next;
  }
  return 0;
}

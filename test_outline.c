#include "image.h"
#include "outline.h"

int main(int argc, char *argv[]) {
  Image I = readImageFile(argv[1]);
  sequence s = outline(I);
  writeSequence(argv[1], s);
  return 0;
}

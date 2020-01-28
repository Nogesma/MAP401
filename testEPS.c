#include "file.h"

int main(int argc, char *argv[]) {
  Image I = readImageFile(argv[1]);
  Image P = mask(I);
  sequence s = outline(P);
  writeEps(argv[1], s, P, argv[2]);
  return 0;
}

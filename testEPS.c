#include "file.h"

int main(int argc, char *argv[]) {
  Image I = readImageFile(argv[1]);
  sequence s = outline(I);
  writeEps(argv[1], s, I, argv[2]);
  return 0;
}

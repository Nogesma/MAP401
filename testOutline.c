#include "file.h"

int main(int argc, char *argv[]) {
  Image I = readImageFile(argv[1]);
  sequence s = getOutlines(I);
  s = simplifyOutline(s, 5);

  writeEps(argv[1], s, I, "f");
  return 0;
}

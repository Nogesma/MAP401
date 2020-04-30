#include "file.h"

int main(int argc, char *argv[]) {
  Image I = readImageFile(argv[2]);
  sequence s = getOutlines(I);
  s = simplifyOutline(s, atoi(argv[1]));

  writeEps(argv[2], s, I, "s");
  return 0;
}

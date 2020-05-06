#include "file.h"

int main(int argc, char *argv[]) {

  Image I = readImageFile(argv[2]);
  sequence s = getOutlines(I);

  simplifyOutline(s, atoi(argv[1]));

  return 0;
}

#include "image.h"
#include <string.h>

int main(int argc, char const *argv[]) {
  Image I = readImageFile("caractere2.pbm");
  writeImage(I);
  printf("\n\n\n");
  setPixelOfImage(I, 3, 1, Black);
  setPixelOfImage(I, 2, 2, Black);
  setPixelOfImage(I, 4, 2, Black);
  writeImage(I);
  return 0;
}

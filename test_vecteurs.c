#include "types_macros.h"
#include "vectors.h"

int main() {
  Point A, B, C;
  Vector U;
  A = setPoint(1.0, -3.0);
  B = setPoint(4.0, 1.0);
  C = addPoint(A, B);
  U = vectBipoint(C, A);
  printf("C: %.2f, %.2f\n", C.x, C.y);
  printf("U: %.2f, %.2f\n", U.x, U.y);
  return 0;
}

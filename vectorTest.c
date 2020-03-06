#include "vectors.h"
#include <stdio.h>

int main() {
  Point P, A, B;
  double input;

  printf("P.x: ");
  scanf("%lf", &input);
  P.x = input;
  printf("P.y: ");
  scanf("%lf", &input);
  P.y = input;
  printf("\nA.x: ");
  scanf("%lf", &input);
  A.x = input;
  printf("A.y: ");
  scanf("%lf", &input);
  A.y = input;
  printf("\nB.x: ");
  scanf("%lf", &input);
  B.x = input;
  printf("B.y: ");
  scanf("%lf", &input);
  B.y = input;

  printf("%.2f\n", pointLineDistance(P, A, B));
  return 0;
}

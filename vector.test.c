#include "vectors.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void error(int testNumber) {
  printf("Error at test %d\n", testNumber);
  exit(1);
}

int doubleEquals(double a, double b) { return fabs(a - b) < 0.001; }

int main() {
  Point P = {0, 0};
  Point A = {0, 0};
  Point B = {0, 0};

  P.y = 5;
  if (!doubleEquals(pointLineDistance(P, A, B), 5))
    error(0);

  P.x = -1;
  B.x = 2;
  if (!doubleEquals(pointLineDistance(P, A, B), 5.09902))
    error(1);

  P.x = 4;
  if (!doubleEquals(pointLineDistance(P, A, B), 5.38516))
    error(2);

  P.x = 1;
  if (!doubleEquals(pointLineDistance(P, A, B), 5))
    error(3);

  return 0;
}

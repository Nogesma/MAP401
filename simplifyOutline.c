#include "file.h"

int main(int argc, char *argv[]) {

  arrInfo A;
  A.n = 9;
  A.arr = (Point *)malloc(A.n * sizeof(Point));
  A.arr[0] = setPoint(0, 0);
  A.arr[1] = setPoint(1, 0);
  A.arr[2] = setPoint(1, 1);
  A.arr[3] = setPoint(1, 2);
  A.arr[4] = setPoint(2, 2);
  A.arr[5] = setPoint(3, 2);
  A.arr[6] = setPoint(3, 3);
  A.arr[7] = setPoint(4, 3);
  A.arr[8] = setPoint(5, 3);

  Bezier2 B = approxBezier(A, 0, A.n - 1);

  printf("%f, %f", B.c1.x, B.c1.y);
  return 0;
}

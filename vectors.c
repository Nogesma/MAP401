#include "vectors.h"
#include <math.h>
#include <stdlib.h>

Point setPoint(double x, double y) {
  Point P = {x, y};
  return P;
}

Point addPoint(Point P1, Point P2) {
  return setPoint(P1.x + P2.x, P1.y + P2.y);
}

Vector vectBipoint(Point A, Point B) {
  Vector V = {B.x - A.x, B.y - A.y};
  return V;
}

double distance(Point A, Point B) {
  return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
}

double pointLineDistance(Point P, Point A, Point B) {

  double a = P.x - A.x;
  double b = P.y - A.y;
  double c = B.x - A.x;
  double d = B.y - A.y;

  double dot = a * c + b * d;
  double len_sq = pow(c, 2) + pow(d, 2);

  double lambda = -1;
  if (len_sq != 0) {
    lambda = dot / len_sq;
  }

  if (lambda < 0) {
    return distance(P, A);
  } else if (lambda > 1) {
    return distance(P, B);
  } else {
    Point Q = {A.x + lambda * c, A.y + lambda * d};
    return distance(P, Q);
  }
}

Bezier2 approxBezier(arrInfo C, int j1, int j2) {
  Bezier2 *B = (Bezier2 *)malloc(sizeof(Bezier2));

  int n = (double)j2 - (double)j1;

  B->c0 = C.arr[j1];
  B->c2 = C.arr[j2];

  if (n == 1) {
    B->c1 = C.arr[j1];
  } else {
    Point sumOfPoints = {0, 0};

    for (int j = j1 + 1; j < j2; ++j) {
      i = j - j1;
      ti = (double)i / (double)n;
    }

    for (int i = 0; i < n; ++i) {
      sumOfPoints = addPoint(sumOfPoints, C.arr[i + j1]);
    }
    double alpha = (n * (n - 1)) / 2;
    sumOfPoints.x = sumOfPoints.x * alpha;
    sumOfPoints.y = sumOfPoints.y * alpha;

    double beta = (n * (n - 1) * (2 * n - 1) / 6);
    Point finalPoint = addPoint(B->c0, B->c2);
    finalPoint.x = finalPoint.x * beta;
    finalPoint.y = finalPoint.y * beta;
    finalPoint = addPoint(sumOfPoints, finalPoint);

    B->c1 = finalPoint;
  }
  return *B;
}

double distanceBezierPoint(Bezier2 B, Point P, int i) {

  Point C = {};

  return distance(Ci, P);
}

#include "vectors.h"
#include <math.h>

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

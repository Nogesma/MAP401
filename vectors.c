#include "vectors.h"

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

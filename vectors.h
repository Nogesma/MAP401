typedef struct Vector_ {
  double x, y;
} Vector;

typedef struct Point_ {
  double x, y;
} Point;

Point setPoint(double x, double y);

Point addPoint(Point P1, Point P2);

Vector vectBipoint(Point A, Point B);

double pointLineDistance(Point P, Point A, Point B);

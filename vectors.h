typedef struct Vector_ {
  double x, y;
} Vector;

typedef struct Point_ {
  double x, y;
} Point;

typedef struct Bezier2_ {
  Point c0, c1, c2;
} Bezier2;

typedef struct Bezier3_ {
  Point c0, c1, c2, c3;
} Bezier3;

typedef struct {
  unsigned int n;
  Point *arr;
} arrInfo;

Point setPoint(double x, double y);

Point addPoint(Point P1, Point P2);

Vector vectBipoint(Point A, Point B);

double pointLineDistance(Point P, Point A, Point B);

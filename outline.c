#include "outline.h"

Point firstPixel(Image I) {
  double i, j;
  Point P = {-1, -1};
  for (i = 0; i < I.L; ++i) {
    for (j = 0; j < I.H; ++j) {
      if (getPixelOfImage(I, i, j) == Black &&
          getPixelOfImage(I, i, j - 1) == White) {
        P.x = i;
        P.y = j;

        return P;
      }
    }
  }
  return P;
}

Orientation turnLeft(Orientation o) {
  switch (o) {
  case North:
    return West;
  case West:
    return South;
  case South:
    return East;
  default:
    return North;
  }
}

Orientation turnRight(Orientation o) {
  switch (o) {
  case North:
    return East;
  case East:
    return South;
  case South:
    return West;
  default:
    return North;
  }
}
cell *newCell() {
  cell *c;
  c = (cell *)malloc(sizeof(cell));
  return c;
}

void getLRPixel(Point p, Point *leftPixel, Point *rightPixel, Orientation o) {
  switch (o) {
  case North:
    leftPixel->x = p.x - 1;
    leftPixel->y = p.y - 1;

    rightPixel->x = p.x;
    rightPixel->y = p.y - 1;
    break;
  case West:
    leftPixel->x = p.x - 1;
    leftPixel->y = p.y;

    rightPixel->x = p.x - 1;
    rightPixel->y = p.y - 1;
    break;
  case East:
    leftPixel->x = p.x;
    leftPixel->y = p.y - 1;

    rightPixel->x = p.x;
    rightPixel->y = p.y;
    break;
  default:
    leftPixel->x = p.x;
    leftPixel->y = p.y;

    rightPixel->x = p.x - 1;
    rightPixel->y = p.y;
    break;
  }
}

Point move(Point p, Orientation o) {
  switch (o) {
  case North:
    p.y--;
    break;
  case West:
    p.x--;
    break;
  case East:
    p.x++;
    break;
  default:
    p.y++;
    break;
  }
  return p;
}
sequence outline(Image I) {
  Orientation o = East;
  Point P = firstPixel(I);
  cell *c = newCell();
  sequence s;
  s.head = c;
  outlineRec(I, P, P, c, o);
  return s;
}

void outlineRec(Image I, Point initialPosition, Point currentPosition, cell *c,
                Orientation o) {
  Point leftPixel, rightPixel;
  c->p = currentPosition;
  cell *c1 = newCell();
  c->next = c1;
  currentPosition = move(currentPosition, o);
  getLRPixel(currentPosition, &leftPixel, &rightPixel, o);
  if (getPixelOfImage(I, leftPixel.x, leftPixel.y) == Black) {
    o = turnLeft(o);
  } else if (getPixelOfImage(I, rightPixel.x, rightPixel.y) == White) {
    o = turnRight(o);
  }

  if (o == East && currentPosition.x == initialPosition.x &&
      currentPosition.y == initialPosition.y) {
    return;
  }
  outlineRec(I, initialPosition, currentPosition, c1, o);
}

#include "outline.h"

Point firstPixel(Image I) {
  double i, j;
  Point P = {-1, -1};
  for (j = 0; j < I.H; ++j) {
    for (i = 0; i < I.L; ++i) {
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
  case East:
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
  case West:
    return North;
  }
}

cell *newCell() {
  cell *c;
  c = (cell *)malloc(sizeof(cell));
  return c;
}

outline *newOutline() {
  outline *o;
  o = (outline *)malloc(sizeof(outline));
  return o;
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
  case South:
    p.y++;
    break;
  }
  return p;
}

sequence getOutlines(Image I) {
  sequence s;
  outline *ot = newOutline();
  s.head = ot;
  Image M = mask(I);
  Point P = firstPixel(M);
  while (P.x != -1 && P.y != -1) {
    cell *c = newCell();
    ot->o = c;
    Orientation o = East;
    setPixelOfImage(M, P.x, P.y, White);
    outlineRec(I, M, P, P, c, o);
    P = firstPixel(M);
    outline *otN = newOutline();
    ot->next = otN;
    ot = ot->next;
  }
  return s;
}

void outlineRec(Image I, Image M, Point initialPosition, Point currentPosition,
                cell *c, Orientation o) {
  Point leftPixel, rightPixel;
  cell *c1 = newCell();

  c->p = currentPosition;
  c->next = c1;

  if (o == East)
    setPixelOfImage(M, currentPosition.x, currentPosition.y, White);
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
  outlineRec(I, M, initialPosition, currentPosition, c1, o);
}

Image mask(Image I) {
  int x, y;
  Image P = createImage(I.L, I.H);

  for (y = 0; y < I.H; ++y) {
    for (x = 0; x < I.L; ++x) {
      if (getPixelOfImage(I, x, y) == Black &&
          getPixelOfImage(I, x, y - 1) == White) {
        P.tab[x][y] = Black;
      } else {
        P.tab[x][y] = White;
      }
    }
  }
  return P;
}

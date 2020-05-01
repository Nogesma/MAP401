#include "outline.h"

Point firstPixel(Image I) {
  short i, j;
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
  cell *c = (cell *)malloc(sizeof(cell));
  return c;
}

outline *newOutline() {
  outline *o = (outline *)malloc(sizeof(outline));
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

arrInfo outlineToArray(outline o) {
  cell *c = newCell();
  c = o.o;
  int i = 0;
  while (c != NULL) {
    ++i;
    c = c->next;
  }
  c = o.o;
  arrInfo A;
  Point *L = (Point *)malloc(i * sizeof(Point));
  A.arr = L;
  A.n = i;
  for (i = 0; i < A.n; ++i) {
    L[i] = c->p;
    c = c->next;
  }
  return A;
}

cell *arrayToOutline(arrInfo A) {
  outline *o = newOutline();
  cell *c1 = newCell();
  o->o = c1;
  for (int i = 0; i < A.n - 1; ++i) {
    cell *c2 = newCell();
    c1->p = A.arr[i];
    c1->next = c2;
    c1 = c2;
  }
  c1->p = A.arr[A.n - 1];
  return o->o;
}

// sequence simplifyOutlineBezier(sequence s, int d) {
//  outline *ot = newOutline();
//  ot = s.head;
//  while (ot != NULL) {
//    arrInfo C = outlineToArray(*ot);
//    ot->o = arrayToOutline(simplifyOutlineRec(C, 0, C.n - 1, d));
//    ot = ot->next;
//  }
//  return s;
//}

// arrInfo simplifyOutlineBezier((arrInfo C, int j1, int j2, int d) {
//  double dmax = 0, dj, ti;
//  int i, k = j1;
//  int n = j2 - j1;
//
//  B = approxBezier(C, j1, j2);
//
//  for (int j = j1 + 1; j < j2; ++j) {
//    i = j - j1;
//    ti = (double)i / (double)n;
//    dj = distancePointBezier(C.arr[j], B, ti);
//    if (dmax < dj) {
//      dmax = dj;
//      k = j;
//    }
//  }
//
//  arrInfo A;
//  A.n = 0;
//  if (dmax <= d) {
//    A.n = 1;
//    A.arr = (Bezier2 *)malloc(A.n * sizeof(Bezier2));
//    A.arr[0] = C.arr[j1];
//    A.arr[1] = C.arr[j2];
//  } else {
//    arrInfo A1 = simplifyOutlineBezierRec(C, j1, k, d);
//    arrInfo A2 = simplifyOutlineBezierRec(C, k, j2, d);
//
//    A.n = A1.n + A2.n - 1;
//    A.arr = (Bezier2 *)malloc(A.n * sizeof(Bezier2));
//    for (int i = 0; i < A.n; ++i) {
//      if (i < A1.n)
//        A.arr[i] = A1.arr[i];
//      else
//        A.arr[i] = A2.arr[i - A1.n + 1];
//    }
//  }
//  return A;
//
//}
#include "image.h"
#include "vectors.h"

typedef enum { North, East, South, West } Orientation;

typedef struct cells {
  Point p;
  struct cells *next;
} cell;

typedef struct sequences {
  cell *head;
} sequence;
cell *newCell();

Point firstPixel(Image I);

Orientation turnLeft(Orientation o);

Orientation turnRight(Orientation o);

void getLRPixel(Point p, Point *leftPixel, Point *rightPixel, Orientation o);

Point move(Point p, Orientation o);

sequence outline(Image I);

void outlineRec(Image I, Point initialPosition, Point currentPosition, cell *c,
                Orientation o);

void writeSequence(char *fileName, sequence s);

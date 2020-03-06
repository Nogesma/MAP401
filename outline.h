#include "image.h"
#include "vectors.h"

typedef enum { North, East, South, West } Orientation;

typedef struct cells {
  Point p;
  struct cells *next;
} cell;

typedef struct outlines {
  cell *o;
  struct outlines *next;
} outline;

typedef struct sequences {
  outline *head;
} sequence;

typedef struct lists {
  struct list *next;
  Point p[];
} list;

cell *newCell();

outline *newOutline();

Point firstPixel(Image I);

Orientation turnLeft(Orientation o);

Orientation turnRight(Orientation o);

void getLRPixel(Point p, Point *leftPixel, Point *rightPixel, Orientation o);

Point move(Point p, Orientation o);

sequence getOutlines(Image I);

void outlineRec(Image I, Image M, Point initialPosition, Point currentPosition,
                cell *c, Orientation o);

Image mask(Image I);
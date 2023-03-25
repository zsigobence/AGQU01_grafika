#include <SDL2/SDL.h>
#ifndef LINE_H
#define LINE_H



typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
} Line;

void set_startingpoint(Line* line,int x ,int y);

void set_endingpoint(Line* line,int x,int y);




#endif

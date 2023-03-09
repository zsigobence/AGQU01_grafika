#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct Brick{
    int a;
    int b;
    int c;
}Brick;

void set_size(Brick* brick,int a,int b,int c);

float calc_volume(Brick* brick);

float calc_surface(Brick* brick);


#endif
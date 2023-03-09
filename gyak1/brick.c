#include "brick.h"
#include <math.h>


void set_size(Brick* brick,int a,int b,int c){
    if(a >= 0){
    brick->a = a;
    }else{
        brick->a = NAN;
    }
    if(b >= 0){
    brick->b = b;
    }else{
        brick->b = NAN;
    }
    if(c >= 0){
    brick->c = c;
    }else{
        brick->c = NAN;
    }
}

float calc_volume(Brick* brick){
    float volume = brick->a * brick->b * brick->c;
    return volume;
}

float calc_surface(Brick* brick){
    float surface = (brick->a * brick->b + brick->a * brick->c + brick->b * brick->c) * 2;
    return surface;
}
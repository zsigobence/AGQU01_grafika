#include <stdio.h>
#include "brick.h"

int main(){
    Brick brick;
    set_size(&brick,2,3,4);
    printf("terfogat: %f\n",calc_volume(&brick));
    printf("felszin: %f\n",calc_surface(&brick));
    return 0;
}
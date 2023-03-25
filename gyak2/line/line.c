#include <SDL2/SDL.h>

#include <stdio.h>
#include <windows.h>
#include "line.h"
#include <stdbool.h>

void set_startingpoint(Line* line,int x ,int y){
    line->start.x = x;
    line->start.y = y;
}

void set_endingpoint(Line* line,int x,int y){
    line->end.x = x;
    line->end.y = y;
}

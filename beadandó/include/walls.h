#ifndef WALLS_H
#define WALLS_H

#include "utils.h"
#include "texture.h"
#include <math.h>
#include <stdbool.h>

typedef struct Wall
{
    vec3 position_a;
    vec3 position_b;
    vec3 position_c;
    vec3 position_d;
    GLuint texture_id;
    bool is_open;
}Wall;

/**
 * Initialize the track by set the walls.
 */
void init_track(Wall* wall);

/**
 * Render the wall objects.
 */
void render_walls(const Wall* wall);

/*
* Allow other methods to access the walls data
*/
Wall get_wall_datas(const Wall* wall,int i);


#endif
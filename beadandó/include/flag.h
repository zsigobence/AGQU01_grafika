#ifndef FLAG_H
#define FLAG_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Flag
{
    Model model;
    GLuint texture_id;
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Flag;

/**
 * Initialize the flag by loading model.
 */
void init_flag(Flag* flag);

/**
 * Render the flag object.
 */
void render_flag(const Flag* flag);

/**
 * Makes the flag moving up and down.
 */
void flag_movement(Flag* flag,double time);

#endif /* FLAG_H */

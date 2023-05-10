#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "flag.h"
#include "walls.h"
#include <SDL2/SDL.h>
#include "camera.h"

#include <obj/model.h>

typedef struct Scene
{
    float light;
    Camera camera;
    Material material;
    Flag flag;
    Wall wall[14];
    GLuint floor_texture_id;
    int fogenable;
    int showhelp;
    int game_end;
    double cursorpos;
} Scene;

typedef struct Rect
{
    float x;
    float y;
    float w;
    float h;
} Rect;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float x);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene,double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);


/**
 * Render the floor of the scene.
 */
void render_floor(const Scene* scene);


/**
 * .
 */
void collision_detection(Scene* scene);

bool has_intersection(const Rect * A, const Rect * B);

void help_menu(Scene *scene);

void end_game(Scene *scene);


#endif /* SCENE_H */

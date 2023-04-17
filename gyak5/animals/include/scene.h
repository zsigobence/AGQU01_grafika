#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model hat_model;
    Model duck_model;
    Material material;
    GLuint hat_texture_id;
    GLuint duck_texture_id;
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene,double time);
void set_scene_rotationx(Scene* scene,double speed);
void set_scene_rotationy(Scene* scene,double speed);
void set_scene_rotationz(Scene* scene,double speed);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */

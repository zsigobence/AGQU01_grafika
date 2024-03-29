#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    scene->position.x = 0.0;
    scene->position.y = 0.0;
    scene->position.z = 0.0;
    scene->rotation.x = 0.0;
    scene->rotation.y = 0.0;
    scene->rotation.z = 0.0;
    scene->speed.x = 0.0;
    scene->speed.y = 0.0;
    scene->speed.z = 0.0;
    load_model(&(scene->duck_model), "assets/models/duck.obj");
    scene->duck_texture_id = load_texture("assets/textures/duck.jpg");

    load_model(&(scene->hat_model), "assets/models/hat.obj");
    scene->hat_texture_id = load_texture("assets/textures/hat.png");

    scene->grass_texture_id = load_texture("assets/textures/grass.jpg");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 10.0;
    scene->grass_offset = 0;
    scene->grass_speed = 1;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 5.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene,double time)
{
    scene->rotation.x += scene->speed.x * time;
    scene->rotation.y += scene->speed.y * time;
    scene->rotation.z += scene->speed.z * time;
    scene->grass_offset += scene->grass_speed * time;
}

void set_scene_rotationx(Scene* scene,double speed){
    scene->speed.x = speed;
}

void set_scene_rotationy(Scene* scene,double speed){
    scene->speed.y = speed;
}

void set_scene_rotationz(Scene* scene,double speed){
    scene->speed.z = speed;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    
 glPushMatrix();
    glTranslatef(scene->position.x, scene->position.y, scene->position.z); 
    glRotatef(scene->rotation.x, 1.0, 0.0, 0.0); 
    glRotatef(scene->rotation.y, 0.0, 1.0, 0.0); 
    glRotatef(scene->rotation.z, 0.0, 0.0, 1.0); 


    glBindTexture(GL_TEXTURE_2D, scene->duck_texture_id);
    draw_model(&(scene->duck_model));
    

    glBindTexture(GL_TEXTURE_2D, scene->hat_texture_id);
    draw_model(&(scene->hat_model));
     glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, scene->grass_texture_id);
    draw_grass(scene);
   
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_grass(const Scene* scene)
{
    int size = 100; 
    double square_size = 0.5; 
     glPushMatrix();
    glTranslatef(-(size*square_size)/2 ,-(size*square_size)/2, 0);
    glBegin(GL_QUADS); 
    glBindTexture(GL_TEXTURE_2D, scene->grass_texture_id);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            glTexCoord2f(0.0 + scene->grass_offset, 0.0 + scene->grass_offset);
            glVertex3f(i * square_size, j * square_size, 0);
            glTexCoord2f(1.0 + scene->grass_offset, 0.0 + scene->grass_offset);
            glVertex3f((i + 1) * square_size, j * square_size, 0);
            glTexCoord2f(1.0 + scene->grass_offset, 1.0 + scene->grass_offset);
            glVertex3f((i + 1) * square_size, (j + 1) * square_size, 0);
            glTexCoord2f(0.0 + scene->grass_offset, 1.0 + scene->grass_offset);
            glVertex3f(i * square_size, (j + 1) * square_size, 0);
        }
    }
    glEnd();
     glPopMatrix();
}
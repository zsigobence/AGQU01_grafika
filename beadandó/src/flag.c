#include "flag.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_flag(Flag* flag){
    flag->position.x = -1.2;
    flag->position.y = -1.0;
    flag->position.z = 0.29;
    flag->rotation.x = 1.0;
    flag->rotation.y = 0.0;
    flag->rotation.z = 0.0;
    flag->speed.x = 0.0;
    flag->speed.y = 0.0;
    flag->speed.z = 0.0;

    load_model(&(flag->model), "assets/models/flag.obj");
    flag->texture_id = load_texture("assets/textures/flag.jpg");

}

void render_flag(const Flag* flag){
glPushMatrix();
    glTranslatef(flag->position.x, flag->position.y, flag->position.z);
    glScalef(0.15f, 0.15f, 0.15f);
    glRotatef(180,0.0f, 0.0f ,1.0f);
    glBindTexture(GL_TEXTURE_2D, flag->texture_id);
    draw_model(&(flag->model));
    
    glPopMatrix();
}

void flag_movement(Flag* flag,double time){
    glPushMatrix();
    double current_time = (double)SDL_GetTicks() / 1000;
    flag->position.z += flag->speed.z * time;
    flag->position.z = sin(current_time) * 0.2 + 0.4;
    flag->rotation.x += flag->rotation.x * time; 
    glRotatef(-(flag->rotation.x + 90), 1, 0, 0.0);

    glPopMatrix();
}
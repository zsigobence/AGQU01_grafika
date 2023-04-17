#include "ball.h"
#include "texture.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 200;
    ball->speed_y = 200;
    ball->acceleration = 1;
    ball->is_moving = false;
    ball->rotation_angle = 0;
    ball->texture_id = load_texture("assets/textures/texture.jpg");
}



void update_ball_speed(Ball* ball,float acc){
    ball->acceleration *= acc;
}

void change_ball_size(Ball* ball,float size){
    if((ball->radius + size < 200) && (ball->radius + size > -200)){
        ball->radius += size;
    }
}

void update_ball_moving(Ball*ball,bool is_it){
    ball->is_moving = is_it;
}


void update_ball(Ball* ball, double time)
{
    ball->x += (ball->speed_x * ball->acceleration) * time;
    ball->y += (ball->speed_y * ball->acceleration)  * time;
}



void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;
    
    
 glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation_angle, 0.0, 0.0, 1.0); // A labda forgatása a saját tengelye körül
    glTranslatef(-ball->x, -ball->y, 0.0);


    
    glTranslatef(ball->x, ball->y, 0.0);
    glBindTexture(GL_TEXTURE_2D, ball->texture_id);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glTexCoord2f(0.5, 0.5);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glTexCoord2f((x/ball->radius+1)/2, (y/ball->radius+1)/2);
        glVertex2f(x, y);
        angle += 0.8;
       
    }
    
    glEnd();
    
    glPopMatrix();

    if (ball->rotation_angle >= 0 ) {
        ball->rotation_angle += 0.3;
    }
    if (ball->rotation_angle < 0 ) {
        ball->rotation_angle -= 0.3;
    }
    
    if (ball->rotation_angle > 360.0 ) {
        ball->rotation_angle = 0;
    }
    if(ball->rotation_angle < -360.0){
        ball->rotation_angle = -0.01;
    }
}

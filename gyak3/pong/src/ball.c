#include "ball.h"

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
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
        glMatrixMode(GL_MODELVIEW);
    glRotatef(60,0,1,0);
    }
    
    glEnd();
    
    glPopMatrix();
}

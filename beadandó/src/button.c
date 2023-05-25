#include "button.h"



void init_button(Button* button){
    button->numParticles = 600;
    initParticles(button);
}


void render_button(const Button* button){
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.7f, -0.7f, 0.001f);
    glVertex3f(1.3f, -0.7f, 0.001f);
    glVertex3f(1.3f, -1.3f, 0.001f);
    glVertex3f(0.7f, -1.3f, 0.001f);
    glEnd();
glPopMatrix();
drawParticles(button);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}

void initParticles(Button* button) {
    int i;
    for (i = 0; i < button->numParticles; i++) {
        button->particles[i].position[0] = 1;
        button->particles[i].position[1] = -1 ;
        button->particles[i].position[2] = 0.002;

        button->particles[i].speed[0] = (float)(rand() % 200 - 100) / 70000.0f;
        button->particles[i].speed[1] = (float)(rand() % 200 - 100) / 70000.0f;

        button->particles[i].color[0] = 1.0;
        button->particles[i].color[1] = (float)(rand() % 100) / 200;
        button->particles[i].color[2] = 0.001;
    }
}

void updateParticles(Button* button) {
    int i;
    for (i = 0; i < button->numParticles; i++) {
        button->particles[i].position[0] += button->particles[i].speed[0];
        button->particles[i].position[1] -= button->particles[i].speed[1];
        

         
        if (button->particles[i].position[1] < -1.3) {
            button->particles[i].position[0] = 1;
            button->particles[i].position[1] = -1;
        }
        if (button->particles[i].position[1] > -0.7) {
            button->particles[i].position[0] = 1;
            button->particles[i].position[1] = -1;
        }
        if (button->particles[i].position[0] < 0.7) {
            button->particles[i].position[0] = 1;
            button->particles[i].position[1] = -1;
        }
        if (button->particles[i].position[0] > 1.3) {
            button->particles[i].position[0] = 1;
            button->particles[i].position[1] = -1;
        }
    }
}


void drawParticles(const Button* button) {
    glPointSize(9.0f);
     glBegin(GL_POINTS);
    for (int i = 0; i < button->numParticles; i++) {
        glColor3fv(button->particles[i].color);
        glVertex3fv(button->particles[i].position);
    }
    glEnd();
}

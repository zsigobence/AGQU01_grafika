#ifndef BUTTON_H
#define BUTTON
#include <GL/gl.h>
#include <stdlib.h>
typedef struct {
    float position[3];
    float speed[3];
    float color[3];
} Particle;

typedef struct{
    Particle particles[600];
    int numParticles;
}Button;

void init_button(Button* button);
void initParticles(Button* button) ;
void updateParticles(Button* button);
void drawParticles(const Button* button);
void render_button(const Button* button);



#endif
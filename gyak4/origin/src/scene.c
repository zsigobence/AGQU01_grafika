#include "scene.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

void init_scene(Scene* scene)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // háttérszín beállítása
    glEnable(GL_DEPTH_TEST); // mélységteszt bekapcsolása
    
}

void update_scene(Scene* scene)
{
    // Az idő alapján számoljuk ki a forgatási szöget
    static float angle = 0.0f;
    angle += 0.01f;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }

    glMatrixMode(GL_MODELVIEW); // Aktív mátrix beállítása
    glLoadIdentity(); // Az aktív mátrix nullra állítása
    glRotatef(angle, 1.0f, 1.0f, 0.0f); // Forgatás
    
    render_scene(scene);
}

void render_scene(const Scene* scene)
{
   
    draw_triangle();
    draw_origin();
    draw_sphere();
    draw_chessboard();
    
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

void draw_triangle(){
   glBegin(GL_TRIANGLES);

    // Sárga csúcs
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    // Cián csúcs
    glColor3f(0, 1, 1);
    glVertex3f(1, 0, 0);
    // Magenta csúcs
    glColor3f(1, 0, 1);
    glVertex3f(0, 1, 0);

    // Sárga csúcs
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    // Magenta csúcs
    glColor3f(1, 0, 1);
    glVertex3f(0, 1, 0);
    // Kék csúcs
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 1);

    // Sárga csúcs
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    // Kék csúcs
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 1);
    // Cián csúcs
    glColor3f(0, 1, 1);
    glVertex3f(1, 0, 0);

    // Sárga csúcs
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    // Cián csúcs
    glColor3f(0, 1, 1);
    glVertex3f(1, 0, 0);
    // Magenta csúcs
    glColor3f(1, 0, 1);
    glVertex3f(0, 1, 0);

    glEnd();
}

void draw_sphere()
{
 glPushMatrix(); 
    glTranslatef(0.5f, 0.5f, 0.5f); 
    static float angle = 0.0f;
    angle += 0.01f;
    glRotatef(angle, 1.0f, 1.0f, 0.0f); 
    
    float colors[4][3] = { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f} };
    
    
    int segs = 20; 
    int rgs = 20;
    float radius = 0.2;
    
    for(int j = 0; j < segs; j++) {
        float v0 = (float)j/(float)segs;
        float v1 = (float)(j+1)/(float)segs;
        
        glBegin(GL_TRIANGLE_STRIP);
        
        for(int i = 0; i <= rgs; i++) {
            float u = (float)i/(float)rgs;
            
            float c0[3], c1[3];
            for(int k = 0; k < 3; k++) {
                c0[k] = colors[j][k];
                c1[k] = colors[j+1][k];
            }
            
            float color[3];
            for(int k = 0; k < 3; k++) {
                color[k] = c0[k]*(1.0-u) + c1[k]*u;
            }
            
            glColor3fv(color);
            
            float x = radius * cos(u*2*M_PI) * sin(v1*M_PI);
            float y = radius * sin(u*2*M_PI) * sin(v1*M_PI);
            float z = radius * cos(v1*M_PI);
            glVertex3f(x, y, z);
            
            x = radius * cos(u*2*M_PI) * sin(v0*M_PI);
            y = radius * sin(u*2*M_PI) * sin(v0*M_PI);
            z = radius * cos(v0*M_PI);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    
    glPopMatrix();
}

void draw_chessboard()
{
    int size = 8; // sakktábla mérete
    double square_size = 0.125; // egy mező mérete

    glBegin(GL_QUADS); // négyszögek rajzolása
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i + j) % 2 == 0) { // fehér mező
                glColor3f(1.0f, 1.0f, 1.0f);
            }
            else { // fekete mező
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            glVertex3f(i * square_size, j * square_size, 0);
            glVertex3f((i + 1) * square_size, j * square_size, 0);
            glVertex3f((i + 1) * square_size, (j + 1) * square_size, 0);
            glVertex3f(i * square_size, (j + 1) * square_size, 0);
        }
    }
    glEnd();
}



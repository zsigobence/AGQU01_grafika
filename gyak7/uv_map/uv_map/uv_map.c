#include "model.h"

#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include <stdio.h>

#define VIEWPORT_RATIO (4.0 / 3.0)

struct Model model;

typedef GLubyte Pixel[3];

struct Color
{
	float red;
	float green;
	float blue;
};

struct Color wire_color;

void draw_texture()
{
    glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3d(0, 0, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3d(0, 1, 0);

	glTexCoord2f(1.0, 1.0);
	glVertex3d(1, 1, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3d(1, 0, 0.0);

    glEnd();
}

void draw_wire(const struct Model* model, const struct Color* color)
{
    int i, k;
    int texture_index;
    double u, v;

    glDisable(GL_TEXTURE_2D);
    glColor3f(color->red, color->green, color->blue);
    for (i = 0; i < model->n_triangles; ++i) {
    	glBegin(GL_LINES);
        for (k = 0; k < 3; ++k) {
            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glVertex3d(u, -1 - v, 0.01);
        }
        glEnd();
    }
    glEnable(GL_TEXTURE_2D);
}

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename, Pixel* image)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

    return texture_name;
}

void initialize_texture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    char texture_filename[] = "raptor.png";

    int width;
    int height;

    unsigned char* image = SOIL_load_image(texture_filename, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
            (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	draw_texture();
	draw_wire(&model, &wire_color);

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport (x, y, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2, 2, 1.5, -1.5);
}

void mouseHandler(int button, int state, int x, int y)
{
}

void motionHandler(int x, int y)
{
    glutPostRedisplay();
}

void idle()
{
}

void initialize()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    initialize_texture();
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    load_model("raptor.obj", &model);
    print_bounding_box(&model);

    wire_color.red = 1.0;
    wire_color.green = 0.0;
    wire_color.blue = 0.0;

    glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	int window = glutCreateWindow("GLUT Window");
	glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}

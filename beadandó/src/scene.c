#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <Windows.h>

void init_scene(Scene* scene)
{   
    scene->cursorpos = 0.0;
    scene->game_end = 0;
    scene->light = 1.0f;
    scene->floor_texture_id = load_texture("assets/textures/floor.jpg");
    init_flag(&(scene->flag));
    init_track(scene->wall);
    scene->material.ambient.red = 0.1;
    scene->material.ambient.green = 0.1;
    scene->material.ambient.blue = 0.1;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.5;
    scene->material.specular.green = 0.5;
    scene->material.specular.blue = 0.5;

    scene->material.shininess = 100.0;
    
    scene->fogenable = 0;
    scene->showhelp = 0;
    scene->numParticles = 300;
    initParticles(scene);
    
}

void set_lighting(float x)
{
    float ambient_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float diffuse_light[] = { x, x, x, 1.0f };
    float specular_light[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    float position[] = { 2.75f, -3.5f, 10.0f, 1.0f };

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
    
    flag_movement(&(scene->flag),time);
    collision_detection(scene);
    updateParticles(scene);
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene->light);
    render_floor(scene);
    render_flag(&(scene->flag));
    render_walls(scene->wall);
    
    render_button();
    render_roof();
    drawParticles(scene);
    
    
}

void render_floor(const Scene* scene){
glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->floor_texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_QUADS);
    glTexCoord2f(5.0,0.0);
   glVertex3f(-1.0, 0.5, 0.0);
   glTexCoord2f(5.0,5.0);
   glVertex3f(6.5, 0.5, 0.0);
   glTexCoord2f(0.0,5.0);
   glVertex3f(6.5, -3.5, 0.0);
   glTexCoord2f(0.0,0.0);
   glVertex3f(-1.0 , -3.5, 0.0);
   glEnd();
glPopMatrix();
}

void render_roof(){
    glDisable(GL_TEXTURE_2D);
glPushMatrix();
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    glBegin(GL_QUADS);
   glVertex3f(-1.0, 0.5, 1.0);
   glVertex3f(6.5, 0.5, 1.0);
   glVertex3f(6.5, -3.5, 1.0);
   glVertex3f(-1.0 , -3.5, 1.0);
   glEnd();
glPopMatrix();
glEnable(GL_TEXTURE_2D);
}

void render_button(){
    glDisable(GL_TEXTURE_2D);
glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.7f, -0.7f, 0.001f);
    glVertex3f(1.3f, -0.7f, 0.001f);
    glVertex3f(1.3f, -1.3f, 0.001f);
    glVertex3f(0.7f, -1.3f, 0.001f);
    glEnd();
glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void collision_detection(Scene* scene){
    Rect wall[15];
    Rect camera = {scene->camera.position.x - 0.1,scene->camera.position.y - 0.1,0.1,0.2};
    Wall walls;
    Rect flag = {scene->flag.position.x + 0.1,scene->flag.position.y + 0.3,0.2,0.6};
    Rect button = {0.6 , -0.8 , 0.5 , 0.5};
    for(int i = 0;i < 15;i++){
    walls = get_wall_datas(scene->wall,i);
    wall[i].x = walls.position_a.x;
    wall[i].y = walls.position_a.y;
    wall[i].w = fabs(walls.position_d.x - walls.position_a.x) ;
    wall[i].h = fabs(walls.position_d.y - walls.position_a.y) ;
    }

    for(int i = 0;i < 15;i++){
        if(scene->wall->is_open && i==14){
            continue;
        }
        if(has_intersection(&wall[i],&camera)){
            if(scene->camera.speed.y > 0){
                set_camera_speed(&(scene->camera),0);
                scene->camera.position.x -= cos(degree_to_radian(scene->camera.rotation.z)) * 0.01;
                scene->camera.position.y -= sin(degree_to_radian(scene->camera.rotation.z)) * 0.01;
                
            }
            if(scene->camera.speed.x > 0){
                set_camera_side_speed(&(scene->camera),0);
                scene->camera.position.x -= cos(degree_to_radian(scene->camera.rotation.z + 90.0)) * 0.01;
                scene->camera.position.y -= sin(degree_to_radian(scene->camera.rotation.z + 90.0)) * 0.01;
                
            }
            if(scene->camera.speed.y < 0){
                set_camera_speed(&(scene->camera),0);
                scene->camera.position.x += cos(degree_to_radian(scene->camera.rotation.z)) * 0.01;
                scene->camera.position.y += sin(degree_to_radian(scene->camera.rotation.z)) * 0.01;
                
            }
            if(scene->camera.speed.x < 0){
                set_camera_side_speed(&(scene->camera),0);
                scene->camera.position.x += cos(degree_to_radian(scene->camera.rotation.z + 90.0)) * 0.01;
                scene->camera.position.y += sin(degree_to_radian(scene->camera.rotation.z + 90.0)) * 0.01;
                
            }
        }
    }
    if(has_intersection(&flag,&camera)){
        scene->game_end = 1;
    }
    if(has_intersection(&button,&camera)){
        scene->wall->is_open = true;
    }
    
}


bool has_intersection(const Rect * A, const Rect * B){
    if (B->x + B->w <= A->x) {
        return false;
    }
    if (B->x >= A->x + A->w) {
        return false;
    }
    if (B->y + B->h<= A->y - A->h) {
        return false;
    }
    if (B->y >= A->y) {
        return false;
    }
    return true;
}


void help_menu(Scene *scene)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("assets/textures/help.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(0.5f,0.5f,1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-1.6, -1.2, -3);
    glTexCoord2f(1, 0);
    glVertex3d(1.6, -1.2, -3);
    glTexCoord2f(1, 1);
    glVertex3d(1.6, -1.15, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-1.6, -1.15, -3);
    glEnd();

    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-0.05 + scene->cursorpos, -1.2, -3);
    glTexCoord2f(1, 0);
    glVertex3d(0.05 + scene->cursorpos, -1.2, -3);
    glTexCoord2f(1, 1);
    glVertex3d(0.05 + scene->cursorpos, -1.15, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-0.05 + scene->cursorpos, -1.15, -3);
    glEnd();

    glEnable(GL_TEXTURE_2D);

    if (scene->fogenable == 1)
        glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void end_game(Scene *scene)
{   
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("assets/textures/end.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();
    if (scene->fogenable == 1)
        glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void initParticles(Scene *scene) {
    int i;
    for (i = 0; i < scene->numParticles; i++) {
        scene->particles[i].position[0] = 1;
        scene->particles[i].position[1] = -1 ;
        scene->particles[i].position[2] = 0.002;

        scene->particles[i].speed[0] = (float)(rand() % 200 - 100) / 70000.0f;
        scene->particles[i].speed[1] = (float)(rand() % 200 - 100) / 70000.0f;

        scene->particles[i].color[0] = 1.0;
        scene->particles[i].color[1] = (float)(rand() % 100) / 200;
        scene->particles[i].color[2] = 0.001;
    }
}

void updateParticles(Scene *scene) {
    int i;
    for (i = 0; i < scene->numParticles; i++) {
        scene->particles[i].position[0] += scene->particles[i].speed[0];
        scene->particles[i].position[1] -= scene->particles[i].speed[1];
        

         
        if (scene->particles[i].position[1] < -1.3) {
            scene->particles[i].position[0] = 1;
            scene->particles[i].position[1] = -1;
        }
        if (scene->particles[i].position[1] > -0.7) {
            scene->particles[i].position[0] = 1;
            scene->particles[i].position[1] = -1;
        }
        if (scene->particles[i].position[0] < 0.7) {
            scene->particles[i].position[0] = 1;
            scene->particles[i].position[1] = -1;
        }
        if (scene->particles[i].position[0] > 1.3) {
            scene->particles[i].position[0] = 1;
            scene->particles[i].position[1] = -1;
        }
    }
}


void drawParticles(const Scene *scene) {
    
    glPointSize(9.0f);
     glBegin(GL_POINTS);
    for (int i = 0; i < scene->numParticles; i++) {
        glColor3fv(scene->particles[i].color);
        glVertex3fv(scene->particles[i].position);
    }
    glEnd();
}

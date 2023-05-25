#include "walls.h"

void init_track(Wall* wall){
    wall->texture_id = load_texture("assets/textures/cool.webp");
    wall->is_open = false;
    wall[0].position_a.x = -1.0;
    wall[0].position_a.y = 0.5;
    wall[0].position_a.z = 0.0;
    wall[0].position_b.x = -1.0;
    wall[0].position_b.y = 0.5;
    wall[0].position_b.z = 1.0;
    wall[0].position_c.x = 6.5;
    wall[0].position_c.y = 0.5;
    wall[0].position_c.z = 1.0;
    wall[0].position_d.x = 6.5;
    wall[0].position_d.y = 0.5;
    wall[0].position_d.z = 0.0;  
    wall[1].position_a.x = -1.0;
    wall[1].position_a.y = -0.5;
    wall[1].position_a.z = 0.0;
    wall[1].position_b.x = -1.0;
    wall[1].position_b.y = -0.5;
    wall[1].position_b.z = 1.0;
    wall[1].position_c.x = 0.5;
    wall[1].position_c.y = -0.5;
    wall[1].position_c.z = 1.0;
    wall[1].position_d.x = 0.5;
    wall[1].position_d.y = -0.5;
    wall[1].position_d.z = 0.0; 
    wall[2].position_a.x = 6.5;
    wall[2].position_a.y = 0.5;
    wall[2].position_a.z = 0.0; 
    wall[2].position_b.x = 6.5;
    wall[2].position_b.y = 0.5;
    wall[2].position_b.z = 1.0;
    wall[2].position_c.x = 6.5;
    wall[2].position_c.y = -3.5;
    wall[2].position_c.z = 1.0;
    wall[2].position_d.x = 6.5;
    wall[2].position_d.y = -3.5;
    wall[2].position_d.z = 0.0;
    wall[3].position_a.x = -1.0;
    wall[3].position_a.y = -3.5;
    wall[3].position_a.z = 0.0;
    wall[3].position_b.x = -1.0;
    wall[3].position_b.y = -3.5;
    wall[3].position_b.z = 1.0;
    wall[3].position_c.x = 6.5;
    wall[3].position_c.y = -3.5;
    wall[3].position_c.z = 1.0;
    wall[3].position_d.x = 6.5;
    wall[3].position_d.y = -3.5;
    wall[3].position_d.z = 0.0;
    wall[4].position_a.x = -1.0;
    wall[4].position_a.y = -1.5;
    wall[4].position_a.z = 0.0; 
    wall[4].position_b.x = -1.0;
    wall[4].position_b.y = -1.5;
    wall[4].position_b.z = 1.0;
    wall[4].position_c.x = -1.0;
    wall[4].position_c.y = -3.5;
    wall[4].position_c.z = 1.0;
    wall[4].position_d.x = -1.0;
    wall[4].position_d.y = -3.5;
    wall[4].position_d.z = 0.0; 
    wall[5].position_a.x = 2.0;
    wall[5].position_a.y = -0.5;
    wall[5].position_a.z = 0.0;
    wall[5].position_b.x = 2.0;
    wall[5].position_b.y = -0.5;
    wall[5].position_b.z = 1.0;
    wall[5].position_c.x = 5.0;
    wall[5].position_c.y = -0.5;
    wall[5].position_c.z = 1.0;
    wall[5].position_d.x = 5.0;
    wall[5].position_d.y = -0.5;
    wall[5].position_d.z = 0.0;
    wall[6].position_a.x = 0.5;
    wall[6].position_a.y = -1.5;
    wall[6].position_a.z = 0.0;
    wall[6].position_b.x = 0.5;
    wall[6].position_b.y = -1.5;
    wall[6].position_b.z = 1.0;
    wall[6].position_c.x = 5.0;
    wall[6].position_c.y = -1.5;
    wall[6].position_c.z = 1.0;
    wall[6].position_d.x = 5.0;
    wall[6].position_d.y = -1.5;
    wall[6].position_d.z = 0.0;
    wall[7].position_a.x = 0.5;
    wall[7].position_a.y = -2.5;
    wall[7].position_a.z = 0.0;
    wall[7].position_b.x = 0.5;
    wall[7].position_b.y = -2.5;
    wall[7].position_b.z = 1.0;
    wall[7].position_c.x = 2.0;
    wall[7].position_c.y = -2.5;
    wall[7].position_c.z = 1.0;
    wall[7].position_d.x = 2.0;
    wall[7].position_d.y = -2.5;
    wall[7].position_d.z = 0.0;
    wall[8].position_a.x = 3.5;
    wall[8].position_a.y = -2.5;
    wall[8].position_a.z = 0.0;
    wall[8].position_b.x = 3.5;
    wall[8].position_b.y = -2.5;
    wall[8].position_b.z = 1.0;
    wall[8].position_c.x = 5.0;
    wall[8].position_c.y = -2.5;
    wall[8].position_c.z = 1.0;
    wall[8].position_d.x = 5.0;
    wall[8].position_d.y = -2.5;
    wall[8].position_d.z = 0.0;
    wall[9].position_a.x = -1.0;
    wall[9].position_a.y = 0.5;
    wall[9].position_a.z = 0.0;
    wall[9].position_b.x = -1.0;
    wall[9].position_b.y = 0.5;
    wall[9].position_b.z = 1.0;
    wall[9].position_c.x = -1.0;
    wall[9].position_c.y = -0.5;
    wall[9].position_c.z = 1.0;
    wall[9].position_d.x = -1.0;
    wall[9].position_d.y = -0.5;
    wall[9].position_d.z = 0.0;
    wall[10].position_a.x = 2.0;
    wall[10].position_a.y = 0.5;
    wall[10].position_a.z = 0.0;
    wall[10].position_b.x = 2.0;
    wall[10].position_b.y = 0.5;
    wall[10].position_b.z = 1.0;
    wall[10].position_c.x = 2.0;
    wall[10].position_c.y = -0.5;
    wall[10].position_c.z = 1.0;
    wall[10].position_d.x = 2.0;
    wall[10].position_d.y = -0.5;
    wall[10].position_d.z = 0.0;
    wall[11].position_a.x = 0.5;
    wall[11].position_a.y = -0.5;
    wall[11].position_a.z = 0.0;
    wall[11].position_b.x = 0.5;
    wall[11].position_b.y = -0.5;
    wall[11].position_b.z = 1.0;
    wall[11].position_c.x = 0.5;
    wall[11].position_c.y = -1.5;
    wall[11].position_c.z = 1.0;
    wall[11].position_d.x = 0.5;
    wall[11].position_d.y = -1.5;
    wall[11].position_d.z = 0.0;
    wall[12].position_a.x = 2.0;
    wall[12].position_a.y = -1.5;
    wall[12].position_a.z = 0.0;
    wall[12].position_b.x = 2.0;
    wall[12].position_b.y = -1.5;
    wall[12].position_b.z = 1.0;
    wall[12].position_c.x = 2.0;
    wall[12].position_c.y = -2.5;
    wall[12].position_c.z = 1.0;
    wall[12].position_d.x = 2.0;
    wall[12].position_d.y = -2.5;
    wall[12].position_d.z = 0.0;
    wall[13].position_a.x = 5.0;
    wall[13].position_a.y = -1.5;
    wall[13].position_a.z = 0.0;
    wall[13].position_b.x = 5.0;
    wall[13].position_b.y = -1.5;
    wall[13].position_b.z = 1.0;
    wall[13].position_c.x = 5.0;
    wall[13].position_c.y = -2.5;
    wall[13].position_c.z = 1.0;
    wall[13].position_d.x = 5.0;
    wall[13].position_d.y = -2.5;
    wall[13].position_d.z = 0.0;

    wall[14].position_a.x = 5.0;
    wall[14].position_a.y = -1.5;
    wall[14].position_a.z = 0.0;

    wall[14].position_b.x = 5.0;
    wall[14].position_b.y = -1.5;
    wall[14].position_b.z = 1.0;

    wall[14].position_c.x = 6.5;
    wall[14].position_c.y = -1.5;
    wall[14].position_c.z = 1.0;

    wall[14].position_d.x = 6.5;
    wall[14].position_d.y = -1.5;
    wall[14].position_d.z = 0.0;
}





void render_walls(const Wall* wall){
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, wall->texture_id); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    for(int i=0;i<15;i++){
    glBegin(GL_QUADS);
    if(wall->is_open && i == 14){
        continue;
    }
    else{
    glTexCoord2f(0.0,4.0);
   glVertex3f( wall[i].position_a.x,  wall[i].position_a.y,  wall[i].position_a.z);
   glTexCoord2f(4.0,4.0);
   glVertex3f(wall[i].position_b.x, wall[i].position_b.y, wall[i].position_b.z);
   glTexCoord2f(4.0,0.0);
   glVertex3f(wall[i].position_c.x, wall[i].position_c.y, wall[i].position_c.z);
   glTexCoord2f(0.0,0.0);
   glVertex3f(wall[i].position_d.x, wall[i].position_d.y, wall[i].position_d.z);
   glEnd();}
}
glPopMatrix();
}

Wall get_wall_datas(const Wall* wall,int i){
    return wall[i];
}

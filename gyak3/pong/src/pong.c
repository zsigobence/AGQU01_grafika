#include "pong.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_rect.h"
#include <stdio.h>

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad),0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}


void bounce_ball(Pong* pong)
{
    SDL_Rect leftpad = {pong->left_pad.x ,(int)(pong->left_pad.y),pong->left_pad.width+50,(int)(pong->left_pad.height)};
    SDL_Rect rightpad = {(int)(pong->right_pad.x),(int)(pong->right_pad.y),(int)(pong->right_pad.width),(int)(pong->right_pad.height)};
    SDL_Rect theball = {(int)(pong->ball.x),(int)(pong->ball.y),(int)(pong->ball.radius),(int)(pong->ball.radius)};

    if(SDL_HasIntersection(&rightpad,&theball)){
        
        pong->ball.speed_x *= -1;
        pong->ball.rotation_angle *= -1;
    
    }else if(pong->ball.x  > pong->width ){
            pong->left_pad.score += 1;
            
            init_ball(&(pong->ball),pong->width / 2,pong->height / 2);
            update_ball_moving(&(pong->ball),false);
            printf("%d--%d\n",pong->left_pad.score,pong->right_pad.score);

    }

    if(SDL_HasIntersection(&leftpad,&theball)){
        pong->ball.speed_x *= -1;
        pong->ball.rotation_angle *= -1;
    }else if(pong->ball.x < 0){
    
        pong->right_pad.score += 1;
            init_ball(&(pong->ball),pong->width / 2,pong->height / 2);
            update_ball_moving(&(pong->ball),false);
            printf("%d--%d\n",pong->left_pad.score,pong->right_pad.score);
    }
    
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
        
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
        
    }
}

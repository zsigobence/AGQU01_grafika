#ifndef BALL_H
#define BALL_H
#include <stdbool.h>

/**
 * Ball position and speed
 */
typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
    float acceleration;
    bool is_moving;
} Ball;

void change_ball_size(Ball* ball,float size);

void change_ball_rotation(Ball* ball,int direction);

void update_ball_moving(Ball*ball ,bool is_it);
/**
 * Move the ball to the given position.
 */
void init_ball(Ball* ball, float x, float y);

void update_ball_speed(Ball* ball,float acc);
/**
 * Update the ball.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball* ball, double time);

/**
 * Render the ball.
 */
void render_ball(Ball* ball);


#endif /* BALL_H */

#include "game.h"
#include "texture.h"
#include <GL/gl.h>


#include <stdio.h>

void init_game(Game* game, int width, int height)
{
    game->is_running = false;
    game->width = width;
    game->height = height;
    if (init_sdl(game) == false) {
        return;
    }
    init_opengl(game);
    init_pong(&(game->pong), width, height);
    game->is_running = true;
    game->bgTexture = load_texture("assets/textures/pong.jpg");
}

void destroy_game(Game* game)
{
    if (game->gl_context != NULL) {
        SDL_GL_DeleteContext(game->gl_context);
    }

    if (game->window != NULL) {
        SDL_DestroyWindow(game->window);
    }

    SDL_Quit();
}

void handle_game_events(Game* game)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                game->is_running = false;
                break;
                case SDL_SCANCODE_SPACE:
        update_ball_moving(&(game->pong.ball),true);
        break;
            case SDL_SCANCODE_W:
                set_left_pad_speed(&(game->pong), -300);
                break;
            case SDL_SCANCODE_S:
                set_left_pad_speed(&(game->pong), +300);
                break;
            case SDL_SCANCODE_KP_PLUS:
                update_ball_speed(&(game->pong.ball),1.05);
                break;
            case SDL_SCANCODE_KP_MINUS:
                update_ball_speed(&(game->pong.ball),0.95);
                break;
            case SDL_SCANCODE_UP:
                change_ball_size(&(game->pong.ball),10);
            break;
            case SDL_SCANCODE_DOWN:
                change_ball_size(&(game->pong.ball),-10);    
            break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_left_pad_speed(&(game->pong), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            init_ball(&(game->pong.ball),x,y);
            update_ball_moving(&(game->pong.ball),false);
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            set_right_pad_position(&(game->pong), y);
            break;
        
        case SDL_QUIT:
            game->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_game(Game* game)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - game->last_update_time;
    game->last_update_time = current_time;
    if(game->pong.ball.is_moving){
    update_pong(&(game->pong), elapsed_time);
    }
    else{
        update_pong(&(game->pong), 0);
    }
}

void render_game(Game* game)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_background(game);
    render_pong(&(game->pong));
    SDL_GL_SwapWindow(game->window);
}

bool init_sdl(Game* game)
{
    int error_code;
    

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow(
        "Pong!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        game->width, game->height,
        SDL_WINDOW_OPENGL);
    if (game->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return false;
    }

   

    game->gl_context = SDL_GL_CreateContext(game->window);
    if (game->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return false;
    }


    return true;
}

void init_opengl(Game* game)
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_TEXTURE_2D);

    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game->width, game->height, 0, -200, 200);
    glViewport(0, 0, game->width, game->height);
    
}

void render_background(Game* game)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, game->bgTexture);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2d(0, 0);
    glTexCoord2d(1, 0); glVertex2d(game->width, 0);
    glTexCoord2d(1, 1); glVertex2d(game->width, game->height);
    glTexCoord2d(0, 1); glVertex2d(0, game->height);
    glEnd();
}


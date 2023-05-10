#include "app.h"

#include <SDL2/SDL_image.h>


void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;
    app->movement_enabled = 1;
    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Labirinth",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }
    

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->scene.camera));
    init_scene(&(app->scene));

    app->is_running = true;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetWindowGrab(app->window, SDL_TRUE);
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0, 0, 0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            
            case SDL_SCANCODE_W:
            if(app->movement_enabled){
                set_camera_speed(&(app->scene.camera), 1);}
                break;
            case SDL_SCANCODE_S:
            if(app->movement_enabled){
                set_camera_speed(&(app->scene.camera), -1);}
                break;
            case SDL_SCANCODE_A:
            if(app->movement_enabled){
                set_camera_side_speed(&(app->scene.camera), 1);}
                break;
            case SDL_SCANCODE_D:
            if(app->movement_enabled){
                set_camera_side_speed(&(app->scene.camera), -1);}
                break;
            case SDL_SCANCODE_KP_PLUS:
                app->scene.light += 0.1;
                break;
            case SDL_SCANCODE_KP_MINUS:
                app->scene.light -= 0.1;
                break;
            case SDL_SCANCODE_F1:
                if (app->scene.showhelp == 0){
                    app->scene.showhelp = 1;
                    app->movement_enabled = 0;
                    SDL_ShowCursor(SDL_ENABLE);
                    SDL_SetWindowGrab(app->window, SDL_FALSE);
                }
                else
                {
                    app->scene.showhelp = 0;
                    app->movement_enabled = 1;
                    SDL_ShowCursor(SDL_DISABLE);
                    SDL_SetWindowGrab(app->window, SDL_TRUE);
                    glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                }
                break;
            case SDL_SCANCODE_F2:
                if (app->scene.fogenable == 0)
                {
                    glEnable(GL_FOG);
                    app->scene.fogenable = 1;
                }
                else
                {
                    glDisable(GL_FOG);
                    app->scene.fogenable = 0;
                }
            case SDL_SCANCODE_SPACE:
            if (app->scene.game_end == 1){
                    init_camera(&(app->scene.camera));
                    init_scene(&(app->scene));
                    app->scene.game_end = 0;
                    app->movement_enabled = 1;
                    SDL_ShowCursor(SDL_DISABLE);
                    SDL_SetWindowGrab(app->window, SDL_TRUE);
                    glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                }
            break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->scene.camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->scene.camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
        if(app->scene.showhelp == 0){
            SDL_GetMouseState(&x, &y);
            if(x<70 || x>=799 || y<=0 || y>=599 ){
                mouse_x = 400;
                mouse_y = 300;
                SDL_WarpMouseInWindow(app->window, 400, 300);
            }
            if ( app->movement_enabled) {
                rotate_camera(&(app->scene.camera), mouse_x - x,mouse_y-y);
            }
            mouse_x = x;
            mouse_y = y;
            
        }else{
            if(event.button.button == SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x, &y);
            if(y <= 500 && y >= 490 && x <= 660 && x >= 140){
                app->scene.cursorpos = (x-400) * 0.006;
                app->scene.camera.sensitivity = 1.0 + (x - 400.0)/260;
            }
        }
        }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            if(y <= 500 && y >= 490 && x <= 660 && x >= 140){
                app->scene.cursorpos = (x-400) * 0.006;
                app->scene.camera.sensitivity = 1.0 + (x - 400.0)/260;
            }
        break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->scene.camera), elapsed_time);
    update_scene(&(app->scene),elapsed_time);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->scene.camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->scene.camera.is_preview_visible) {
        show_texture_preview();
    }
    if (app->scene.showhelp){
        help_menu(&(app->scene));}

    if(app->scene.game_end){
        app->movement_enabled = 0;
        SDL_ShowCursor(SDL_ENABLE);
        SDL_SetWindowGrab(app->window, SDL_FALSE);
        end_game(&(app->scene));
    }
    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }
    
}

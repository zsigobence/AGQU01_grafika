#include <SDL2/SDL.h>

#include <stdio.h>
#include <windows.h>
#include "line.h"
#include <stdbool.h>

const SDL_Color colors[30] = {
    {255, 0, 0, 255},  
    {0, 255, 0, 255},  
    {0, 0, 255, 255},  
    {255, 255, 0, 255}, 
    {0, 255, 255, 255}, 
    {255, 0, 255, 255}, 
};

const int segment_width = 100;
const int segment_height = 100;


int main(int argc, char* argv[]) {
    Line line;
    int x,y,x1,y1,w,h;
    

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("title",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,600,500,SDL_WINDOW_SHOWN);
    SDL_Surface* screen = SDL_GetWindowSurface(win);
    
    
    SDL_Renderer* ren;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);
    
    SDL_Rect segment_rects[sizeof(colors) / sizeof(colors[0])];
    for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        SDL_Rect rect = {i * segment_width, 0, segment_width, segment_height};
        segment_rects[i] = rect;
    }

    for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        
                SDL_SetRenderDrawColor( ren, colors[i].r, colors[i].g, colors[i].b, 255 );
                SDL_RenderFillRect( ren, &segment_rects[i] );
                SDL_RenderPresent(ren);
            } 
    
    
    
    
    bool run = true;
    bool next = false;

     while(run && !next){
    SDL_Event paletta;
        while(SDL_PollEvent(&paletta)){
            switch(paletta.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if(y<101){
                        for(int i=0;i<6;i++){
                            if(x<((i+1)*100)){
                                SDL_SetRenderDrawColor(0,0,0,0,255);
                                SDL_RenderClear(ren);
                                SDL_RenderPresent( ren );
                                SDL_SetRenderDrawColor( ren, colors[i].r, colors[i].g, colors[i].b, 255 );
                                
                                break;
                            }
                        }
                       
                    }else{
                        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                    }
                    next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
     }
     next=false;
    while(run && !next){
        SDL_Event ev;
        
        while(SDL_PollEvent(&ev)){
            
            
            switch(ev.type)
            {
                
                case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&x,&y);
                set_startingpoint(&line,x,y);
                printf("Kezdopont:%d %d\n",line.start.x,line.start.y);
                next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
         
    }


next =false;
while(run && !next){
SDL_Event ev2;
while(SDL_PollEvent(&ev2)){
            
            switch(ev2.type)
            {
                case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&x,&y);
                set_endingpoint(&line,x,y);
                printf("vegpont:%d %d\n",line.end.x,line.end.y);
                next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
 }
SDL_RenderDrawLine(ren,line.start.x,line.start.y,line.end.x,line.end.y);
          SDL_RenderPresent( ren );

next=false;
while(run && !next){
    SDL_Event tovabb;
    while(SDL_PollEvent(&tovabb)){
        switch(tovabb.type){
            case SDL_MOUSEBUTTONDOWN:
            next=true;
            break;
            case SDL_QUIT:
                run = false;
                break;
        }
    }
}


for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        
                SDL_SetRenderDrawColor( ren, colors[i].r, colors[i].g, colors[i].b, 255 );
                SDL_RenderFillRect( ren, &segment_rects[i] );
                SDL_RenderPresent(ren);
            } 


next=false;
 while(run && !next){
    SDL_Event paletta2;
        while(SDL_PollEvent(&paletta2)){
            switch(paletta2.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if(y<101){
                        for(int i=0;i<6;i++){
                            if(x<((i+1)*100)){
                                SDL_SetRenderDrawColor(0,0,0,0,255);
                                SDL_RenderClear(ren);
                                SDL_RenderPresent( ren );
                                SDL_SetRenderDrawColor( ren, colors[i].r, colors[i].g, colors[i].b, 255 );
                                break;
                            }
                        }
                       
                    }else{
                        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                    }
                    next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
     }

next=false;
    while(run && !next){
        SDL_Event ev3;
        
        while(SDL_PollEvent(&ev3)){
            
            
            switch(ev3.type)
            {
                
                case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&x1,&y1);
                next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
         
    }
next =false;
while(run && !next){
SDL_Event ev4;
while(SDL_PollEvent(&ev4)){
            
            switch(ev4.type)
            {
                case SDL_MOUSEBUTTONDOWN :
                SDL_GetMouseState(&w,&h);
                next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
 }
SDL_Rect tegla = {x1,y1,w-x1,h-y1};
SDL_RenderFillRect( ren, &tegla );
SDL_RenderPresent(ren);

 while(run){
    SDL_Event ev5;
    while(SDL_PollEvent(&ev5)){
        
        switch(ev5.type){
          
          case SDL_QUIT:
                run = false;
                break;  
        }

    }
 }
      
   
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

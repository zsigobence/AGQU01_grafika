#include "circle.h"
#include <SDL2/SDl.h>
#include <stdbool.h>
#include <math.h>

#include <stdio.h>


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

int main(int argc, char* argv[])
{
	Circle circles[5];
	double area;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	bool run;
	bool next;
	int x,y,rx,ry,r;
	
	


	window = SDL_CreateWindow("Circle",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,600,500,SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);



 SDL_Rect segment_rects[sizeof(colors) / sizeof(colors[0])];
    for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        SDL_Rect rect = {i * segment_width, 0, segment_width, segment_height};
        segment_rects[i] = rect;
    }

    for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        
                SDL_SetRenderDrawColor( renderer, colors[i].r, colors[i].g, colors[i].b, 255 );
                SDL_RenderFillRect( renderer, &segment_rects[i] );
                SDL_RenderPresent(renderer);
            } 
    



	run=true;
	next=false;
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
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent( renderer );
                                SDL_SetRenderDrawColor( renderer, colors[i].r, colors[i].g, colors[i].b, 255 );
                                circles[0].color=colors[i];
                                break;
                            }
                        }
                       
                    }else{
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    }
                    next=true;
                break;
                case SDL_QUIT:
                run = false;
                break;
            }
        }
     }
	 int k=0;
	 while(k<5){
		circles[k].color=circles[0].color;
     next=false;
	while(run && !next){
		SDL_Event kozeppont;
		while(SDL_PollEvent(&kozeppont)){
			switch(kozeppont.type){
				case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x,&y);
				next=true;
				break;
				case SDL_QUIT:
				run=false;
				break;
			}
		}
	}
	next=false;
	while(run && !next){
		SDL_Event sugar;
		while(SDL_PollEvent(&sugar)){
			switch(sugar.type){
				case SDL_MOUSEBUTTONUP:
				SDL_GetMouseState(&rx,&ry);
				r=sqrt(pow((rx-x),2)+pow((ry-y),2));
				next=true;
				break;
				case SDL_QUIT:
				run=false;
				break;
			}
		}
	}
	set_circle_data(&circles[k], x, y, r);
	area = calc_circle_area(&circles[k]);
	for(float i = 0;i<7;i+=0.2){
					SDL_RenderDrawLine(renderer,x+r*cos(i),y+r*sin(i),x+r*cos(i+0.2),y+r*sin(i+0.2));
					SDL_RenderPresent(renderer);
					
				}

	int a,b,c;
	next = false;
	while(run && !next){
		SDL_Event bent;
		while(SDL_PollEvent(&bent)){
			switch(bent.type){
				case SDL_MOUSEMOTION:
				
		SDL_GetMouseState(&a,&b);
				for(int i=0;i<k+1;i++){
		c=sqrt(pow((a-circles[i].x),2)+pow((b-circles[i].y),2));
		if( c < circles[i].radius){
			printf("A(z) %d. Koron belul vagy",i+1);
			SDL_RenderDrawLine(renderer,circles[i].x-5,circles[i].y-5,circles[i].x+5,circles[i].y+5);
			SDL_RenderDrawLine(renderer,circles[i].x+5,circles[i].y-5,circles[i].x-5,circles[i].y+5);
			SDL_RenderPresent(renderer);
		}else if( c > circles[i].radius) {
			printf("NEM VAGY");
			SDL_SetRenderDrawColor(renderer,0,0,0,255);
			SDL_RenderDrawLine(renderer,circles[i].x-5,circles[i].y-5,circles[i].x+5,circles[i].y+5);
			SDL_RenderDrawLine(renderer,circles[i].x+5,circles[i].y-5,circles[i].x-5,circles[i].y+5);
			SDL_RenderPresent(renderer);

		}
		SDL_SetRenderDrawColor(renderer,circles[k].color.r,circles[k].color.g,circles[k].color.b,255);
	}
				break;
				case SDL_KEYDOWN:
				next=true;
				break;
				case SDL_QUIT:
				run=false;
				break;
			}
		}
	}
	
	k++;
	}
	
	printf("Circle area: %lf\n", area);





	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}

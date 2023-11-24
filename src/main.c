#include <math.h>
#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdbool.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800


void drawFractal(SDL_Renderer **renderer,int startX,int startY,int length, double angle,int depth);
int main(int argc,char**argv)
{
    SDL_Renderer * renderer =NULL;
    SDL_Window * window =NULL;

    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        fprintf(stderr,"error init sdl : %s\n",SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("fractal",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if(window==NULL)
    {
        fprintf(stderr,"error create sdl :%s\n",SDL_GetError());
        exit(1);
    }

    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer==NULL)
    {
        fprintf(stderr,"error create renderer :%s\n",SDL_GetError());
        SDL_DestroyWindow(window);
        exit(1);
    }

    bool gameOver =false;


    while(!gameOver){
        SDL_Event event;
        while(SDL_PollEvent(&event)!=0)
        {
            switch(event.type)
            {
                case SDL_QUIT:{
                    gameOver=true;
                    break;
                }
            }
        }

       SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        

         // Draw a line from (100, 100) to (400, 300)
        int startX = WINDOW_WIDTH/2;
        int startY = WINDOW_HEIGHT;
        int length = 200;
        double angle = 0.0;
        int depth = 10;

       drawFractal(&renderer,startX,startY,length,angle,depth);
        //SDL_RenderDrawLine(renderer, startX, startY, 200, 300);

        SDL_RenderPresent(renderer);
    }

    
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void drawFractal(SDL_Renderer **renderer,int startX,int startY,int length, double angle,int depth)
{
    SDL_SetRenderDrawColor(*renderer, 242, 111,40, 255);
    if(depth == 0){
        return ;
    }
    int x2 = startX + length * sin(angle);
    int y2 = startY - length * cos(angle);

    SDL_RenderDrawLine(*renderer, startX, startY, x2, y2);

    drawFractal(renderer, x2, y2, length * 0.7, angle + 0.5, depth - 1);
    drawFractal(renderer, x2, y2, length * 0.7, angle - 0.5, depth - 1);
}
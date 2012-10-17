#include <stdlib.h>

#include <SDL.h>
#include <SDL_opengl.h>
#undef main

#include "GameController.h"

GameController *controller;

#define WIDTH 640
#define HEIGHT 480
#define WINDOW_TITLE "void ray"

SDL_Surface *screen;

void Initialize();

#define TICK_INTERVAL    30

double TimerUpdate(void)
{
    static Uint32 last_time = 0;
    Uint32 now;
    
    now = SDL_GetTicks();
    if ( last_time <= now ) {
        if(now - last_time < TICK_INTERVAL)
            return(0);
    }
    
    Uint32 new_time = now - last_time;
    last_time = now;
    
    return new_time / 1000.0;
}

void render() {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    controller->Update(TimerUpdate());
	controller->Render();
}

/****************************************************************************
 main()
*****************************************************************************/
int main(int argc, char *argv[]) {

    Initialize();

	controller = new GameController(screen);
    
    bool done = false;
    while(!done) 
    {
        SDL_Event event;
        
        // Respond to any events that occur
        while(SDL_PollEvent(&event))
        {
            switch(event.type) 
            {
                case SDL_VIDEORESIZE:
                    screen = SDL_SetVideoMode(event.resize.w, 
                                              event.resize.h, 0,
                                              SDL_OPENGL | SDL_RESIZABLE);
                    if(screen)
                    {
                        // reshape(screen->w, screen->h);
                    } 
                    else 
                    {
                        ; // Oops, we couldn't resize for some reason. 
                        // This should never happen
                    }
                    break;
                    
                case SDL_QUIT:
                    done = true;
                    break;		
                    
                    // ## INSERT CODE TO HANDLE ANY OTHER EVENTS HERE ##
            }
        }
        
        // Check for escape
        Uint8 *keys = SDL_GetKeyState(NULL);
        if( keys[SDLK_ESCAPE] ) {
            done = true;
        }
        
        // Draw the screen
        render();
        
        SDL_GL_SwapBuffers();
    }
    
    SDL_Quit();
    return 0;
}

void Initialize() {
    // Initialize
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    // Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Create a OpenGL window
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL | 
                              SDL_RESIZABLE);
    if(!screen) 
    {
        printf("Couldn't set %dx%d GL video mode: %s\n", WIDTH,
               HEIGHT, SDL_GetError());
        SDL_Quit();
        exit(2);
    }
    SDL_WM_SetCaption(WINDOW_TITLE, WINDOW_TITLE);

	glEnable( GL_TEXTURE_2D );
}



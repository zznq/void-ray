#include <stdlib.h>
#include <SDL.h>

#include "GameWorld.hpp"
#include "Timer.hpp"

#define TICK_INTERVAL    30

GameWorld *world;

void render();

#undef main
/****************************************************************************
 main()
*****************************************************************************/
int main(int argc, char *argv[]) {
	world = new GameWorld();
    
	Timer::Initialize(true);
    
	bool done = false;
    while(!done) 
    {
        SDL_Event event;
        
        // Respond to any events that occur
        while(SDL_PollEvent(&event))
        {
            switch(event.type) 
            {
				case SDL_MOUSEBUTTONUP:
					
					if(event.button.state == SDL_RELEASED) {
						world->UpdateTarget(event.button.x, event.button.y);
					}
					break;
                case SDL_VIDEORESIZE:
                    /*screen = SDL_SetVideoMode(event.resize.w, 
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
                    }*/
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

void render() { 
	world->Update(Timer::TimerUpdate());
	
	world->Render();
}

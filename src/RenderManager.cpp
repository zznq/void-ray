#include "RenderManager.h"

#include <SDL/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480
#define WINDOW_TITLE "void ray"

RenderManager* RenderManager::Instance() {
	static RenderManager* instance;
	if(!instance) 
		instance = new RenderManager;

	return instance;
}

void RenderManager::Initialize() {
    // Initialize
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    // Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Create a OpenGL window
    this->_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL | 
                              SDL_RESIZABLE);
    if(!this->_screen)
    {
        printf("Couldn't set %dx%d GL video mode: %s\n", WIDTH,
               HEIGHT, SDL_GetError());
        SDL_Quit();
        exit(2);
    }
    SDL_WM_SetCaption(WINDOW_TITLE, WINDOW_TITLE);

	glEnable( GL_TEXTURE_2D );
}

void RenderManager::ClearColorBitBuffer() {
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderManager::DrawImage(char* path, GLfloat vertices[]) 
{
	SDL_Surface* temp = NULL;
	SDL_Surface* image = NULL;

	GLuint texture;			// This is a handle to our texture object
	GLenum texture_format;
	GLint  nOfColors;

	if((temp = IMG_Load(path)) != NULL) {
		image = SDL_DisplayFormatAlpha(temp);
		if(image == NULL){
			printf("Error Converting To Alpha : %s \n", SDL_GetError());
		}

		nOfColors = image->format->BytesPerPixel;
	    if (nOfColors == 4)     // contains an alpha channel
	    {
	            if (image->format->Rmask == 0x000000ff)
	                    texture_format = GL_RGBA;
	            else
	                    texture_format = GL_BGRA;
	    } else if (nOfColors == 3)     // no alpha channel
	    {
	            if (image->format->Rmask == 0x000000ff)
	                    texture_format = GL_RGB;
	            else
	                    texture_format = GL_BGR;
	    } else {
	            printf("warning: the image is not truecolor..  this will probably break\n");
	            // this error should not go unhandled
	    }
 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
	 
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, image->w, image->h, 0,
			              texture_format, GL_UNSIGNED_BYTE, image->pixels );

		// Bind the texture to which subsequent calls refer to
		glBindTexture( GL_TEXTURE_2D, texture );

		GLfloat squareTexCoord[] = {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		};

		// activate and specify pointer to vertex array
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, squareTexCoord);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glDrawArrays(GL_QUADS, 0, 4);

		// deactivate vertex arrays after drawing
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		SDL_FreeSurface(temp);
		SDL_FreeSurface(image);
	} else {
		printf("Error Loading Image : %s \n", path);
	}
}

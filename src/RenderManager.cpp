#include "RenderManager.hpp"

#include <SDL/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480
#define WINDOW_TITLE "void ray"

SDL_Surface* RenderManager::_screen = NULL;

void RenderManager::Initialize() {
    // Initialize
    SDL_Init(SDL_INIT_VIDEO);
    
    // Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Create a OpenGL window
    RenderManager::_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL | 
                              SDL_RESIZABLE);
    if(!RenderManager::_screen)
    {
        printf("Couldn't set %dx%d GL video mode: %s\n", WIDTH,
               HEIGHT, SDL_GetError());
        SDL_Quit();
        exit(2);
    }

    SDL_WM_SetCaption(WINDOW_TITLE, WINDOW_TITLE);

	glViewport(0, 0, WIDTH, HEIGHT);
	 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	 
	glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, 1, -1);
	 
	glMatrixMode(GL_MODELVIEW);
	 
	glEnable(GL_TEXTURE_2D);
	 
	glLoadIdentity();
}

void RenderManager::ClearColorBitBuffer() {
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderManager::MoveAndRotate(Vector3 translation, float angle, int angleBits) {
	glMatrixMode(GL_MODELVIEW);

	RenderManager::LoadIdentity();

	if((angleBits & 1) == 1){ 
		RenderManager::Roll(angle);
	} else if((angleBits & 2) == 2) {
		RenderManager::Pitch(angle);
	} else if((angleBits & 4) == 4) {
		RenderManager::Yaw(angle);
	}

	RenderManager::Translate(translation);
}

void RenderManager::Translate(Vector3 translation) {
	glTranslatef(translation.x, translation.y, translation.z);
}

void RenderManager::Roll(float angle) {
	glRotatef(angle, 0, 0, 1);
}

void RenderManager::Pitch(float angle) {
	glRotatef(angle, 0, 1, 0);
}

void RenderManager::Yaw(float angle) {
	glRotatef(angle, 1, 0, 0);
}

void RenderManager::LoadIdentity() {
	glLoadIdentity();
}

void RenderManager::DrawPoint(float x, float y) {
	glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, y);
	glEnd();

	RenderManager::ClearColorBitBuffer();
}

void RenderManager::DrawImage(const std::string& path, const GLfloat vertices[]) 
{
	SDL_Surface* temp = NULL;
	SDL_Surface* image = NULL;

	GLuint texture;			// This is a handle to our texture object
	GLenum texture_format;
	GLint nOfColors;

	temp = IMG_Load(path.c_str());
	if(temp == NULL) {
		printf("Error Loading Image : %s \n", path.c_str());
		return;	
	}

	/*Uint32 colorkey = SDL_MapRGB(temp->format, 0, 0, 0);
	// now tell SDL to remeber our choice
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, colorkey);*/

	image = SDL_DisplayFormatAlpha(temp);
	if(image == NULL){
		printf("Error Converting To Alpha : %s \n", SDL_GetError());
		return;
	}

	nOfColors = image->format->BytesPerPixel;
	
    texture_format = RenderManager::GetTextureFormat(image, nOfColors);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, squareTexCoord);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 4);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_BLEND);

	SDL_FreeSurface(temp);
	SDL_FreeSurface(image);
	
}

GLenum RenderManager::GetTextureFormat(SDL_Surface* surface, GLint nOfColors) {
    if (nOfColors == 4)     // contains an alpha channel
    {
            if (surface->format->Rmask == 0x000000ff)
                    return GL_RGBA;
            else
                    return GL_BGRA;
    } else if (nOfColors == 3)     // no alpha channel
    {
            if (surface->format->Rmask == 0x000000ff)
                    return GL_RGB;
            else
                    return GL_BGR;
    } else {
        printf("warning: the image is not truecolor..  this will probably break\n");
        
		return GL_RGB;
    }
}

#include <SDL/SDL_image.h>

#include "RenderManager.hpp"



SDL_Surface* RenderManager::_screen = NULL;

void RenderManager::Initialize(int width, int height,std::string window_title) {
    // Initialize
    SDL_Init(SDL_INIT_VIDEO);
    
    // Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Create a OpenGL window
    RenderManager::_screen = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | 
                              SDL_RESIZABLE);
    if(!RenderManager::_screen)
    {
        printf("Couldn't set %dx%d GL video mode: %s\n", width,
               height, SDL_GetError());
        SDL_Quit();
        exit(2);
    }

    SDL_WM_SetCaption(window_title.c_str(), window_title.c_str());

	glViewport(0, 0, width, height);
	 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	 
	glOrtho(-width/2, width/2, -height/2, height/2, 1, -1);
	 
	glMatrixMode(GL_MODELVIEW);
	 
	glEnable(GL_TEXTURE_2D);
	 
	glLoadIdentity();
}

void RenderManager::ClearColorBitBuffer() {
	glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

/*
RM -> CM
0  -> 0
1  -> 4
2  -> 8
3  -> 12
4  -> 1
5  -> 5
6  -> 9
7  -> 13
8  -> 2
9  -> 6
10 -> 10
11 -> 14
12 -> 3
13 -> 7
14 -> 11
15 -> 15
*/
void RenderManager::LoadMatrix(const GLfloat viewMatrix[], bool colMajor) {
	glMatrixMode(GL_MODELVIEW);
	
	RenderManager::LoadIdentity();

	//RenderManager:: PrintModelView();

	if(!colMajor) {
		float newMatrix[16];

		newMatrix[0] = viewMatrix[0];
		newMatrix[4] = viewMatrix[1];
		newMatrix[8] = viewMatrix[2];
		newMatrix[12] = viewMatrix[3];
	    newMatrix[1] = viewMatrix[4];
		newMatrix[5] = viewMatrix[5];
		newMatrix[9] = viewMatrix[6];
		newMatrix[13] = viewMatrix[7];
		newMatrix[2] = viewMatrix[8];
		newMatrix[6] = viewMatrix[9];
		newMatrix[10] = viewMatrix[10];
		newMatrix[14] = viewMatrix[11];
		newMatrix[3] = viewMatrix[12];
		newMatrix[7] = viewMatrix[13];
		newMatrix[11] = viewMatrix[14];
		newMatrix[15] = viewMatrix[15];
	
		glLoadMatrixf(newMatrix);
	} else {
		glLoadMatrixf(viewMatrix);
	}

	//RenderManager:: PrintModelView();
}

void RenderManager::MoveAndRotate(Vector3 translation, float angle, int angleAxis) {
	glMatrixMode(GL_MODELVIEW);

	RenderManager::LoadIdentity();

	RenderManager::Translate(translation);

	/*if(angleAxis == ROTATEZ){ 
		RenderManager::Roll(angle);
	} else if(angleAxis == ROTATEY) {
		RenderManager::Pitch(angle);
	} else if(angleAxis == ROTATEX) {
		RenderManager::Yaw(angle);
	}*/

	RenderManager:: PrintModelView();
}

void RenderManager:: PrintModelView() {
	GLfloat	 params[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, params);
 
	printf("----- GL MATRIX Print Out --------\n");

	for(int col = 0; col < 4; col++){
		for(int row = 0; row < 4; row++) {
			printf("%d => %f ", (row * 4) + col, params[(row * 4) + col]);
		}
		printf("\n");
	}
}

void RenderManager::Translate(Vector3 translation) {
	glTranslatef(translation.x, translation.y, translation.z);
}

// Rotation in Degrees
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

void RenderManager::DrawLine(const GLfloat vertices[]){

	glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertexPointer(2, GL_FLOAT, 0, vertices);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_LINES, 0, 2);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);

	RenderManager::ClearColorBitBuffer();

	//glColor3f(0.0f, 0.0f, 0.0f);
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

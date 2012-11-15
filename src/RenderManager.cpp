#include <SDL/SDL_image.h>

#include "RenderManager.hpp"

SDL_Surface* RenderManager::_screen = NULL;
std::map<std::string, SDL_Surface*> RenderManager::images = std::map<std::string, SDL_Surface*>();
std::map<std::string, GLuint> RenderManager::textures = std::map<std::string, GLuint>();

void RenderManager::Initialize(int width, int height,std::string window_title) {
    // Initialize
    SDL_Init(SDL_INIT_VIDEO);
    
    // Enable double-buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Create a OpenGL window
    RenderManager::_screen = SDL_SetVideoMode(width, height, 0, SDL_OPENGL);
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

	RenderManager::Flush();
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

void RenderManager::LoadIdentity() {
	glLoadIdentity();
}

void RenderManager::DrawPoint(const GLfloat vertices[], const GLfloat colors[]) {
	RenderManager::DrawArray(GL_POINTS, 1, 2, vertices, colors);
}

void RenderManager::DrawSquare(const GLfloat vertices[], const GLfloat colors[], int vertexCount){
    RenderManager::DrawArray(GL_TRIANGLE_STRIP, vertexCount, 2, vertices, colors);
}

void RenderManager::DrawLine(const GLfloat vertices[], const GLfloat colors[]){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(1);

	RenderManager::DrawArray(GL_LINE_STRIP, 2, 2, vertices, colors);
}

void RenderManager::DrawArray(GLenum mode, GLint vcount, GLint vsize, const GLfloat vertices[], const GLfloat colors[]) {
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(vsize, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(mode, 0, vcount);
    
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY) ;
	glEnable(GL_TEXTURE_2D);
}

SDL_Surface* RenderManager::LoadImage(const std::string& path) {
	SDL_Surface* temp = NULL;
	SDL_Surface* image = NULL;

	std::map<std::string,SDL_Surface*>::iterator it;
	it = RenderManager::images.find(path);

	if(it != RenderManager::images.end()) {
		//(*it) is a pair<std:string, SDL_Surface*> object
		image = it->second;

		return image;
	}

	temp = IMG_Load(path.c_str());
	if(temp == NULL) {
		printf("Error Loading Image : %s \n", path.c_str());
		return NULL;	
	}

	image = SDL_DisplayFormatAlpha(temp);
	if(image == NULL){
		SDL_FreeSurface(temp);
		printf("Error Converting To Alpha : %s \n", SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(temp);

	RenderManager::images.insert(std::make_pair(path, image));
	return image;
}

void RenderManager::DrawImage(const std::string& path, const GLfloat vertices[]) {
	float _colors[] = {
		255.0f, 255.0f,  255.0f, 1.0f,
		255.0f, 255.0f,  255.0f, 1.0f,
		255.0f, 255.0f,  255.0f, 1.0f,
		255.0f, 255.0f,  255.0f, 1.0f
	};

	RenderManager::DrawImage(path, vertices, _colors);
}

void RenderManager::DrawImage(const std::string& path, const GLfloat vertices[], const GLfloat colors[]) {
	SDL_Surface* image = RenderManager::LoadImage(path);

	if(image == NULL){
		printf("Error Loading Image: %s \n", SDL_GetError());
		return;
	}
	
	GLuint texture;			// This is a handle to our texture object
	GLenum texture_format;
	GLint nOfColors;

	nOfColors = image->format->BytesPerPixel;
	
    texture_format = RenderManager::GetTextureFormat(image, nOfColors);

	//glGenTextures( 1, &texture );
	std::map<std::string, GLuint>::iterator it = RenderManager::textures.find(path);
	if(it == RenderManager::textures.end()) {
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
		RenderManager::textures.insert(std::make_pair(path, texture));
	} else {
		texture = it->second;
	}

	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, image->w, image->h, 0,
		              texture_format, GL_UNSIGNED_BYTE, image->pixels );

	static GLfloat squareTexCoord[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, squareTexCoord);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glColorPointer(4, GL_FLOAT, 0, colors);
	glDrawArrays(GL_QUADS, 0, 4);
	
	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisable(GL_BLEND);
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

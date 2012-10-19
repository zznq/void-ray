#ifndef RENDER_MANAGER
#define RENDER_MANAGER

#include <SDL.h>
#include <SDL/SDL_opengl.h>

class RenderManager {
private:
	SDL_Surface* _screen;
public:
	static RenderManager* Instance();	

	void Initialize();

	void ClearColorBitBuffer();
	void DrawImage(char* path, GLfloat vertices[]);
};

#endif

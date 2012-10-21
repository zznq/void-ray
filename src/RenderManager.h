#ifndef RENDER_MANAGER
#define RENDER_MANAGER

#include <SDL.h>
#include <SDL/SDL_opengl.h>

#include <string>

class RenderManager {
protected:
	static SDL_Surface* _screen;//?
public:
	static void Initialize();

	static void ClearColorBitBuffer();
	static void DrawImage(const std::string& path, const GLfloat vertices[]);
};

#endif

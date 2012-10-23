#ifndef RENDER_MANAGER
#define RENDER_MANAGER

#include <SDL.h>
#include <SDL/SDL_opengl.h>

#include <string>
#include "util/Vector3.hpp"

class RenderManager {
protected:
	static SDL_Surface* _screen;
	static GLenum GetTextureFormat(SDL_Surface* surface, GLint nOfColors);
public:
	static void Initialize();

	static void ClearColorBitBuffer();
	static void RenderManager::Translate(Vector3 translation);

	static void RenderManager::Roll(float angle);
	static void RenderManager::Pitch(float angle);
	static void RenderManager::Yaw(float angle);
	static void RenderManager::LoadIdentity();

	static void RenderManager::MoveAndRotate(Vector3 translation, float angle, int angleBits);
	static void DrawImage(const std::string& path, const GLfloat vertices[]);
};

#endif

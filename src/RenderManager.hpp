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
	static const int ROTATENONE = 0x00;
	static const int ROTATEX 	= 0x01;
	static const int ROTATEY 	= 0x10;
	static const int ROTATEZ 	= 0x11;

	static void Initialize(int width, int height,std::string window_title);
	static void MoveAndRotate(Vector3 translation, float angle, int angleBits);

	/* openGL Matrix Transform call wrappers */
	static void Translate(Vector3 translation);
	static void Roll(float angle);
	static void Pitch(float angle);
	static void Yaw(float angle);
	static void LoadIdentity();

	/* openGL function call wrappers */
	static void LoadMatrix(const GLfloat viewMatrix[], bool colMajor);
	static void PrintModelView();
	static void ClearColorBitBuffer();
	static void DrawPoint(float x, float y);
	static void DrawLine(const GLfloat vertices[]);
	static void DrawImage(const std::string& path, const GLfloat vertices[]);
};

#endif

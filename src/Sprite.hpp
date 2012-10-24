#ifndef AI_SPRITE
#define AI_SPRITE

#include <string>
#include <vector>
#include "Entity.hpp"
#include "RenderManager.hpp"

class Sprite : public Entity {
protected:
	std::string _path;
	std::vector<float> _vertices;
public:
	Sprite(std::string path, float vScale) {
		float vertices[] = {
			-vScale,  vScale, 0.0f,
			 vScale,  vScale, 0.0f,
			 vScale, -vScale, 0.0f,
			-vScale, -vScale, 0.0f
		};
		std::vector<float> _v (vertices, vertices + 12);
		this->_vertices = _v;

		this->_path =  path;
	};

	virtual ~Sprite() {
    }
	virtual void Update(double time_elapsed) {};
    virtual void Render();
};

#endif

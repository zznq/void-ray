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
	Sprite(std::string path) {
		this->_path =  path;
	}

	virtual ~Sprite() {
    }
	virtual void Update(double time_elapsed) {};
    virtual void Render() {
		RenderManager::DrawImage(this->_path, &this->_vertices[0]);
	};
};

#endif

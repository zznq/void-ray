#ifndef AI_SPRITE
#define AI_SPRITE

#include <string>
#include <vector>
#include "MovingEntity.h"
#include "RenderManager.h"

class Sprite : public MovingEntity {
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
    virtual void Render() { };
};

#endif

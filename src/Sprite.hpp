#ifndef AI_SPRITE
#define AI_SPRITE

#include <string>
#include <vector>
#include "util\Vector3.hpp"
#include "BaseEntity.hpp"

class Sprite : public BaseEntity {
protected:
	std::string _path;
	std::vector<float> _vertices;

	void _setup(std::string path, float vScale, Vector3 pos) {
		float vertices[] = {
			-vScale,  vScale, 0.0f,
			 vScale,  vScale, 0.0f,
			 vScale, -vScale, 0.0f,
			-vScale, -vScale, 0.0f
		};
		std::vector<float> _v (vertices, vertices + 12);
		this->_vertices = _v;

		this->_path =  path;

		this->position = pos;
	}
public:
	Sprite(BaseEntity* parent, std::string path, float vScale)
	: BaseEntity(parent) {
		this->_setup(path, vScale, Vector3());
	}
	
	Sprite(std::string path, float vScale) : BaseEntity() {
		this->_setup(path, vScale, Vector3());
	};

	Sprite(BaseEntity* parent, std::string path, float vScale, Vector3 pos) 
		: BaseEntity(parent) {
		this->_setup(path, vScale, pos);
	};
	
	Sprite(std::string path, float vScale, Vector3 pos) : BaseEntity() {
		this->_setup(path, vScale, pos);
	};

	virtual ~Sprite() {
    }
    virtual void Render();
};

#endif

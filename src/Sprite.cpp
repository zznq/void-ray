#include <cmath>

#include "Sprite.hpp"

void Sprite::Render() {
	BaseEntity::Render();
	
	float _colors[] = {
		255.0f, 255.0f,  255.0f, this->_opacity,
		255.0f, 255.0f,  255.0f, this->_opacity,
		255.0f, 255.0f,  255.0f, this->_opacity,
		255.0f, 255.0f,  255.0f, this->_opacity
	};

	RenderManager::DrawImage(this->_path, &this->_vertices[0], &_colors[0]);
}

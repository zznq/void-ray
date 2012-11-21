#include <cmath>

#include "Sprite.hpp"

void Sprite::Render() {
	BaseEntity::Render();

  double _opacity_multiplier = 1.0;
  if(this->IsNear()){
    _opacity_multiplier = 0.25;
  }

	float _colors[] = {
		255.0f, 255.0f,  255.0f, this->_opacity * _opacity_multiplier,
		255.0f, 255.0f,  255.0f, this->_opacity * _opacity_multiplier,
		255.0f, 255.0f,  255.0f, this->_opacity * _opacity_multiplier,
		255.0f, 255.0f,  255.0f, this->_opacity * _opacity_multiplier
	};

	RenderManager::DrawImage(this->_path, &this->_vertices[0], &_colors[0]);
}

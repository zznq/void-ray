#include <cmath>

#include "Sprite.hpp"

void Sprite::Render() {
	BaseEntity::Render();
	
	RenderManager::DrawImage(this->_path, &this->_vertices[0]);
}

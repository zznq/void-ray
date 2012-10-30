#include <cmath>

#include "Sprite.hpp"

void Sprite::Render() {
	Entity::Render();
	
	RenderManager::DrawImage(this->_path, &this->_vertices[0]);
}

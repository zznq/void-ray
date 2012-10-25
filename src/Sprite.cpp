#include <cmath>

#include "Sprite.hpp"

void Sprite::Render() {
	Vector3 pos = this->getPosition();

	RenderManager::MoveAndRotate(pos, 0, RenderManager::ROTATEZ);

	RenderManager::DrawImage(this->_path, &this->_vertices[0]);
}

#include "util/Vector3.hpp"
#include "ChildSprite.hpp"

ChildSprite::ChildSprite(BaseEntity* parent, std::string path, float offsetx)
	: Sprite(parent, path, 14)
{
	this->_position = Vector3(offsetx, -28.0f, 0.0f);
}
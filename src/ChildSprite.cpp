#include "util/Vector3.hpp"
#include "ChildSprite.hpp"

ChildSprite::ChildSprite(BaseEntity* parent, std::string path, float offsetx, float offsety)
	: Sprite(parent, path, 14)
{
	this->position = Vector3(offsetx, offsety, 0.0f);
	this->SetFlag(entity_propulsion);
}

ChildSprite::ChildSprite(std::string path, float offsetx, float offsety)
	: Sprite(path, 14)
{
	this->position = Vector3(offsetx, offsety, 0.0f);
	this->SetFlag(entity_propulsion);
}

void ChildSprite::Update(double time_elapsed) {
	if(parent != NULL && HasFlag(entity_propulsion)) {
		this->_opacity = (this->parent->Speed() / this->parent->MaxSpeed()) * 10;
	}
}
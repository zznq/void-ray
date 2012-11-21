#include <cmath>

#include "util/Vector3.hpp"
#include "ChildSprite.hpp"

ChildSprite::ChildSprite(BaseEntity* parent, std::string path, float offsetx, float offsety)
	: Sprite(parent, path, 14)
{
	this->position = Vector3(offsetx, offsety, 0.0f);
	this->_origPosition = this->position;
	this->SetFlag(entity_propulsion);
}

ChildSprite::ChildSprite(std::string path, float offsetx, float offsety)
	: Sprite(path, 14)
{
	this->position = Vector3(offsetx, offsety, 0.0f);
	this->_origPosition = this->position;
	this->SetFlag(entity_propulsion);
}

void ChildSprite::Update(double time_elapsed) {
	if(parent != NULL && HasFlag(entity_propulsion)) {
		float unitSpeed = (this->parent->Speed() / this->parent->MaxSpeed());

		this->_opacity = unitSpeed * 3;

		float unitScale = unitSpeed * 3;

		if(unitScale > 1.0f) {
			unitScale = 1.0f;
		}

		float delta = this->_scale - (this->_scale * unitScale);
		
		/*if(this->_origPosition.x > 0.0f) {
			this->position.x = this->_origPosition.x + (delta / 2);
		} else {
			this->position.x = this->_origPosition.x - (delta / 2);
		}*/
		this->position.y = this->_origPosition.y + delta;
	
		this->scale = Vector3(unitScale, unitScale, 1);
	}
}

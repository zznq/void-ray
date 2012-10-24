#include "Entity.hpp"
#include <stdio.h>

Vector3 Entity::getPosition() {
	if(this->parent != NULL) {
		return this->parent->getPosition() + this->position;
	} else {
		return this->position;		
	}
}

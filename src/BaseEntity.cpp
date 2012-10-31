#include "BaseEntity.hpp"
#include <stdio.h>
#include <vector>

float* BaseEntity::getViewModelMatrix() {
	this->transform.reset();
	
	if(this->parent != NULL) {
		float* parent = this->parent->getViewModelMatrix();
		this->transform.viewMatrix = std::vector<float> (parent, parent + 16);
	}
 
	this->transform.translate(this->_position.x, this->_position.y, this->_position.z);
	this->transform.rotate(this->_rotation.x, this->_rotation.y, this->_rotation.z);

	return &this->transform.viewMatrix[0];
}

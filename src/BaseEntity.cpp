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

void BaseEntity::loadDefaults() {
	this->transform = Transform();
	this->behaviors = new SteeringBehaviors(this);

	this->target = Vector3();
	this->_rotation = Vector3();
	this->_velocity = Vector3();

	this->_heading = Vector3(this->_velocity);
	this->_heading.normalize();

	this->_side = Perp(this->_heading);
	this->_up = Vector3(0.0f, 1.0f, 0.0f);
	this->_left = Vector3(-1.0f, 0.0f, 0.0f);

	this->_mass = 0;
	this->_maxSpeed = 0.0;
	this->_maxForce = 0.0;
	this->_maxTurnRate = 0.0;
	this->_timeElapsed = 0.0;
};
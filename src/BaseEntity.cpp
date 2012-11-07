#include "BaseEntity.hpp"
#include "GameController.hpp"
#include <stdio.h>
#include <vector>
#include <cmath>

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

void BaseEntity::Update(double time_elapsed)  {
	this->_timeElapsed = time_elapsed;

	float _distance = distance(this->target, this->_position);
	
	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);
	
	this->_velocity.truncate(this->_maxSpeed);

	this->_position += (this->_velocity * this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		Vector3 newHeading = Vector3(this->_velocity);
		newHeading.normalize();
		this->_heading = newHeading;

		this->_side = Perp(this->_heading);
	}

	this->_rotation.z = this->Rotation();

	this->WrapWorld();
};

void BaseEntity::Render() {
	for(std::vector<BaseEntity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}

	RenderManager::LoadMatrix(this->getViewModelMatrix(), false);
};

void BaseEntity::WrapWorld() {
	if(abs(this->_position.x) > (GameController::Width() / 2)) {
		this->_position.x = (GameController::Width() / 2) * (this->_position.x / -this->_position.x);
	}

	if(abs(this->_position.y) > (GameController::Height() / 2)) {
		this->_position.y = (GameController::Height() / 2) * (this->_position.y / -this->_position.y);
	}
};
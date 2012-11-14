#include "BaseEntity.hpp"
#include "GameWorld.hpp"
#include <stdio.h>
#include <vector>
#include <cmath>

float* BaseEntity::ViewModelMatrix() {
	this->transform.reset();
	
	if(this->parent != NULL) {
		float* parent = this->parent->ViewModelMatrix();
		this->transform.viewMatrix = std::vector<float> (parent, parent + 16);
	}
 
	this->transform.translate(this->position.x, this->position.y, this->position.z);
	this->transform.rotate(this->rotation.x, this->rotation.y, this->rotation.z);

	return &this->transform.viewMatrix[0];
};

Vector3 BaseEntity::Position() {
	Vector3 pos = Vector3(this->position);
		
	if(this->parent != NULL) {
		pos += this->parent->Position();
	}
 
	return pos;
};

void BaseEntity::_LoadDefaults() {
	this->transform = Transform();
	this->behaviors = new SteeringBehaviors(this);

	this->target = Vector3();
	this->rotation = Vector3();
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

	float _distance = distance(this->target, this->position);
	
	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / (float)this->_mass;

	this->_velocity += (acceleration * (float)this->_timeElapsed);
	
	this->_velocity.truncate(this->_maxSpeed);

	this->position += (this->_velocity * (float)this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		Vector3 newHeading = Vector3(this->_velocity);
		newHeading.normalize();
		this->_heading = newHeading;

		this->_side = Perp(this->_heading);
	}

	this->rotation.z = this->Rotation();

	this->WrapWorld();
};

void BaseEntity::Render() {
	for(std::vector<BaseEntity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
		if((*it)) {
			(*it)->Render();
		}
	}

	if(this->_drawHelpers) {
		RenderManager::LoadIdentity();

		float _heading[] = {
			this->position.x,
			this->position.y,
			this->position.x + (this->_heading.x * this->_helperMagnitude),
			this->position.y + (this->_heading.y * this->_helperMagnitude)
		};

		float _headingColors[] = {
			255,  0, 0, 255,
			255,  0, 0, 255
		};

		RenderManager::DrawLine(_heading, _headingColors);

		float _side[] = {
			this->position.x,   this->position.y,
			this->position.x + (this->_side.x * this->_helperMagnitude), this->position.y + (this->_side.y  * this->_helperMagnitude)
		};

		float _sideColors[] = {
			0,  0, 255, 255,
			0,  0, 255, 255
		};

		RenderManager::DrawLine(_side, _sideColors);
	}

	RenderManager::LoadMatrix(this->ViewModelMatrix(), false);
};

void BaseEntity::WrapWorld() {
	if(abs(this->position.x) > (GameWorld::Width() / 2)) {
		this->position.x = (float)(GameWorld::Width() / 2) * (this->position.x / -this->position.x);
	}

	if(abs(this->position.y) > (GameWorld::Height() / 2)) {
		this->position.y = (float)(GameWorld::Height() / 2) * (this->position.y / -this->position.y);
	}
};

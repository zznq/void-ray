#include <cmath>
#include <stdio.h>
#include <vector>

#include "BaseEntity.hpp"
#include "GameWorld.hpp"

float* BaseEntity::ViewModelMatrix() {
	this->transform.reset();
	
	if(this->parent != NULL) {
		float* parent = this->parent->ViewModelMatrix();
		this->transform.viewMatrix = std::vector<float> (parent, parent + 16);
	}
 
	this->transform.translate(this->position.x, this->position.y, this->position.z);
	this->transform.rotate(this->rotation.x, this->rotation.y, this->rotation.z);

	this->transform.scale(this->scale.x, this->scale.y, this->scale.z);

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

	this->scale = Vector3(1.0f,1.0f,1.0f);

	this->_up = Vector3(0.0f, 1.0f, 0.0f);
	this->_left = Vector3(-1.0f, 0.0f, 0.0f);

	this->_heading = Vector3(Vector3(-1.0f, 1.0f, 0.0f));
	this->_heading.normalize();

	this->_side = Perp(this->_heading);
	this->_mass = 0;
	this->_maxSpeed = 0.0;
	this->_maxForce = 0.0;
	this->_maxTurnRate = 0.0;
	this->_timeElapsed = 0.0;

  this->_radius = 0.0;

	this->_flags = entity_none;
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

	for(std::vector<BaseEntity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
		if((*it)) {
			(*it)->Update(time_elapsed);
		}
	}
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

		Vector3 obsLocal = this->ConvertToLocal(Vector3(20.0f, 60.0f, 0.0f));

		float _obs[] = {
			0,   0,
			obsLocal.x, obsLocal.y
		};

		float _obsColors[] = {
			0, 255,  0, 255,
			0, 255,  0, 255
		};

		RenderManager::LoadMatrix(this->ViewModelMatrix(), false);

//		RenderManager::DrawLine(_obs, _obsColors);

		RenderManager::LoadIdentity();

    Vector3 obsWorld = this->ConvertToWorld(obsLocal);

    float _obsWorld[] = {
      this->position.x, this->position.y,
      obsWorld.x, obsWorld.y
    };

    float _obsWorldColor[] = {
      100, 255, 0, 255,
      100, 255, 0, 255
    };

    RenderManager::DrawLine(_obsWorld, _obsWorldColor);
	}

	RenderManager::LoadMatrix(this->ViewModelMatrix(), false);
};

Vector3 BaseEntity::ConvertToLocal(Vector3 pos) {
	Vector3 delta = pos - this->Position();

	float r = -(this->Rotation());
	Vector3 result = Vector3(cosf(r) * delta.x + -sinf(r) * delta.y, sinf(r) * delta.x + cosf(r) * delta.y, 0.0f);

  printf("Local x: %f  y: %f  z: %f\n", result.x, result.y, result.z);
	return result;
}

Vector3 BaseEntity::ConvertToWorld(Vector3 pos) {
  float r = this->Rotation();

	Vector3 result = Vector3(cosf(r) * pos.x + -sinf(r) * pos.y, sinf(r) * pos.x + cosf(r) * pos.y, 0.0f);

  result.x = result.x + this->Position().x;
  result.y = result.y + this->Position().y;

  printf("World x: %f  y: %f  z: %f\n", result.x, result.y, result.z);
  return result;
}

void BaseEntity::WrapWorld() {
	if(abs(this->position.x) > (GameWorld::Width() / 2)) {
		this->position.x = (float)(GameWorld::Width() / 2) * (this->position.x / -this->position.x);
	}

	if(abs(this->position.y) > (GameWorld::Height() / 2)) {
		this->position.y = (float)(GameWorld::Height() / 2) * (this->position.y / -this->position.y);
	}
};

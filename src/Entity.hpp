//
//  MovingEntity.h
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef void_ray_Entity_h
#define void_ray_Entity_h

#include <vector>
#include <cstddef>

#include "util/Vector3.hpp"
#include "util/Transform.hpp"
#include "RenderManager.hpp"
#include "SteeringBehaviors.hpp"

class SteeringBehaviors;

class Entity {
protected:
    SteeringBehaviors *behaviors;
    
	Vector3 _velocity;
	//Confused about how to set/use heading
	Vector3 _heading;
	Vector3 _side;
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
	double _timeElapsed;

public:
	Vector3 _rotation;
	Vector3 _position;
	Vector3 _scale;

	Transform transform;

	Entity* parent;

	std::vector<Entity*> children;

    Entity() {
		this->parent = NULL;
		this->transform = Transform();
	};

	Entity(Entity* parent) { 
		this->parent = parent;
		//Add myself to the children list of my new parent
		this->parent->AddChild(this);
		this->transform = Transform();
	};

	~Entity() {
		for(std::vector<Entity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
			if((*it)) {
				delete (*it);
			}
		}
	};
    
	void AddChild(Entity* child) { this->children.push_back(child); };

    virtual void Update(double time_elapsed) {};
    virtual void Render() {
		RenderManager::LoadMatrix(this->getViewModelMatrix(), false);	
	};

	Vector3 target;    
    double maxSpeed() { return this->_maxSpeed; }
    Vector3 velocity() { return this->_velocity; }
	float* getViewModelMatrix();

	virtual void UpdateTarget(int x, int y) {}
};

#endif

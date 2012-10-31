//
//  MovingEntity.h
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef void_ray_BaseEntity_h
#define void_ray_BaseEntity_h

#include <vector>
#include <cstddef>

#include "util/Vector3.hpp"
#include "util/Transform.hpp"
#include "RenderManager.hpp"
#include "SteeringBehaviors.hpp"

class SteeringBehaviors;

class BaseEntity {
private:
	int _id;
	
	//used by the constructor to give each entity a unique ID
	int NextValidID(){static int NextID = 0; return NextID++;}
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

	enum { default_entity_type };
public:
	Vector3 _rotation;
	Vector3 _position;
	Vector3 _scale;

	Transform transform;

	BaseEntity* parent;

	std::vector<BaseEntity*> children;

    BaseEntity() : _id(NextValidID()) {
		this->parent = NULL;
		this->transform = Transform();
	};

	BaseEntity(BaseEntity* parent) : _id(NextValidID()) { 
		this->parent = parent;
		//Add myself to the children list of my new parent
		this->parent->AddChild(this);
		this->transform = Transform();
	};

	~BaseEntity() {
		for(std::vector<BaseEntity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
			if((*it)) {
				delete (*it);
			}
		}
	};
    
	void AddChild(BaseEntity* child) { this->children.push_back(child); };

    virtual void Update(double time_elapsed) {};
    virtual void Render() {
		
		RenderManager::LoadMatrix(this->getViewModelMatrix(), false);	
	};

	Vector3 target;    
    double maxSpeed() { return this->_maxSpeed; }
    Vector3 velocity() { return this->_velocity; }
	float* getViewModelMatrix();

	virtual void UpdateTarget(int x, int y) {}

	double MaxForce() { return this->_maxForce; }
};

#endif

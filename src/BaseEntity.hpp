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
	Vector3 _velocity;
	//Confused about how to set/use heading
	Vector3 _heading;
	Vector3 _side;
	Vector3 _up;
	Vector3 _left;
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
	double _timeElapsed;

	enum { default_entity_type };

	void loadDefaults();
public:
	SteeringBehaviors *behaviors;
	BaseEntity* parent;
	
	Vector3 target;
	Vector3 _rotation;
	Vector3 _position;
	Vector3 _scale;

	Transform transform;

	std::vector<BaseEntity*> children;

    BaseEntity() : _id(NextValidID()) {
		this->parent = NULL;

		this->loadDefaults();
	};

	BaseEntity(BaseEntity* parent) : _id(NextValidID()) { 
		this->parent = parent;
		//Add myself to the children list of my new parent
		this->parent->AddChild(this);

		this->loadDefaults();
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
		for(std::vector<BaseEntity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
			if((*it)) {
				(*it)->Render();
			}
		}

		RenderManager::LoadMatrix(this->getViewModelMatrix(), false);
	};
 
    double maxSpeed() const { return this->_maxSpeed; }
    Vector3 velocity() const { return this->_velocity; }
	double Speed()const{return vectorMag(this->_velocity);}
	double SpeedSq()const{return vectorMagSq(this->_velocity);}

	float* getViewModelMatrix();

	virtual void UpdateTarget(int x, int y) {}

	double MaxForce() const { return this->_maxForce; }

	Vector3 Heading() const { return this->_heading; }
	Vector3 Side() const { return this->_side; }
};

#endif

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
	//used by the constructor to give each entity a unique ID
	int NextValidID(){static int NextID = 0; return NextID++;}

protected:
	bool _drawHelpers;
	int _id;
	enum { default_entity_type };
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
	double _timeElapsed;
	float _helperMagnitude;

	Vector3 _velocity;
	//Confused about how to set/use heading
	Vector3 _heading;
	Vector3 _side;
	Vector3 _up;
	Vector3 _left;
	
	void _LoadDefaults();
public:
	Transform transform;
	Vector3 target;
	Vector3 rotation;
	Vector3 position;
	Vector3 scale;

	BaseEntity* parent;
	std::vector<BaseEntity*> children;

	SteeringBehaviors *behaviors;

    BaseEntity() : _id(NextValidID()), _drawHelpers(false), _helperMagnitude(40) {
		this->parent = NULL;

		this->_LoadDefaults();
	};

	BaseEntity(BaseEntity* parent) : _id(NextValidID()), _drawHelpers(false), _helperMagnitude(40) { 
		this->parent = parent;

		//Add myself to the children list of my new parent
		this->parent->AddChild(this);

		this->_LoadDefaults();
	};

	~BaseEntity() {
		for(std::vector<BaseEntity*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
			if((*it)) {
				delete (*it);
			}
		}
	};
    
	void AddChild(BaseEntity* child) { this->children.push_back(child); };

    virtual void Update(double time_elapsed);
    virtual void Render();
 
	Vector3 Velocity() const { return this->_velocity; }
    double MaxSpeed() const { return this->_maxSpeed; }
	double Speed()const{return vectorMag(this->_velocity);}
	double SpeedSq()const{return vectorMagSq(this->_velocity);}
	double MaxForce() const { return this->_maxForce; }

	float* ViewModelMatrix();
	Vector3 Heading() const { return this->_heading; }
	Vector3 Side() const { return this->_side; }

	float Rotation() const { 
		float sign = (this->_heading * this->_left) > 0 ? 1.0f : -1.0f;
		float radians = acos(this->_heading * this->_up);

		return sign * radians;
	}

	double ElapsedTime() const { return this->_timeElapsed; }
	void WrapWorld();
	virtual void UpdateTarget(int x, int y) {}
};

#endif

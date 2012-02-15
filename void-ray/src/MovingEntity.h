//
//  MovingEntity.h
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef void_ray_MovingEntity_h
#define void_ray_MovingEntity_h

#include "util/Vector3.h"
#include "SteeringBehaviors.h"

class SteeringBehaviors;

class MovingEntity {
    
protected:
    SteeringBehaviors *behaviors;
    
	Vector3 _velocity;
	Vector3 _heading;
	Vector3 _side;
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
	double _timeElapsed;
    
public:
    Vector3 position;
	Vector3 target;
    
    double maxSpeed() { return this->_maxSpeed; }
    Vector3 velocity() { return this->_velocity; }

	MovingEntity() {};
    
    virtual void Update(double time_elapsed) {};
    virtual void Render() {};
};

#endif

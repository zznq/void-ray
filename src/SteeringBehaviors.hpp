//
//  SteeringBehaviors.h
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef void_ray_SteeringBehaviors_h
#define void_ray_SteeringBehaviors_h

#include "util/Vector3.hpp"
#include "BaseEntity.hpp"

class BaseEntity;

class SteeringBehaviors {
private:
    BaseEntity *_vehicle;
	Vector3    _steeringForce;

	enum behavior_type {
		none	= 0x00000,
		seek	= 0x00002,
		flee	= 0x00004,
		arrive  = 0x00008
	};

	int _flags;

	void SetFlag(behavior_type flag) {
		_flags |= flag;
	}
	void RemoveFlag(behavior_type flag) {
		_flags ^= flag;
	}

	bool On(behavior_type flag) {
		return (_flags & flag) == flag;
	}

	enum Deceleration{slow = 3, normal = 2, fast = 1};
	Deceleration _deceleration;

	static const double _panicDistance;

	bool AccumulateForce(Vector3 &RunningTot, Vector3 ForceToAdd);

	Vector3 Seek(const Vector3 target);
    Vector3 Flee(const Vector3 target);
    Vector3 Arrive(const Vector3 target, Deceleration deceleration);
public:
    SteeringBehaviors(BaseEntity* vehicle) : _vehicle(vehicle) {
		_flags = none;
		_deceleration = slow;
	}
    
    Vector3 Calculate();
    double ForwardComponent();
	double SideComponent();
    
	/*
    void SetPath();
    void SetTarget(Vector3 target);
    */

	void seekOn() { SetFlag(seek); }
	void fleeOn() { SetFlag(flee); }
	void arriveOn() { SetFlag(arrive); }

	void seekOff() { RemoveFlag(seek); }
	void fleeOff() { RemoveFlag(flee); }
	void arriveOff() { RemoveFlag(arrive); }
};

#endif

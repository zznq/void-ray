#ifndef VOID_RAY_STEERING_BEHAVIORS
#define VOID_RAY_STEERING_BEHAVIORS

#include <cmath>
#include <time.h>

#include "util/Vector3.hpp"
#include "BaseEntity.hpp"

#define TwoPi (3.14159265359 * 2)

class BaseEntity;

class SteeringBehaviors {
private:
    BaseEntity* _vehicle;
	Vector3    _steeringForce;

	enum behavior_type {
		none	= 0x00000,
		seek	= 0x00002,
		flee	= 0x00004,
		arrive  = 0x00008,
		pursue	= 0x00020,
		evade   = 0x00040,
		wander  = 0x00080
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

	BaseEntity *evador1;
	BaseEntity *pursuer1;

	double _wanderRadius;
	double _wanderDistance;
	double _wanderJitter;

	Vector3 _wanderTarget;

	bool AccumulateForce(Vector3 &RunningTot, Vector3 ForceToAdd);

	Vector3 Seek(const Vector3 target);
    Vector3 Flee(const Vector3 target);
    Vector3 Arrive(const Vector3 target, Deceleration deceleration);
	Vector3 Pursue(const BaseEntity* evador);
	Vector3 Evade(const BaseEntity* pursuer);
	Vector3 Wander(); //Broken :(

	double LookAheadTime(const BaseEntity* entity, Vector3 targetPos);

	void ObstacleAvoidance(const std::vector<BaseEntity*> &obstacles);
public:
    SteeringBehaviors(BaseEntity* vehicle) : _vehicle(vehicle) {
		_flags = none;
		_deceleration = fast;

		_wanderRadius = 125;
		_wanderDistance = 50;
		_wanderJitter = 150;

		srand((int)time(NULL));

		//stuff for the wander behavior
		double theta = (double)rand() * TwoPi;

		//create a vector to a target position on the wander circle
		this->_wanderTarget = Vector3((float)(_wanderRadius * cos(theta)),
									(float)(_wanderRadius * sin(theta)), 0.0f);
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
	void pursueOn(BaseEntity *evador) { 
		SetFlag(pursue);
		this->evador1 = evador;
	}
	void wanderOn() { SetFlag(wander); }

	void evadeOn(BaseEntity *pursuer) { 
		SetFlag(evade);
		this->pursuer1 = pursuer;
	}

	void seekOff() { RemoveFlag(seek); }
	void fleeOff() { RemoveFlag(flee); }
	void arriveOff() { RemoveFlag(arrive); }
	void pursueOff() { 
		RemoveFlag(pursue);
		this->evador1 = NULL;
	}
	
	void evadeOff() { 
		RemoveFlag(evade); 
		this->pursuer1 = NULL;
	}
	
	void wanderOff() { RemoveFlag(wander); }
};

#endif
#include <algorithm>

#include "SteeringBehaviors.hpp"

//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool SteeringBehaviors::AccumulateForce(Vector3 &RunningTot, Vector3 ForceToAdd)
{
	//calculate how much steering force the vehicle has used so far
	double MagnitudeSoFar = vectorMag(RunningTot);

	//calculate how much steering force remains to be used by this vehicle
	double MagnitudeRemaining = _vehicle->MaxForce() - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	double MagnitudeToAdd = vectorMag(ForceToAdd);
  
	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
	RunningTot += ForceToAdd;
	}
	else
	{
	Vector3 forceNormal = Vector3(ForceToAdd);
	forceNormal.normalize();
	//add it to the steering force
	RunningTot += (forceNormal * MagnitudeRemaining); 
	}

	return true;
}

/*
void SteeringBehaviors::ObstacleAvoidance(const std::vector<BaseEntity*> &obstacles) {
	double minDetectionBox = 10;
	double _detectionBox = minDetectionBox + (this->_vehicle->Speed() / this->_vehicle->MaxSpeed()) * minDetectionBox;

	((Agent)this->_vehicle)->world->TagObstaclesWithinViewRange(this->_vehicle, minDetectionBox);

	//Closest Intersecting Obstacle (CIB)
	BaseEntity* closestIntersectingObstacle = NULL;

	//Distance to CIB
	double distToClosestIP = 100000;//maxDouble;

	Vector3 localPosOfCIB;

	std::vector<BaseEntity*>::const_iterator curObstacle = obstacles.begin();

	while(curObstacle != obstacles.end()) {
		if((*curObstacle)->IsTagged())) {
			//Transform the curObstacle position into local coods in relation to the _vehicle
			//This needs to take into account rotation!!!!
			Vector3 localPos = this->_vehicle->Position() - (*curObstacle)->Position();

			//if x is negative it is behind us and we don't need to worry about it 
			if(localPos.x >= 0) {
				double expandedRadius = (*curObstacle)->Radius() + this->_vehicle->Radius();

				if(fabs(localPos.y) < expandedRadius) {
					/*
					 * 	Line/Circle intersection:
					 *  The intersection points are given by the folowing formula
					 *  x = cX +/-sqrt(r^2-cY^2) for y=0
					 * /
					 double cX = localPos.x;
					 double cY = localPos.y;
					 
					 double sqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cY*cY);
					 
					 double ip = cX - sqrtPart;
					 
					 if(ip <= 0) {
					 	ip = cX + sqrtPart;
					 }
				}
			}
		}
	}
} */

Vector3 SteeringBehaviors::Calculate() {
	this->_steeringForce.zero();
	Vector3 force;

	if(On(flee)) {
		
		force = Flee(_vehicle->target);

		if (!AccumulateForce(_steeringForce, force)) return _steeringForce;
	}

	if(On(seek)) {
		force = Seek(_vehicle->target);

		if (!AccumulateForce(_steeringForce, force)) return _steeringForce;
	}

	if(On(arrive)) {
		force = Arrive(_vehicle->target, _deceleration);

		if (!AccumulateForce(_steeringForce, force)) return _steeringForce;
	}

	if(On(pursue)) {
		force = Pursue(this->evador1);

		if (!AccumulateForce(_steeringForce, force)) return _steeringForce;
	}

	if(On(evade)) {
		force = Evade(this->pursuer1);

		if (!AccumulateForce(_steeringForce, force)) return _steeringForce;
	}

	if(On(wander)) {
		force = Wander();
		
		if(!AccumulateForce(_steeringForce, force)) return _steeringForce;
	}

	return _steeringForce;
}

double SteeringBehaviors::ForwardComponent(){
    return _vehicle->Heading() * _steeringForce;
}

double SteeringBehaviors::SideComponent(){
    return _vehicle->Side() * _steeringForce;
}

Vector3 SteeringBehaviors::Seek(const Vector3 target) {
    Vector3 desiredVelocity = (target - _vehicle->position);
	desiredVelocity.normalize();
	desiredVelocity *= _vehicle->MaxSpeed();
    
	return desiredVelocity - _vehicle->Velocity();
}

const double SteeringBehaviors::_panicDistance = 150.0;

Vector3 SteeringBehaviors::Flee(const Vector3 target) {
	Vector3 toTarget = _vehicle->position - target;

	double dist = vectorMagSq(toTarget);

	Vector3 desiredVelocity;

	if(dist > SteeringBehaviors::_panicDistance * SteeringBehaviors::_panicDistance) {
		const double decelerationTween = 0.3;

		double speed = dist * ((double)normal * decelerationTween);

		speed = std::min(speed, _vehicle->MaxSpeed());

		desiredVelocity = toTarget * (speed / dist);
	} else {
		desiredVelocity = (_vehicle->position - target);
		desiredVelocity.normalize();
		desiredVelocity *= _vehicle->MaxSpeed();
	}

	return desiredVelocity - _vehicle->Velocity();
}

Vector3 SteeringBehaviors::Arrive(const Vector3 target, Deceleration deceleration) {
	Vector3 toTarget = target - _vehicle->position;

	double dist = vectorMag(toTarget);

	if(dist > 0) {
		const double decelerationTween = 0.3;

		double speed = dist * ((double)deceleration * decelerationTween);

		speed = std::min(speed, _vehicle->MaxSpeed());

		Vector3 desiredVelocity = toTarget * (speed / dist);
		return desiredVelocity - _vehicle->Velocity();
	}

	return Vector3();
}

double SteeringBehaviors::LookAheadTime(const BaseEntity* entity, Vector3 targetPos) {
	Vector3 toTargetNormal = targetPos - entity->position;
	toTargetNormal.normalize();

	double dot = entity->Heading() * toTargetNormal;

	const double coefficient = 0.5;

	return (dot - 1) * -coefficient;
}

Vector3 SteeringBehaviors::Pursue(const BaseEntity *evador) {
	Vector3 toEvador = evador->position - this->_vehicle->position;

	double relativeHeader = (this->_vehicle->Heading() * evador->Heading());

	if((toEvador * this->_vehicle->Heading()) > 0) {
		return Seek(evador->position);
	}

	double lookAheadTime = vectorMag(toEvador) / (this->_vehicle->MaxSpeed() + evador->Speed());

	lookAheadTime += this->LookAheadTime(this->_vehicle, evador->position);

	return Seek(evador->position + evador->Velocity()  * lookAheadTime);
}

Vector3 SteeringBehaviors::Evade(const BaseEntity *pursuer) {
	Vector3 toPursuer = pursuer->position - this->_vehicle->position;

	double lookAheadTime = vectorMag(toPursuer) / (this->_vehicle->MaxSpeed() + pursuer->Speed());

	lookAheadTime += this->LookAheadTime(this->_vehicle, pursuer->position);

	return Flee(pursuer->position + pursuer->Velocity()  * lookAheadTime);
}

Vector3 SteeringBehaviors::Wander() {
	double xRand = ((((rand() % 1000) + 1.0) / 1000.0) * 2.0) - 1.0;
	double yRand = ((((rand() % 1000) + 1.0) / 1000.0) * 2.0) - 1.0;
	
	double JitterThisTimeSlice = this->_wanderJitter * this->_vehicle->ElapsedTime();

	this->_wanderTarget += Vector3(xRand * JitterThisTimeSlice, yRand * JitterThisTimeSlice, 0);
	this->_wanderTarget.normalize();

	this->_wanderTarget *= this->_wanderRadius;

	Vector3 targetLocal = this->_wanderTarget + Vector3(_wanderDistance, 0, 0);

	Vector3 targetWorld = targetLocal + this->_vehicle->position + Vector3(cos(this->_vehicle->Rotation()), sin(this->_vehicle->Rotation()), 0);

	return targetWorld - this->_vehicle->position;
}

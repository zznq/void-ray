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

	return _steeringForce;
}

double SteeringBehaviors::ForwardComponent(){
    return _vehicle->Heading() * _steeringForce;
}

double SteeringBehaviors::SideComponent(){
    return _vehicle->Side() * _steeringForce;
}

Vector3 SteeringBehaviors::Seek(const Vector3 target) {
    Vector3 desiredVelocity = (target - _vehicle->_position);
	desiredVelocity.normalize();
	desiredVelocity *= _vehicle->maxSpeed();
    
	return desiredVelocity - _vehicle->velocity();
}

Vector3 SteeringBehaviors::Flee(const Vector3 target) {
     Vector3 desiredVelocity = (_vehicle->_position - target);
	desiredVelocity.normalize();
	desiredVelocity *= _vehicle->maxSpeed();
    
	return desiredVelocity - _vehicle->velocity();
}

Vector3 SteeringBehaviors::Arrive(const Vector3 target, Deceleration deceleration) {
	Vector3 toTarget = target - _vehicle->_position;

	double dist = vectorMag(toTarget);

	if(dist > 0) {
		const double decelerationTween = 0.3;

		double speed = dist * ((double)deceleration * decelerationTween);

		speed = std::min(speed, _vehicle->maxSpeed());

		Vector3 desiredVelocity = toTarget * (speed / dist);
		return desiredVelocity - _vehicle->velocity();
	}

	return Vector3();
}
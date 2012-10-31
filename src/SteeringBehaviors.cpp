//
//  SteeringBehaviors.cpp
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "SteeringBehaviors.hpp"

//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool SteeringBehaviors::AccumulateForce(Vector3 &RunningTot, Vector3 ForceToAdd)
{
	printf("ForceToAdd: (%d, %d, %d)\n", ForceToAdd.x, ForceToAdd.y, ForceToAdd.z);
	printf("RunningTot: (%d, %d, %d)\n", RunningTot.x, RunningTot.y, RunningTot.z);

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

Vector3 SteeringBehaviors::Seek(Vector3 target){

    Vector3 desiredVelocity = (target - _vehicle->_position);
	desiredVelocity.normalize();
	desiredVelocity *= _vehicle->maxSpeed();
    
	return desiredVelocity - _vehicle->velocity();
}

Vector3 SteeringBehaviors::Flee(Vector3 target){
     Vector3 desiredVelocity = (_vehicle->_position - target);
	desiredVelocity.normalize();
	desiredVelocity *= _vehicle->maxSpeed();
    
	return desiredVelocity - _vehicle->velocity();
}

Vector3 SteeringBehaviors::Arrive(Vector3 target) {
    return this->Seek(this->_vehicle->target);
}

Vector3 SteeringBehaviors::Calculate(){
    Vector3 force;
	this->_steeringForce += this->Seek(this->_vehicle->target);

	if (!AccumulateForce(this->_steeringForce, force)) return this->_steeringForce;

	this->_steeringForce.truncate(this->_vehicle->MaxForce());

	return this->_steeringForce;
}

Vector3 SteeringBehaviors::ForwardComponent(){
    return this->Seek(this->_vehicle->target);
}

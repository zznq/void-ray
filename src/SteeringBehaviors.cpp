//
//  SteeringBehaviors.cpp
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "SteeringBehaviors.hpp"

Vector3 SteeringBehaviors::Seek(Vector3 target){

    Vector3 desiredVelocity = (target - _vehicle->position);
	desiredVelocity.normalize();
	desiredVelocity *= _vehicle->maxSpeed();
    
	return desiredVelocity - _vehicle->velocity();
}

Vector3 SteeringBehaviors::Flee(Vector3 target){
    return this->Seek(this->_vehicle->target);
}

Vector3 SteeringBehaviors::Arrive(Vector3 target) {
    return this->Seek(this->_vehicle->target);
}

Vector3 SteeringBehaviors::Calculate(){
    return this->Seek(this->_vehicle->target);
}

Vector3 SteeringBehaviors::ForwardComponent(){
    return this->Seek(this->_vehicle->target);
}

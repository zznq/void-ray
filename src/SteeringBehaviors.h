//
//  SteeringBehaviors.h
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef void_ray_SteeringBehaviors_h
#define void_ray_SteeringBehaviors_h

#include "util/Vector3.h"
#include "MovingEntity.h"

class MovingEntity;

class SteeringBehaviors{
    MovingEntity *_vehicle;
public:
    SteeringBehaviors(MovingEntity* vehicle) : _vehicle(vehicle) {}
    
    Vector3 Seek(Vector3 target);
    Vector3 Flee(Vector3 target);
    Vector3 Arrive(Vector3 target);
    
    Vector3 Calculate();
    Vector3 ForwardComponent();
    
    void SetPath();
    void SetTarget(Vector3 target);
    
    bool seekOn;
    bool fleeOn;
    bool arriveOn;
};

#endif

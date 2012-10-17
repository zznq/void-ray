//
//  MovingEntity.h
//  void-ray
//
//  Created by Joe Buszkiewic on 2/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef void_ray_Entity_h
#define void_ray_Entity_h

#include <vector>
#include "util/Vector3.h"

using namespace std;

class Entity {
    
public:
    Vector3 position;
	Vector3 scale;

	Entity* parent;    

	vector<Entity> children;

    Entity() { };
	Entity(Entity* parent) { 
		this->parent = parent;
		//Add myself to the children list of my new parent
		this->parent->AddChild(this);
	};
    
	void AddChild(Entity* child) { this->children.push_back(child); };

    virtual void Update(double time_elapsed) {};
    virtual void Render() {};
};

#endif

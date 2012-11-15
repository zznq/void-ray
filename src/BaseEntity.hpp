#ifndef VOID_RAY_BASE_ENTITY
#define VOID_RAY_BASE_ENTITY

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
	int _flags;
	int _id;

	enum { default_entity_type };
	enum entity_flag {
		entity_none		  = 0x00000,
		entity_near		  = 0x00002,
		entity_propulsion = 0x00004
	};
	
	double _mass;
	double _maxSpeed;
	double _maxForce;
	double _maxTurnRate;
	double _timeElapsed;
	double _radius;
	float _helperMagnitude;

	Vector3 _velocity;
	//Confused about how to set/use heading
	Vector3 _heading;
	Vector3 _side;
	Vector3 _up;
	Vector3 _left;

	void _LoadDefaults();
	void SetFlag(entity_flag flag) {
		_flags |= flag;
	};
	void RemoveFlag(entity_flag flag) {
		_flags ^= flag;
	};

	bool HasFlag(entity_flag flag) {
		return (entity_flag)(_flags & flag) == flag;
	};
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
    
	void AddChild(BaseEntity* child) { 
		this->children.push_back(child);
		child->parent = this;
	};

    virtual void Update(double time_elapsed);
    virtual void Render();
 
	Vector3 Velocity() const { return this->_velocity; }
    double MaxSpeed() const { return this->_maxSpeed; }
	double Speed()const{return vectorMag(this->_velocity);}
	double SpeedSq()const{return vectorMagSq(this->_velocity);}
	double MaxForce() const { return this->_maxForce; }
	double Radius() const { return this->_radius; }

	float* ViewModelMatrix();

	Vector3 Position();
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

	void SetEntityNearViewRange() {
		SetFlag(entity_near);
	}

	void ClearEntityNearViewRange() {
		RemoveFlag(entity_near);
	}

	bool IsTagged() {
		return this->_flags != entity_none;
	}

	Vector3 ConvertToLocal(Vector3 pos);
};

#endif
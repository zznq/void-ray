#include <cmath>
#include <SDL/SDL_opengl.h>
#include "Ship.h"

double const Ship::SHIP_HALF_HEIGHT = 0.2;
double const Ship::SHIP_HEIGHT_OFFSET = 0.1;
double const Ship::SHIP_HALF_WIDTH = 0.1;
double const Ship::SHIP_WIDTH_OFFSET = 0.0;

Ship::Ship()
{
	this->position = Vector3(0.0f, 0.0f, -5.0f);
	this->target = Vector3(0.0f, -0.0f, -5.0f);

	this->_velocity = Vector3(1.0f, 1.0f, -5.0f);
	this->_heading = Vector3(1.0f, -1.5f, -5.0f);
	this->_side = Vector3(0.0f, 0.0f, -5.0f);

	this->_mass = 1;
	this->_maxSpeed = 1;
	this->_maxForce = 10.0;
	this->_maxTurnRate = 150.0;
	this->_timeElapsed = 0.0;
    
    this->behaviors = new SteeringBehaviors(this);
}

void Ship::Update(double time_elapsed)
{
	this->_timeElapsed = time_elapsed;

    //int radians = acos(this->_velocity * this->_heading);

	Vector3 steeringForce = this->behaviors->Calculate();

	Vector3 acceleration = steeringForce / this->_mass;

	this->_velocity += (acceleration * this->_timeElapsed);

	this->position += (this->_velocity * this->_timeElapsed);

	if(vectorMagSq(this->_velocity) > 0.00000001){
		this->_velocity.normalize();
		this->_heading = this->_velocity;
	}
}

void Ship::Render(){
    float globalz = 0.0f;
    
    float topy = Ship::SHIP_HEIGHT_OFFSET + (Ship::SHIP_HALF_HEIGHT);
    float bottomy = Ship::SHIP_HEIGHT_OFFSET - (Ship::SHIP_HALF_HEIGHT);
    
    float leftx = Ship::SHIP_WIDTH_OFFSET - (Ship::SHIP_HALF_WIDTH);
    float rightx = Ship::SHIP_WIDTH_OFFSET + (Ship::SHIP_HALF_WIDTH);
    
    float tipx = 0.0f + this->position.x;
    float tipy = topy + this->position.y;
    
    float rightflankx = rightx + this->position.x;
    float rightflanky = bottomy + this->position.y;
    
    float leftflankx = leftx + this->position.x;
    float leftflanky = bottomy + this->position.y;
    
    // draw a triangle
    glBegin(GL_TRIANGLES);
        //glColor3f(1.0, 0.0, 0.0);
        glVertex3f(tipx, tipy, globalz);
        
        //glColor3f(0.0, 1.0, 0.0);
        glVertex3f(rightflankx, rightflanky, globalz);
    
        //glColor3f(0.0, 0.0, 1.0);
        glVertex3f(leftflankx, leftflanky, globalz);
    glEnd();
}
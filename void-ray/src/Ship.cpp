#include <cmath>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "Ship.h"

double const Ship::SHIP_HALF_HEIGHT = 0.2;
double const Ship::SHIP_HEIGHT_OFFSET = 0.1;
double const Ship::SHIP_HALF_WIDTH = 0.1;
double const Ship::SHIP_WIDTH_OFFSET = 0.0;

Ship::Ship(SDL_Surface* screen)
{
	this->_screen = screen;
 
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, -5.0f);

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
	SDL_Surface* temp = NULL;
	SDL_Surface* image = NULL;

	GLuint texture;			// This is a handle to our texture object
	GLenum texture_format;
	GLint  nOfColors;

	float globalz = 0.0f;

	if((temp = IMG_Load("resources/wreck_out_ship.png")) != NULL) {
		
		//Uint32 colorkey = SDL_MapRGB( temp->format, 0, 0, 0); // choose black
		// now tell SDL to remeber our choice
		//SDL_SetColorKey( temp, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
	
		image = SDL_DisplayFormatAlpha(temp);
		if(image == NULL){
			printf("Error Converting To Alpha : %s \n", SDL_GetError());
		}

		nOfColors = image->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (image->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }
 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
	 
		// Set the texture's stretching properties
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, image->w, image->h, 0,
		                  texture_format, GL_UNSIGNED_BYTE, image->pixels );

		// Bind the texture to which subsequent calls refer to
		glBindTexture( GL_TEXTURE_2D, texture );
		 
		glBegin( GL_QUADS );
			//Top-left vertex (corner)
			glTexCoord2i( 0, 0 );
			glVertex3f( this->position.x + 0.0f, this->position.y + 0.128f, globalz );
		 
			//Top-right vertex (corner)
			glTexCoord2i( 1, 0 );
			glVertex3f( this->position.x + 0.128f, this->position.y + 0.128f, globalz );
		 
			//Bottom-right vertex (corner)
			glTexCoord2i( 1, 1 );
			glVertex3f( this->position.x + 0.128f, this->position.y + 0.0f, globalz );
		 
			//Bottom-left vertex (corner)
			glTexCoord2i( 0, 1 );
			glVertex3f( this->position.x + 0.0f, this->position.y + 0.0f, globalz );
		glEnd();

		SDL_FreeSurface(temp);
		SDL_FreeSurface(image);
	} else {
		printf("Oh My Goodness, an error : %s \n", IMG_GetError());

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
}

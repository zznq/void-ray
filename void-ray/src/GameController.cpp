#include "GameController.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#elif defined __linux__
//Add Linux specific GLUT headers
#else
	#include "glut.h"
#endif

#include "Ship.h"


void GameController::Start(){
	this->timer.Start();
}

void GameController::Update(){
	this->ship->Update(this->timer.TimeElapsed());
}

void GameController::DrawShip(Ship *s){
  float globalz = 0.0f;

  float topy = Ship::SHIP_HEIGHT_OFFSET + (Ship::SHIP_HALF_HEIGHT);
  float bottomy = Ship::SHIP_HEIGHT_OFFSET - (Ship::SHIP_HALF_HEIGHT);

  float leftx = Ship::SHIP_WIDTH_OFFSET - (Ship::SHIP_HALF_WIDTH);
  float rightx = Ship::SHIP_WIDTH_OFFSET + (Ship::SHIP_HALF_WIDTH);

  float tipx = 0.0f + s->position.x;
  float tipy = topy + s->position.y;
  
  float rightflankx = rightx + s->position.x;
  float rightflanky = bottomy + s->position.y;

  float leftflankx = leftx + s->position.x;
  float leftflanky = bottomy + s->position.y;

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

void GameController::Render()
{
  // set up the camera
  glLoadIdentity();
  gluLookAt(0.0, 1.0, 6.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);

  // clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawShip(ship);

  // draw everything and swap the display buffer
  glutSwapBuffers();
}

void GameController::MouseHandler(int button, int state, int x, int y)
{
	//glLoadIdentity();

	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy, realx;  // OpenGL y coordinate position
	GLdouble wx, wy, wz;  // returned world x, y, z coords

	glGetIntegerv (GL_VIEWPORT, viewport);
    glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
	
	//note viewport[3] is height of window in pixels
    realy = viewport[3] - (GLint) y - 1;
    //not working!
    gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0f,
        mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
	
	ship->target = Vector3((float)wx, (float)wy, 0.0);
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		{
			//exit(0);
		} break;
	default:
		break;
	}

	// force a screen redraw
	glutPostRedisplay();
}
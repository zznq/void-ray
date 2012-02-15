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
	//this->timer.Start();
}

void GameController::Update(){
	this->ship->Update(0.01); //this->timer.TimeElapsed());
}

void GameController::DrawEntity(MovingEntity *s){
    s->Render();
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

  DrawEntity(ship);

  // draw everything and swap the display buffer
  glutSwapBuffers();
}

void GameController::MouseHandler(int button, int state, int x, int y)
{
	//glLoadIdentity();

	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy;  // OpenGL y coordinate position
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
#include "GameController.h"
#include "glut.h"

#include <GL\glu.h>
#include <GL\gl.h>

void Initialize();
void MouseHandler(int button, int state, int x, int y);
void KeyboardHandler(unsigned char key, int x, int y);
void MainMenuHandler(int option);
void Animate();
void Reshape(int width, int height);
void Display();

GameController *controller;

/****************************************************************************
 main()

 Setup GLUT and OpenGL, drop into the event loop
*****************************************************************************/
int main(int argc, char **argv)
{
  controller = new GameController();

  // Setup the basic GLUT stuff
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Create the window
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("BOGLGP Chapter 1");

  Initialize();

  // Register the event callback functions
  glutDisplayFunc(Display); 
  glutReshapeFunc(Reshape);
  glutMouseFunc(MouseHandler);
  glutKeyboardFunc(KeyboardHandler);
  glutIdleFunc(Animate);

  // At this point, control is relinquished to the GLUT event handler.
  // Control is returned as events occur, via the callback functions.
  glutMainLoop();   
   
  return 0;
} // end main()


/****************************************************************************
 Initialize()

 One time setup, including creating menus, creating a light, setting the
 shading mode and clear color, and loading textures.
*****************************************************************************/
void Initialize()
{
  // set up the only meny
  int mainMenu;

  mainMenu = glutCreateMenu(MainMenuHandler);

  glutSetMenu(mainMenu);
  glutAddMenuEntry("Exit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glEnable(GL_DEPTH_TEST);
} // end Initialize()


/****************************************************************************
 MouseHandler()
 
 Handle mouse events. For this simple demo, just exit on a left click.
*****************************************************************************/
void MouseHandler(int button, int state, int x, int y)
{
	/*
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy;  /*  OpenGL y coordinate position  * /
	GLdouble wx, wy, wz;  /*  returned world x, y, z coords  * /

	glGetIntegerv (GL_VIEWPORT, viewport);
    glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
/*  note viewport[3] is height of window in pixels  * /
    realy = viewport[3] - (GLint) y - 1;
    
    gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0,
        mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
    
    gluUnProject ((GLdouble) x, (GLdouble) realy, 1.0,
        mvmatrix, projmatrix, viewport, &wx, &wy, &wz);

	glLoadIdentity();

	
	glGetIntegerv(GL_VIEWPORT, viewport);  
	
	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection); 

	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	winX = (float)x;
	winY = (float)y;

	winY = (float)viewport[3] - winY;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	*/
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
} // end MouseHandler()


/****************************************************************************
 KeyboardHandler()

 Keyboard handler. Again, we'll just exit when q is pressed.
*****************************************************************************/
void KeyboardHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'q':  // exit
    {
      exit(0);
    } break;
  default:
    {
    } break;
  }
  glutPostRedisplay();
} // end KeyboardHandler()


/****************************************************************************
 MainMenuHandler()

 Main menu callback.
*****************************************************************************/
void MainMenuHandler(int option)
{
  switch(option)
  {
  case 0:
    {
      exit(0);
    } break;
  default:
    break;
  }
  glutPostRedisplay();
} // end MainMenuHandler()


/****************************************************************************
 Animate()

 Rotate the cube by 4 degrees and force a redisplay.
*****************************************************************************/
void Animate()
{
  glutPostRedisplay();
} // end Animate()


/****************************************************************************
 Reshape()

 Reset the viewport for window changes
*****************************************************************************/
void Reshape(int width, int height)
{
  if (height == 0)
    return;

  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, width/height, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
} // end Reshape


/****************************************************************************
 Display()

 Clear and redraw the scene.
*****************************************************************************/
void Display()
{
  controller->Render();
} // end Display()



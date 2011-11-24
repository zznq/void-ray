#include "GameController.h"
#include "glut.h"
#include "Ship.h"

void GameController::DrawShip(Ship *s){
  float globalz = Ship::SHIP_SIZE->z + s->position->z;

  float tipx = 0.0f + s->position->x;
  float tipy = Ship::SHIP_SIZE->x + s->position->y;
  
  float rightflankx = -(Ship::SHIP_SIZE->y) + s->position->x;
  float rightflanky = -(Ship::SHIP_SIZE->y) + s->position->y;

  float leftflankx = Ship::SHIP_SIZE->y + s->position->x;
  float leftflanky = -(Ship::SHIP_SIZE->y) + s->position->y;

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
  DrawShip(ship2);
  

  // draw a polygon
  /*glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 2.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-3.0, -0.5, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.5, -3.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, -2.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
  glEnd();*/

  // draw everything and swap the display buffer
  glutSwapBuffers();
}
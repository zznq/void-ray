#include "GameController.h"
#include "glut.h"
#include "Ship.h"

void GameController::DrawShip(Ship *s){
  float globalz = 0.0f;

  float topy = Ship::SHIP_HEIGHT_OFFSET + (Ship::SHIP_HALF_HEIGHT);
  float bottomy = Ship::SHIP_HEIGHT_OFFSET - (Ship::SHIP_HALF_HEIGHT);

  float leftx = Ship::SHIP_WIDTH_OFFSET - (Ship::SHIP_HALF_WIDTH);
  float rightx = Ship::SHIP_WIDTH_OFFSET + (Ship::SHIP_HALF_WIDTH);

  float tipx = 0.0f + s->position->x;
  float tipy = topy + s->position->y;
  
  float rightflankx = rightx + s->position->x;
  float rightflanky = bottomy + s->position->y;

  float leftflankx = leftx + s->position->x;
  float leftflanky = bottomy + s->position->y;

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
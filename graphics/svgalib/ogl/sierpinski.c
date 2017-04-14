//sierpinski.c

#include <stdlib.h>
#include <sys/time.h>

#include <GL/glut.h>

void myinit(void)
{
  //attributes

  glClearColor(0.0, 0.0, 0.0, 0.0); //black
  glColor3f(0.0, 0.0, 1.0); //draw in blue

  //set up viewing
  //500x500 window with origin lower left
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 500.0, 0.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
  //define a point data type
  typedef GLfloat point2[2];

  point2 vertices[3]={ {0.0, 0.0}, {250.0, 500.0},
		       {500.0, 0.0} };

  //a triangle
  int i, j, k;
  random();
  point2 p={75.0, 50.0}; //arbitraty initial point

  glClear(GL_COLOR_BUFFER_BIT); //cler the window

  //compute and plot 5000 points
  for(k = 0; k < 10000; k++)
    {
      j=random()%3; //pick a vertex at random

      //compute point halfway between vertex and old point
      p[0] = ( p[0] +vertices[j][0] ) / 2.0;
      p[1] = ( p[1] +vertices[j][1] ) / 2.0;
      
      double x = 250.0;

      double r = p[0]/(double) x;
      double g = p[1]/(double) x;
      double b = 0/(double) x;

      //plot new point
      glBegin(GL_POINTS);
      glColor3f( r, g, b);
      glVertex2fv(p);
      glEnd();
      
    }//end for

  glFlush(); //clear buffers
  
}

void main(int argc, char **argv)
{
  //standard GLUT initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  //default, not needed
  glutInitWindowSize(500, 500); //500x500 pixel window
  glutInitWindowPosition(0,0); //top left on display

  glutCreateWindow("sierpinski gasket"); //window title
  glutDisplayFunc(display); //display callback after window opens

  myinit();
  
  glutMainLoop(); //enter event loop
}
   

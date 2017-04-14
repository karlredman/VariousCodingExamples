//sierpinski.c

#include <stdlib.h>
#include <unistd.h>
//#include <sys/time.h>

#include <GL/glut.h>

int i;
void myinit(void)
{
  //attributes

  glClearColor(0.0, 0.0, 0.0, 0.0); //black
  glColor3f(0.0, 0.0, 1.0); //draw in blue

  //set up viewing
  //500x500 window with origin lower left
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);
  glOrtho(0.0, 500.0, 0.0, 500.0, -500.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
  //define a point data type
  typedef GLfloat point[3];
  int j, k;
  point vertices[4];

      switch(i)
	{
	case 1:
	  /*rear left*/
	  vertices[0][0]=100.0;
	  vertices[0][1]=100.0;
	  vertices[0][2]=-400.0;

	  /*rear right*/
	  vertices[1][0]= 400.0;
	  vertices[1][1]= 100.0;
	  vertices[1][2]= -400.0;
	  /*top*/
	  vertices[2][0]=250.0;
	  vertices[2][1]= 400.0;
	  vertices[2][2]= 0.0;
	  /*front bottom*/
	  vertices[3][0]=250.0;
	  vertices[3][1]= 100.0;
	  vertices[3][2]= 400.0;

	  break;

	case 2:
	  /*rear left*/
	  vertices[0][0]= 125.0;
	    vertices[0][1]= 100.0;
	    vertices[0][2]= -425.0;
	    /*rear right*/
	    vertices[1][0]=375.0;
	    vertices[1][1]= 100.0;
	    vertices[1][2]= -375.0;

	    /*top*/
	    vertices[2][0]=250.0;
	    vertices[2][1]= 375.0;
	    vertices[2][2]= -25.0;
	    /*front bottom*/
	    vertices[3][0]=225.0;
	    vertices[3][1]= 125.0;
	    vertices[3][2]= 425.0;
	    break;

	case 3:
	  /*rear left*/
	  vertices[0][0]=100.0;
	    vertices[0][1]= 100.0;
	    vertices[0][2]=400.0;
	    /*rear right*/
	    vertices[1][0]=400.0;
	    vertices[1][1]=100.0;
	    vertices[1][2]= 400.0;
	    /*top*/
	    vertices[2][0]=250.0;
	    vertices[2][1]= 200.0;
	    vertices[2][2]= -400.0;
	    /*front bottom*/
	    vertices[3][0]=250.0;
	    vertices[3][1]= 400.0;
	    vertices[3][2]= 400.0;
	    break;

	case 4:
	  /*rear left*/
	  vertices[0][0]=0.0;
	    vertices[0][1]= 0.0;
	    vertices[0][2]= -500.0;

	    /*rear right*/
	    vertices[1][0]=500.0;
	    vertices[1][1]= 0.0;
	    vertices[1][2]= -500.0;
	    /*top*/
	    vertices[2][0]=250.0;
	    vertices[2][1]= 500.0;
	    vertices[2][2]= 0.0;
	    /*front bottom*/
	    vertices[3][0]= 250.0;
	    vertices[3][1]= 0.0;
	    vertices[3][2]= 500.0;
	    break;
	case 5:
	  /*rear left*/
	  vertices[0][0]=-200.0;
	    vertices[0][1]= 0.0;
	    vertices[0][2]= -500.0;

	    /*rear right*/
	    vertices[1][0]=700.0;
	    vertices[1][1]= 0.0;
	    vertices[1][2]= -500.0;
	    /*top*/
	    vertices[2][0]=250.0;
	    vertices[2][1]= 5000.0;
	    vertices[2][2]= 0.0;
	    /*front bottom*/
	    vertices[3][0]= 250.0;
	    vertices[3][1]= 0.0;
	    vertices[3][2]= 500.0;
	    break;
	default:
	  i=0;
	  break;
	}
    

      /*negative is away from me, positive is twords me on the z axis */

      //a triangle
      random();
      point p={250.0, 100.0, 250}; //arbitraty initial point

      glClear(GL_COLOR_BUFFER_BIT); //cler the window
      
      int x = 100000;

      if(i == 5)
	x = 1000000;
      //compute and plot 5000 points
      for(k = 0; k < x; k++)
	{
	  j=random()%4; //pick a vertex at random

	  //compute point halfway between vertex and old point
	  p[0] = ( p[0] +vertices[j][0] ) / 2.0;
	  p[1] = ( p[1] +vertices[j][1] ) / 2.0;
	  p[2] = ( p[2] +vertices[j][2] ) / 2.0;
      
	  double x = 250.0;

	  double r = p[0]/(double) x;
	  double g = p[1]/(double) x;
	  double b = p[2]/(double) x;

	  //plot new point
	  glBegin(GL_POINTS);
	  glColor3f( r, g, b);
	  glVertex3fv(p);
	  glEnd();
      
	}//end for

      glFlush(); //clear buffers

}

void main(int argc, char **argv)
{
  i = argc;

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
   

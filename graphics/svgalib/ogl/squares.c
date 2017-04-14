//squares.c

#include <stdlib.h>
#include <GL/glut.h>

GLsizei wh = 500, ww = 500;	/* initial window size */
GLfloat size = 3.0;		/* one-half of side length of square */

int myrandom(int n);
void reshape_handler(GLsizei w, GLsizei h);
void drawSquare(int x, int y);
void myinit(void);
void mouse_handler(int button, int state, int x, int y);
void display(void);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("squares");

  myinit();

  glutDisplayFunc(display); 
  glutReshapeFunc(reshape_handler);
  glutMouseFunc(mouse_handler);
  //  glutKeyboardFunc(keyboard_handler);

  glutMainLoop();
}

void display(void) {}

void mouse_handler(int button, int state, int x, int y)
{
  if(state == GLUT_DOWN)
    {
      switch(button)
	{
	case GLUT_LEFT_BUTTON:
	  drawSquare(x, y);
	  break;
	case GLUT_MIDDLE_BUTTON:
	  exit(0);
	  break;
	default:
	  break;
	}
    }//end if(state...
}

void myinit(void)
{
  glViewport(0, 0, ww, wh);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
  //  glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  
  /* set clear color to black, and clear window */
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

}

void drawSquare(int x, int y)
{
  y=wh-y;			/* reverse y for windowing systems
				   coordinates (origin is at top) */

  glColor3ub( (char)myrandom(256), (char)myrandom(256),
	      (char)myrandom(256));
  
  glBegin(GL_POLYGON);
  //
  glVertex2f(x+size, y+size);
  glVertex2f(x-size, y+size);
  glVertex2f(x-size, y-size);
  glVertex2f(x+size, y-size);
  //
  glEnd();

  glFlush();
}

void reshape_handler(GLsizei w, GLsizei h)
{
  /* adjust clipping box */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
  //glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* adjust viewport and clear */
  glViewport(0, 0, w, h);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

  ww = w;
  wh = h;
}
  


int myrandom(int n)
{
  int j = 1+(int)( (float) n*rand()/(RAND_MAX+1.0));
  return(j);
}

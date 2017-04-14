//sierpinski.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include <GL/glut.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void InitWindow ();
typedef unsigned long Pixel;
Display *disp;
Window root;
GC WinGC;
char *dispname = NULL, *color = "white", *Geometry = 0, *command;
char *fontName = "fixed";
int screen, ScreenHeight, ScreenWidth, w=-1, h=-1, win_x=30, win_y=30;

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
  InitWindow();
  
  glutMainLoop(); //enter event loop
}
   
void InitWindow ()
{
  XGCValues gcv;
  Font font;
  unsigned long gcm;
  XFontStruct *info;
  if (!(disp = XOpenDisplay (dispname)))
    {
      fprintf (stderr, "Error opening display %s.\n", dispname);
      exit (-1);
    }
  screen = DefaultScreen (disp);
  ScreenHeight = DisplayHeight (disp, screen);
  ScreenWidth = DisplayWidth (disp, screen);
  root = RootWindow (disp, screen);
  gcm = GCBackground;
  gcv.graphics_exposures = True;
  WinGC = XCreateGC (disp, root, gcm, &gcv);
  XMapWindow (disp, root);
  //  XSetForeground (disp, WinGC, GetColor ("white"));
  font = XLoadFont (disp, fontName);
  XSetFont (disp, WinGC, font);
  //  info = XQueryFont (disp, font);
  //  font_width = info->max_bounds.width;
  //  font_height = info->max_bounds.ascent + info->max_bounds.descent;
  //  w = width * font_width;
  //  h = listlen * font_height;
  w=500;
  h = 500;
  if (win_x < 0)
    win_x = win_x + ScreenWidth - w;
  if (win_y < 0)
    win_y = win_y + ScreenHeight - h;

#ifdef break_expose
#else
#define EVENTMASK  ExposureMask \
		| SubstructureNotifyMask \
	        | VisibilityChangeMask  \
		| StructureNotifyMask \
		| FocusChangeMask \
		| PropertyChangeMask
  XSelectInput (disp, root, EVENTMASK);
#endif
}

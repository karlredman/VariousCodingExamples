//plasma.c
/*
   build: gcc -Wall plasma.c -o plasma -lvgagl -lvga
*/ 
	

#include <stdio.h>
#include <vga.h>
#include <vgagl.h>

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <term.h>
//#include <curses.h>
#include <unistd.h>

//#include <vroot.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void initPalette(void);
void rotate_colors(void);
void setVGApallette(unsigned char *buffer);
void setVGAreg(int reg_no, int red, int green, int blue);
void subdivide(int x1, int y1, int x2, int y2, int chaos);

int kbhit(void);
void init_keyboard(void);
void close_keyboard();
void myrandomize(void);
int myrandom(int n);

void InitWindow ();
typedef unsigned long Pixel;
Display *disp;
Window root;
GC WinGC;
char *dispname = NULL, *color = "white", *Geometry = 0, *command;
char *fontName = "fixed";
int screen, ScreenHeight, ScreenWidth, w=-1, h=-1, win_x=30, win_y=30;

static struct termios initial_settings;
struct timespec timerx;

int xres = 319, yres=199;
int palette[512][3];
char ch;
int i, j, k;

int xx = 0;

#define STATE_SIZE 256
char state[STATE_SIZE];

GraphicsContext physicalscreen;


int main(int argc, char** argv)
{
  int iterations = 0;

  InitWindow ();		// just a dummy to get the color lookups right
     
  //initialize
  if(vga_init()!= 0)
    {
      printf("Error initializing svgalib!\n");
      exit(1);
    }



  if(vga_setmode(G320x200x256)!=0)
    {
      printf("can't set mode 320x200x256!\n");
      exit(1);
    }

  if(gl_setcontextvga(G320x200x256) != 0)
    {
      printf("Error setting context!\n");
      exit(1);
    }
  
  gl_getcontext(&physicalscreen);
  if(gl_setcontextvgavirtual(G320x200x256) !=0)
    {
      printf("Error setting virtual context!\n");
      exit(1);
    }

  gl_clearscreen(0);

  initPalette();
  myrandomize();
  gl_setpixel(0, 0, myrandom(255) +1);
  gl_setpixel(xres, 0, myrandom(255) +1);
  gl_setpixel(xres, yres, myrandom(255) +1);
  gl_setpixel(0, yres, myrandom(255) +1);

  //gl_setpixel(50, 50, 1);

  //gl_copyscreen(&physicalscreen);
  //ch = getchar();

  subdivide(0, 0, xres, yres, 0);
  gl_copyscreen(&physicalscreen);
  
  rotate_colors();
  
  //restore
  vga_setmode(TEXT);
  return(0);
}


void initPalette(void)
{
  int max_color = 63;
  int index;

  for(index = 0; index < 85; index++)
    {
      palette[index][0] = 0;
      palette[index][1] = (index*max_color)/85;
      palette[index][2] = ((86 - index)*max_color)/85;

      palette[index+255][0] = 0;
      palette[index+255][1] = (index*max_color)/85;
      palette[index+255][2] = ((86 - index)*max_color)/85;

      palette[index+85][0] = 0;
      palette[index+85][1] = (index*max_color)/85;
      palette[index+85][2] = ((86 - index)*max_color)/85;

      palette[index+339][0] = 0;
      palette[index+339][1] = (index*max_color)/85;
      palette[index+339][2] = ((86 - index)*max_color)/85;

      palette[index+170][0] = 0;
      palette[index+170][1] = (index*max_color)/85;
      palette[index+170][2] = ((86 - index)*max_color)/85;

      palette[index+424][0] = 0;
      palette[index+424][1] = (index*max_color)/85;
      palette[index+424][2] = ((86 - index)*max_color)/85;
    }
      vga_setpalvec(0,256,palette[0]);
}

void rotate_colors(void)
{
  int old_red, old_green, old_blue, new_red, new_green,
    new_blue, last_step = 32, step = 1;

  char ch = '0';
  int iterations = 0;

  for(;;)
    {

      if(/* (ch = kbhit()) != 0*/1)
	    {
	      if(ch == 10)
		break;
	      else
		{
		  if(iterations > 24 || xx ==2)
		    {
		      if(((ch - '0') > 9) ||  ((ch - '0' < 0)))
			{
			  ch = '1';
			  last_step = 32;
			}
		      
		      if( (ch - '0' <= 9) && (ch - '0' > 0) )
			{
			  if(xx)
			    last_step = 4*(int)myrandom((ch-'0'));
			  else
			    last_step = 4*(int)(ch-'0');
			  ch++;
			}
		      else
			ch++;

		      iterations = 0;

		    }
		  else
		    iterations++;

	  
	      old_red = palette[step+253][0];
	      old_green = palette[step+253][1];
	      old_blue = palette[step+253][2];
	      
	      new_red = rand()%64;
	      new_green = rand()%64;
	      new_blue = rand()%64;
	      
	      for(j = 1; j<last_step; j++)
		{
		  palette[step+254][0] = old_red +
		    ((new_red - old_red)*j) / last_step;
		  palette[step-1][0] = palette[step+254][0];
		  
		  palette[step+254][1] = old_green +
		    ((new_green - old_green)*j) / last_step;
		  palette[step-1][1] = palette[step+254][1];
		  
		  palette[step+254][2] = old_blue +
		    ((new_blue - old_blue)*j) / last_step;
		  palette[step-1][2] = palette[step+254][2];
		  
 		  vga_waitretrace();
		  vga_setpalvec(0,256,palette[step]);

		  step = step%255+1;
		  
		}//for
	    }//else
	}//if(ch=..
    }//for
}

void subdivide(int x1, int y1, int x2, int y2, int chaos)
{
  int x,y,color,dist;
  
  x= ((x1 +x2) >> 1);
  y= ((y1 +y2) >> 1);
  
  if(x == x1)
    return;
  
  dist = x2 - x1;

  color = myrandom(dist << 1) -dist;
  color += chaos+ (gl_getpixel(x1,y1) + gl_getpixel(x2,y1) +1) >> 1;
  color = (color < 1) ? 1 : (color > 255) ? 255 : color;

  if(gl_getpixel(x,y1) == 0)
    gl_setpixel(x, y1, color);
  
  color = myrandom(dist << 1) -dist;
  color += chaos+ (gl_getpixel(x1,y2) + gl_getpixel(x2, y2) +1) >> 1;
  color = (color < 1) ? 1 : (color > 255) ? 255 : color;

  if(gl_getpixel(x,y2) == 0)
    gl_setpixel(x, y2, color);

  dist = y2 - y1;

  color = myrandom(dist << 1) -dist;
  color += chaos+ (gl_getpixel(x2,y1) + gl_getpixel(x2, y2) +1) >> 1;
  color = (color < 1) ? 1 : (color > 255) ? 255 : color;

  if(gl_getpixel(x2,y) == 0)
    gl_setpixel(x2, y, color);

  color = myrandom(dist << 1) -dist;
  color += chaos+ (gl_getpixel(x1,y1) + gl_getpixel(x1, y2) +1) >> 1;
  color = (color < 1) ? 1 : (color > 255) ? 255 : color;

  if(gl_getpixel(x1,y) == 0)
    gl_setpixel(x1, y, color);

  color = chaos+ (gl_getpixel(x1, y1) + gl_getpixel(x2, y1) + 
	   gl_getpixel(x2, y2) + gl_getpixel(x1,y2) +2) >> 2;
  
  gl_setpixel(x,y,color);
  subdivide(x1, y1, x, y, chaos);
  subdivide(x, y1, x2, y, chaos);
  subdivide(x, y, x2, y2, chaos);
  subdivide(x1, y , x, y2, chaos);
}

int kbhit(void)
{
	int ch = 0;

	//set keyboard state - no echo, single char input
	init_keyboard();

	//get charecter
	read(STDIN_FILENO, &ch, 1); /* getchar() works here too */

	//set keyboard back to initial state
	close_keyboard();

	return(ch);
}  

void init_keyboard()
{
	struct termios new_settings;

	//save attribures for close
	tcgetattr(0, &initial_settings);

	//set no echo, one char input,
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
	//reset terminal to initial settings
	tcsetattr(0, TCSANOW, &initial_settings);
}

int myrandom(int n)
{
  int j = 1+(int)( (float) n*rand()/(RAND_MAX+1.0));
  return(j);
}

void myrandomize(void)
{
  /*
  for(int i = 0; i < STATE_SIZE; i++)
    state[i]=i;

  initstate(1, state, STATE_SIZE);
  */
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


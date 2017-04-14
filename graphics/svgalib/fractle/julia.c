//svgatest.c

#include <stdio.h>
#include <vga.h>
#include <vgagl.h>

int main()
{
  GraphicsContext physicalscreen;

  //initialize
  if(vga_init()!= 0)
    {
      printf("Error initializing svgalib!\n");
      exit(1);
    }

  if(vga_setmode(G640x480x16)!=0)
    //  if(vga_setmode(G320x200x256)!=0)
    {
      printf("can't set mode 320x200x256!\n");
      exit(1);
    }

  if(gl_setcontextvga(G640x480x16) != 0)
    //if(gl_setcontextvga(G320x200x256) != 0)
    {
      printf("Error setting context!\n");
      exit(1);
    }
  
  gl_getcontext(&physicalscreen);
  if(gl_setcontextvgavirtual(G640x480x16) !=0)
    //if(gl_setcontextvgavirtual(G320x200x256) !=0)
    {
      printf("Error setting virtual context!\n");
      exit(1);
    }

  /*
  gl_setpalettecolor(0,0,0,0);
  gl_setpalettecolor(1,63,0,0);
  gl_setpalettecolor(2,0,63,0);
  gl_setpalettecolor(3,0,0,63);
  gl_setpalettecolor(4,63,63,63);
  */

  //use
  gl_clearscreen(0);

  /*
    gl_setpixel(20, 20, 1);
    gl_fillbox(100,80,100,100,4);
    gl_line(30,20,300,180,3);
    gl_fillbox(50,50,100,100,2);
    gl_setpixel(75, 75, 1);
    vga_waitretrace();
    gl_copyscreen(&physicalscreen);
  */

  //julia
  int xres=640, yres = 480;
  int color, row, col;
  float Xmax=1.8, Xmin=-1.8, Ymax = 1.2, Ymin=-1.2;
  float P=-0.053750, Q = 0.653000, deltaX, deltaY, x, y, xsq, ysq;

  deltaX = (Xmax-Xmin)/xres;
  deltaY = (Ymax - Ymin)/yres;

  col = 0;

  
 cols:
  
  if(col<xres)
    {
      row = 0;
    rows:
      
      if (row<yres)
	{
	  x = Xmin+col*deltaX;
	  y = Ymax - row*deltaY;
	  
	  xsq = ysq = 0.0;

	  color = 0;

	iterations:
	  
	  if((color<64) && (xsq+ysq<4))
	    {
	      xsq = x*x;
	      ysq = y*y;
	      x = xsq -ysq +P;
	      y = 2*x*y +Q;
	      color++;
	      goto iterations;
	    }

	  if(color >= 64)
	    color = ((int ((xsq +ysq) * 8.0)) %7) +9;
	  else
	    color = 1;

	  gl_setpixel(col, row, color);
	  row++;
	  goto rows;

	}
      col++;
      goto cols;
    }

  vga_waitretrace();
  gl_copyscreen(&physicalscreen);
  getchar();

  //restore
  vga_setmode(TEXT);
  return(0);
}
       

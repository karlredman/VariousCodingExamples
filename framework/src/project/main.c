/* project-template my-project main.c file
 */

#include <stdio.h>
#include <termios.h>
#include <curses/curses.h>
#include <unistd.h>

#include "parasyte.h"

int main()
{
  struct termios saved_settings;
  int ch = 0;

  printf("PRESS ANY KEY TO CONTINUE\n");
	fflush((FILE *)0);

	//set keyboard state - no echo, single char input
	init_keyboard(&saved_settings);

	//get charecter
	read(STDIN_FILENO, &ch, 1); /* getchar() works here too */
	printf("you hit: %c\n",ch);

	//set keyboard back to initial state
	restore_keyboard(&saved_settings);

	printf("done.\n");
	exit(0);
}

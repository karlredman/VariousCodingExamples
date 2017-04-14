//common console (keyboard and screen) functions for libparasyte

#include <termios.h>
#include <unistd.h>
#include <curses/curses.h>

//#include <term.h>

#include "parasyte.h"

void init_keyboard(struct termios *saved_settings)
{
	struct termios new_settings;

	//save attribures for close
	tcgetattr(0, saved_settings);

	//set no echo, one char input,
	new_settings = *saved_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new_settings);
}

void restore_keyboard(struct termios *saved_settings)
{
	//reset terminal to initial settings
	tcsetattr(0, TCSANOW, saved_settings);
}

/* program that lockes user out of you screen. Not very secure but I was 
learning c on linux with gcc at the time. I have no idea about special 
compiler options at the time. -ksr
*/
#include<curses.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>


main()
{
	int true = 1, i, length, flag = 0, count = 0;
	char key;
	char password[] = {"grendel"};

	initscr();
	nonl();
	noecho();
	raw();

	length = strlen(password);

	clear();
	mvaddstr(10, 10, "ENTER PASSWORD:");
	move(10, 27);
	refresh();
	

	while(true)
	{
		for(i = 0; i < length; i++)
		{
			key = getch();
			if(key != password[i])
				break;

		}
		if(key == '')
			flag = 0;

			if(i==length)
				goto check;
			mvaddstr(20, 34, "IN SLEEP MODE");
			move(21, 1);
			clrtoeol();
			move(21, 31);
			printw("LEVEL %d SO FAR!!!", flag);
			move(10, 27);
			refresh();
			if(flag > 10)
				{
				count += 1;
				move(22, 28);
				printw("(this could take forever)");
				refresh();
				sleep(flag-(flag-count));
				move(22, 1);
				clrtoeol();
				move(10, 27);
				refresh();
				}

	check:	
		if(key == password[length-1] && i == length)
			true = 0;
		flag += 1;
	}
	clear();
	refresh();
	endwin();
}

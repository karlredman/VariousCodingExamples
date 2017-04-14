#include<curses.h>


main()
{
	int true = 1, i, length, flag = 0, count = 0;
	char key;
	char password[] = {"grendel"};

	initscr();
	nonl();
	noecho();
	cbreak();

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

			if(i==length)
				goto check;
			mvaddstr(20, 34, "IN SLEEP MODE");
			move(21, 1);
			clrtoeol();
			move(21, 31);
			printw("LEVEL %d SO FAR!!!", flag);
			move(10, 27);
			refresh();
			if(flag > 9)
				{
				count += 1;
				move(22, 28);
				printw("(this could take forever)");
				refresh();
				sleep(flag - (flag - count));
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

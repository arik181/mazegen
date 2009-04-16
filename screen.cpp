#include <ncurses.h>
#include <cstdlib>

using namespace std;

#include "screen.h"

screen::screen()
{
	/*** Begin ncurses mode ***/
        initscr();

	/*** Turn off echo. This is turned on again at the end of the program, 
	* and it's turned on every time we use a textfield. ***/
	noecho();

	/*** Turn off the cursor ***/
	curs_set(0);

	/*** Turn on keypad interpretation ***/
	keypad(stdscr, TRUE);

	/*** Turn off the escape key delay ***/
	notimeout(stdscr,TRUE);
	ESCDELAY = 0;

	/*** Get the max x and y coordinates for the screen. ***/
	screenx = 0;
	screeny = 0;
	getmaxyx(stdscr, screeny, screenx);
	napms(500);
}

int screen::getx()
{
	return screenx;
}

int screen::gety()
{
	return screeny;
}

screen::~screen()
{
	refresh();
	
	/*** Turn the cursor back on ***/
	curs_set(1);

	/*** Turn echo back on ***/
	echo();

	/*** End ncurses mode ***/
	endwin();
}

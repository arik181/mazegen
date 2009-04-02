#include <ncurses.h>
using namespace std;

#include "screen.h"

screen::screen()
{
	// Begin ncurses mode
        initscr();

	// Turn off echo. This is turned on again at the end of the program, 
	// and it's turned on every time we use a textfield.
	noecho();

	// Turn off the cursor
	curs_set(0);

	// Turn off the escape key delay
	notimeout(stdscr,TRUE);
	ESCDELAY = 0;
}

screen::~screen()
{
	refresh();
	
	// Turn the cursor back on
	curs_set(1);

	// Turn echo back on 
	echo();

	// End ncurses mode 
	endwin();
}
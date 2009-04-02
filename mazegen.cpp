#include <ncurses.h>
#include <time.h>
using namespace std;

#include "mazegen.h"
#include "maze.h"

/*** Main Loop ***/
int main()
{
	/*** Routines for dealing with ncurses ***/
	init();

	/*** Test of main routines. ***/
	test();

	/*** Routines for dealing with ncurses ***/
	cleanup();

	return 0;
}

/*** Routines for dealing with ncurses ***/
void init()
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

/*** Routines for dealing with ncurses ***/
void cleanup()
{
	refresh();
	
	// Turn the cursor back on
	curs_set(1);

	// Turn echo back on 
	echo();

	// End ncurses mode 
	endwin();
}

/*** Test of main routines. ***/
void test()
{
	/*** Test to be sure ncurses was initialized. ***/
	clear();
	mvaddstr(0,0,"Hello.");
	refresh();
	napms(500);
}

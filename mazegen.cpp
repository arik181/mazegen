#include <ncurses.h>
#include <cstdlib>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

#include "mazegen.h"
#include "screen.h"
#include "maze.h"
#include "node.h"

/*** Create a new ncurses screen. ***/
screen scr;
/*** Create a new maze object. ***/
maze mz;

/*** Main Loop ***/
int main()
{
	/*** Create a new maze. ***/
	mz.create(scr.getx(), scr.gety());
	mz.render();

	/*** Print a menu. ***/

	/*** Get user input. ***/
	getinput();

	return 0;
}

/*** Get user input. This is the main loop.***/
void getinput()
{
	int quit = 0;
	int input = 0;
	while (!quit)
	{
		input = getch();

		if (input == 'q')
			quit = 1;
		else if (input == KEY_UP || input == 'w')
			mz.move(NORTH);
		else if (input == KEY_RIGHT || input == 'd')
			mz.move(EAST);
		else if (input == KEY_DOWN || input == 's')
			mz.move(SOUTH);
		else if (input == KEY_LEFT || input == 'a')
			mz.move(WEST);

	}
}

/*** Test of main routines and objects. ***/
void test()
{
	/*** Test to be sure ncurses was initialized by the 
	* screen object. ***/
	/***  
	clear();
	mvaddstr(0,0,"Hello.");
	refresh();
	napms(500);
	***/

	/***  Test to be certain that the maze renders.***/
	mz.render();

	/*** Test to be certain that we can move the player. ***/
	mz.move(EAST);
	napms(500);

	mz.move(SOUTH);
	napms(500);

	mz.move(SOUTH);
	napms(500);
}

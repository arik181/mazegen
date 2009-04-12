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
maze mz;

/*** Main Loop ***/
int main()
{
	/*** Create a new maze. ***/
	mz.create(scr.getx(), scr.gety());

	return 0;
}

/*** Test of main routines and objects. ***/
void test()
{
	/*** Test to be sure ncurses was initialized by the 
	* screen object. ***/
	clear();
	mvaddstr(0,0,"Hello.");
	refresh();
	napms(500);
}

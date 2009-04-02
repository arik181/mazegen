#include <ncurses.h>
#include <time.h>
using namespace std;

#include "mazegen.h"
#include "screen.h"
#include "maze.h"

screen scr;

/*** Main Loop ***/
int main()
{
	return 0;
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

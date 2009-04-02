#include <ncurses.h>
#include <time.h>
using namespace std;

#include "mazegen.h"
#include "screen.h"
#include "maze.h"
#include "node.h"

screen scr;
node nd;

/*** Main Loop ***/
int main()
{
	nd.test();
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

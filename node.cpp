#include <ncurses.h>
#include <cstring>
using namespace std;

#include "node.h"

/*** Default Constructor ***/
node::node()
{
	/*** Neighboring Nodes. NULL if top layer. ***/
	n = NULL;
	e = NULL;
	s = NULL;
	w = NULL;

	/*** Parent Node. NULL if top layer. ***/
	parent = NULL;

	/*** Child Nodes. NULL if bottom layer. ***/
	nw = NULL;
	ne = NULL;
	sw = NULL;
	se = NULL;

	/*** A Neighbor that "knows" the location of Finish. 
	 * ***/
	knowsfinish = NULL;

	/*** A Neighbor that "knows" the location of Start. 
	 * ***/
	knowsstart = NULL;
}

/*** Default Constructor ***/
cell::cell()
{
	/*** State Data ***/
	state = 0x0;

	/*** Location Data ***/
	x = 0;
	y = 0;
}

/*** Destructor ***/
cell::~cell()
{
	/*** State Data ***/
	state = 0x0;

	/*** Location Data ***/
	x = 0;
	y = 0;
}

/*** Destructor ***/
node::~node()
{
	/*** Location Data ***/
	x = 0;
	y = 0;

	/*** Neighboring Nodes. NULL if top layer. ***/
	n = NULL;
	e = NULL;
	s = NULL;
	w = NULL;

	/*** Parent Node. NULL if top layer. ***/
	parent = NULL;

	/*** Child Nodes. NULL if bottom layer. ***/
	nw = NULL;
	ne = NULL;
	sw = NULL;
	se = NULL;

	/*** A Neighbor that "knows" the location of Finish. 
	 * ***/
	knowsfinish = NULL;

	/*** A Neighbor that "knows" the location of Start. 
	 * ***/
	knowsstart = NULL;
}

/*** Draws the node on the screen. Default location is x,y ***/
void node::render()
{
	render(x,y);
}

/*** Draws the cell contents on the screen. Default location is x,y ***/
void cell::render()
{
	render(x,y);
}

/*** Draws the contents of a cell on the screen at a particular location. ***/
void cell::render(int x, int y)
{
	/*** Order here ensures priority ***/
	if (state & ISSTART)
		mvaddch(y+1,x+1,'S');
	if (state & ISFINISH)
		mvaddch(y+1,x+1,'F');
	if (state & HASPLAYER)
		mvaddch(y+1,x+1,ACS_DIAMOND);
}

/*** Draws the walls of a node on the screen at a particular location.***/
void node::render(int x, int y)
{
	/*** Draw walls where applicable ***/
	if (!n)
		mvaddch(y,x+1,ACS_HLINE);
	if (!s)
		mvaddch(y+2,x+1,ACS_HLINE);
	if (!w)
		mvaddch(y+1,x,ACS_VLINE);
	if (!e)
		mvaddch(y+1,x+2,ACS_VLINE);

	/*** Draw corners where applicable ***/
	if (!n && !w)
		mvaddch(y,x,ACS_ULCORNER);
	else if (!n)
		mvaddch(y,x,ACS_VLINE);
	else if (!w)
		mvaddch(y,x,ACS_HLINE);

	if (!n && !e)
		mvaddch(y,x+2,ACS_URCORNER);
	else if (!n)
		mvaddch(y,x+2,ACS_VLINE);
	else if (!e)
		mvaddch(y,x+2,ACS_HLINE);

	mvaddch(y+2,x,ACS_LLCORNER);
	mvaddch(y+2,x+2,ACS_LRCORNER);

	cell::render(x,y);
}

/*** Test. ***/
void node::test()
{
	clear();
	render();
	refresh();
	napms(500);

	state |= ISSTART;
	clear();
	render();
	refresh();
	napms(500);

	state |= ISFINISH;
	clear();
	render();
	refresh();
	napms(500);

	state |= HASPLAYER;
	clear();
	render();
	refresh();
	napms(500);

	clear();
	render(10,5);
	refresh();
	napms(500);

	clear();
	render(20,5);
	refresh();
	napms(500);

	clear();
	render(30,5);
	refresh();
	napms(500);

	clear();
	render(40,5);
	refresh();
	napms(500);

}


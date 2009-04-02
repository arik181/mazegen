#include "node.h"

/*** Default Constructor ***/
node::node()
{
	/*** State Data ***/
	state = 0x0;

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

/*** Destructor ***/
node::~node()
{
	/*** State Data ***/
	state = 0x0;

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

/*** Draws the node on the screen. Default location is 0,0 ***/
void node::render()
{
	render(0,0);
}

/*** Draws the node on the screen. Default location is 0,0 ***/
void node::render(int x, int y)
{
	mvaddch(y,x,ACS_ULCORNER);
	mvaddch(y,x+1,ACS_HLINE);
	mvaddch(y,x+2,ACS_URCORNER);

	mvaddch(y+1,x,ACS_VLINE);
	mvaddch(y+1,x+2,ACS_VLINE);

	mvaddch(y+2,x,ACS_LLCORNER);
	mvaddch(y+2,x+1,ACS_HLINE);
	mvaddch(y+2,x+2,ACS_LRCORNER);
}

/*** Test. ***/
void node::test()
{
	render();
	refresh();
	napms(5000);
}


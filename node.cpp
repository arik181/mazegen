#include <ncurses.h>
#include <cstring>
using namespace std;

#include "node.h"

/*** Default Constructor ***/
node::node()
{
	/*** Indicates the current layer of the node. ***/
	layer = 0;

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

/*** Generates the node ***/
void node::generate(int depth)
{
	/*** YOU ARE HERE ***/
	layer = depth;

	/*** This means that there is only one node, and one active cell. ***/
	if (layer == 0);
	/*** This means that there are five nodes, and four active cells. ***/
	else if (layer == 1);
	/*** This means that there are 22 two nodes, and 16 active cells. ***/
	else if (layer == 2);
	/*** This means that there are 86 nodes, and 64 active cells. ***/
	else if (layer == 3);
	else
		/*** Currently we only support four layers. ***/
		perror("Faulty Layer Number");
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

	/*** Draw corners and connectors where applicable ***/
	if (!n && !w)
		mvaddch(y,x,ACS_ULCORNER);
	else if (!n)
		mvaddch(y,x,ACS_HLINE);
	else if (!w)
		mvaddch(y,x,ACS_VLINE);

	if (!n && !e)
		mvaddch(y,x+2,ACS_URCORNER);
	else if (!n)
		mvaddch(y,x+2,ACS_HLINE);
	else if (!e)
		mvaddch(y,x+2,ACS_VLINE);

	if (!s && !w)
		mvaddch(y+2,x,ACS_LLCORNER);
	else if (!s)
		mvaddch(y+2,x,ACS_HLINE);
	else if (!w)
		mvaddch(y+2,x,ACS_VLINE);

	if (!s && !e)
		mvaddch(y+2,x+2,ACS_LRCORNER);
	else if (!s)
		mvaddch(y+2,x+2,ACS_HLINE);
	else if (!e)
		mvaddch(y+2,x+2,ACS_VLINE);

	/*** Render the contents of the cell. ***/
	if (layer == bottom)
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

	n = new node;
	clear();
	render(10,5);
	refresh();
	napms(500);

	e = new node;
	clear();
	render(20,5);
	refresh();
	napms(500);

	s = new node;
	clear();
	render(30,5);
	refresh();
	napms(500);

	w = new node;
	clear();
	render(40,5);
	refresh();
	napms(500);

	delete n;
	delete e;
	delete s;
	delete w;

	n = e = s = w = NULL;

}


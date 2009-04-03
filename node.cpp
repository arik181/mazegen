#include <ncurses.h>
#include <cstring>
using namespace std;

#include "node.h"

/*** Default Constructor ***/
node::node()
{
	/*** Indicates the current layer of the node. ***/
	depth = 0;

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
	/*** Indicates the current layer of the node. ***/
	depth = 0;

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
void node::generate(int factor, unsigned mystate)
{
	/*** The calling Parent tells us our depth. ***/
	depth = factor;
	state = mystate;

	if (depth)
	{
		/*** If the depth is one, we only worry about rendering
		 * the current node. ***/
		if (depth == 1)
		{
			state |= ACTIVE;
			clear();
			render();
			refresh();
		}
		/*** Only currently supporting a depth between 1 and 4 ***/
		else if (depth >= 5)
		{
			clear();
			refresh();
			perror("Depth too great, or depth too shallow");
		}
		/*** If the depth is between 2 and 4, we do not render the
		 * current node, but we do create children, and give them 
		 * an identity. This includes populating all their data. ***/
		else 
		{
			node * thisptr;
			thisptr = this;

			nw = new node;
			ne = new node;
			sw = new node;
			se = new node;

			if (n)
			{
				/*** YOU ARE HERE ***/
				/*** Here is where we will find potential 
				 * neighbors from other nodes. ***/
				//node * nnptr = n -> getnnptr();
			}
			if (e);
			if (s);
			if (w);

			node * nwptr = nw;
			node * neptr = ne;
			node * swptr = sw;
			node * septr = se;

			nw -> setparent(thisptr);
			ne -> setparent(thisptr);
			sw -> setparent(thisptr);
			se -> setparent(thisptr);

			nw -> setneighbors(NULL, neptr, swptr, NULL);
			ne -> setneighbors(NULL, NULL, septr, nwptr);
			sw -> setneighbors(nwptr, septr, NULL, NULL);
			se -> setneighbors(neptr, NULL, NULL, swptr);

			/*** YOU ARE HERE ***/
			/*** Still to do: Give each child an x y position. ***/

			/*** YOU ARE HERE ***/
			/*** Still to do: Modify the childstate. This will
			 * include the creation of random walls. ***/
			unsigned childstate = state;

			nw -> generate((depth-1), childstate);
			ne -> generate((depth-1), childstate);
			sw -> generate((depth-1), childstate);
			se -> generate((depth-1), childstate);
		}
	}
	napms(500);
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
	if (state & ACTIVE)
	{
		/*** Order here ensures priority of rendering. ***/
		if (state & HASPLAYER)
			mvaddch(y+1,x+1,ACS_DIAMOND);
		else if (state & ISFINISH)
			mvaddch(y+1,x+1,'F');
		else if (state & ISSTART)
			mvaddch(y+1,x+1,'S');
	}
}

/*** Draws the walls of a node on the screen at a particular location.***/
void node::render(int x, int y)
{
	if (state & ACTIVE)
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

		cell::render(x,y);
	}
}

/*** Called by the parent when creating children ***/
void node::setparent(node * theparent)
{
	parent = theparent;
}

/*** Called by the parent when creating children ***/
void node::setneighbors(node * north, node * east, node * south, node * west)
{
	n = north;
	e = east;
	s = south;
	w = west;
}

/*** Test. ***/
void node::rendertest()
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

	s = new node;
	clear();
	render(10,5);
	refresh();
	napms(500);

	delete n;
	delete s;

	n = s = NULL;
	render(10,5);
	refresh();
	napms(500);

	e = new node;
	clear();
	render(10,5);
	refresh();
	napms(500);

	w = new node;
	clear();
	render(10,5);
	refresh();
	napms(500);

	delete e;
	delete w;

	e = w = NULL;

	clear();
	render(10,5);
	refresh();
	napms(500);

	clear();
	render();
	refresh();
	napms(500);

}

/*** Test. ***/
void node::gentest()
{
	unsigned int mystate;
	mystate = 0x0;
	mystate |= ( ISFINISH | ISSTART | HASPLAYER |
			UPWALL | DOWNWALL | LEFTWALL | RIGHTWALL );

	generate(3,  mystate);
}

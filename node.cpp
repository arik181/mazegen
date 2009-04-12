#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

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
	state = DEFAULT;

	/*** Location Data ***/
	x = 0;
	y = 0;
}

/*** Destructor ***/
node::~node()
{
	/*** Indicates the current layer of the node. ***/
	depth = 0;

	/*** Size Data ***/
	width  = 0;
	height = 0;

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
void node::generate()
{
	/*** If the depth is 2 or above, we do not render the
	 * current node, but we do generate children and give them 
	 * an identity. This includes populating all their data. ***/
	if (depth)
	{
		node * thisptr;
		thisptr = this;

		/*** Pointers to neighboring nodes are arranged as follows:
		 * upwest, upeast,
		 * downwest, downeast,
		 * leftnorth, leftsouth,
		 * rightnorth, rightsouth
		 * ***/
		node * uwptr = NULL;
		node * ueptr = NULL;
		node * dwptr = NULL;
		node * deptr = NULL;
		node * lnptr = NULL;
		node * lsptr = NULL;
		node * rnptr = NULL;
		node * rsptr = NULL;

		/*** Pointers to child nodes ***/
		node * nwptr = NULL;
		node * neptr = NULL;
		node * swptr = NULL;
		node * septr = NULL;

		nw = new node;
		ne = new node;
		sw = new node;
		se = new node;

		if (n)
		{
			uwptr = n -> getswptr();
			ueptr = n -> getseptr();
		}
		if (e)
		{
			rnptr = e -> getnwptr();
			rsptr = e -> getswptr();
		}
		if (s)
		{
			dwptr = s -> getnwptr();
			deptr = s -> getneptr();
		}
		if (w)
		{
			lnptr = w -> getneptr();
			lsptr = w -> getseptr();
		}

		nwptr = nw;
		neptr = ne;
		swptr = sw;
		septr = se;

		/*** YOU ARE HERE ***/
		/*** Still to do: Modify the childstate.
		 * Do you have the player? Do you have the start? finish? ***/
		unsigned nwstate = DEFAULT;
		unsigned nestate = DEFAULT;
		unsigned swstate = DEFAULT;
		unsigned sestate = DEFAULT;

		/*** This is where we add the random walls into the maze. 
		 * One random wall goes amongst our children, and one random
		 * wall for each of our sides. We must confer with our neighbors
		 * in order to iron out conflicts. If a wall has already been put in,
		 * we don't worry about it. If we put in a wall, we make certain that
		 * we aren't blocking any sections off.
		 * ***/
		int centerwall	= 0;
		int northwall	= 0;
		int eastwall	= 0;
		int southwall	= 0;
		int westwall	= 0;
		centerwall = rand() % 3;
		northwall  = 1;
		eastwall   = 2;
		southwall  = 1;
		westwall   = 2;

		nw -> setneighbors(uwptr, neptr, swptr, lnptr);
		ne -> setneighbors(ueptr, rnptr, septr, nwptr);
		sw -> setneighbors(nwptr, septr, dwptr, lsptr);
		se -> setneighbors(neptr, rsptr, deptr, swptr);

		/*** First we plant the central wall. ***/
		if (centerwall == 0)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			nw -> setneighbors(uwptr, NULL, swptr, lnptr);
			ne -> setneighbors(ueptr, rnptr, septr, NULL);
		}
		else if (centerwall == 1)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			ne -> setneighbors(ueptr, rnptr, NULL, nwptr);
			se -> setneighbors(NULL, rsptr, deptr, swptr);
		}
		else if (centerwall == 2)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			sw -> setneighbors(nwptr, NULL, dwptr, lsptr);
			se -> setneighbors(neptr, rsptr, deptr, NULL);
		}
		else if (centerwall == 3)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			nw -> setneighbors(uwptr, neptr, NULL, lnptr);
			sw -> setneighbors(NULL, septr, dwptr, lsptr);
		}

		/*** Player and Start/Finish States are inherited randomly from parents. ***/
		if ((state & ISSTART) && (centerwall == 0))
		{
			nwstate |= (ISSTART | HASPLAYER);
		}
		else if ((state & ISSTART) && (centerwall == 1))
		{
			nestate |= (ISSTART | HASPLAYER);
		}
		else if ((state & ISSTART) && (centerwall == 2))
		{
			swstate |= (ISSTART | HASPLAYER);
		}
		else if ((state & ISSTART) && (centerwall == 3))
		{
			sestate |= (ISSTART | HASPLAYER);
		}

		if ((state & ISFINISH) && (centerwall == 2))
			nwstate |= ISFINISH;
		else if ((state & ISFINISH) && (centerwall == 3))
			nestate |= ISFINISH;
		else if ((state & ISFINISH) && (centerwall == 1))
			swstate |= ISFINISH;
		else if ((state & ISFINISH) && (centerwall == 0))
			sestate |= ISFINISH;

		nw -> setparent(thisptr);
		ne -> setparent(thisptr);
		sw -> setparent(thisptr);
		se -> setparent(thisptr);

		/*** Give each child an x,y position. ***/
		int xmiddle = x+(width/2);
		int ymiddle = y+(height/2);

		nw -> setposition(x,y);
		ne -> setposition(xmiddle, y);
		sw -> setposition(x,ymiddle);
		se -> setposition(xmiddle,ymiddle);

		nw -> setstate(nwstate);
		ne -> setstate(nestate);
		sw -> setstate(swstate);
		se -> setstate(sestate);

		nw -> setfactor(depth-1);
		ne -> setfactor(depth-1);
		sw -> setfactor(depth-1);
		se -> setfactor(depth-1);

		nw -> generate();
		ne -> generate();
		sw -> generate();
		se -> generate();
	}
}

/*** Called by the parent when creating children ***/
void node::setfactor(int mydepth)
{
	/*** This tells the node what "layer" it exists at. ***/
	depth = mydepth;

	/*** This tells the node how large it is, literally, (in characters). ***/
	int n = 0;
	n = pow(2,mydepth);

	width = height = (n * 2);
}

/*** Called by the parent when creating children ***/
void node::setposition(int myx, int myy)
{
	x = myx;
	y = myy;
}

/*** Called by the parent when creating children ***/
void node::setstate(unsigned mystate)
{
	state = mystate;
}

/*** Draws the node on the screen. Default location is x,y ***/
void node::render()
{
	/*** If the depth is zero, we only worry about rendering
	 * the current node. ***/
	if (depth == 0)
	{
		state |= ACTIVE;
		render(x,y);
	}
	else
	{
		nw -> render();
		ne -> render();
		sw -> render();
		se -> render();
	}
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
		/*** Draw walls where applicable. If you discover that 
		 * you have a neighbor, draw a space in order to clear
		 * out any existing wall between you. ***/
		if (!n)
			mvaddch(y,x+1,ACS_HLINE);
		else
		{
			mvaddch(y,x,' ');
			mvaddch(y,x+1,' ');
			mvaddch(y,x+2,' ');
		}

		if (!s)
			mvaddch(y+2,x+1,ACS_HLINE);
		else
		{
			mvaddch(y+2,x,' ');
			mvaddch(y+2,x+1,' ');
			mvaddch(y+2,x+2,' ');
		}

		if (!w)
			mvaddch(y+1,x,ACS_VLINE);
		else
		{
			mvaddch(y,x,' ');
			mvaddch(y+1,x,' ');
			mvaddch(y+2,x,' ');
		}

		if (!e)
			mvaddch(y+1,x+2,ACS_VLINE);
		else
		{
			mvaddch(y,x+2,' ');
			mvaddch(y+1,x+2,' ');
			mvaddch(y+2,x+2,' ');
		}

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
		refresh();
		napms(40);
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

/*** Returns the nw child ***/
node * node::getnwptr()
{
	return nw;
}

/*** Returns the ne child ***/
node * node::getneptr()
{
	return ne;
}

/*** Returns the sw child ***/
node * node::getswptr()
{
	return sw;
}

/*** Returns the se child ***/
node * node::getseptr()
{
	return se;
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
	mystate |= ( ISFINISH | ISSTART | HASPLAYER );

	generate();
}

#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#include "node.h"
#include "maze.h"

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

	/*** Timing Delay (for effect ;) ***/
	delay = 0;
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
	/*** If the depth is 1 or above, we do not render the
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

		nwptr = nw;
		neptr = ne;
		swptr = sw;
		septr = se;

		unsigned nwstate = DEFAULT;
		unsigned nestate = DEFAULT;
		unsigned swstate = DEFAULT;
		unsigned sestate = DEFAULT;

		/*** This is where we add the first set of random walls into the maze. 
		 * One random wall goes amongst our children. 
		 * ***/
		int centerwall	= 0;
		centerwall = rand() % 3;

		/*** These are defaults. ***/
		nw -> setneighbors(uwptr, neptr, swptr, lnptr);
		ne -> setneighbors(ueptr, rnptr, septr, nwptr);
		sw -> setneighbors(nwptr, septr, dwptr, lsptr);
		se -> setneighbors(neptr, rsptr, deptr, swptr);

		/*** First we plant the central wall. ***/
		if (centerwall == 0)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			nw -> seteastneighbor(NULL);
			ne -> setwestneighbor(NULL);
		}
		else if (centerwall == 1)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			ne -> setsouthneighbor(NULL);
			se -> setnorthneighbor(NULL);
		}
		else if (centerwall == 2)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			sw -> seteastneighbor(NULL);
			se -> setwestneighbor(NULL);
		}
		else if (centerwall == 3)
		{
			/*** Neighbors are set in the order n,e,s,w ***/
			nw -> setsouthneighbor(NULL);
			sw -> setnorthneighbor(NULL);
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

/*** Recursively stitches all nodes together. ***/
void node::stitch()
{
	if (depth)
	{
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

		if (n)
		{
			uwptr = n -> sw;
			ueptr = n -> se;
		}
		if (e)
		{
			rnptr = e -> nw;
			rsptr = e -> sw;
		}
		if (s)
		{
			dwptr = s -> nw;
			deptr = s -> ne;
		}
		if (w)
		{
			lnptr = w -> ne;
			lsptr = w -> se;
		}

		/*** Set the external neighbors ***/
		nw -> setnorthneighbor(uwptr);
		nw -> setwestneighbor(lnptr);

		ne -> setnorthneighbor(ueptr);
		ne -> seteastneighbor(rnptr);

		sw -> setsouthneighbor(dwptr);
		sw -> setwestneighbor(lsptr);

		se -> seteastneighbor(rsptr);
		se -> setsouthneighbor(deptr);

		nw -> stitch();
		ne -> stitch();
		sw -> stitch();
		se -> stitch();
	}
}

/*** Called by the parent when creating children ***/
void node::setfactor(int mydepth)
{
	/*** This tells the node what "layer" it exists at. ***/
	depth = mydepth;

	/*** This tells the node how large it is, literally, (in characters). ***/
	int n = 0;
	/*** Casting to a double fixes an ambiguity in pow() that breaks compilation
	 * under Mac OSX. 
	 * Bug fix courtesy of Greg Haynes. ***/
	n = pow((double)2,mydepth);

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
void node::wallrender()
{
	/*** If the depth is zero, we only worry about rendering
	 * the current node. ***/
	if (depth == 0)
	{
		state |= ACTIVE;
		wallrender(x,y);
	}
	else
	{
		nw -> wallrender();
		ne -> wallrender();
		sw -> wallrender();
		se -> wallrender();
	}
}

/*** Draws the node on the screen. Default location is x,y ***/
void node::connectrender()
{
	/*** If the depth is zero, we only worry about rendering
	 * the current node. ***/
	if (depth == 0)
	{
		state |= ACTIVE;
		connectrender(x,y);
	}
	else
	{
		nw -> connectrender();
		ne -> connectrender();
		sw -> connectrender();
		se -> connectrender();
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
		else
		{
			mvaddch(y+1,x+1,' ');

			if (state & ISFINISH)
				mvaddch(y+1,x+1,'F');
			else if (state & ISSTART)
				mvaddch(y+1,x+1,'S');

		}
	}
}

/*** Draws the walls of a node on the screen at a particular location.***/
void node::wallrender(int x, int y)
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
	}
	refresh();
	if (delay)
		napms(delay);
}


/*** Draws the walls of a node on the screen at a particular location.***/
void node::connectrender(int x, int y)
{
	if (state & ACTIVE)
	{	

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
		if (delay)
			napms(delay);
	}
}

/*** Draws the doors of a node. ***/
void node::doorrender()
{
	/*** If the depth is zero, we only worry about rendering
	 * the current node. ***/
	if (depth == 1)
	{
		state |= ACTIVE;
		doorrender(x,y);
	}
	else
	{
		nw -> doorrender();
		ne -> doorrender();
		sw -> doorrender();
		se -> doorrender();
	}
}

/*** Draws the doors of a node.
 * One random wall for each of our sides. We must confer with our neighbors
 * in order to iron out conflicts. If a wall has already been put in,
 * we don't worry about it. If we put in a wall, we make certain that
 * we aren't blocking any sections off.
 * ***/
void node::doorrender(int x, int y)
{
	/*** We now plant a wall on each side, making certain that we don't 
	 * seal off any part of the maze entirely. ***/
	int wallseed	= 0;
	wallseed  = rand() % 3;

	int northwall	= 0;
	int eastwall	= 0;
	int southwall	= 0;
	int westwall	= 0;

	if (wallseed == 0)
	{
		northwall  = 0;
		eastwall   = 2;
		southwall  = 3;
		westwall   = 1;
	}
	else if (wallseed == 1)
	{
		northwall  = 3;
		eastwall   = 0;
		southwall  = 1;
		westwall   = 2;
	}
	else if (wallseed == 2)
	{
		northwall  = 2;
		eastwall   = 1;
		southwall  = 0;
		westwall   = 3;
	}
	else if (wallseed == 3)
	{
		northwall  = 1;
		eastwall   = 3;
		southwall  = 2;
		westwall   = 0;
	}

	/*** Does a wall already exist in the north? south? east? west? ***/
	int northwallexists = 0;
	int eastwallexists = 0;
	int southwallexists = 0;
	int westwallexists = 0;

	/*** Does North even exist? ***/
	if (!n)
		northwallexists = 1;
	/*** Half wall? ***/
	else if (!(n -> sw -> s) || !(n -> se -> s))
		northwallexists = 1;

	/*** Does East even exist? ***/
	if (!e)
		eastwallexists = 1;
	/*** Half wall? ***/
	else if (!(e -> sw -> w) || !(e -> nw -> w))
		eastwallexists = 1;

	/*** Does South even exist? ***/
	if (!s)
		southwallexists = 1;
	/*** Half wall? ***/
	else if (!(s -> nw -> n) || !(s -> ne -> n))
		southwallexists = 1;

	/*** Does West even exist? ***/
	if (!w)
		westwallexists = 1;
	/*** Half wall? ***/
	else if (!(w -> ne -> e) || !(w -> se -> e))
		westwallexists = 1;

	if (!northwallexists)
	{
		if (northwall)
		{
			nw -> n = NULL;
			n -> sw -> s = NULL;
		}
		else
		{
			ne -> n = NULL;
			n -> se -> s = NULL;
		}
	}

	if (!eastwallexists)
	{
		if (eastwall)
		{
			ne -> e = NULL;
			e -> nw -> w = NULL;
		}
		else
		{
			se -> e = NULL;
			e -> sw -> w = NULL;
		}
	}

	if (!southwallexists)
	{
		if (southwall)
		{
			sw -> s = NULL;
			s -> nw -> n = NULL;
		}
		else
		{
			se -> s = NULL;
			s -> ne -> n = NULL;
		}
	}

	if (!westwallexists)
	{
		if (westwall)
		{
			nw -> w = NULL;
			w -> ne -> e = NULL;
		}
		else
		{
			sw -> w = NULL;
			w -> se -> e = NULL;
		}
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

/*** Set an individual neighbor ***/
void node::setnorthneighbor(node * north)
{
	n = north;
}

/*** Set an individual neighbor ***/
void node::seteastneighbor(node * east)
{
	e = east;
}

/*** Set an individual neighbor ***/
void node::setsouthneighbor(node * south)
{
	s = south;
}

/*** Set an individual neighbor ***/
void node::setwestneighbor(node * west)
{
	w = west;
}

/*** Set an individual neighbor ***/
node * node::getnorthneighbor()
{
	return n;
}

/*** Set an individual neighbor ***/
node * node::geteastneighbor()
{
	return e;
}

/*** Set an individual neighbor ***/
node * node::getsouthneighbor()
{
	return s;
}

/*** Set an individual neighbor ***/
node * node::getwestneighbor()
{
	return w;
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

/*** Get the location of the cell center for rendering the player. ***/
int cell::getx()
{
	return x;
}

int cell::gety()
{
	return y;
}


/*** Remove the player from the current cell. ***/
void cell::pickupplayer()
{
	state &= ~(HASPLAYER);
}

/*** Place the player in the current cell. ***/
void cell::placeplayer()
{
	state |= (HASPLAYER);
}

/*** Place the player in the current cell. ***/
void cell::toggleplayer()
{
	state ^= (HASPLAYER);
}

/*** Change the current location of the player by recursively 
 * traversing the maze tree. This is the only place where 
 * node::placeplayer gets called. ***/
void node::pickupplayer(int direction, int maxscry)
{
	cell::toggleplayer();

	/*** If we are at the bottom of the tree... ***/
	if (depth == 0)
	{
		node * newnode = 0x0;

		if (direction == NORTH)
		{
			newnode = n;
		}
		else if (direction == EAST)
		{
			newnode = e;
		}
		else if (direction == SOUTH)
		{
			newnode = s;
		}
		else if (direction == WEST)
		{
			newnode = w;
		}

		if (newnode)
		{
			newnode -> placeplayer(maxscry);
			cell::render();
		}
		else
		{
			cell::toggleplayer();
			cell::render();
			parent -> placeplayer(maxscry);
			invalidmoveerr(maxscry);
		}
	}
	else
	{
		if (nw -> hasplayer())
			nw -> pickupplayer(direction, maxscry);
		else if (ne -> hasplayer())
			ne -> pickupplayer(direction, maxscry);
		else if (sw -> hasplayer())
			sw -> pickupplayer(direction, maxscry);
		else if (se -> hasplayer())
			se -> pickupplayer(direction, maxscry);
	}
}

/*** Give the player a warning about invalid moves ***/
void node::invalidmoveerr(int myscry)
{
	mvaddstr(myscry-2,1,"   Invalid Move   ");
	refresh();
	napms(50);
	mvaddstr(myscry-2,1,"                                              ");
	mvaddstr(myscry-1,1,"                                              ");
	refresh();
}

/*** Give the player a warning about invalid moves ***/
void node::wingame(int myscry)
{
	mvaddstr(myscry-2,1,"   Congratulations, You've solved the maze!");
	mvaddstr(myscry-1,1,"       Have a cookie. You've earned it.");
	refresh();
}

/*** Place the player in a new position. ***/
/*** After node::pickupplayer crawls down the tree toggling the player
 * status as it goes, node::placeplayer crawls back up the tree until
 * it hits the top. ***/
void node::placeplayer(int maxscry)
{
	cell::toggleplayer();

	/*** If we are at the top of the tree... ***/
	if (parent == 0x0);
	else
	{
		if (depth == 0)
		{
			cell::render();
			refresh();
			if (state & ISFINISH)
			{
				wingame(maxscry);
				//newgamerequest();
			}

			refresh();
		}
		parent -> placeplayer(maxscry);
	}
}

/*** Report whether the current node contains the player. ***/
int node::hasplayer()
{
	if (state & HASPLAYER)
		return 1;
	else return 0;
}

/*** Report whether the current node contains the "finish line". ***/
int node::isfinish()
{
	if (state & ISFINISH)
		return 1;
	else return 0;
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

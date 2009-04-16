#include <ncurses.h>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#include "maze.h"

/*** Produces the largest factor of two which will
 * produce a maze that fits inside the screen size. ***/
#define GETFACTOR(y)	(int)floor(sqrt((float)(y/3)))

/*** Default Constructor ***/
maze::maze()
{
}

/*** Create a new maze (which the root node of a tree) by creating its 
 * root node, and giving it some information to start from, such as the 
 * intended depth of the entire tree. Takes the max x and y coordinates 
 * of the screen as input. 
 * ***/
void maze::create(int scrx, int scry)
{
	/*** Seed the random number generator ***/
	srand(time(NULL));

	/*** The following is a bit cryptic, and thus bears explanation.
	 * We determine the size of the screen by using a macro. That 
	 * macro determines the number of layers in our maze by calculating
	 * the minimum required space for our maze using the screen size
	 * (scrx and scry) to give us a factor of 2 for height and width.
	 *
	 * Taken another way: 
	 * A maze of factor 0 will contain one node.
	 * A maze of factor 1 will contain four nodes, or 2 squared, 
	 *   with a single parent node.
	 * A maze of factor 2 will contain sixteen nodes, or four squared,
	 *   with four parent nodes, and one grandparent node.
	 * etc, etc...
	 *
	 * The factor is passed on to the first layer of nodes, and each layer
	 * recursively passes on a factor of n-1 to their children. The "bottom" 
	 * layer of nodes (factor 0) renders itself.
	 * ***/

	int factorx = GETFACTOR(scrx);
	int factory = GETFACTOR(scry);

	if (factorx < factory)
		setfactor(factorx);
	else
		setfactor(factory);

	setposition(0,0);

	setstate(HASPLAYER | ISFINISH | ISSTART);

	generate();

	myscrx = scrx;
	myscry = scry;
}

/*** Create a new maze (which the root node of a tree) by creating its 
 * root node, and giving it some information to start from, such as the 
 * intended depth of the entire tree. Takes a factor of depth as input.
 * ***/
void maze::create(int mydepth)
{
	/*** Seed the random number generator ***/
	srand(time(NULL));

	/*** The following is a bit cryptic, and thus bears explanation.
	 * We determine the size of the screen by using a macro. That 
	 * macro determines the number of layers in our maze by calculating
	 * the minimum required space for our maze using the screen size
	 * (scrx and scry) to give us a factor of 2 for height and width.
	 *
	 * Taken another way: 
	 * A maze of factor 0 will contain one node.
	 * A maze of factor 1 will contain four nodes, or 2 squared, 
	 *   with a single parent node.
	 * A maze of factor 2 will contain sixteen nodes, or four squared,
	 *   with four parent nodes, and one grandparent node.
	 * etc, etc...
	 *
	 * The factor is passed on to the first layer of nodes, and each layer
	 * recursively passes on a factor of n-1 to their children. The "bottom" 
	 * layer of nodes (factor 0) renders itself.
	 * ***/

	setfactor(mydepth);
	
	setposition(0,0);

	setstate(HASPLAYER | ISFINISH | ISSTART);

	generate();
}

/*** Duh. ***/
void maze::render()
{
	clear();
	doorrender();
	wallrender();
	connectrender();
	refresh();
}

/*** YOU ARE HERE ***/
/*** Move the player in a given direction based on user input. ***/
void maze::move(int direction)
{
	/*** Find current location node. ***/
	node * currentplayerloc =  & locateplayer();

	/*** Find new location node. ***/
	node * newplayerloc = 0x0;

	if (direction == NORTH)
	{
		newplayerloc = & currentplayerloc -> getnorthneighbor();
	}
	else if (direction == EAST)
	{
		newplayerloc = & currentplayerloc -> geteastneighbor();
	}
	else if (direction == SOUTH)
	{
		newplayerloc = & currentplayerloc -> getsouthneighbor();
	}
	else if (direction == WEST)
	{
		newplayerloc = & currentplayerloc -> getwestneighbor();
	}

	/*** If new location exists... ***/
	if (newplayerloc)
	{
		/*** Set HASPLAYER to off in current. ***/
		currentplayerloc -> pickupplayer();

		/*** Set HASPLAYER to on in new location. ***/
		newplayerloc -> placeplayer();
		
		currentplayerloc -> render();
		newplayerloc -> render();

		refresh();
		napms(500);
	}
	/*** Otherwise, simply display an error to the player. ***/
	else
	{
		mvaddstr(myscry-1,1,"  Invalid Move.  ");
		refresh();
		napms(500);
		mvaddstr(myscry-1,1,"                 ");
		refresh();
	}
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

/*** Return the current location of the player by recursively 
 * traversing the maze tree. ***/
node & node::locateplayer()
{
	if (depth == 0)
		return * this;
	else
	{
		if (nw -> hasplayer())
		{
			return nw -> locateplayer();
		}
		else if (ne -> hasplayer())
		{
			return ne -> locateplayer();
		}
		else if (sw -> hasplayer())
		{
			return sw -> locateplayer();
		}
		else if (se -> hasplayer())
		{
			return se -> locateplayer();
		}
	}
}

/*** Report whether the current node contains the player. ***/
int node::hasplayer()
{
	if (state & HASPLAYER)
		return 1;
	else return 0;
}

/*** YOU ARE HERE ***/
/*** Destructor ***/
maze::~maze()
{

}


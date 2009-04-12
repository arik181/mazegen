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

	/*** Seed the random number generator ***/
	srand(time(NULL));

	int factorx = GETFACTOR(scrx);
	int factory = GETFACTOR(scry);

	if (factorx < factory)
		setfactor(factorx);
	else
		setfactor(factory);

	/*** For testing only!!! ***/
	//setfactor(5);
	
	setposition(0,0);

	setstate(HASPLAYER | ISFINISH | ISSTART);

	clear();

	generate();

	doorrender();
	wallrender();
	connectrender();

	refresh();

	napms(10000);
}


/*** Move the player in a given direction based on user input. ***/
/*** YOU ARE HERE ***/
void maze::move(int direction)
{

}

/*** Destructor ***/
maze::~maze()
{

}


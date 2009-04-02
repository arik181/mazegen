#include <cstring>
#include <ncurses.h>

using namespace std;

#ifndef NODE
#define NODE

#define ISFINISH	0x1
#define ISSTART		0x2

class node
{
	public:
		/*** Default Constructor ***/
		node();

		/*** Destructor ***/
		~node();

		/*** Draws the node on the screen ***/
		void render();

	protected:

		/*** State Data:
		 * Tells us whether this node is in fact Finish, or 
		 * start, among other things. One node at each 
		 * parent/child "layer" will "be" Start and one will
		 * "be" Finish for that layer.***/
		unsigned state;

		/*** Location Data ***/
		int x;
		int y;

		/*** Neighboring Nodes. NULL if top layer. ***/
		node * n;
		node * e;
		node * s;
		node * w;

		/*** Parent Node. NULL if bottom layer. ***/
		node * parent;

		/*** Child Nodes. NULL if top layer. ***/
		node * nw;
		node * ne;
		node * sw;
		node * se;

		/*** A Neighbor that "knows" the location of Finish. 
		 * In other words, if we follow this "trail" until it
		 * is NULL, we will be at the Finish. Each node must
		 * either be Finish, or know someone who knows Finish. 
		 * ***/
		node * knowsfinish;

		/*** A Neighbor that "knows" the location of Start. 
		 * In other words, if we follow this "trail" until it
		 * is NULL, we will be at the Start. Each node must 
		 * either be Start, or know someone who knows Start.
		 * ***/
		node * knowsstart;

};

#endif // NODE

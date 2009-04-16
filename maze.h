#include "node.h"

#ifndef MAZE
#define MAZE

class maze : public node
{
	public:

		/*** Default Constructor ***/
		maze();

		/*** Create the maze from screen size ***/
		void create(int scrx, int scry);

		/*** Create the maze from a given depth factor***/
		void create(int mydepth);

		/*** Move the player in a given direction based on user input. ***/
		void move(int direction);

		/*** Destructor ***/
		~maze();
};

#endif // MAZE

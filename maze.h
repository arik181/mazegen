#include "node.h"

#ifndef MAZE
#define MAZE

class maze : public node
{
	public:

		/*** Default Constructor ***/
		maze();

		/*** Create the maze ***/
		void create(int scrx, int scry);

		/*** Move the player in a given direction based on user input. ***/
		void move(int direction);

		/*** Destructor ***/
		~maze();
};

#endif // MAZE

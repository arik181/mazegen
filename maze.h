#include "node.h"

#ifndef MAZE
#define MAZE

#define NORTH	0
#define EAST	1
#define SOUTH	2
#define WEST	3

class maze : public node
{
	public:

		/*** Default Constructor ***/
		maze();

		/*** Create the maze from screen size ***/
		void create(int scrx, int scry);

		/*** Create the maze from a given depth factor***/
		void create(int mydepth);

		/*** Draw the maze ***/
		void render();

		/*** Move the player in a given direction based on user input. ***/
		void move(int direction);

		/*** Destructor ***/
		~maze();
	
	protected:

		int myscrx;
		int myscry;

};

#endif // MAZE
/*** maze.h ***/
/*** maze.h ***/

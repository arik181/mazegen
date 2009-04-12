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

		/*** Destructor ***/
		~maze();

};

#endif // MAZE

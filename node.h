#ifndef NODE
#define NODE

/*** Node States ***/
#define ISFINISH	0x1
#define ISSTART		0x2
#define HASPLAYER	0x4
#define ACTIVE		0x8

class cell
{
	public: 
		/*** Default Constructor ***/
		cell();

		/*** Destructor ***/
		~cell();

		/*** Draws the cell on the screen. Default location is x,y ***/
		void render();
		void render(int x, int y);

		/*** Tests Cell Routines ***/
		void test();

	protected:

		/*** Location Data ***/
		int x;
		int y;

		/*** State Data:
		 * Tells us whether this node is in fact Finish, or 
		 * start. One node at each parent/child "layer" will 
		 * "be" Start and one will "be" Finish for that layer. 
		 * Also tracks whether the "player" is in the current cell.
		 * ***/
		unsigned state;
};

class node : public cell
{
	public:
		/*** Default Constructor ***/
		node();

		/*** Destructor ***/
		~node();

		/*** Generates the node ***/
		void generate(int depth);

		/*** Draws the cell on the screen. Default location is 0,0 ***/
		void render();
		void render(int x, int y);

		/*** Tests Node Routines ***/
		void test();

	protected:

		/*** Indicates the current layer of the node. ***/
		int layer;

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

#ifndef NODE
#define NODE

/*** Node States ***/
#define ISFINISH	0x1
#define ISSTART		0x2
#define HASPLAYER	0x4
#define ACTIVE		0x8

/*** States describing walls ***/
#define UPWALL		0x16
#define DOWNWALL	0x32
#define LEFTWALL	0x64
#define RIGHTWALL	0x128

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
		void generate(int depth, unsigned mystate);

		/*** Draws the cell on the screen. Default location is 0,0 ***/
		void render();
		void render(int x, int y);

		/*** Tests Node Routines ***/
		void rendertest();
		void gentest();

		/*** Called by the parent when creating children ***/
		void setparent(node * theparent);
		void setneighbors(node * north, node * east,
				  node * south, node * west);

	protected:

		/*** Indicates the current layer of the node. ***/
		int depth;

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

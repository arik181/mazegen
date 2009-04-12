#ifndef NODE
#define NODE

/*** Node States ***/
#define DEFAULT		0x0
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

		/*** Timing Delay (for effect ;) ***/
		int delay;
};

class node : public cell
{
	public:
		/*** Default Constructor ***/
		node();

		/*** Destructor ***/
		~node();

		/*** Generates the node ***/
		void generate();

		/*** Draws the node on the screen. Default location is 0,0 ***/
		void wallrender();
		void wallrender(int x, int y);
		void connectrender();
		void connectrender(int x, int y);
		void doorrender();
		void doorrender(int x, int y);

		/*** Tests Node Routines ***/
		void rendertest();
		void gentest();

		/*** Called by the parent when creating children ***/
		void setparent(node * theparent);
		void setposition(int myx, int myy);
		void setstate(unsigned mystate);
		void setfactor(int mydepth);
		void setneighbors(node * north, node * east,
				  node * south, node * west);

		/*** Set individual neighbors ***/
		void setnorthneighbor(node * north);
		void seteastneighbor(node * east);
		void setsouthneighbor(node * south);
		void setwestneighbor(node * west);

		/*** Returns the node's children. Useful for setting neighbors. ***/
		node * getnwptr();
		node * getneptr();
		node * getswptr();
		node * getseptr();

	protected:

		/*** Indicates the current layer of the node. ***/
		int depth;

		/*** Size Data ***/
		int width;
		int height;

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

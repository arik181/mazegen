#ifndef SCREEN
#define SCREEN

/*** Deals with the ncurses screen ***/
class screen
{
	public:

		/*** Constructor ***/
		screen();
		~screen();

		/*** Return the coordinates of the screen. ***/
		int getx();
		int gety();

	private:

		int screenx;
		int screeny;
};

#endif // SCREEN

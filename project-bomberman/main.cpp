#include "SFML\Graphics.hpp";
#include "World.h"
#include "Menu.h"
#include "time.h"

void main()
{
	/*World world;
	//srand(time(0));
	world.init();
	world.start();*/

	Menu menu(15*64, 11*64);
	srand(time(0));
	menu.Run();
}
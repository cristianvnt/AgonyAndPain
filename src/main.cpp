#include "Core/Game.h"

int main()
{
	Game game{ "config/settings.ini" };
	game.Run();
}
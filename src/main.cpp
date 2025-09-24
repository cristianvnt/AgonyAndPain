#include "Core/Game.h"

int main()
{
	Game game{ "Config/settings.ini" };
	game.Run();
}
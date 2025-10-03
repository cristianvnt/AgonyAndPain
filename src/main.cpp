#include "Game/Game.h"
#include "Utils/Paths.h"

int main()
{
	Game game(Path::Settings::CONFIG);
	game.Run();
}
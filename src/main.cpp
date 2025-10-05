#include "Game/Game.h"
#include "Engine/Utils/Paths.h"

int main()
{
	Game game(Path::Settings::CONFIG);
	game.Run();
}
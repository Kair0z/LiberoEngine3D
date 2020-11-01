#include "Libero/Engine/Engine.h"
#include "MainGame.h"

#include <Windows.h>

using namespace Libero;

Libero::Game* Libero::CreateGame()
{
	return new MainGame();
}

#ifdef main
#undef main
#endif

int main()
{
	WinMain(GetModuleHandle(0), 0, 0, SW_SHOW);
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//srand(time(NULL));
	Engine* pEngine = new Engine();
	Game* pGame = Libero::CreateGame();

	if (pGame) pEngine->SetGame(pGame);
	pEngine->Run(hInstance);

	delete pEngine;
	delete pGame;

	return 0;
}
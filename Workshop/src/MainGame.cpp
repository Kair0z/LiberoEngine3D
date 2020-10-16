#include "MainGame.h"
#include "EmptyScene.h"

void MainGame::Initialize()
{
	AddScene(new EmptyScene());
}
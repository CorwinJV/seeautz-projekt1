#include "tutorialMap1.h"
#include "GameStateManager.h"



bool tutorialMap1::Update()
{


	return true;
}

bool tutorialMap1::Draw()
{
	tutorialmap1->draw();

	return false;
}

bool tutorialMap1::initialize()
{
	tutorialmap1 = new gameBoard();
	tutorialmap1->LoadGameMapFromFile("maps\\tutorialMap1.txt");
	return true;
}
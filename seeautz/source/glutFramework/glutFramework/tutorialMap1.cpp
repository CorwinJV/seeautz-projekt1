#include "tutorialMap1.h"
#include "GameStateManager.h"



bool tutorialMap1::Update()
{
	tutorialmap1->mapScroll();
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
	tutorialmap1->LoadGameMapFromFile("maps\\map2.txt");

	return true;
}

void tutorialMap1::processMouse(int x, int y)
{
	tutorialmap1->processMouse(x, y);
}

void tutorialMap1::processMouseClick(int button, int state, int x, int y)
{
	tutorialmap1->processMouseClick(button, state, x, y);
}

void tutorialMap1::keyboardInput(unsigned char c, int x, int y)
{
	tutorialmap1->keyboardInput(c, x, y);
}
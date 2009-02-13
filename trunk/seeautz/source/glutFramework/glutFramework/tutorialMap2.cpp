#include "tutorialMap2.h"
#include "GameStateManager.h"

bool tutorialMap2::Update()
{
	tutorialmap2->mapScroll();
	// see if the robot is at the end square
	return true;
}

bool tutorialMap2::Draw()
{
	tutorialmap2->draw();
	return false;
}

bool tutorialMap2::initialize()
{
	tutorialmap2 = new gameBoard();
	tutorialmap2->LoadGameMapFromFile("maps\\tutorialMap2.txt");
	return true;
}

void tutorialMap2::processMouse(int x, int y)
{
	tutorialmap2->processMouse(x, y);
}

void tutorialMap2::processMouseClick(int button, int state, int x, int y)
{
	tutorialmap2->processMouseClick(button, state, x, y);
}

void tutorialMap2::keyboardInput(unsigned char c, int x, int y)
{
	tutorialmap2->keyboardInput(c, x, y);
}
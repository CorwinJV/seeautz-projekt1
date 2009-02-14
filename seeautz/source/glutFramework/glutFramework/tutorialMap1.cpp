#include "tutorialMap1.h"
#include "tutorialMap2.h"
#include "GameStateManager.h"



bool tutorialMap1::Update()
{
	tutorialmap1->mapScroll();
	// see if the robot is at the end square
	if(tutorialmap1->robotAtEndSquare())
	{
		tutorialmap1->~gameBoard();
		delete tutorialmap1;
		GSM->addGameState<tutorialMap2>();
		this->setStatus(DeleteMe);
	}

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
	//tutorialmap1->LoadGameMapFromFile("maps\\tutorialMap1.txt");
	tutorialmap1->LoadGameMapFromFile("maps\\testMap1.txt");
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
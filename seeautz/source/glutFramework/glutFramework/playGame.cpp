#include "playGame.h"
#include "GameStateManager.h"



bool playGame::Update()
{
	tutorialmap1->mapScroll();
	// see if the robot is at the end square
	if(tutorialmap1->robotAtEndSquare())
	{
		tutorialmap1->~gameBoard();
		delete tutorialmap1;
		GSM->addGameState<playGame>();
		this->setStatus(DeleteMe);
	}

	return true;
}

bool playGame::Draw()
{
	tutorialmap1->draw();
	mInterface.Draw();
	return false;
}

bool playGame::initialize()
{
	tutorialmap1 = new gameBoard();
	//tutorialmap1->LoadGameMapFromFile("maps\\tutorialMap1.txt");
	tutorialmap1->LoadGameMapFromFile("maps\\Map11.txt");

	//=====================================================
	// Register the gameBoard callback with the interface!
	mInterface.SetExecuteHandler(BE::CreateFunctionPointer1R(tutorialmap1, &gameBoard::interfaceHasFiredExecuteOrder));

	return true;
}

void playGame::processMouse(int x, int y)
{
	tutorialmap1->processMouse(x, y);
	mInterface.processMouse(x, y);
}

void playGame::processMouseClick(int button, int state, int x, int y)
{
	tutorialmap1->processMouseClick(button, state, x, y);
	mInterface.processMouseClick(button, state, x, y);
}

void playGame::keyboardInput(unsigned char c, int x, int y)
{
	tutorialmap1->keyboardInput(c, x, y);
}
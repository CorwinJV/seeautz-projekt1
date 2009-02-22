#include "playGame.h"
#include "GameStateManager.h"


bool playGame::Update()
{
	gamePlay->update();
	gamePlay->mapScroll();
	// see if the robot is at the end square
	if(gamePlay->robotAtEndSquare())
	{
		//gamePlay->~gameBoard();
		//delete gamePlay;
		//GSM->addGameState<playGame>();
		//this->setStatus(DeleteMe);
	}

	return true;
}

bool playGame::Draw()
{
	gamePlay->draw();
	mInterface.Draw();
	return false;
}

bool playGame::initialize()
{
	gamePlay = new gameBoard();
	//gamePlay->LoadGameMapFromFile("maps\\tutorialMap1.txt");
	gamePlay->LoadGameMapFromFile("maps\\testMap1.txt");

	//=====================================================
	// Register the gameBoard callback with the interface!
	mInterface.SetExecuteHandler(BE::CreateFunctionPointer1R(gamePlay, &gameBoard::interfaceHasFiredExecuteOrder));
	mInterface.SetAbortHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredAbortOrder));
	return true;
}

void playGame::processMouse(int x, int y)
{
	gamePlay->processMouse(x, y);
	mInterface.processMouse(x, y);
}

void playGame::processMouseClick(int button, int state, int x, int y)
{
	gamePlay->processMouseClick(button, state, x, y);
	mInterface.processMouseClick(button, state, x, y);
}

void playGame::keyboardInput(unsigned char c, int x, int y)
{
	gamePlay->keyboardInput(c, x, y);
}
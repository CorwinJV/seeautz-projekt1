#include "playGame.h"
#include "GameStateManager.h"


bool playGame::Update()
{
	GameBoardState curState;
	curState = gamePlay->getCurState();
	int levelCounter;

	gamePlay->update();
	gamePlay->mapScroll();
	
	// see if the robot is at the end square
	if((gamePlay->robotAtEndSquare())&& (curState == GB_EXECUTION))
	{
		curState = GB_VIEWSCORE;
		gamePlay->setState(curState);
	}

	switch(curState)
	{
	case GB_VIEWSCORE:
		//save the game for the player, whether they like it or not!
		GameVars->SavePlayerGame(GameVars->getPlayerName());

		//this will eventually be displayed on the menu, until now deal with it
		std::cout << GameVars->getPlayerName() << std::endl;
		std::cout << GameVars->getLevelScore() << std::endl;
		std::cout << GameVars->getTotalScore() << std::endl;
		//display a menu that shows info and contains advance and exit buttons
		//once advance button is clicked set curState to GB_FINISHED
		curState = GB_FINISHED;
		gamePlay->setState(curState);
		//if exit it clicked quit game
		break;
	case GB_FINISHED:
		//gamePlay->~gameBoard();
		delete gamePlay;
		
		mInterface.ClearExecutionList();
		
		// in with the new
		gamePlay = new gameBoard();

		levelCounter = GameVars->getCurrentLevel();
		levelCounter++;
		GameVars->setLevel(levelCounter);
		gamePlay->LoadGameMapFromFile(levelList[levelCounter]->getFile());
	
		//=====================================================
		// Register the gameBoard callback with the interface!
		mInterface.SetExecuteHandler(BE::CreateFunctionPointer1R(gamePlay, &gameBoard::interfaceHasFiredExecuteOrder));
		mInterface.SetAbortHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredAbortOrder));
		curState = GB_LOGICVIEW;
		gamePlay->setState(curState);
		break;
	default:
		break;
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
	GameVars->setLevel(0);

	levelData* tempLevel;

	tempLevel = new levelData("Tutorial 1", 1024, "Opening Doors", "maps\\tutorialMap1.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 2", 1024, "Moving and Turning", "maps\\tutorialMap2.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 3", 1024, "Move forward until you hit an obstacle", "maps\\tutorialMap3.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 4", 1024, "Croutching", "maps\\tutorialMap4.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 5", 1024, "Jumping", "maps\\tutorialMap5.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 6", 1024, "Punching", "maps\\tutorialMap6.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 7", 1024, "Complete Tutorial", "maps\\tutorialMap7.txt");
	levelList.push_back(tempLevel);


	gamePlay = new gameBoard();
	//gamePlay->LoadGameMapFromFile("maps\\testMap1.txt");
	gamePlay->LoadGameMapFromFile(levelList[GameVars->getCurrentLevel()]->getFile());

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

playGame::~playGame()
{
	//below is memory management that may or may not work, we'll see (Oscar)

	vector<levelData*>::iterator itr = levelList.end();
	for (; itr != levelList.begin(); itr--)
	{
		delete(*itr);
		levelList.erase(itr);
	}
}
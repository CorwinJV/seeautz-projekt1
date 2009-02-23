#include "playGame.h"
#include "GameStateManager.h"
#include <sstream>


bool playGame::Update()
{
	curState = gamePlay->getCurState();
	int levelCounter;
	
	// see if the robot is at the end square
	if((gamePlay->robotAtEndSquare())&& (curState == GB_EXECUTION))
	{
		curState = GB_VIEWSCORE;
		gamePlay->setState(curState);
	}

	switch(curState)
	{
	case GB_LOGICVIEW:
		gameSaved = false;
		gamePlay->update();
		gamePlay->mapScroll();
		break;
	case GB_EXECUTION:
		gameSaved = false;
		gamePlay->update();
		gamePlay->mapScroll();
		break;
	case GB_PREGAME:
		gameSaved = false;
		break;
	case GB_VIEWSCORE:
		//save the game for the player, if it hasn't been saved yet
		if(!gameSaved)
		{
			GameVars->SavePlayerGame(GameVars->getPlayerName());
			gameSaved = true;
		}

		//this will eventually be displayed on the menu, until now deal with it
		/*std::cout << GameVars->getPlayerName() << std::endl;
		std::cout << GameVars->getLevelScore() << std::endl;
		std::cout << GameVars->getTotalScore() << std::endl;*/
		
		myMenu->Update();
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
	GameBoardState curState;
	curState = gamePlay->getCurState();
	string tempString;

	switch(curState)
	{
	case GB_LOGICVIEW:
		gamePlay->draw();
		mInterface.Draw();
		break;
	case GB_EXECUTION:
		gamePlay->draw();
		mInterface.Draw();
		break;
	case GB_PREGAME:
		// gl shit that may or may not be needed for font stuff, we shall find out shortly
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glColor3ub(255, 255, 255);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		tempString = "Player Name: " + GameVars->getPlayerName();
		GameVars->fontArial.drawText(150, 50, tempString);
		tempString = "Level #" + GameVars->getCurrentLevel();
		GameVars->fontArial.drawText(150, 75, tempString);
		GameVars->fontArial.drawText(150, 100, levelList[GameVars->getCurrentLevel()]->getName());
		GameVars->fontArial.drawText(150, 125, levelList[GameVars->getCurrentLevel()]->getDesc());
		
		break;
	case GB_VIEWSCORE:
		gamePlay->draw();
		if(myMenu != NULL)
			myMenu->Draw();
		//mInterface.Draw();
		break;
	case GB_FINISHED:
		//gamePlay->draw();
		//mInterface.Draw();

		break;
	default:
		break;
	}
	return false;
}

bool playGame::initialize()
{
	GameVars->setLevel(0);

	levelData* tempLevel;

	tempLevel = new levelData("DEBUG MAP", "THIS IS FOR DAVE TO DEBUG MAP TILES", "maps\\testMap1.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 1", "Opening Doors", "maps\\tutorialMap1.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 2", "Moving and Turning", "maps\\tutorialMap2.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 3", "Moving Forward Until Unable", "maps\\tutorialMap3.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 4", "Crouching", "maps\\tutorialMap4.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 5", "Climbing and Jumping", "maps\\tutorialMap5.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 6", "Punching", "maps\\tutorialMap6.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Tutorial 7", "Complete Tutorial", "maps\\tutorialMap7.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Map 11", "Insanity #1", "maps\\Map11.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Map 12", "Insanity #2", "maps\\Map12.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Map 13", "Insanity #3", "maps\\Map13.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Map 14", "Insanity #4", "maps\\Map14.txt");
	levelList.push_back(tempLevel);

	tempLevel = new levelData("Map 15", "Insanity #5", "maps\\Map15.txt");
	levelList.push_back(tempLevel);

	gamePlay = new gameBoard();
	GameVars->setLevel(1);
	gamePlay->LoadGameMapFromFile(levelList[GameVars->getCurrentLevel()]->getFile());

	//=====================================================
	// Register the gameBoard callback with the interface!
	mInterface.SetExecuteHandler(BE::CreateFunctionPointer1R(gamePlay, &gameBoard::interfaceHasFiredExecuteOrder));
	mInterface.SetAbortHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredAbortOrder));

	gamePlay->setState(GB_LOGICVIEW);
	gameSaved = false;

	//display a menu that shows info and contains advance and exit buttons
	img = new oglTexture2D();
	if(img != NULL)
		img->loadImage("..\\Content\\statescreens\\mainmenu.png", 1024, 120);
	img->mY = 618;

	myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
	myMenu->addButton("..\\Content\\buttons\\advance.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &playGame::advance));
	myMenu->addButton("..\\Content\\buttons\\exit.png",	 "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &playGame::exitGame));
	Update();

	// pregame textinfo
	preGameTextOffsetX = 100;
	preGameTextOffsetY = 100;
	preGameTextSpacing = 45;
	return true;
}

void playGame::processMouse(int x, int y)
{
	gamePlay->processMouse(x, y);
	mInterface.processMouse(x, y);
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void playGame::processMouseClick(int button, int state, int x, int y)
{
	gamePlay->processMouseClick(button, state, x, y);
	mInterface.processMouseClick(button, state, x, y);
	if(curState == GB_VIEWSCORE)
	{
		if(myMenu != NULL)
			myMenu->processMouseClick(button, state, x, y);
	}

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

bool playGame::advance()
{
	curState = GB_FINISHED;
	gamePlay->setState(curState);

	return true;
}

bool playGame::exitGame()
{
	exit(0);

	return true;
}




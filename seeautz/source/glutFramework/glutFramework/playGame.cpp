#include "playGame.h"
#include "GameStateManager.h"
#include <sstream>
#include <string>


bool playGame::Update()
{
	curState = gamePlay->getCurState();
	int levelCounter;
	string tempString;
	int tempInt;
	
	// see if the robot is at the end square
	if((gamePlay->robotAtEndSquare())&& (curState == GB_EXECUTION))
	{
		curState = GB_VIEWSCORE;
		gamePlay->setState(curState);
	}

	// Update mInterface all the time
	mInterface.Update();

	int maxLevel;
	switch(curState)
	{
	case GB_LOGICVIEW:
		gameSaved = false;
		pregameRunning = false;
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
		if(pregameRunning)
		{
			timer = clock();
			if(timer > (startTime + 5000))
			{
				pregameRunning = false;
				gamePlay->setState(GB_LOGICVIEW);
			}
		}
		else
		{
			startTime = clock();
			timer = clock();
			pregameRunning = true;
		}
		break;

	case GB_ROBOTDIED:
		gameSaved = false;
		if(pregameRunning)
		{
			timer = clock();
			if(timer > (startTime + 5000))
			{
				pregameRunning = false;
				gamePlay->setState(GB_LOGICVIEW);
			}
		}
		else
		{
			startTime = clock();
			timer = clock();
			pregameRunning = true;
		}
		break;

	case GB_VIEWSCORE:
		//save the game for the player, if it hasn't been saved yet
		if(!gameSaved)
		{
			GameVars->SavePlayerGame(GameVars->getPlayerName()+".txt");
			gameSaved = true;
		}

		//Get the number of bytes user started the level off with and subtract number remaining
		playerScore = GameVars->getTotalScore();

		// eventually we will implement an equation here to calculate the score based off percentage 
		// of points used for the level score
		
		myMenu->Update();
		break;

	case GB_FINISHED:
		//gamePlay->~gameBoard();

		mInterface.ClearExecutionList();
		mInterface.ResetExecutionMode();
		levelCounter = GameVars->getCurrentLevel();
		levelCounter++;
		maxLevel = GameVars->getMaxLevel();

		if(levelCounter < (GameVars->getMaxLevel()))
		{
			delete gamePlay;			
			// in with the new
			gamePlay = new gameBoard();			
			tempString = GameVars->getFilename(levelCounter);
			tempInt = GameVars->getCurrentLevel();
			gamePlay->LoadGameMapFromFile(tempString);
			mInterface.GetCurrentMapLogicBank();
			curState = GB_PREGAME;
		}
		else
		{
			curState = GB_YOUWIN;
			levelCounter;
			//gamePlay = NULL;
			//gamePlay->LoadGameMapFromFile(levelList[levelCounter]->getFile());			
		}

		GameVars->setLevel(levelCounter);
	
		//=====================================================
		// Register the gameBoard callback with the interface!
		mInterface.SetExecuteHandler(BE::CreateFunctionPointer3R(gamePlay, &gameBoard::interfaceHasFiredExecuteOrder));
		mInterface.SetAbortHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredAbortOrder));
		mInterface.SetResetHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredResetOrder));
		gamePlay->SetInterfaceAdvanceHandler(BE::CreateFunctionPointer2R(&mInterface, &LogicInterface::CommandAdvanced));

		gamePlay->setState(curState);
		pregameRunning = false;
		break;
	case GB_YOUWIN:
		// upload score onto server (when it gets implemented)

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
	int offsetAmt = 0;
	std::stringstream painInTheAss;
	//clock_t startTime;
	int tempInt;
	oglTexture2D fadeToBlack;

	switch(curState)
	{
	case GB_LOGICVIEW:
		gamePlay->draw();
		mInterface.Draw();
		drawLevelInfo();
		break;

	case GB_EXECUTION:
		gamePlay->draw();
		mInterface.Draw();
		drawLevelInfo();
		break;

	case GB_PREGAME:
		// gl shit that may or may not be needed for font stuff, we shall find out shortly
		glClearColor(0, 0, 0, 0);
		//glutSwapBuffers();
		//glEnable(GL_TEXTURE_2D);
		//glEnable(GL_BLEND);

		glColor3ub(255, 0, 0);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		// player name
		tempString = "Player Name: ";
		tempString += GameVars->getPlayerName();
		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;

		// level title
		tempInt = GameVars->getCurrentLevel();
		tempString = GameVars->getFilename(tempInt);

		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;

		tempString = GameVars->getDesc(tempInt);
		// description
		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;

		// bytes available
		tempString = "Bytes Available: ";
		painInTheAss.clear();
		tempInt = GameVars->getCurrentLevelBytes();
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;			
		break;

	case GB_ROBOTDIED:
		// gl shit that may or may not be needed for font stuff, we shall find out shortly
		glClearColor(0, 0, 0, 0);
		//glutSwapBuffers();
		//glEnable(GL_TEXTURE_2D);
		//glEnable(GL_BLEND);

		glColor3ub(255, 0, 0);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		// player name
		GameVars->fontDigital200.drawText(150 + rand()%15, 250 + rand()%15, "YOU DIED");
		break;

	case GB_VIEWSCORE:
		if(myMenu != NULL)
			myMenu->Draw();

		// clear the temp string
		tempString = "";

		// display the level score
		tempString = "YOUR LEVEL SCORE: ";
		painInTheAss.clear();
		tempInt = GameVars->getLevelScore();
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial32.drawText(225, 200, tempString);

		// clear the temp string
		tempString = "";

		// display the total score
		tempString = "YOUR TOTAL SCORE: ";
		painInTheAss.clear();
		tempInt = GameVars->getTotalScore();
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial32.drawText(225, 300, tempString);

		
		if(myMenu != NULL)
			myMenu->Draw();
		//mInterface.Draw();
		break;

	case GB_FINISHED:
		//gamePlay->draw();
		//mInterface.Draw();
		break;

	case GB_YOUWIN:
		doEndGameDraw();
		break;

	default:
		break;
	}
	return false;
}

bool playGame::initialize()
{
	string tempString;
	int playerCurrentLevel;

	gamePlay = new gameBoard();

	//this wont work if we're coming in out of a level select
	playerCurrentLevel = GameVars->getPlayerMaxLevel();
	GameVars->setLevel(playerCurrentLevel);

	tempString = GameVars->getFilename(playerCurrentLevel);
	gamePlay->LoadGameMapFromFile(tempString);
	//gamePlay->LoadGameMapFromFile(levelList[GameVars->getCurrentLevel()]->getFile());
	mInterface.GetCurrentMapLogicBank();

	//=====================================================
	// Register the gameBoard callback with the interface!
	mInterface.SetExecuteHandler(BE::CreateFunctionPointer3R(gamePlay, &gameBoard::interfaceHasFiredExecuteOrder));
	mInterface.SetAbortHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredAbortOrder));
	mInterface.SetResetHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredResetOrder));
	gamePlay->SetInterfaceAdvanceHandler(BE::CreateFunctionPointer2R(&mInterface, &LogicInterface::CommandAdvanced));

	
	gamePlay->setState(GB_PREGAME);
	pregameRunning = false;
	gameSaved = false;

	//display a menu that shows info and contains advance and exit buttons
	img = new oglTexture2D();
	if(img != NULL)
		img->loadImage("..\\Content\\statescreens\\mainmenu.png", 1024, 120);
	img->mY = 618;
	

	myMenu = new MenuSys(250, 50, "blank.png", None);
	myMenu->addButton("..\\Content\\buttons\\advance.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &playGame::advance));
	myMenu->setLastButtonDimensions(100, 100);
	myMenu->setLastButtonPosition(600, 400);
	myMenu->addButton("..\\Content\\buttons\\exit.png",	 "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &playGame::exitGame));
	myMenu->setLastButtonDimensions(100, 100);
	myMenu->setLastButtonPosition(350, 400);
	Update();

	// pregame textinfo
	preGameTextOffsetX = 100;
	preGameTextOffsetY = 100;
	preGameTextSpacing = 45;
	return true;
}

void playGame::processMouse(int x, int y)
{
	switch(curState)
	{
	case GB_LOGICVIEW:
	case GB_EXECUTION:
	case GB_FINISHED:
	case GB_VIEWSCORE:
		gamePlay->processMouse(x, y);
		mInterface.processMouse(x, y);
		if(myMenu != NULL)
			myMenu->processMouse(x, y);
		break;
	case GB_PREGAME:
	case GB_ROBOTDIED:
		break;
	default:
		break;
	}
}

void playGame::processMouseClick(int button, int state, int x, int y)
{
	switch(curState)
	{
	case GB_LOGICVIEW:
	case GB_EXECUTION:
	case GB_FINISHED:
	case GB_VIEWSCORE:
		gamePlay->processMouseClick(button, state, x, y);
		mInterface.processMouseClick(button, state, x, y);
		if(curState == GB_VIEWSCORE)
		{
			if(myMenu != NULL)
				myMenu->processMouseClick(button, state, x, y);
		}
		break;
	case GB_PREGAME:
	case GB_ROBOTDIED:
		break;
	default:
		break;
	}
}

void playGame::keyboardInput(unsigned char c, int x, int y)
{
	switch(curState)
	{
	case GB_LOGICVIEW:
	case GB_EXECUTION:
		gamePlay->keyboardInput(c, x, y);
		break;
	case GB_PREGAME:
	case GB_ROBOTDIED:
		switch(c)
		{
		case 27:
			gamePlay->setState(GB_LOGICVIEW);
			break;
		default:
			break;
		}
		break;
	case GB_YOUWIN:
		switch(c)
		{
		case 27:
			exit(0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
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

void playGame::levelSelect()
{
	//add level select state info here when it's setup
}

void playGame::doEndGameDraw()
{
	if(endGamePics.size() == 0)
	{
		// load in alot of pictures
		int numPics = 45;
		oglTexture2D* tempPic;
		for(int x = 0; x < numPics; x++)
		{
			string filename;
			stringstream filenumber;
			// build a variable filename
			filenumber.clear();
			filenumber << x;
			filename = "..\\Content\\ending\\frames\\ending00";
			filename += filenumber.str();
			filename += ".png";
			tempPic = new oglTexture2D;
			tempPic->loadImage(filename, 1024, 768);
			endGamePics.push_back(tempPic);
		}
		endGameAnimation = endGamePics.begin();
	}
	else
	{
		// iterate through the pictures drawing them
		(*endGameAnimation)->drawImage(0, 0);
		endGameAnimation++;
		if(endGameAnimation == endGamePics.end())
			endGameAnimation = endGamePics.begin();
		timer = clock();
		startTime = clock();
		while(timer < startTime + 50)
		{
			timer = clock();
		}		
	}
}

void playGame::drawLevelInfo()
{
	string tempString;
	int playerCurrentLevel;

	int textOffsetX = 20;
	int textOffsetY = 20;
	int textSpacing = 20;
	int offsetAmt = 0;
	glColor3ub(255, 0, 0);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	//this wont work if we're coming in out of a level select
	playerCurrentLevel = GameVars->getCurrentLevel();

	tempString = GameVars->getFilename(playerCurrentLevel);
		
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, tempString);
	offsetAmt++;

	// description
	tempString = GameVars->getDesc(playerCurrentLevel);
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, tempString);
	offsetAmt++;
}
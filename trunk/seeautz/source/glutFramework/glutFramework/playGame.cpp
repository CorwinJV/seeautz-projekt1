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
		if(!finishing)
		{
			startTime = clock();
			spintimer = clock();
			spintimerStart = clock();
			finishing = true;
		}
		timer = clock();
		if(timer > startTime + 2000)
		{
			finishing = false;
			finishNow = true;
			curState = GB_VIEWSCORE;
			gamePlay->setState(curState);
			GameVars->totalCommandsProcessed += GameVars->commandsProcessed;
			double scoreToAdd = 0;
			int bytesUsed = GameVars->getBytesUsed();
			int bytesAvail = GameVars->getCurrentLevelBytes();
			scoreToAdd = ((100 - (((double)bytesUsed/(double)bytesAvail)*100)) * 10) + 200;
			//scoreToAdd *= (double)GameVars->getCurrentLevel() * 0.1;
			GameVars->setLevelScore(scoreToAdd);
			GameVars->setTotalScore(GameVars->getLevelScore() + GameVars->getTotalScore());
		}
		spintimer = clock();
		if(spintimer > spintimerStart + 200)
		{
			gamePlay->spinRobot();
			spintimerStart = clock();
		}

	}

	// Update mInterface all the time
	mInterface.Update();
	compass->Update();

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
		if(!finishNow && !finishing)
		{
			gameSaved = false;
			gamePlay->update();
			gamePlay->mapScroll();
		}
		break;

	case GB_PREGAME:
		gameSaved = false;
		if(pregameRunning)
		{
			timer = clock();
			if(timer > (startTime + 5000))
			{
				pregameRunning = false;
				GameVars->commandsProcessed = 0;
				GameVars->totalCommandsProcessed = 0;
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
		doneDead = false;
		if(pregameRunning)
		{
			timer = clock();
			if(timer > (startTime + 5000))
			{
				pregameRunning = false;
				doneDead = true;
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
		finishNow = false;
		if(!gameSaved)
		{
			GameVars->updatePlayerFile();
		//	GameVars->PM->saveProfile();
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
			mInterface.GetCurrentLevelBytes();
			GameVars->commandsProcessed = 0;
			GameVars->totalCommandsProcessed = 0;
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

	if((!gamePlay->getRobotAlive()) && doneDead)
	{
		mInterface.AbortButtonClick();
		doneDead = false;
		gamePlay->setState(GB_LOGICVIEW);
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
	int textspacing = 30;
	int viewscoretext = backgroundImage->mY+50;

	switch(curState)
	{
	case GB_LOGICVIEW:
		glClearColor(0, 0, 0, 0);
		gamePlay->draw();
		mInterface.Draw();
		drawLevelInfo();
		compass->Draw();
		break;

	case GB_EXECUTION:
		glClearColor(0, 0, 0, 0);
		gamePlay->draw();
		mInterface.Draw();
		drawLevelInfo();
		compass->Draw();
		break;

	case GB_PREGAME:

		if(currentStatus == Passive)	// waiting for click ok to continue to finish...
		{
			startTime = clock();
			timer = clock();
			pregameRunning = true;
			gamePlay->setState(GB_PREGAME);
		}

		clearBackground();

		logoImage->drawImage();
		backgroundImage->drawImage();

		glColor3ub(0, 0, 0);

		// player name
		tempString = "Player Name: ";
		tempString += GameVars->PM->getPlayerName();
		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;

		// level name
		tempInt = GameVars->getCurrentLevel();
		tempString = GameVars->getLevelName(tempInt);

		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;

		// level description
		tempString = GameVars->getDesc(tempInt);
		// description
		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;

		// bytes available
		tempString = "Bytes Available: ";
		painInTheAss.str("");
		tempInt = GameVars->getCurrentLevelBytes();
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial32.drawText(preGameTextOffsetX, preGameTextOffsetY + offsetAmt*preGameTextSpacing, tempString);
		offsetAmt++;
		break;

	case GB_ROBOTDIED:
		// gl shit that may or may not be needed for font stuff, we shall find out shortly
		clearBackground();
		//glutSwapBuffers();
		//glEnable(GL_TEXTURE_2D);
		//glEnable(GL_BLEND);

		glColor3ub(255, 0, 0);

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		// player name
		//GameVars->fontDigital200.drawText(150 + rand()%15, 250 + rand()%15, "YOU DIED");
		youDiedImage->mX = rand()%15;
		youDiedImage->mY = rand()%15;
		youDiedImage->drawImage();
		break;

	case GB_VIEWSCORE:
		clearBackground();
		logoImage->drawImage();
		backgroundImage->drawImage();
		
		if(myMenu != NULL)
			myMenu->Draw();

		glColor3ub(0, 0, 0);
		//
		// level name
		tempString = "Congratulations! Level Complete!";
		GameVars->fontArial32.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;
		offsetAmt++;
		offsetAmt++;

		// level name
		tempInt = GameVars->getCurrentLevel();
		tempString = GameVars->getLevelName(tempInt);

		GameVars->fontArial24.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;

		// level description
		tempString = GameVars->getDesc(tempInt);
		// description
		GameVars->fontArial24.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;
		offsetAmt++;

		painInTheAss.str("");

		// bytes used
		tempString = "";
		tempString = "BYTES USED: ";
		tempInt = GameVars->getBytesUsed(); // this should get the bytes used value
		painInTheAss.str("");
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial24.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;

		// commands used
		tempString = "";
		tempString = "COMMANDS PROCESSED: ";
		tempInt = GameVars->totalCommandsProcessed;
		painInTheAss.str("");
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial24.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;
		
		// level score
		tempString = "";
		tempString = "YOUR LEVEL SCORE: ";
		tempInt = GameVars->getLevelScore();
		painInTheAss.str("");
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial24.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;

		// TOTAL SCORE
		tempString = "";
		tempString = "YOUR TOTAL SCORE: ";
		tempInt = GameVars->getTotalScore();
		painInTheAss.str("");
		painInTheAss << tempInt;
		tempString += painInTheAss.str();
		GameVars->fontArial24.drawText(200, viewscoretext+ offsetAmt*textspacing, tempString);
		offsetAmt++;
		
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
	finishNow = false;
	finishing = false;
	string tempString;
	int playerCurrentLevel;
	youDiedImage = new oglTexture2D();
	youDiedImage->loadImage("youdied.png", 1024,768);
	doneDead = false;

	gamePlay = new gameBoard();

	//check to see if a level has been specified (initialized to -1)
	playerCurrentLevel = GameVars->getLevelSpecified();
	if(playerCurrentLevel < 0)
	{
		//if a level has not been specified, set to max level
		playerCurrentLevel = GameVars->getPlayerMaxLevel();
	}

	// debug brute force of level
	// abcxyz
	//playerCurrentLevel = 0;
	GameVars->setLevel(playerCurrentLevel);
	
	

	tempString = GameVars->getFilename(playerCurrentLevel);
	gamePlay->LoadGameMapFromFile(tempString);
	//gamePlay->LoadGameMapFromFile(levelList[GameVars->getCurrentLevel()]->getFile());
	mInterface.GetCurrentMapLogicBank();
	mInterface.GetCurrentLevelBytes();

	//=====================================================
	// Register the gameBoard callback with the interface!
	mInterface.SetExecuteHandler(BE::CreateFunctionPointer3R(gamePlay, &gameBoard::interfaceHasFiredExecuteOrder));
	mInterface.SetAbortHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredAbortOrder));
	mInterface.SetResetHandler(BE::CreateFunctionPointer0R(gamePlay, &gameBoard::interfaceHasFiredResetOrder));
	gamePlay->SetInterfaceAdvanceHandler(BE::CreateFunctionPointer2R(&mInterface, &LogicInterface::CommandAdvanced));

	
	gamePlay->setState(GB_PREGAME);
	pregameRunning = false;
	gameSaved = false;

	//display a menu that shows info and contains advance, replay level and exit buttons

	blackImage = new oglTexture2D();
	blackImage->loadImage("black.png", 373, 61);
	

	myMenu = new MenuSys(250, 50, "blank.png", None);
	myMenu->addButton("buttons\\advance.png", "buttons\\advancehover.png", "buttons\\advancehover.png", CreateFunctionPointer0R(this, &playGame::advance));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(350, backgroundImage->mY+backgroundImage->dY - 60);

	myMenu->addButton("buttons\\exit.png",	 "buttons\\exithover.png", "buttons\\exithover.png", CreateFunctionPointer0R(this, &playGame::exitGame));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(600, backgroundImage->mY+backgroundImage->dY - 60);

	myMenu->addButton("buttons\\replaylevel.png",	 "buttons\\replaylevelhover.png", "buttons\\replaylevelhover.png", CreateFunctionPointer0R(this, &playGame::replayLevel));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(475, backgroundImage->mY+backgroundImage->dY - 60);

	// compass stuff
	compassOffsetX = 763;
	compassOffsetY = 580;
	compass = new MenuSys(compassOffsetX, compassOffsetY, "blank.png", None);

	// rotate map left
	compass->addButton("compass\\rotateleftnormal.png", "compass\\rotatelefthover.png", "compass\\rotatelefthover.png", CreateFunctionPointer0R(this, &playGame::rotatemapleft));
	compass->setLastButtonDimensions(37, 25);
	compass->setLastButtonPosition(compassOffsetX+6, compassOffsetY+5);

	// zoom out
	compass->addButton("compass\\zoomoutnormal.png", "compass\\zoomouthover.png", "compass\\zoomouthover.png", CreateFunctionPointer0R(this, &playGame::zoomout));
	compass->setLastButtonDimensions(35, 25);
	compass->setLastButtonPosition(compassOffsetX+6+37, compassOffsetY+5);
	
	// zoom in
	compass->addButton("compass\\zoominnormal.png", "compass\\zoominhover.png", "compass\\zoominhover.png", CreateFunctionPointer0R(this, &playGame::zoomin));
	compass->setLastButtonDimensions(36, 25);
	compass->setLastButtonPosition(compassOffsetX + 6 + 37 + 35, compassOffsetY+5);

	// zoom in
	compass->addButton("compass\\rotaterightnormal.png", "compass\\rotaterighthover.png", "compass\\rotaterighthover.png", CreateFunctionPointer0R(this, &playGame::rotatemapright));
	compass->setLastButtonDimensions(38, 25);
	compass->setLastButtonPosition(compassOffsetX + 6 + 37 + 35 + 36, compassOffsetY+5);

	////////////////////////////////
	// up left
	compass->addButton("compass\\upleftnormal.png", "compass\\uplefthover.png", "compass\\uplefthover.png", CreateFunctionPointer0R(this, &playGame::panupleft));
	compass->setLastButtonDimensions(48, 45);
	compass->setLastButtonPosition(compassOffsetX+3, compassOffsetY+30+3);

	// up
	compass->addButton("compass\\upnormal.png", "compass\\uphover.png", "compass\\uphover.png", CreateFunctionPointer0R(this, &playGame::panup));
	compass->setLastButtonDimensions(51, 48);
	compass->setLastButtonPosition(compassOffsetX+48+3, compassOffsetY+30);

	// up right
	compass->addButton("compass\\uprightnormal.png", "compass\\uprighthover.png", "compass\\uprighthover.png", CreateFunctionPointer0R(this, &playGame::panupright));
	compass->setLastButtonDimensions(49, 45);
	compass->setLastButtonPosition(compassOffsetX+48+51+3, compassOffsetY+30+3);

	///////////////////////////////
	// left
	compass->addButton("compass\\leftnormal.png", "compass\\lefthover.png", "compass\\lefthover.png", CreateFunctionPointer0R(this, &playGame::panleft));
	compass->setLastButtonDimensions(51, 47);
	compass->setLastButtonPosition(compassOffsetX, compassOffsetY+33+48-3);

	// center
	compass->addButton("compass\\center.png", "compass\\centerhover.png", "compass\\centerhover.png", CreateFunctionPointer0R(this, &playGame::center));
	compass->setLastButtonDimensions(51, 47);
	compass->setLastButtonPosition(compassOffsetX+51, compassOffsetY+33+48-3);

	// right
	compass->addButton("compass\\rightnormal.png", "compass\\righthover.png", "compass\\righthover.png", CreateFunctionPointer0R(this, &playGame::panright));
	compass->setLastButtonDimensions(52, 47);
	compass->setLastButtonPosition(compassOffsetX+51+51, compassOffsetY+33+48-3);

	//////////////////////////////////
	// down left
	compass->addButton("compass\\downleftnormal.png", "compass\\downlefthover.png", "compass\\downlefthover.png", CreateFunctionPointer0R(this, &playGame::pandownleft));
	compass->setLastButtonDimensions(48, 46);
	compass->setLastButtonPosition(compassOffsetX+3, compassOffsetY+33+48+47-3);

	// down
	compass->addButton("compass\\downnormal.png", "compass\\downhover.png", "compass\\downhover.png", CreateFunctionPointer0R(this, &playGame::pandown));
	compass->setLastButtonDimensions(51, 49);
	compass->setLastButtonPosition(compassOffsetX+48+3, compassOffsetY+33+48+47-3);


	// down right
	compass->addButton("compass\\downrightnormal.png", "compass\\downrighthover.png", "compass\\downrighthover.png", CreateFunctionPointer0R(this, &playGame::pandownright));
	compass->setLastButtonDimensions(49, 46);
	compass->setLastButtonPosition(compassOffsetX+48+51+3, compassOffsetY+33+48+47-3);

	// pregame textinfo
	preGameTextOffsetX = 150;
	preGameTextOffsetY = 350;
	preGameTextSpacing = 45;

	Update();
	return true;
}

bool playGame::panleft()		{	gamePlay->panleft();	return true;}
bool playGame::panright()		{	gamePlay->panright();	return true;}
bool playGame::panup()			{	gamePlay->panup();		return true;}
bool playGame::pandown()		{	gamePlay->pandown();	return true;}
bool playGame::panupleft()		{	gamePlay->panupleft();	return true;}
bool playGame::panupright()		{	gamePlay->panupright();	return true;}
bool playGame::pandownleft()	{	gamePlay->pandownleft();return true;}
bool playGame::pandownright()	{	gamePlay->pandownright();return true;}
bool playGame::zoomout()		{	gamePlay->zoomout();	return true;}
bool playGame::zoomin()			{	gamePlay->zoomin();		return true;}
bool playGame::center()			{	gamePlay->center();		return true;}
bool playGame::rotatemapleft()	{	gamePlay->rotateMapLeft(); return true;}
bool playGame::rotatemapright()	{	gamePlay->rotateMapRight(); return true;}

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
		compass->processMouse(x, y);
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
		compass->processMouseClick(button, state, x, y);
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
		switch(c)
		{
		case 27:
			GSM->addGameState<PauseGameState>();
			this->setStatus(Passive);
			break;
		default:
			break;
		}
		gamePlay->keyboardInput(c, x, y);
		break;
	case GB_PREGAME:
		switch(c)
		{
		case 27:
			gamePlay->setState(GB_LOGICVIEW);
			//doneDead = false;
			break;
		default:
			break;
		}
		break;
	case GB_ROBOTDIED:
		switch(c)
		{
		case 27:
			gamePlay->setState(GB_LOGICVIEW);
			doneDead = true;
			break;
		default:
			break;
		}
		break;
	case GB_YOUWIN:
		switch(c)
		{
		case 27:
			this->setStatus(DeleteMe);
			GSM->addGameState<PauseGameState>();
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
	// sets the game state to finished to allow advancement through mini state manager
	curState = GB_FINISHED;
	gamePlay->setState(curState);

	return true;
}

bool playGame::exitGame()
{
	//delete this state while creating a Main Menu State
	GSM->addGameState<MainMenuState>();
	this->setStatus(DeleteMe);

	return true;
}

bool playGame::replayLevel()
{
	// reset the state to pregame of the current level
	curState = GB_PREGAME;
	gamePlay->setState(curState);

	// reset the map for a fresh start for the replay
	gamePlay->resetMap();

	mInterface.ClearExecutionList();
	mInterface.ResetExecutionMode();

	//GameVars->PM->saveProfile();
	GameVars->updatePlayerFile();

	// is there a way to clear the instruction list?
	// find/use same code as when user clicks clear button on interface
	return true;
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
			filename = "ending\\frames\\ending00";
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

	blackImage->mX = 0;
	blackImage->mY = 0;
	blackImage->drawImageFaded(0.75);
	
	glColor3ub(255, 0, 0);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//this wont work if we're coming in out of a level select
	playerCurrentLevel = GameVars->getCurrentLevel();

	tempString = GameVars->getLevelName(playerCurrentLevel);
		
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, tempString);
	offsetAmt++;

	// description
	tempString = GameVars->getDesc(playerCurrentLevel);
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, tempString);
	offsetAmt++;
}
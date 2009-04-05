#include "LevelSelectState.h"

bool LevelSelectState::Update()
{	
	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool LevelSelectState::Draw()
{
	std::stringstream painInTheAss;
	int playerMaxLevel;
	playerMaxLevel = GameVars->getPlayerMaxLevel();
	string tempString;
	int tempInt;

	clearBackground();
	solidWhite->drawImage();
	logoImage->drawImage();

	backgroundImage->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();

	// Have a button to go back or forth a level if applicable until desired level is found 
	// right side increments one, left side decrements one, if you get to the end on either 
	// side, it wraps around to the other side.

	int offsetAmt = 0;
	int textspacing = 30;
	int offsetX = backgroundImage->mX + 50;
	int offsetY = backgroundImage->mY + 50;

	glColor3ub(0, 0, 0);

	// profile name
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, GameVars->getPlayerName());
	offsetAmt++;

	// level number
	painInTheAss.str("");
	tempString = "Level : ";
	tempInt = playerCurrentLevel;
	painInTheAss << tempInt;
	painInTheAss << " / ";
	painInTheAss << GameVars->getPlayerMaxLevel();
	tempString += painInTheAss.str();
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;

	// level name
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, GameVars->getLevelName(playerCurrentLevel));
	offsetAmt++;

	// level description
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, GameVars->getDesc(playerCurrentLevel));
	offsetAmt++;

	// your best score for level
	painInTheAss.str("");
	tempString = "Your best score on this level : ";
	//tempInt = 0;		// this needs to read in something
	tempInt = GameVars->PM->getPlayerLevelScore(playerCurrentLevel);
	if(tempInt < 0)
	{
		tempInt = 0;
	}
	painInTheAss << tempInt;
	tempString += painInTheAss.str();
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;

	// your best commands for level
	/*tempString = "Your least commands processed on this level: ";
	tempInt = playerCurrentLevel;
	painInTheAss << tempInt;
	tempString += painInTheAss.str();
	GameVars->fontArial32.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;*/

	// picture of level
	GameVars->levelArt[playerCurrentLevel]->mX = 1024/2 - GameVars->levelArt[playerCurrentLevel]->dX/2;
	GameVars->levelArt[playerCurrentLevel]->mY = offsetY + offsetAmt*textspacing;
	GameVars->levelArt[playerCurrentLevel]->drawImage();


	glColor3ub(0, 0, 0);
	GameVars->fontArial24.drawText(offsetX+125,565, "Would you like to load this level?");

	return false;
}

bool LevelSelectState::selectLevel()
{
	// player has pressed the select button, set the level
	// they selected as the current level and load the game
	gameBoard *gamePlay;
	string tempString;

	gamePlay = new gameBoard();
	GameVars->setLevelSpecified(playerCurrentLevel);
	//GameVars->setLevel(playerCurrentLevel);
	
	
	tempString = GameVars->getFilename(playerCurrentLevel);
	gamePlay->LoadGameMapFromFile(tempString);

	GameVars->setLevel(playerCurrentLevel);
	GSM->launchNewGame();
	this->setStatus(DeleteMe);

	return true;
}


bool LevelSelectState::decrement()
{
	// decrement the level by one
	playerCurrentLevel -= 1;
	
	// if decrement past the first tutorial level, 
	// wrap it around back to the player's max level
	if(playerCurrentLevel < 1)
		playerCurrentLevel = GameVars->getPlayerMaxLevel();
	
	return true;
}

bool LevelSelectState::increment()
{
	// increment the level by one
	playerCurrentLevel += 1;

	// if incremented past the player's max level, 
	// reset it back to tutorial level 1
	if(playerCurrentLevel > GameVars->getPlayerMaxLevel())
		playerCurrentLevel = 1;

	return true;
}

void LevelSelectState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void LevelSelectState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void LevelSelectState::keyboardInput(unsigned char c, int x, int y)
{
	switch(c)
	{
	case 27: // escape key
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
		break;
	default:
		break;
	}

}
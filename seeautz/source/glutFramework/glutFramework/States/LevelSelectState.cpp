#include "LevelSelectState.h"
#include "LogicViewState.h"

bool LevelSelectState::Update()
{	
	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool LevelSelectState::selectLevel()
{
	// player has pressed the select button, set the level
	// they selected as the current level and load the game
	gameBoard *gamePlay;
	string tempString;

	gamePlay = new gameBoard();
	GameVars->setLevel(playerCurrentLevel);
	
	tempString = GameVars->getFilename(playerCurrentLevel);
	gamePlay->LoadGameMapFromFile(tempString);

	gamePlay->setState(GB_PREGAME);
	return true;
}


int LevelSelectState::getPlayerCurrentLevel()
{
	return playerCurrentLevel;
}

bool LevelSelectState::Draw()
{
	std::stringstream painInTheAss;
	int playerMaxLevel;
	playerMaxLevel = GameVars->getPlayerMaxLevel();
	string tempString;
	int tempInt;

	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();

	// Have a button to go back or forth a level if applicable until desired level is found 
	// right side increments one, left side decrements one, if you get to the end on either 
	// side, it wraps around to the other side.
	tempString = "Would you like to load this level?";
	painInTheAss.clear();
	tempInt = playerCurrentLevel;
	painInTheAss << tempInt;
	tempString += painInTheAss.str();
	GameVars->fontArial32.drawText(225, 300, tempString);

	return false;
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
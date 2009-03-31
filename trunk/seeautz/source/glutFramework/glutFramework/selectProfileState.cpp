#include "selectProfileState.h"

bool selectProfileState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	if(done == 1)
	{
		GameVars->setPMStatus(0);
		GSM->addGameState<clickOKState>();
		this->setStatus(DeleteMe);
	}

	return true;
}

bool selectProfileState::Draw()
{
	int tempInt;
	std::string tempString;
	std::stringstream displayString;

	playerName = GameVars->PM->getPlayerName();
	totScore = GameVars->PM->getPlayerTotalScore();
	highestLevel = GameVars->PM->getPlayerHighestLevel();

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


	// display which profile are you looking at
	displayString.str("");
	tempString = "Profile # ";
	tempInt = profileViewing + 1;
	displayString << tempInt;
	tempString += displayString.str();
	tempString += " of ";
	tempInt = maxNumProfiles + 1;
	displayString.str("");
	displayString << tempInt;
	tempString += displayString.str();
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;

	// profile name
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, playerName);
	offsetAmt++;

	// total score
	displayString.str("");
	tempString = "Total Overall Score : ";
	if(totScore < 0)
		totScore = 0;
	displayString << totScore;
	tempString += displayString.str();
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;

	// max level 
	displayString.str("");
	tempString = "Highest Level Reached: ";
	tempInt = highestLevel;
	displayString << tempInt;
	tempString += displayString.str();
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;

	// level description
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, GameVars->getDesc(highestLevel));
	offsetAmt++;

	// your best score for level
	displayString.str("");
	tempString = "Your best score on this level : ";
	tempInt = GameVars->PM->getPlayerLevelScore(highestLevel);
	if(tempInt < 0)
		tempInt = 0;
	displayString << tempInt;
	tempString += displayString.str();
	GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, tempString);
	offsetAmt++;


	// picture of level
	GameVars->levelArt[highestLevel]->mX = 1024/2 - GameVars->levelArt[highestLevel]->dX/2;
	GameVars->levelArt[highestLevel]->mY = offsetY + offsetAmt*textspacing;
	int tempheight = GameVars->levelArt[highestLevel]->dY;
	GameVars->levelArt[highestLevel]->dY *= 0.75;
	GameVars->levelArt[highestLevel]->drawImage();
	GameVars->levelArt[highestLevel]->dY = tempheight;


	glColor3ub(0, 0, 0);
	GameVars->fontArial24.drawText(offsetX+125,565, "Would you like to load this profile?");


	return false;
}

void selectProfileState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void selectProfileState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void selectProfileState::keyboardInput(unsigned char c, int x, int y)
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
void selectProfileState::setPlayerInfo(std::string name, int score, int curLevel, int maxLevel)
{
	GameVars->setPlayerName(name);
	GameVars->setTotalScore(score);	
	GameVars->setCurrentLevel(curLevel);
	GameVars->setPlayerMaxLevel(maxLevel);
}

bool selectProfileState::increment()
{
	if(profileViewing != maxNumProfiles)
	{
		profileViewing++;
		GameVars->PM->setCurrentRecord(profileViewing);
		done = 0;
	}

	return true;
}

bool selectProfileState::decrement()
{
	if(profileViewing != 0)
	{
		profileViewing--;
		GameVars->PM->setCurrentRecord(profileViewing);
		done = 0;
	}
		
	return true;
}

bool selectProfileState::selectProfile()
{
	setPlayerInfo(playerName, totScore, highestLevel, highestLevel);
	done = 1;

	return true;
}
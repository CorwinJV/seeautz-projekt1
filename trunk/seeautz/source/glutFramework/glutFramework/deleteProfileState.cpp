#include "deleteProfileState.h"

bool deleteProfileState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();

	// make sure we're staying in range of the vector
	if(profileViewing > GameVars->PM->getMaxRecords())
		profileViewing = GameVars->PM->getMaxRecords();
	else if(profileViewing < 0)
		profileViewing = 0;

	if((GameVars->PM->getMaxRecords() - 1) < 0)
	{
		GameVars->setPMStatus(3);
		this->setStatus(DeleteMe);
		GSM->addGameState<MainMenuState>();
		GSM->addGameState<clickOKState>();
	}

	return true;
}

bool deleteProfileState::Draw()
{
	int tempInt;
	std::string tempString;
	std::stringstream displayString;

	if((GameVars->PM->getMaxRecords() - 1) >= 0)
	{
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
		int offsetX = backgroundImage->mX + 25;
		int offsetY = backgroundImage->mY + 25;

		glColor3ub(0, 0, 0);


		// display which profile are you looking at
		displayString.str("");
		tempString = "Profile # ";
		tempInt = profileViewing + 1;
		displayString << tempInt;
		tempString += displayString.str();
		tempString += " of ";
		tempInt = GameVars->PM->getMaxRecords();
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
		offsetAmt += GameVars->fontArial24.drawText(offsetX, offsetY + offsetAmt*textspacing, GameVars->getLevelName(highestLevel), 35);
		
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
		offsetAmt++;

		// picture of level
		GameVars->levelArt[highestLevel]->mX = 1024/2 - GameVars->levelArt[highestLevel]->dX/2;
		GameVars->levelArt[highestLevel]->mY = offsetY + offsetAmt*textspacing;
		int tempheight = GameVars->levelArt[highestLevel]->dY;
		GameVars->levelArt[highestLevel]->dY *= 0.75;
		GameVars->levelArt[highestLevel]->drawImage();
		GameVars->levelArt[highestLevel]->dY = tempheight;


		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(offsetX+50,565, "Would you like to delete this profile?");
	}

	return false;
}

void deleteProfileState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void deleteProfileState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void deleteProfileState::keyboardInput(unsigned char c, int x, int y)
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
bool deleteProfileState::back()
{
	GSM->addGameState<MainMenuState>();
	this->setStatus(DeleteMe);
	return true;
}

bool deleteProfileState::increment()
{
	if(profileViewing != (GameVars->PM->getMaxRecords() - 1))
	{
		profileViewing++;
		GameVars->PM->setCurrentRecord(profileViewing);
	}

	return true;
}

bool deleteProfileState::decrement()
{
	if(profileViewing != 0)
	{
		profileViewing--;
		GameVars->PM->setCurrentRecord(profileViewing);
	}
		
	return true;
}

bool deleteProfileState::deleteProfile()
{
	string profileName;
	profileName = GameVars->PM->getPlayerName();
	GameVars->PM->deleteProfile(profileName);
	GameVars->setPMStatus(1);
	setStatus(Passive);

	if(profileViewing == GameVars->PM->getMaxRecords())
	{
		decrement();
	}

	GSM->addGameState<clickOKState>();
	return true;
}
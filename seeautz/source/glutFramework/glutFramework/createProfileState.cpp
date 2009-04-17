#include "createProfileState.h"
#include "skipTutorialsPopupState.h"

bool createProfileState::Update()
{
	if((!creatingProfile)&&(checked==2))
	{
		//set new player info 
		GameVars->PM->createProfile(tempString);
		GameVars->PM->setPlayerLevelInfo(1, -1, -1, -1);
		GameVars->PM->setPlayerCurrentLevel(1);
		GameVars->PM->setPlayerHighestLevel(1);
		GameVars->PM->setPlayerName(tempString);
		GameVars->setCurrentLevel(1);
		GameVars->setPlayerMaxLevel(1);
		GameVars->setLevel(1);
		GameVars->setPlayerName(tempString);
		GameVars->setTotalScore(0);
		GameVars->setLevelSpecified(-1);
		//GameVars->PM->setCurrentRecord(GameVars->PM->getallPlayerInfo.size();()-1);
		

		//reset values for another record to be entered
		checked = 0;
		creatingProfile = false;
		tempString = "";
		GameVars->setPMStatus(2);
		/*GSM->addGameState<playGame>();
		GSM->addGameState<helpScreenState>();*/
		//GSM->addGameState<playGame>();
		GSM->addGameState<skipTutorialsPopupState>();
		GSM->addGameState<clickOKState>();
		GSM->setAllButTopPassive();
		this->setStatus(DeleteMe);
		
	}

	// if we aren't in the middle of any profile management or checking anything
	// then update the menu
	if((!creatingProfile)&&(checked == 0))
	{
		if(myMenu != NULL)
			myMenu->Update();
	}
	if(profileCheck >= 0)
	{
		if(myMenu != NULL)
			myMenu->Update();
	}
	return true;
}

bool createProfileState::Draw()
{

	solidWhite->drawImage();
	logoImage->drawImage();
	
	int offsetX = 0;
	if((!creatingProfile)&&(checked == 0))
	{
		if(img != NULL)
			img->drawImage();

		if(myMenu != NULL)
			myMenu->Draw();
	}
	if((creatingProfile)&&(checked == 0))
	{
		offsetX = 200;
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(offsetX, 300, "Enter Your Name: ");
		GameVars->fontArial24.drawText(offsetX+300, 300, tempString);
		GameVars->fontArial24.drawText(offsetX, 350, "Press the ENTER key when finished");
		GameVars->fontArial24.drawText(offsetX, 400, "No numbers or special characters");
		GameVars->fontArial24.drawText(offsetX, 450, "Or press the ESCAPE key to return");
		GameVars->fontArial24.drawText(offsetX, 500, "to the main menu");
	}
	if((!creatingProfile)&&(checked == 1)&&(profileCheck >= 0))
	{
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		offsetX = 200;
		GameVars->fontArial24.drawText(offsetX, 300, "That name already exists, click the");
		GameVars->fontArial24.drawText(offsetX, 350, "\"select this profile\" button below");
		GameVars->fontArial24.drawText(offsetX, 400, "below to select the profile with this");
		GameVars->fontArial24.drawText(offsetX, 450, "name, or press the ENTER key to enter");
		GameVars->fontArial24.drawText(offsetX, 500, "a different name.");

		if(!added)
		{
			added = true;
			myMenu->addButton("buttons\\selectprofile.png", "buttons\\selectprofilehover.png", "buttons\\selectprofilehover.png", CreateFunctionPointer0R(this, &createProfileState::SelectProfile));
			myMenu->setLastButtonDimensions(400, 50);
			myMenu->setLastButtonPosition((int)1024/2 - 200, 550);
			myMenu->addButton("buttons\\back.png", "buttons\\backhover.png", "buttons\\backhover.png",CreateFunctionPointer0R(this, &createProfileState::back));
			myMenu->setLastButtonDimensions(100, 50);
			myMenu->setLastButtonPosition((int)1024/2 - 50, 625);
		}
		
		if(myMenu != NULL)
			myMenu->Draw();
	}
	if((!creatingProfile)&&(checked == 1)&&(profileCheck == -2))
	{
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		offsetX = 175;
		GameVars->fontArial24.drawText(offsetX, 300, "Name can't be left blank, press enter"); 
		GameVars->fontArial24.drawText(offsetX, 350, "to try another name, or press the");
		GameVars->fontArial24.drawText(offsetX, 400, "escape key to return to the main menu");
	}
	return false;
}

bool createProfileState::SelectProfile()
{
	// since we already know the name exists, run it through the check function, so it returns
	// the position the name is in, and set the current record to that position
	int recNum = doesNameAlreadyExists(tempString);
	GameVars->PM->setCurrentRecord(recNum);
	
	// retrieve the information from the save file
	int score = GameVars->PM->getPlayerTotalScore();
	int currentLev = GameVars->PM->getPlayerCurrentLevel();
	int maxLev = GameVars->PM->getPlayerHighestLevel();

	// and set it as the active information
	GameVars->setPlayerName(tempString);
	GameVars->setTotalScore(score);	
	GameVars->setCurrentLevel(currentLev);
	GameVars->setPlayerMaxLevel(maxLev);
	GSM->addGameState<LevelSelectState>();

	return true;
}

void createProfileState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void createProfileState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void createProfileState::keyboardInput(unsigned char c, int x, int y)
{

	switch(c)
	{
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		if((creatingProfile)&&(tempString.length() <= 10))
		{
			tempString += c;
			creatingProfile = true;
		}
		break;
	case 13: // enter key
		if((creatingProfile)&&(checked == 0))
		{
			creatingProfile = false;
			//checked = 1;
		}
		else if((!creatingProfile)&&(checked == 1))
		{
			creatingProfile = true;
			checked = 0;
			tempString = "";
			profileCheck = -3;
		}
		else if(tempString == "")
		{
			creatingProfile = true;
			checked = 1;
		}
		break;
	case 8:	 // backspace
		if(tempString.length() > 0)
			tempString.erase(tempString.length() - 1, 1);
		break;
	case 27: // escape key
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
		break;
	default:
		break;
	}

	//once player is finished, check to see if profile under same name already exists
	if((!creatingProfile)&&(checked == 0))
	{
		profileCheck = doesNameAlreadyExists(tempString);
		if(profileCheck == -2)
		{
			tempString = "";	// name can't be left blank, try again
			checked = 1;
		}
		if(profileCheck == -1)
		{
			checked = 2;		// profile doesn't already exist, proceed with new profile using the chosen name
		}
		if(profileCheck >= 0) 
		{
			checked = 1;		// a profile using this name exists, check if they wish to load this profile
		}
	}

}

bool createProfileState::back()
{
	creatingProfile = true;
	checked = 0;
	tempString = "";
	profileCheck = -3;
	return true;
}

int createProfileState::doesNameAlreadyExists(std::string playerGame)
{
	string tempName = playerGame;

	if(playerGame == "")
		return -2;

	for(int i = 0; i < GameVars->PM->getMaxRecords(); i++)
	{
		GameVars->PM->setCurrentRecord(i);
		if(playerGame == GameVars->PM->getPlayerName())
		{
			return i;
		}
	}

	return -1;
}

void createProfileState::setPlayerInfo(std::string name, int score, int curLevel, int maxLevel)
{
	GameVars->setPlayerName(name);
	GameVars->setTotalScore(score);	
	GameVars->setCurrentLevel(curLevel);
	GameVars->setPlayerMaxLevel(maxLevel);

	GameVars->PM->createProfile(name);
}

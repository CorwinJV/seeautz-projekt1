#include "createProfileState.h"

bool createProfileState::Update()
{
	if((!creatingProfile)&&(checked==2))
	{
		//set new player info 
		GameVars->PM->setPlayerLevelInfo(1, -1, -1, -1);
		GameVars->PM->setPlayerCurrentLevel(1);
		GameVars->PM->setPlayerHighestLevel(1);
		GameVars->PM->setPlayerName(tempString);
		
		//reset values for another record to be entered
		checked = 0;
		creatingProfile = false;
		tempString = "";
		GameVars->setPMStatus(2);
		GSM->addGameState<clickOKState>();
		this->setStatus(DeleteMe);
	}

	// if we aren't in the middle of any profile management or checking anything
	// then update the menu
	if((!creatingProfile)&&(checked == 0))
	{
		if(myMenu != NULL)
			myMenu->Update();
	}
	return true;
}

bool createProfileState::Draw()
{

	logoImage->drawImage();
	
	
	if((!creatingProfile)&&(checked == 0))
	{
		if(img != NULL)
			img->drawImage();

		if(myMenu != NULL)
			myMenu->Draw();
	}
	if((creatingProfile)&&(checked == 0))
	{
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(150, 300, "Enter Your Name: ");
		GameVars->fontArial24.drawText(400, 300, tempString);
		GameVars->fontArial24.drawText(150, 350, "Press the ENTER key when finished");
		GameVars->fontArial24.drawText(150, 400, "No numbers or special characters");
		GameVars->fontArial24.drawText(150, 450, "Or press the escape key to return to the main menu");
	}
	if((!creatingProfile)&&(checked == 1))
	{
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(150, 300, "Name already exists, please enter another name: ");
		GameVars->fontArial24.drawText(150, 350, "Or press the escape key to return to the main menu");
	}
	return false;
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
	bool profileCheck;

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
		if(profileCheck)
		{
			checked = 2;		// if profile doesn't already exist, proceed
		}
		else 
		{
			tempString = "";	// otherwise clear the string out and try again
			checked = 1;
		}
	}

}

void createProfileState::setPlayerInfo(std::string name, int score, int curLevel, int maxLevel)
{
	GameVars->setPlayerName(name);
	GameVars->setTotalScore(score);	
	GameVars->setCurrentLevel(curLevel);
	GameVars->setPlayerMaxLevel(maxLevel);
}

bool createProfileState::doesNameAlreadyExists(std::string playerGame)
{
	return GameVars->PM->createProfile(tempString);
}
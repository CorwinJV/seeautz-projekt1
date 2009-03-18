#include "deleteProfileState.h"

bool deleteProfileState::Update()
{
	if((!deletingProfile)&&(checked==2))
	{
		// code for deleting profile
		GameVars->PM->deleteProfile(tempString);

		//reset values for another record to be entered
		checked = 0;
		deletingProfile = false;
		tempString = "";
		GameVars->setPMStatus(2);
		GSM->addGameState<clickOKState>();
	}

	// if we aren't in the middle of any profile management or checking anything
	// then update the menu
	if((!deletingProfile)&&(checked == 0))
	{
		this->setStatus(DeleteMe);
	}
	return true;
}

bool deleteProfileState::Draw()
{

	logoImage->drawImage();
	
	
	if((!deletingProfile)&&(checked == 0))
	{
		if(img != NULL)
			img->drawImage();

		if(myMenu != NULL)
			myMenu->Draw();
	}
	if((deletingProfile)&&(checked == 0))
	{
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(150, 300, "Enter the name of the profile you wish to delete: ");
		GameVars->fontArial24.drawText(400, 350, tempString);
		GameVars->fontArial24.drawText(150, 400, "Press the ENTER key when finished");
		GameVars->fontArial24.drawText(150, 450, "No numbers or special characters");
		GameVars->fontArial24.drawText(150, 500, "Or press the escape key to return to the main menu");
	}
	if((!deletingProfile)&&(checked == 1))
	{
		backgroundImage->drawImage();
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(150, 300, "Name does not exist, please try another name: ");
		GameVars->fontArial24.drawText(150, 350, "Or press the escape key to return to the main menu");
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
		if((deletingProfile)&&(tempString.length() <= 10))
		{
			tempString += c;
			deletingProfile = true;
		}
		break;
	case 13: // enter key
		if((deletingProfile)&&(checked == 0))
		{
			deletingProfile = false;
			//checked = 1;
		}
		else if((!deletingProfile)&&(checked == 1))
		{
			deletingProfile = true;
			checked = 0;
		}
		else if(tempString == "")
		{
			deletingProfile = true;
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
	if((!deletingProfile)&&(checked == 0))
	{
		profileCheck = doesNameAlreadyExists(tempString);
		if(profileCheck)
		{
			checked = 1;		// if profile doesn't exist, try again
			tempString = "";
		}
		else 
		{
			checked = 2;		// Profile exists, proceed to deletion
		}
	}
}

void deleteProfileState::setPlayerInfo(std::string name, int score, int curLevel, int maxLevel)
{
	GameVars->setPlayerName(name);
	GameVars->setTotalScore(score);	
	GameVars->setCurrentLevel(curLevel);
	GameVars->setPlayerMaxLevel(maxLevel);
}

bool deleteProfileState::doesNameAlreadyExists(std::string playerGame)
{
	return GameVars->PM->createProfile(tempString);
}
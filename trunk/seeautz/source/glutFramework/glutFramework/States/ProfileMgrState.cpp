#include "ProfileMgrState.h"

bool ProfileMgrState::Update()
{
	
	if((!creatingProfile)&&(checked == 2))
	{
		if(myMenu != NULL)
			myMenu->Update();
		//GSM->addGameState<ProfileMgrState>();
	}
	return true;
}

bool ProfileMgrState::Draw()
{
	logoImage->drawImage();
	
	if(!creatingProfile)
	{
		if(img != NULL)
			img->drawImage();

		if(myMenu != NULL)
			myMenu->Draw();
	}
	if(creatingProfile)
	{
		GameVars->fontArial24.drawText(150, 300, "Enter Your Name: ");
		GameVars->fontArial24.drawText(400, 300, tempString);
		GameVars->fontArial24.drawText(150, 350, "Press the ENTER key when finished");
		GameVars->fontArial24.drawText(150, 400, "No numbers or special characters");
		GameVars->fontArial24.drawText(150, 450, "Or press the escape key to return to the main menu");
	}
	if((creatingProfile)&&(checked == 1))
	{
		GameVars->fontArial24.drawText(150, 300, "Name already exists, please enter another name: ");
		GameVars->fontArial24.drawText(150, 350, "Or press the escape key to return to the main menu");
	}
	return false;
}

void ProfileMgrState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void ProfileMgrState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool ProfileMgrState::MainMenuStateCallback()
{
	GSM->addGameState<MainMenuState>();
	this->setStatus(DeleteMe);

	return true;
}

bool ProfileMgrState::DeleteProfile()
{
	//code for deleting profile

	return true;
}

bool ProfileMgrState::CreateProfile()
{
	creatingProfile = true;

	//once name has been entered and cleared
	if(checked == 2)
	{
		// set new player info 
		GameVars->PM->setPlayerLevelInfo(1, -1, -1, -1);
		GameVars->PM->setPlayerCurrentLevel(1);
		GameVars->PM->setPlayerHighestLevel(1);
		GameVars->PM->setPlayerName(tempString);
	}
	
	return true;
}

bool ProfileMgrState::SelectProfile()
{
	// code for selecting profile
	GameVars->PM->selectProfile(tempString);
	return true;
}

void ProfileMgrState::keyboardInput(unsigned char c, int x, int y)
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
		if(tempString.length() <= 10)
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
		}
		else if(tempString == "")
		{
			creatingProfile = true;
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
		if(!profileCheck)
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

void ProfileMgrState::setPlayerInfo(std::string name, int score, int curLevel, int maxLevel)
{
	GameVars->setPlayerName(name);
	GameVars->setTotalScore(score);	
	GameVars->setCurrentLevel(curLevel);
	GameVars->setPlayerMaxLevel(maxLevel);
}

bool ProfileMgrState::doesNameAlreadyExists(std::string playerGame)
{
	ifstream PlayerInfo;
	
	std::string playerName = playerGame;
	std::string newTempString = "";

	newTempString = "savedGames\\";
	newTempString += playerName.c_str();
	newTempString += ".txt";
	std::cout << "Checking if " << newTempString << " exists " << endl;

	PlayerInfo.open(newTempString.c_str());

	if(!PlayerInfo)
	{
		std::cout << "file doesn't exist" << endl;
		newTempString = "";
		PlayerInfo.close();
		return false;
	}

	std::cout << "file exists" << endl;
	return true;
}
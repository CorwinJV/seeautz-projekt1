#include "LoadGameState.h" 
#include "..\GameStateManager.h"

bool LoadGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool LoadGameState::Draw()
{
	if(finished == 0)
	{
		GameVars->fontArial32.drawText(125, 200, "Enter the name of the profile you wish to load: ");
		GameVars->fontArial32.drawText(535, 250, tempString);
		GameVars->fontArial32.drawText(125, 300, "Press the ENTER key when finished");
		GameVars->fontArial32.drawText(125, 350, "No numbers or special characters");
		GameVars->fontArial32.drawText(125, 450, "Or press Escape to return to the main menu ");
	}
	if(finished == 1)
	{
		if(img != NULL)
			img->drawImage();

		if(myMenu != NULL)
			myMenu->Draw();
	}
	if(finished == 2)
	{
		GameVars->fontArial32.drawText(105, 200, "No profile found, press Enter to retry: ");
		GameVars->fontArial32.drawText(105, 250, "Or press Escape to return to the main menu ");
	}

	return false;
}

bool LoadGameState::loadGame(string playerGame)
{
	cout << "Loading Game...: " << playerGame <<std::endl;
	ifstream PlayerInfo;
	int score;
	int level;
	string playerName = playerGame;

	//implement later
	int xPos;
	int yPos;
	int switchesFlipped;
	int bytesRemaining;

	tempString = "savedGames\\";
	tempString += playerGame.c_str();
	tempString += ".txt";
	
	PlayerInfo.open(tempString.c_str());

	if(!PlayerInfo)
	{
		finished = 2;
	}

	// code for loading player stats here
	PlayerInfo >> level;
	GameVars->setPlayerMaxLevel(level);

	PlayerInfo >> score;
	GameVars->setTotalScore(score);

	PlayerInfo >> playerName;
	GameVars->setPlayerName(playerName);

	PlayerInfo.close();

	return true;
}

bool LoadGameState::MainMenuCallback()
{
	GSM->addGameState<MainMenuState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 255, 0);

	return true;
} 

bool LoadGameState::playGameCallback()
{
	GSM->addGameState<playGame>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
} 

bool LoadGameState::levelSelectCallback()
{
	GSM->addGameState<LevelSelectState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void LoadGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void LoadGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void LoadGameState::keyboardInput(unsigned char c, int x, int y)
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
		if(tempString.length() <= 10)
		{
			tempString += c;
			finished = 0;
		}
		break;
	case 13: // enter key
		if(finished == 2)
		{
			tempString = "";
			finished = 0;
		}
		else
			finished = 1;
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

	if(finished)
	{
		loadGame(tempString);
	}

}
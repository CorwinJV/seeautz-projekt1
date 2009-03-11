#include "StartNewGameState.h"
#include "..\GameStateManager.h"

bool StartNewGameState::Update()
{

	// Once ENTER key is pressed, and name has been checked move into game
	if((finished)&&(checked))
	{
		GSM->addGameState<playGame>();
		this->setStatus(DeleteMe);
		glClearColor(255, 0, 255, 0);
	}

	return true;
}

bool StartNewGameState::Draw()
{
	// Display onto the screen until user advances with ENTER key
	if(!finished)
	{
		GameVars->fontArial32.drawText(125, 200, "Enter Your Name: ");
		GameVars->fontArial32.drawText(535, 200, tempString);
		GameVars->fontArial32.drawText(125, 250, "Press the ENTER key when finished");
		GameVars->fontArial32.drawText(125, 300, "No numbers or special characters");
		GameVars->fontArial32.drawText(125, 350, "Or press the escape key to return to the main menu");
	}
	if((finished)&&(!checked))
	{
		GameVars->fontArial32.drawText(125, 150, "Name already exists, please enter another name: ");
		GameVars->fontArial32.drawText(125, 200, "Or press the escape key to return to the main menu");
	}
	return false;
}

void StartNewGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void StartNewGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void StartNewGameState::keyboardInput(unsigned char c, int x, int y)
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
			finished = false;
		}
		break;
	case 13: // enter key
		if((!finished)&&(checked))
		{
			finished = true;
			checked = false;
		}
		else if((!finished)&&(!checked))
		{
			finished = true;
		}
		else if(tempString == "")
		{
			finished = false;
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
	if(finished)
	{
		profileCheck = doesNameAlreadyExists(tempString);
		if(!profileCheck)
		{
			checked = true;		// if profile doesn't already exist, proceed
		}
		else 
		{
			tempString = "";	// otherwise clear the string out and try again
			//finished = false;
		}
	}

	if(checked)
	{
		setPlayerName(tempString);
		GameVars->setTotalScore(0);		
	}

}

void StartNewGameState::setPlayerName(string name)
{
	GameVars->setPlayerName(name);
}

bool StartNewGameState::doesNameAlreadyExists(string playerGame)
{
	ifstream PlayerInfo;
	
	string playerName = playerGame;
	string newTempString = "";

	newTempString = "savedGames\\";
	newTempString += playerGame.c_str();
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
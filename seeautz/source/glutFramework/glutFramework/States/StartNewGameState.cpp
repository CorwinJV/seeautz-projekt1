#include "StartNewGameState.h"
#include "..\GameStateManager.h"
#include "PreGameState.h"

bool StartNewGameState::Update()
{
	/*if(myMenu != NULL)
		myMenu->Update();*/

	// Once ENTER key is pressed, move into game
	if(finished)
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
		GameVars->fontArial32.drawText(225, 200, "Enter Your Name: ");
		GameVars->fontArial32.drawText(535, 200, tempString);
		GameVars->fontArial32.drawText(225, 250, "Press the ENTER key when finished");
		GameVars->fontArial32.drawText(225, 300, "No numbers or special characters");
	}
	//else
	//{
	//	if(img != NULL)
	//		//img->drawPixMap();
	//		img->drawImage();

	//	if(myMenu != NULL)
	//		myMenu->Draw();
	//}

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

//bool StartNewGameState::PreGameCallback()
//{
//	GSM->addGameState<PreGameState>();
//	this->setStatus(DeleteMe);
//	glClearColor(255, 255, 255, 0);
//
//	return true;
//} 
//
//bool StartNewGameState::tutorialCallback()
//{
//	GSM->addGameState<playGame>();
//	this->setStatus(DeleteMe);
//	glClearColor(255, 0, 255, 0);
//
//	return true;
//} 

void StartNewGameState::keyboardInput(unsigned char c, int x, int y)
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
			finished = false;
		}
		break;
	case 13: // enter key
		finished = true;
		break;
	case 8:	 // backspace
		if(tempString.length() > 0)
			tempString.erase(tempString.length() - 1, 1);
		break;
	default:
		break;
	}

	if(finished)
	{
		setPlayerName(tempString);
	}

}

void StartNewGameState::setPlayerName(string name)
{
	GameVars->setPlayerName(name);
}
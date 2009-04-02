#include "SaveGameState.h" 
#include "PauseGameState.h"
#include<fstream>
#include<iostream>
#include <string>

using namespace std;

bool SaveGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool SaveGameState::Draw()
{
	/*if(img != NULL)
		img->drawImage();*/

	if(saved)
	{
		if(myMenu != NULL)
			myMenu->Draw();
		GameVars->fontArial32.drawText(225, 200, "Your game has been saved, click return to");
		GameVars->fontArial32.drawText(225, 225, "game or press the Enter key to continue...");
	}

	return false;
}

bool SaveGameState::SavePlayerGame() 
{
	

	return true;
}


bool SaveGameState::PauseGameCallback()
{
	GSM->addGameState<PauseGameState>();
	this->setStatus(DeleteMe);
	return true;
}

void SaveGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void SaveGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void SaveGameState::keyboardInput(unsigned char c, int x, int y)
{
	switch(c)
	{
	case 13: // enter key
		saved = true;
		break;
	case 27: // escape key
		break;
	default:
		break;
	}
}
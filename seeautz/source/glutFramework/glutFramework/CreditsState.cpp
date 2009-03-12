#include "CreditsState.h"
#include <fstream>

bool CreditsState::Update()
{

	return true;
}

bool CreditsState::Draw()
{

	return false;
}

void CreditsState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void CreditsState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void CreditsState::keyboardInput(unsigned char c, int x, int y)
{
	switch(c)
	{
	case 27:
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
		break;
	default:
		break;
	}
}
void CreditsState::init()
{
	ifstream creditsfile;
	creditsfile.open("credits.txt");

	string *tempStringP;
	string tempString;

	numlines = 0;
	offsetY = 768;

	while(!creditsfile.eof())
	{
		tempStringP = new string;
		getline (creditsfile, tempString);
		*tempStringP = tempString;
		creditsList.push_back(tempStringP);
		numlines++;
	}
}
#include "CreditsState.h"
#include <fstream>

bool CreditsState::Update()
{
	timer = clock();
	return true;
}

bool CreditsState::Draw()
{
	solidWhite->dX = 1024;
	solidWhite->dY = 768;
	solidWhite->drawImage();
	if(timer > startTime + scrollSpeed)
	{
		startTime = clock();
		offsetY-= scrollAmount;
	}
	drawCredits();

	if(offsetY < offsetYLimit)
	{
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
	}
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
		scrollSpeed = 1;
		scrollAmount = 8;
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
	lineSpacing = 28;
	offsetYLimit = 0 - numlines*lineSpacing - 50;
	startTime = clock() + 500;
	timer = clock();
	scrollSpeed = 50;
	scrollAmount = 1;
}
void CreditsState::drawCredits()
{
	vector<string*>::iterator sitr = creditsList.begin();
	int drawOffsetY = 0;
	
	glColor3ub(0, 0, 0);

	for(;sitr < creditsList.end(); sitr++)
	{
		int length = (*sitr)->length();
		GameVars->fontArial24.drawText(200, offsetY + drawOffsetY, (*sitr)->c_str());
		drawOffsetY += lineSpacing;
	}

}
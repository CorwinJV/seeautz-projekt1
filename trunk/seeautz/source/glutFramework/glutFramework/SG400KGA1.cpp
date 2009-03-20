#include "SG400KGA1.h"

bool SG400KGA1::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool SG400KGA1::Draw()
{
	// interface
	glColor3ub(255, 0, 0);
	GameVars->fontArial18.drawText(25, 700, "Enter Command:");

	glColor3ub(0, 255, 0);
	GameVars->fontArial18.drawText(220, 700, tempString);

	// history
	glColor3ub(255, 255, 255);
	GameVars->fontArial18.drawText(25, 10, "Command History");
	int offsetAmt = 0;
	int textOffset = 19;

	vector<string*>::iterator sitr;
	sitr = commandList.begin();
	
	for(;sitr < commandList.end(); sitr++)
	{
		GameVars->fontArial18.drawText(25, 29 + offsetAmt*textOffset, (*sitr)->c_str());
		offsetAmt++;
	}

	return false;
}

void SG400KGA1::processMouse(int x, int y)
{

}

void SG400KGA1::processMouseClick(int button, int state, int x, int y)
{

}


void SG400KGA1::keyboardInput(unsigned char c, int x, int y)
{
	switch(c)
	{
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
		tempString = "";
		/*GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);*/
		break;
	default:
		if(tempString.length() <= 60)
		{
			tempString += c;
			finished = 0;
		}
		break;
	}

	if(finished)
	{
		tString = new string;
		*tString = tempString;
		commandList.push_back(tString);
		interpret(tempString);
		tempString = "";
	}

}

void SG400KGA1::interpret(string iString)
{
	if(iString == "quit")
	{
		exit(0);
	}

}
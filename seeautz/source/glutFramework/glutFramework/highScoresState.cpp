#include "GameStateManager.h" 
#include "highScoresState.h"
#include <fstream>
#include <iostream>

bool highScoresState::Update()
{
	
	GSM->setAllButTopPassive();

	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool highScoresState::Draw()
{
	clearBackground();
	logoImage->drawImage();


	if(myMenu != NULL)
		myMenu->Draw();

	glColor3ub(0, 0, 0);

	int offX = 245;
	int offY = 200;

	int offInc = 30;
	int offAmt = 0;

	//offAmt++;
	offAmt = GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "There are tutorial levels available to introduce you to many of this game's concepts.", 30);
	offAmt = GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Do you wish to play the tutorial levels?", 30);
	
	return true;
}


void highScoresState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void highScoresState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool highScoresState::nextCallback()
{
	GSM->addGameState<playGame>();
	this->setStatus(DeleteMe);
	return true;
}

bool highScoresState::previousCallback()
{
	GameVars->setCurrentLevel(GameVars->numTutorialLevels + 1);
	GameVars->setPlayerMaxLevel(GameVars->numTutorialLevels +1);
	GSM->addGameState<playGame>();
	this->setStatus(DeleteMe);
	return true;
}

bool highScoresState::exitCallback()
{
	GSM->addGameState<playGame>();
	this->setStatus(DeleteMe);
	return true;
}

void buildHighScoresList()
{
	// first check the file

	// next check profiles

}
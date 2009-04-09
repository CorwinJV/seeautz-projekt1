#include "MainMenuState.h"
#include "StartNewGameState.h"
#include "ProfileMgrState.h"
#include "LoadGameState.h"
#include "OptionsState.h"
#include "..\GameStateManager.h"
#include "LevelSelectState.h"
#include "..\CreditsState.h"

#include "..\playGame.h"

#include "..\oglSpriteFont.h"

bool MainMenuState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool MainMenuState::Draw()
{
	clearBackground();
	logoImage->drawImage();
	//backgroundImage->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();

	// draw the current version number in the top right corner
	glColor3ub(0, 0, 0);
	GameVars->fontArial12.drawText(770, 735, "Stupid Robot v1.00");
	return false;
}

void MainMenuState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void MainMenuState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool MainMenuState::StartNewGameCallback()
{
	//GSM->addGameState<StartNewGameState>();
	GSM->addGameState<createProfileState>();
	this->setStatus(DeleteMe);
	return true;
} 

bool MainMenuState::ProfileManagerCallback()
{
	GSM->addGameState<ProfileMgrState>();
	this->setStatus(DeleteMe);
	Update();

	return true;
} 

bool MainMenuState::LoadGameCallback()
{
	//GSM->addGameState<LoadGameState>();
	GSM->addGameState<selectProfileState>();
	this->setStatus(DeleteMe);
	Update();

	return true;
} 

bool MainMenuState::Quit()
{
	exit(0);

	return true;
} 

bool MainMenuState::Credits()
{
	// credit vector to display here
	GSM->addGameState<CreditsState>();
	this->setStatus(DeleteMe);
	Update();
	return true;
}

bool MainMenuState::HelpCallback()
{
	// credit vector to display here
	GSM->addGameState<helpScreenState>();
	Update();
	return true;
}
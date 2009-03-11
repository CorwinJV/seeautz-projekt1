#include "MainMenuState.h"
#include "StartNewGameState.h"
#include "ProfileMgrState.h"
#include "LoadGameState.h"
#include "OptionsState.h"
#include "..\GameStateManager.h"
#include "LevelSelectState.h"

#include "..\playGame.h"

bool MainMenuState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool MainMenuState::Draw()
{
	if(myMenu != NULL)
		myMenu->Draw();

	if(img != NULL)
		img->drawImage();

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
	GSM->addGameState<StartNewGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 0, 0);

	return true;
} 

bool MainMenuState::ProfileManagerCallback()
{
	GSM->addGameState<ProfileMgrState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 0, 0);
	Update();

	return true;
} 

bool MainMenuState::LoadGameCallback()
{
	GSM->addGameState<LoadGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 255, 0);
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

	return true;
}
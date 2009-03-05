#include "ProfileMgrState.h"

bool ProfileMgrState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool ProfileMgrState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

void ProfileMgrState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void ProfileMgrState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool ProfileMgrState::MainMenuStateCallback()
{
	GSM->addGameState<MainMenuState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}

bool ProfileMgrState::LoadGameStateCallback()
{
	GSM->addGameState<LoadGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}

bool ProfileMgrState::StartNewGameStateCallback()
{
	GSM->addGameState<StartNewGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}

bool ProfileMgrState::SaveGameStateCallback()
{
	GSM->addGameState<playGame>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}
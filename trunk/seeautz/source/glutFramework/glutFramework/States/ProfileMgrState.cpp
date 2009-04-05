#include "ProfileMgrState.h"

bool ProfileMgrState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool ProfileMgrState::Draw()
{
	logoImage->drawImage();
	
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

	return true;
}

bool ProfileMgrState::DeleteProfile()
{
	if(GameVars->PM->getMaxRecords() > 0)
	{
		GSM->addGameState<deleteProfileState>();
		this->setStatus(DeleteMe);
	}
	return true;
}

bool ProfileMgrState::CreateProfile()
{
	GSM->addGameState<createProfileState>();
	this->setStatus(DeleteMe);
	return true;
}

bool ProfileMgrState::SelectProfile()
{
	if(GameVars->PM->getMaxRecords() > 0)
	{
		GSM->addGameState<selectProfileState>();
		this->setStatus(DeleteMe);
	}
	return true;
}

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

	return true;
}

bool ProfileMgrState::DeleteProfile()
{
	GSM->addGameState<deleteProfileState>();
	this->setStatus(Passive);
	return true;
}

bool ProfileMgrState::CreateProfile()
{
	GSM->addGameState<createProfileState>();
	this->setStatus(Passive);
	return true;
}

bool ProfileMgrState::SelectProfile()
{
	GSM->addGameState<selectProfileState>();
	this->setStatus(Passive);
	return true;
}

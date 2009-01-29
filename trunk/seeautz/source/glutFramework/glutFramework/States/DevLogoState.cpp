#include "DevLogoState.h"
#include ".\..\GameStateManager.h"

#include "MainMenuState.h"


bool DevLogoState::Update()
{
	timer++;
	if(timer > 200000)
	{
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
	}
	return true;
}

bool DevLogoState::Draw()
{
	logo->drawImage();

	return false;
}
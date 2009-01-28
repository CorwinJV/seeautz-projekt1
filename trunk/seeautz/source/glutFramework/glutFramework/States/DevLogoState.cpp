#include "DevLogoState.h"
#include ".\..\GameStateManager.h"

#include "MainMenuState.h"


bool DevLogoState::Update()
{
	timer++;
	if(timer > 200)
	{
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
	}
	return true;
}

bool DevLogoState::Draw()
{
	logo->drawPixMap();

	return false;
}

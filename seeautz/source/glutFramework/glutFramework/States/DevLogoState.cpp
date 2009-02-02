#include "DevLogoState.h"
#include ".\..\GameStateManager.h"

#include "MainMenuState.h"
#include "..\tempstate.h"



bool DevLogoState::Update()
{
	timer++;
	if(timer > 2)
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

DevLogoState::~DevLogoState()
{
	delete logo;
}

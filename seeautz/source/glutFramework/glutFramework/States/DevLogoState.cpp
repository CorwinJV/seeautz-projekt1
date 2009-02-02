#include "DevLogoState.h"
#include ".\..\GameStateManager.h"

#include "MainMenuState.h"
#include "..\tempstate.h"
#include "..\oglGameVars.h"



bool DevLogoState::Update()
{
	timer++;
	if(timer > 20)
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

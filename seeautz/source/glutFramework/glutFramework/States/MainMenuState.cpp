#include "MainMenuState.h"

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
	return false;
}
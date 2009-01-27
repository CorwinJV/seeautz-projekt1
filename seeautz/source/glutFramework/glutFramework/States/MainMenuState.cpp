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